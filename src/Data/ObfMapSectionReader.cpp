#include "ObfMapSectionReader.h"
#include "ObfMapSectionReader_P.h"

#include "ObfReader.h"

OsmAnd::ObfMapSectionReader::ObfMapSectionReader()
{
}

OsmAnd::ObfMapSectionReader::~ObfMapSectionReader()
{
}

void OsmAnd::ObfMapSectionReader::loadMapObjects(
    const std::shared_ptr<ObfReader>& reader, const std::shared_ptr<const ObfMapSectionInfo>& section,
    ZoomLevel zoom, const AreaI* bbox31 /*= nullptr*/,
    QList< std::shared_ptr<const OsmAnd::Model::MapObject> >* resultOut /*= nullptr*/, MapFoundationType* foundationOut /*= nullptr*/,
    std::function<bool (const std::shared_ptr<const ObfMapSectionInfo>& section, const uint64_t)> filterById /*= nullptr*/,
    std::function<bool(const std::shared_ptr<const OsmAnd::Model::MapObject>&)> visitor /*= nullptr*/, const IQueryController* const controller /*= nullptr*/,
    ObfMapSectionReader_Metrics::Metric_loadMapObjects* const metrics /*= nullptr*/)
{
    ObfMapSectionReader_P::loadMapObjects(reader->_d, section, zoom, bbox31, resultOut, foundationOut, filterById, visitor, controller, metrics);
}
