// The MIT License( MIT )
//
// Copyright( c ) 2020-2021 Scott Aron Bloom
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

#include "../EdgeKiller.h"

#include <QCoreApplication>
#include <string>
#include <memory>
#include <filesystem>
#include "gtest/gtest.h"

////template< typename T1, typename T2 >
//bool operator==( faketype, faketype ) { return true; }
//bool operator==( const std::pair< int64_t, std::list< int64_t > > & lhs, const std::pair< int64_t, std::list< int64_t > >& rhs )
//{
//    return false;
//}

void PrintTo( const QString & str, ::std::ostream * oss )
{
    *oss << qPrintable( str );
}

::std::ostream & operator<<( ::std::ostream & oss, const QString & str )
{
    oss << qPrintable( str );
    return oss;
}

namespace 
{
    TEST( TestEdgeKiller, URLTests )
    {
        EXPECT_EQ( "microso-edge:http://google.com", NEdgeKiller::fixURL( "microso-edge:http://google.com" ).toString() );

        EXPECT_EQ( "http://google.com", NEdgeKiller::fixURL( "microsoft-edge:http://google.com" ).toString() );
        EXPECT_EQ( "https://google.com", NEdgeKiller::fixURL( "MICROSOFT-EDGE:https://google.com" ).toString() );

        EXPECT_EQ( "https://google.com", NEdgeKiller::fixURL( "microsoft-edge:?foo=bar&url=https://google.com&foobar=" ).toString() );

        EXPECT_EQ( "http://google.com", NEdgeKiller::fixURL( "microsoft-edge:google.com" ).toString() );
    }
}


int main( int argc, char **argv ) {
    QCoreApplication appl( argc, argv );
    ::testing::InitGoogleTest( &argc, argv );
    int retVal = RUN_ALL_TESTS();
    return retVal;
}



