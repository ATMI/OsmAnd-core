/**
 * @file
 *
 * @section LICENSE
 *
 * OsmAnd - Android navigation software based on OSM maps.
 * Copyright (C) 2010-2013  OsmAnd Authors listed in AUTHORS file
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _OSMAND_CORE_GPU_API__OPENGL_H_
#define _OSMAND_CORE_GPU_API__OPENGL_H_

#include <OsmAndCore/stdlib_common.h>
#include <array>

#include <OsmAndCore/QtExtensions.h>
#include <QString>

#include <glm/glm.hpp>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OpenGL_Common/GPUAPI_OpenGL_Common.h>

namespace OsmAnd {

    class OSMAND_CORE_API GPUAPI_OpenGL : public GPUAPI_OpenGL_Common
    {
    private:
        void preprocessShader(QString& code);
    protected:
        std::array< GLuint, SamplerTypesCount > _textureSamplers;
    public:
        GPUAPI_OpenGL();
        virtual ~GPUAPI_OpenGL();

        virtual bool initialize();
        virtual bool release();

        virtual GLenum validateResult();

        virtual uint32_t getTileTextureFormat(const std::shared_ptr< const MapTile >& tile);
        virtual void allocateTexture2D(GLenum target, GLsizei levels, GLsizei width, GLsizei height, const std::shared_ptr< const MapTile >& forTile);
        virtual void uploadDataToTexture2D(GLenum target, GLint level,
            GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
            const GLvoid *data, GLsizei dataRowLengthInElements,
            const std::shared_ptr< const MapTile >& fromTile);
        virtual void setMipMapLevelsLimit(GLenum target, const uint32_t mipmapLevelsCount);

        virtual void glGenVertexArrays_wrapper(GLsizei n, GLuint* arrays);
        virtual void glBindVertexArray_wrapper(GLuint array);
        virtual void glDeleteVertexArrays_wrapper(GLsizei n, const GLuint* arrays);

        virtual void preprocessVertexShader(QString& code);
        virtual void preprocessFragmentShader(QString& code);
        virtual void optimizeVertexShader(QString& code);
        virtual void optimizeFragmentShader(QString& code);

        virtual void setSampler(GLenum texture, const SamplerType samplerType);
    };

}

#endif // _OSMAND_CORE_GPU_API__OPENGL_H_
