LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifneq ($(OSMAND_BUILDING_NEON_LIBRARY),true)
    LOCAL_MODULE := OsmAndCore
else
    LOCAL_MODULE := OsmAndCore_neon
    LOCAL_ARM_NEON := true
endif

LOCAL_EXPORT_CFLAGS := \
    -DOSMAND_TARGET_OS_android \
    -DOSMAND_OPENGLES2_RENDERER_SUPPORTED \
    -DOSMAND_CORE_STATIC \
    -DOSMAND_GLM_AVAILABLE \
    -DGLM_SWIZZLE

LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH)/externals/glm/upstream.patched \
    $(LOCAL_PATH)/include

LOCAL_EXPORT_LDLIBS := \
    -lEGL \
    -lGLESv2

ifeq ($(LOCAL_ARM_NEON),true)
    OSMAND_BINARY_SUFFIX := _neon
    OSMAND_QT_PATH_SUFFIX := -neon
else
    OSMAND_BINARY_SUFFIX :=
    OSMAND_QT_PATH_SUFFIX :=
endif

LOCAL_STATIC_LIBRARIES := \
    osmand_protobuf$(OSMAND_BINARY_SUFFIX) \
    osmand_skia$(OSMAND_BINARY_SUFFIX) \
    osmand_gdal$(OSMAND_BINARY_SUFFIX) \
    osmand_glsl-optimizer$(OSMAND_BINARY_SUFFIX) \
    osmand_icu4c$(OSMAND_BINARY_SUFFIX) \
    Qt5Sql$(OSMAND_BINARY_SUFFIX) \
    Qt5Network$(OSMAND_BINARY_SUFFIX) \
    Qt5Core$(OSMAND_BINARY_SUFFIX) \
    boost_system$(OSMAND_BINARY_SUFFIX) \
    boost_atomic$(OSMAND_BINARY_SUFFIX) \
    boost_thread$(OSMAND_BINARY_SUFFIX)

LOCAL_CFLAGS := \
    $(LOCAL_EXPORT_CFLAGS)

LOCAL_C_INCLUDES := \
    $(LOCAL_EXPORT_C_INCLUDES) \
    $(LOCAL_PATH)/include/OsmAndCore \
    $(LOCAL_PATH)/include/OsmAndCore/Data \
    $(LOCAL_PATH)/include/OsmAndCore/Data/Model \
    $(LOCAL_PATH)/include/OsmAndCore/Routing \
    $(LOCAL_PATH)/include/OsmAndCore/Map \
    $(LOCAL_PATH)/src/ \
    $(LOCAL_PATH)/src/Data \
    $(LOCAL_PATH)/src/Data/Model \
    $(LOCAL_PATH)/src/Routing \
    $(LOCAL_PATH)/src/Map \
    $(LOCAL_PATH)/protos

SRC_FILES := \
    $(wildcard $(LOCAL_PATH)/src/*.c*) \
    $(wildcard $(LOCAL_PATH)/src/Data/*.c*) \
    $(wildcard $(LOCAL_PATH)/src/Data/Model/*.c*) \
    $(wildcard $(LOCAL_PATH)/src/Routing/*.c*) \
    $(wildcard $(LOCAL_PATH)/src/Map/*.c*) \
    $(wildcard $(LOCAL_PATH)/src/Map/OpenGL/*.c*) \
    $(wildcard $(LOCAL_PATH)/src/Map/OpenGLES2/*.c*) \
    $(wildcard $(LOCAL_PATH)/protos/*.c*)

HEADER_FILES := \
    $(wildcard $(LOCAL_PATH)/include/*.h) \
    $(wildcard $(LOCAL_PATH)/include/OsmAndCore/*.h) \
    $(wildcard $(LOCAL_PATH)/include/OsmAndCore/Data/*.h) \
    $(wildcard $(LOCAL_PATH)/include/OsmAndCore/Data/Model/*.h) \
    $(wildcard $(LOCAL_PATH)/include/OsmAndCore/Routing/*.h) \
    $(wildcard $(LOCAL_PATH)/include/OsmAndCore/Map/*.h) \
    $(wildcard $(LOCAL_PATH)/src/*.h) \
    $(wildcard $(LOCAL_PATH)/src/Data/*.h) \
    $(wildcard $(LOCAL_PATH)/src/Data/Model/*.h) \
    $(wildcard $(LOCAL_PATH)/src/Routing/*.h) \
    $(wildcard $(LOCAL_PATH)/src/Map/*.h) \
    $(wildcard $(LOCAL_PATH)/src/Map/OpenGL/*.h) \
    $(wildcard $(LOCAL_PATH)/src/Map/OpenGLES2/*.h) \
    $(wildcard $(LOCAL_PATH)/protos/*.h)
mkdirp_ = \
    $(info $(shell ( \
        mkdir -p `dirname $(1)` \
    )))
mkdirp = \
    $(call mkdirp_,$(1))
run_moc = \
    $(call mkdirp,$(1:$(LOCAL_PATH)/%=$(LOCAL_PATH)/moc/%)) \
    $(info $(shell ( \
        $(LOCAL_PATH)/externals/qtbase-android/upstream.patched.$(TARGET_ARCH_ABI)$(OSMAND_QT_PATH_SUFFIX).static/bin/moc \
            -o $(1:$(LOCAL_PATH)/%.h=$(LOCAL_PATH)/moc/%.cpp) \
            $(1) \
        )))
$(info $(shell (rm -rf $(LOCAL_PATH)/moc)))
$(foreach header_file,$(HEADER_FILES),$(call run_moc,$(header_file)))
$(info $(shell (find $(LOCAL_PATH)/moc -type f -size 0 -print0 | xargs -0 rm)))
MOC_FILES := \
    $(shell (find $(LOCAL_PATH)/moc -type f))

$(info $(shell $(LOCAL_PATH)/embed-resources.sh))
GEN_FILES := \
    $(shell (find $(LOCAL_PATH)/gen -type f))

LOCAL_SRC_FILES := \
    $(SRC_FILES:$(LOCAL_PATH)/%=%) \
    $(MOC_FILES:$(LOCAL_PATH)/%=%) \
    $(GEN_FILES:$(LOCAL_PATH)/%=%) \

include $(BUILD_STATIC_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH)/externals)
