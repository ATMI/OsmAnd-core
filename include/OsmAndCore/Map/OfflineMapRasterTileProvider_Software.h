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
#ifndef __OFFLINE_MAP_RASTER_TILE_PROVIDER_SOFTWARE_H_
#define __OFFLINE_MAP_RASTER_TILE_PROVIDER_SOFTWARE_H_

#include <cstdint>
#include <memory>
#include <functional>
#include <array>

#include <QMutex>
#include <QSet>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OsmAndCore/Map/IMapBitmapTileProvider.h>

namespace OsmAnd {

    class OfflineMapDataProvider;
    class OfflineMapRasterTileProvider_Software_P;
    class OSMAND_CORE_API OfflineMapRasterTileProvider_Software : public IMapBitmapTileProvider
    {
    private:
        const std::unique_ptr<OfflineMapRasterTileProvider_Software_P> _d;
    protected:
    public:
        OfflineMapRasterTileProvider_Software(const std::shared_ptr<OfflineMapDataProvider>& dataProvider, const uint32_t outputTileSize = 256, const float density = 1.0f);
        virtual ~OfflineMapRasterTileProvider_Software();

        const std::shared_ptr<OfflineMapDataProvider> dataProvider;

        virtual float getTileDensity() const;
        virtual uint32_t getTileSize() const;

        virtual bool obtainTile(const TileId tileId, const ZoomLevel zoom, std::shared_ptr<MapTile>& outTile);
    };

}

#endif // __OFFLINE_MAP_RASTER_TILE_PROVIDER_SOFTWARE_H_
