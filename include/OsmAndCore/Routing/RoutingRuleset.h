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

#ifndef _OSMAND_CORE_ROUTING_RULESET_H_
#define _OSMAND_CORE_ROUTING_RULESET_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>
#include <QString>
#include <QHash>

#include <OsmAndCore.h>
#include <OsmAndCore/Routing/RoutingRuleExpression.h>

namespace OsmAnd {

    class RoutingProfile;

    class OSMAND_CORE_API RoutingRuleset
    {
    public:
        WEAK_ENUM_EX(Type, int)
        {
            Invalid = -1,
            RoadPriorities = 0,
            RoadSpeed,
            Access,
            Obstacles,
            RoutingObstacles,
            OneWay,

            TypesCount
        };
    private:
        QList< std::shared_ptr<RoutingRuleExpression> > _expressions;
    protected:
        void registerSelectExpression(const QString& value, const QString& type);
        RoutingRuleset(RoutingProfile* owner, const Type type);
    public:
        virtual ~RoutingRuleset();

        RoutingProfile* const owner;
        const Type type;
        const QList< std::shared_ptr<RoutingRuleExpression> >& expressions;

        friend class OsmAnd::RoutingProfile;
        friend class OsmAnd::RoutingRulesetContext;
        friend class OsmAnd::RoutingConfiguration;
    };

} // namespace OsmAnd

#endif // _OSMAND_CORE_ROUTING_RULESET_H_
