#include "CDBCFileParser.h"

#include <iostream>
#include <fstream>
#include <string>

CDBCFileParser::CDBCFileParser()
{

}

CDBCFileParser::~CDBCFileParser()
{

}

bool CDBCFileParser::ReadDBCFile( const std::string& filename )
{
    bool retVal(false);
    std::string dbcLine;

    std::ifstream dbcFile( filename );

    if ( dbcFile.is_open() )
    {
        std::cout << "File opened " << std::endl;
        while( std::getline( dbcFile, dbcLine ) )
        {
            std::cout << dbcLine << std::endl;
            retVal = true;
        }
    }

    return retVal;
}