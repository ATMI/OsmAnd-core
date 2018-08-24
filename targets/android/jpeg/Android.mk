LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

PROJECT_ROOT_RELATIVE := ../../../../platforms/android/OsmAnd
OSMAND_JPEG_ROOT_RELATIVE := ../../../externals/jpeg
OSMAND_JPEG_ROOT := $(LOCAL_PATH)/$(OSMAND_JPEG_ROOT_RELATIVE)
OSMAND_JPEG_RELATIVE := ../../../externals/skia/upstream.patched/third_party/externals/libjpeg-turbo
OSMAND_JPEG := $(LOCAL_PATH)/$(OSMAND_JPEG_RELATIVE)
	
LOCAL_CFLAGS += -DNO_GETENV -fPIC

LOCAL_C_INCLUDES += \
	$(OSMAND_JPEG_ROOT) \
	$(OSMAND_JPEG) \
	$(OSMAND_JPEG)/simd

ifneq ($(filter $(TARGET_ARCH_ABI), armeabi-v7a armeabi-v7a-hard x86),)
LOCAL_ARM_NEON := true
LOCAL_CFLAGS += -D__ARM_HAVE_NEON
endif

LOCAL_ASMFLAGS += -DELF

ifeq ($(TARGET_ARCH_ABI),x86_64)
SIMD_SOURCES := $(OSMAND_JPEG)/simd/x86_64
LOCAL_SRC_FILES += \
	$(SIMD_SOURCES)/jsimd.c \
	$(SIMD_SOURCES)/jfdctflt-sse-64.asm \
	$(SIMD_SOURCES)/jccolor-sse2-64.asm \
	$(SIMD_SOURCES)/jcgray-sse2-64.asm \
	$(SIMD_SOURCES)/jcsample-sse2-64.asm \
	$(SIMD_SOURCES)/jdcolor-sse2-64.asm \
	$(SIMD_SOURCES)/jdmerge-sse2-64.asm \
	$(SIMD_SOURCES)/jdsample-sse2-64.asm \
	$(SIMD_SOURCES)/jfdctfst-sse2-64.asm \
	$(SIMD_SOURCES)/jfdctint-sse2-64.asm \
	$(SIMD_SOURCES)/jidctflt-sse2-64.asm \
	$(SIMD_SOURCES)/jidctfst-sse2-64.asm \
	$(SIMD_SOURCES)/jidctint-sse2-64.asm \
	$(SIMD_SOURCES)/jidctred-sse2-64.asm \
	$(SIMD_SOURCES)/jquantf-sse2-64.asm \
	$(SIMD_SOURCES)/jquanti-sse2-64.asm \

LOCAL_CFLAGS += \
	-DSIZEOF_SIZE_T=8 \

LOCAL_ASMFLAGS += -D__x86_64__

