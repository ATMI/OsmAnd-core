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

#ifndef _OSMAND_CORE_ROUTE_SEGMENT_H_
#define _OSMAND_CORE_ROUTE_SEGMENT_H_

#include <limits>
#include <memory>

#include <OsmAndCore/QtExtensions.h>
#include <QList>
#include <QVector>

#include <OsmAndCore.h>
#include <OsmAndCore/Data/Model/Road.h>
#include <OsmAndCore/Routing/TurnInfo.h>

namespace OsmAnd {

    class RoutePlannerAnalyzer;
    class RoutePlanner;

    class OSMAND_CORE_API RouteSegment
    {
    private:
    protected:
        RouteSegment(const std::shared_ptr<const Model::Road>& road, uint32_t startPointIndex, uint32_t endPointIndex);

        const std::shared_ptr<const Model::Road> _road;
        uint32_t _startPointIndex;
        uint32_t _endPointIndex;
        QVector< QList< std::shared_ptr<RouteSegment> > > _attachedRoutes;

        float _distance;
        float _speed;
        float _time;
        QString _description;
        // this make not possible to make turns in between segment result for now
        TurnInfo _turnType;

        void dump(const QString& prefix = QString()) const;
    public:
        virtual ~RouteSegment();

        const std::shared_ptr<const Model::Road>& road;
        const uint32_t& startPointIndex;
        const uint32_t& endPointIndex;
        const QVector< QList< std::shared_ptr<RouteSegment> > >& attachedRoutes;

        const QString& description;
        const TurnInfo& turnInfo;

        const float& distance;
        const float& speed;
        const float& time;

        double getBearing(uint32_t pointIndex, bool isIncrement) const;
        double getBearingBegin() const;
        double getBearingEnd() const;

        friend class OsmAnd::RoutePlanner;
        friend class OsmAnd::RoutePlannerAnalyzer;
    };

} // namespace OsmAnd

#endif // _OSMAND_CORE_ROUTE_PLANNER_H_
