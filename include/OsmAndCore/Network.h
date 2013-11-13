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

#ifndef __NETWORK_H_
#define __NETWORK_H_

#include <cstdint>
#include <memory>

#include <OsmAndCore/QtExtensions.h>
#include <QUrl>
#include <QNetworkReply>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>

namespace OsmAnd {

    namespace Network {

        struct OSMAND_CORE_API DownloadSettings
        {
            DownloadSettings();
            ~DownloadSettings();

            bool autoFollowRedirects;
            QString userAgent;
        };

        class OSMAND_CORE_API Downloader
        {
        private:
            Downloader();
            ~Downloader();
        protected:
        public:
            static std::shared_ptr<QNetworkReply> download(const QUrl& url, const DownloadSettings& settings = DownloadSettings());
        };
    } // namespace Network

} // namespace OsmAnd

#endif // __NETWORK_H_
