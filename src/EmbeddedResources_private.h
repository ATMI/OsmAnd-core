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

#ifndef _OSMAND_CORE_EMBEDDED_RESOURCES_PRIVATE_H_
#define _OSMAND_CORE_EMBEDDED_RESOURCES_PRIVATE_H_

namespace OsmAnd {

    struct EmbeddedResource
    {
        QString id;
        size_t size;
        const uint8_t* data;
    };

    extern const EmbeddedResource __bundled_resources[];
    extern const uint32_t __bundled_resources_count;

} // namespace OsmAnd

#endif // _OSMAND_CORE_EMBEDDED_RESOURCES_PRIVATE_H_
