#include "MapStyleEvaluator_P.h"
#include "MapStyleEvaluator.h"

#include "MapStyleValue.h"

OsmAnd::MapStyleEvaluator_P::MapStyleEvaluator_P( MapStyleEvaluator* owner_ )
    : owner(owner_)
    , _builtinValueDefs(MapStyle::getBuiltinValueDefinitions())
{
}

OsmAnd::MapStyleEvaluator_P::~MapStyleEvaluator_P()
{
}
