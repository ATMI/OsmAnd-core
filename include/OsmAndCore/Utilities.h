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

#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#include <cstdint>
#include <climits>
#include <memory>
#include <functional>

#include <OsmAndCore/QtExtensions.h>
#include <QtMath>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDir>
#include <QFile>
#include <QVector>
#include <QSet>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>

namespace OsmAnd {

    namespace Utilities
    {
        OSMAND_CORE_API double OSMAND_CORE_CALL toRadians(const double angle);
        OSMAND_CORE_API int32_t OSMAND_CORE_CALL get31TileNumberX(const double longitude);
        OSMAND_CORE_API int32_t OSMAND_CORE_CALL get31TileNumberY(const double latitude);
        OSMAND_CORE_API double OSMAND_CORE_CALL get31LongitudeX(const double x);
        OSMAND_CORE_API double OSMAND_CORE_CALL get31LatitudeY(const double y);
        OSMAND_CORE_API double OSMAND_CORE_CALL getTileNumberX(const float zoom, const double longitude);
        OSMAND_CORE_API double OSMAND_CORE_CALL getTileNumberY(const float zoom, const double latitude);
        OSMAND_CORE_API double OSMAND_CORE_CALL normalizeLatitude(const double latitude);
        OSMAND_CORE_API double OSMAND_CORE_CALL normalizeLongitude(const double longitude);
        OSMAND_CORE_API double OSMAND_CORE_CALL getPowZoom(const float zoom);
        OSMAND_CORE_API double OSMAND_CORE_CALL getLongitudeFromTile(const float zoom, const double x);
        OSMAND_CORE_API double OSMAND_CORE_CALL getLatitudeFromTile(const float zoom, const double y);
        OSMAND_CORE_API bool OSMAND_CORE_CALL extractFirstNumberPosition(const QString& value, int& first, int& last, bool allowSigned, bool allowDot);
        OSMAND_CORE_API double OSMAND_CORE_CALL parseSpeed(const QString& value, const double defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API double OSMAND_CORE_CALL parseLength(const QString& value, const double defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API double OSMAND_CORE_CALL parseWeight(const QString& value, const double defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API int OSMAND_CORE_CALL parseArbitraryInt(const QString& value, const int defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API long OSMAND_CORE_CALL parseArbitraryLong(const QString& value, const long defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API unsigned int OSMAND_CORE_CALL parseArbitraryUInt(const QString& value, const unsigned int defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API unsigned long OSMAND_CORE_CALL parseArbitraryULong(const QString& value, const unsigned long defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API float OSMAND_CORE_CALL parseArbitraryFloat(const QString& value, const float defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API bool OSMAND_CORE_CALL parseArbitraryBool(const QString& value, const bool defValue, bool* wasParsed = nullptr);
        OSMAND_CORE_API double OSMAND_CORE_CALL x31toMeters(const int32_t x31);
        OSMAND_CORE_API double OSMAND_CORE_CALL y31toMeters(const int32_t y31);
        OSMAND_CORE_API double OSMAND_CORE_CALL squareDistance31(const int32_t x31a, const int32_t y31a, const int32_t x31b, const int32_t y31b);
        OSMAND_CORE_API double OSMAND_CORE_CALL distance31(const int32_t x31a, const int32_t y31a, const int32_t x31b, const int32_t y31b);
        OSMAND_CORE_API double OSMAND_CORE_CALL squareDistance31(const PointI& a, const PointI& b);
        OSMAND_CORE_API double OSMAND_CORE_CALL distance31(const PointI& a, const PointI& b);
        OSMAND_CORE_API double OSMAND_CORE_CALL distance(const double xLonA, const double yLatA, const double xLonB, const double yLatB);
        OSMAND_CORE_API double OSMAND_CORE_CALL projection31(const int32_t x31a, const int32_t y31a, const int32_t x31b, const int32_t y31b, const int32_t x31c, const int32_t y31c);
        OSMAND_CORE_API double OSMAND_CORE_CALL normalizedAngleRadians(const double angle);
        OSMAND_CORE_API double OSMAND_CORE_CALL normalizedAngleDegrees(const double angle);
        OSMAND_CORE_API int OSMAND_CORE_CALL javaDoubleCompare(const double l, const double r);
        OSMAND_CORE_API void OSMAND_CORE_CALL findFiles(const QDir& origin, const QStringList& masks, QFileInfoList& files, const bool recursively = true);
        OSMAND_CORE_API double OSMAND_CORE_CALL polygonArea(const QVector<PointI>& points);
        OSMAND_CORE_API bool OSMAND_CORE_CALL rayIntersectX(const PointF& v0, const PointF& v1, const float mY, float& mX);
        OSMAND_CORE_API bool OSMAND_CORE_CALL rayIntersect(const PointF& v0, const PointF& v1, const PointF& v);
        OSMAND_CORE_API bool OSMAND_CORE_CALL rayIntersectX(const PointI& v0, const PointI& v1, const int32_t mY, int32_t& mX);
        OSMAND_CORE_API bool OSMAND_CORE_CALL rayIntersect(const PointI& v0, const PointI& v1, const PointI& v);
        OSMAND_CORE_API double OSMAND_CORE_CALL degreesDiff(const double a1, const double a2);
        OSMAND_CORE_API AreaI OSMAND_CORE_CALL tileBoundingBox31(const TileId tileId, const ZoomLevel zoom);
        OSMAND_CORE_API AreaI OSMAND_CORE_CALL areaRightShift(const AreaI& input, const uint32_t shift);
        OSMAND_CORE_API AreaI OSMAND_CORE_CALL areaLeftShift(const AreaI& input, const uint32_t shift);
        OSMAND_CORE_API uint32_t OSMAND_CORE_CALL getNextPowerOfTwo(const uint32_t value);
        OSMAND_CORE_API double OSMAND_CORE_CALL getMetersPerTileUnit(const float zoom, const double yTile, const double unitsPerTile);
        OSMAND_CORE_API TileId OSMAND_CORE_CALL normalizeTileId(const TileId input, const ZoomLevel zoom);
        OSMAND_CORE_API PointI OSMAND_CORE_CALL normalizeCoordinates(const PointI& input, const ZoomLevel zoom);
        OSMAND_CORE_API PointI OSMAND_CORE_CALL normalizeCoordinates(const PointI64& input, const ZoomLevel zoom);
        OSMAND_CORE_API void OSMAND_CORE_CALL scanlineFillPolygon(const unsigned int verticesCount, const PointF* const vertices, std::function<void (const PointI&)> fillPoint);

        inline int qAbsCeil(qreal v)
        {
            return v > 0 ? qCeil(v) : qFloor(v);
        }
        inline int qAbsFloor(qreal v)
        {
            return v > 0 ? qFloor(v) : qCeil(v);
        }

    } // namespace Utilities

} // namespace OsmAnd

#endif // __UTILITIES_H_
