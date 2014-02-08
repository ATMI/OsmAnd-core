/**
* @file
*
* @section LICENSE
*
* OsmAnd - Android navigation software based on OSM maps.
* Copyright (C) 2010-2014  OsmAnd Authors listed in AUTHORS file
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

#ifndef _OSMAND_CORE_OBFS_COLLECTION_H_
#define _OSMAND_CORE_OBFS_COLLECTION_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>
#include <QList>
#include <QDir>
#include <QFileInfo>
#include <QString>

#include <OsmAndCore.h>

namespace OsmAnd {

    class ObfDataInterface;
    class ObfsCollection_P;
    class OSMAND_CORE_API ObfsCollection
    {
        Q_DISABLE_COPY(ObfsCollection);
    private:
    protected:
        const std::unique_ptr<ObfsCollection_P> _d;
    public:
        ObfsCollection();
        virtual ~ObfsCollection();

        void watchDirectory(const QDir& dir, bool recursive = true);
        void watchDirectory(const QString& dirPath, bool recursive = true);
        void registerExplicitFile(const QFileInfo& fileInfo);
        void registerExplicitFile(const QString& filePath);

        std::shared_ptr<ObfDataInterface> obtainDataInterface() const;
    };

} // namespace OsmAnd

#endif // _OSMAND_CORE_OBFS_COLLECTION_H_