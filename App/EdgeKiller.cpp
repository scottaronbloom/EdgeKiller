// The MIT License( MIT )
//
// Copyright( c ) 2022 Scott Aron Bloom
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "EdgeKiller.h"
#include <QUrl>
#include <map>

namespace NEdgeKiller
{
    const QString sEdgeSchema = "microsoft-edge:";
    bool isEdgeURL( const QString & url )
    {
        return url.startsWith( sEdgeSchema, Qt::CaseSensitivity::CaseInsensitive );
    }

    bool isValidURL( const QUrl & url )
    {
        if ( !url.isValid() )
            return false;
        return !url.scheme().isEmpty() && !url.host().isEmpty();
    }

    QUrl fixURL( const QString & inString )
    {
        if ( !isEdgeURL( inString ) )
            return QUrl( inString );

        QString retVal;
        retVal = inString;
        retVal.replace( sEdgeSchema, QString(), Qt::CaseSensitivity::CaseInsensitive );

        auto url = QUrl( retVal, QUrl::StrictMode );
        if ( !isValidURL( url ) && ( retVal.startsWith( "?" ) && retVal.contains( "&url" ) ) )
        {
            url = QUrl( inString );
            std::map< QString, QString > queryMap;
            auto queries = url.query().split( "&" );
            for( auto && ii : queries )
            {
                auto curr = ii.split( "=" );
                if ( curr.length() >= 2 )
                    queryMap[ curr[ 0 ].toLower() ] = curr[ 1 ];
                else if ( curr.length() == 1 )
                    queryMap[ curr[ 0 ].toLower() ] = QString();
            }
            auto pos = queryMap.find( "url" );
            if ( pos != queryMap.end() )
                url = QUrl( (*pos).second );
        }
        if ( !isValidURL( url ) )
            url = QUrl( "http://" + retVal );

        if ( !isValidURL( url ) )
            return {};
        return url;
    }
}