else ifeq ($(TARGET_ARCH_ABI),x86)
SIMD_SOURCES := $(OSMAND_JPEG)/simd/i386
LOCAL_SRC_FILES += \
	$(SIMD_SOURCES)/jsimd.c \
	$(SIMD_SOURCES)/jsimdcpu.asm \
	$(SIMD_SOURCES)/jfdctflt-3dn.asm \
	$(SIMD_SOURCES)/jidctflt-3dn.asm \
	$(SIMD_SOURCES)/jquant-3dn.asm \
	$(SIMD_SOURCES)/jccolor-mmx.asm \
	$(SIMD_SOURCES)/jcgray-mmx.asm \
	$(SIMD_SOURCES)/jcsample-mmx.asm \
	$(SIMD_SOURCES)/jdcolor-mmx.asm \
	$(SIMD_SOURCES)/jdmerge-mmx.asm \
	$(SIMD_SOURCES)/jdsample-mmx.asm \
	$(SIMD_SOURCES)/jfdctfst-mmx.asm \
	$(SIMD_SOURCES)/jfdctint-mmx.asm \
	$(SIMD_SOURCES)/jidctfst-mmx.asm \
	$(SIMD_SOURCES)/jidctint-mmx.asm \
	$(SIMD_SOURCES)/jidctred-mmx.asm \
	$(SIMD_SOURCES)/jquant-mmx.asm \
	$(SIMD_SOURCES)/jfdctflt-sse.asm \
	$(SIMD_SOURCES)/jidctflt-sse.asm \
	$(SIMD_SOURCES)/jquant-sse.asm \
	$(SIMD_SOURCES)/jccolor-sse2.asm \
	$(SIMD_SOURCES)/jcgray-sse2.asm \
	$(SIMD_SOURCES)/jcsample-sse2.asm \
	$(SIMD_SOURCES)/jdcolor-sse2.asm \
	$(SIMD_SOURCES)/jdmerge-sse2.asm \
	$(SIMD_SOURCES)/jdsample-sse2.asm \
	$(SIMD_SOURCES)/jfdctfst-sse2.asm \
	$(SIMD_SOURCES)/jfdctint-sse2.asm \
	$(SIMD_SOURCES)/jidctflt-sse2.asm \
	$(SIMD_SOURCES)/jidctfst-sse2.asm \
	$(SIMD_SOURCES)/jidctint-sse2.asm \
	$(SIMD_SOURCES)/jidctred-sse2.asm \
	$(SIMD_SOURCES)/jquantf-sse2.asm \
	$(SIMD_SOURCES)/jquanti-sse2.asm \

LOCAL_CFLAGS += \
	-DSIZEOF_SIZE_T=4 \

LOCAL_ASMFLAGS += -DPIC

else ifneq ($(filter $(TARGET_ARCH_ABI), armeabi-v7a armeabi-v7a-hard),)
SIMD_SOURCES := $(OSMAND_JPEG)/simd/arm
LOCAL_SRC_FILES += \
	$(SIMD_SOURCES)/jsimd.c \
	$(SIMD_SOURCES)/jsimd_arm_neon.S \

LOCAL_CFLAGS += \
	-DSIZEOF_SIZE_T=4 \

else ifeq ($(TARGET_ARCH_ABI),armeabi)
LOCAL_CFLAGS += \
	-DSIZEOF_SIZE_T=4 \

else ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
SIMD_SOURCES := $(OSMAND_JPEG)/simd/arm64
LOCAL_SRC_FILES += \
	$(SIMD_SOURCES)/jsimd.c \
	$(SIMD_SOURCES)/jsimd_neon.S \

LOCAL_CFLAGS += \
	-DSIZEOF_SIZE_T=8 \

endif

# libjpeg_la_SOURCES from Makefile.am
LOCAL_SRC_FILES += \
	$(SOURCE_PATH)/jcapimin.c \
	$(SOURCE_PATH)/jcapistd.c \
	$(SOURCE_PATH)/jccoefct.c \
	$(SOURCE_PATH)/jccolor.c \
	$(SOURCE_PATH)/jcdctmgr.c \
	$(SOURCE_PATH)/jchuff.c \
	$(SOURCE_PATH)/jcinit.c \
	$(SOURCE_PATH)/jcmainct.c \
	$(SOURCE_PATH)/jcmarker.c \
	$(SOURCE_PATH)/jcmaster.c \
	$(SOURCE_PATH)/jcomapi.c \
	$(SOURCE_PATH)/jcparam.c \
	$(SOURCE_PATH)/jcphuff.c \
	$(SOURCE_PATH)/jcprepct.c \
	$(SOURCE_PATH)/jcsample.c \
	$(SOURCE_PATH)/jctrans.c \
	$(SOURCE_PATH)/jdapimin.c \
	$(SOURCE_PATH)/jdapistd.c \
	$(SOURCE_PATH)/jdatadst.c \
	$(SOURCE_PATH)/jdatasrc.c \
	$(SOURCE_PATH)/jdcoefct.c \
	$(SOURCE_PATH)/jdcolor.c \
	$(SOURCE_PATH)/jddctmgr.c \
	$(SOURCE_PATH)/jdhuff.c \
	$(SOURCE_PATH)/jdinput.c \
	$(SOURCE_PATH)/jdmainct.c \
	$(SOURCE_PATH)/jdmarker.c \
	$(SOURCE_PATH)/jdmaster.c \
	$(SOURCE_PATH)/jdmerge.c \
	$(SOURCE_PATH)/jdphuff.c \
	$(SOURCE_PATH)/jdpostct.c \
	$(SOURCE_PATH)/jdsample.c \
	$(SOURCE_PATH)/jdtrans.c \
	$(SOURCE_PATH)/jerror.c \
	$(SOURCE_PATH)/jfdctflt.c \
	$(SOURCE_PATH)/jfdctfst.c \
	$(SOURCE_PATH)/jfdctint.c \
	$(SOURCE_PATH)/jidctflt.c \
	$(SOURCE_PATH)/jidctfst.c \
	$(SOURCE_PATH)/jidctint.c \
	$(SOURCE_PATH)/jidctred.c \
	$(SOURCE_PATH)/jquant1.c \
	$(SOURCE_PATH)/jquant2.c \
	$(SOURCE_PATH)/jutils.c \
	$(SOURCE_PATH)/jmemmgr.c \
	$(SOURCE_PATH)/jmemnobs.c \

