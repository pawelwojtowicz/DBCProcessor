#include "CDBCFileParser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

CDBCFileParser::CDBCFileParser()
: m_messageRegExp("^BO_ ([0-9]+) ([A-Z 0-1]+): ([0-9]+) (.+)")
, m_signalRegExp("\\sSG_ (.+) : ([0-9]+)\\|([0-9]+)@([0-9]+)([+|-]) \\(([0-9\\.]+),([0-9\\.]+)\\) \\[([0-9\\.]+)\\|([0-9\\.]+)\\] \\\"(.+)\\\" (.+)")
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
            //std::cout << dbcLine << std::endl;

            std::smatch match;

            if (std::regex_search( dbcLine, match, m_messageRegExp ))
            {
                std::string canID = match[1];
                std::string name = match[2];
                std::string size = match[3];
                std::string sender = match[4];

                std::cout << "name=" << name << " sender=" << sender << std::endl;
            } else if ( std::regex_search( dbcLine, match, m_signalRegExp ) )
            {
                std::cout << "Jest sygnal" << std::endl;
                std::string signalName = match[1];
                std::string bitStart = match[2];
                std::string length = match[3];
                std::string endiannes = match[4];
                std::string withSign = match[5];
                std::string scale = match[6];
                std::string offset = match[7];
                std::string min = match[8];
                std::string max = match[9];
                std::string unit = match[10];
                std::string receiver = match[11];

                std::cout << "name=" << signalName << " unit=" << unit << std::endl;
            }

            retVal = true;
        }
    }

    return retVal;
}