# if WITH_ARITH_ENC from Makefile.am
LOCAL_SRC_FILES += \
	$(SOURCE_PATH)/jaricom.c \
	$(SOURCE_PATH)/jcarith.c \
	$(SOURCE_PATH)/jdarith.c \

# libturbojpeg_la_SOURCES from Makefile.am
LOCAL_SRC_FILES += \
	$(SOURCE_PATH)/turbojpeg.c \
	$(SOURCE_PATH)/transupp.c \
	$(SOURCE_PATH)/jdatadst-tj.c \
	$(SOURCE_PATH)/jdatasrc-tj.c \

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include \

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/$(SOURCE_PATH)/simd \
	$(LOCAL_PATH)/$(SOURCE_PATH) \

LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)/$(SOURCE_PATH) \

LOCAL_CFLAGS += \
	-DBUILD="" \
	-DC_ARITH_CODING_SUPPORTED=1 \
	-DD_ARITH_CODING_SUPPORTED=1 \
	-DBITS_IN_JSAMPLE=8 \
	-DHAVE_DLFCN_H=1 \
	-DHAVE_INTTYPES_H=1 \
	-DHAVE_LOCALE_H=1 \
	-DHAVE_MEMCPY=1 \
	-DHAVE_MEMORY_H=1 \
	-DHAVE_MEMSET=1 \
	-DHAVE_STDDEF_H=1 \
	-DHAVE_STDINT_H=1 \
	-DHAVE_STDLIB_H=1 \
	-DHAVE_STRINGS_H=1 \
	-DHAVE_STRING_H=1 \
	-DHAVE_SYS_STAT_H=1 \
	-DHAVE_SYS_TYPES_H=1 \
	-DHAVE_UNISTD_H=1 \
	-DHAVE_UNSIGNED_CHAR=1 \
	-DHAVE_UNSIGNED_SHORT=1 \
	-DINLINE="inline __attribute__((always_inline))" \
	-DJPEG_LIB_VERSION=62 \
	-DLIBJPEG_TURBO_VERSION="2.0.0" \
	-DMEM_SRCDST_SUPPORTED=1 \
	-DNEED_SYS_TYPES_H=1 \
	-DSTDC_HEADERS=1 \
	-DWITH_SIMD=1 \

LOCAL_MODULE := osmand_jpeg

ifneq ($(OSMAND_USE_PREBUILT),true)
	include $(BUILD_STATIC_LIBRARY)
else
	LOCAL_SRC_FILES := \
		$(PROJECT_ROOT_RELATIVE)/libs/$(TARGET_ARCH_ABI)/lib$(LOCAL_MODULE).a
	include $(PREBUILT_STATIC_LIBRARY)
endif