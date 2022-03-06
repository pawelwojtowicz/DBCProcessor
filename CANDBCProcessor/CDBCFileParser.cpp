#include "CDBCFileParser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

CDBCFileParser::CDBCFileParser()
: m_messageRegExp("^BO_ ([0-9]+) ([A-Z 0-1]+): ([0-9]+) (.+)")
, m_signalRegExp("\\sSG_ ([a-zA-Z0-9_]+) : ([0-9]+)\\|([0-9]+)@([0-9]+)([+|-]) \\(([0-9\\.]+),([0-9\\.]+)\\) \\[([0-9\\.]+)\\|([0-9\\.]+)\\] \\\"(.+)\\\" (.*)")
, m_multiplexedSignalRegExp("\\sSG_ ([a-zA-Z0-9_]+) ([mM0-9]+) : ([0-9]+)\\|([0-9]+)@([0-9]+)([+|-]) \\(([0-9\\.]+),([0-9\\.]+)\\) \\[([0-9\\.]+)\\|([0-9\\.]+)\\] \\\"(.*)\\\" (.+)")
, m_messageCommentRegExp("^CM_ BO_ ([0-9]+) \\\"(.*)\\\"")
, m_signalCommentRegExp("^CM_ SG_ ([0-9]+) ([a-zA-Z0-9_]+) \\\"(.*)\\\";")
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
        while( std::getline( dbcFile, dbcLine ) )
        {
            std::smatch match;
            if (std::regex_search( dbcLine, match, m_messageRegExp ))
            {
                std::string canID = match[1];
                std::string name = match[2];
                std::string size = match[3];
                std::string sender = match[4];

                std::cout << "name=" << name << " sender=" << sender << std::endl;
            }
            else if ( std::regex_search( dbcLine, match, m_signalRegExp ) )
            {
                std::cout << "Jest sygnal ";
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
            else if ( std::regex_search( dbcLine, match, m_multiplexedSignalRegExp ) )
            {
                std::cout << "Jest multiplexed sygnal " ;
                std::string signalName = match[1];
                std::string multiplexer = match[2];
                std::string bitStart = match[3];
                std::string length = match[4];
                std::string endiannes = match[5];
                std::string withSign = match[6];
                std::string scale = match[7];
                std::string offset = match[8];
                std::string min = match[9];
                std::string max = match[10];
                std::string unit = match[11];
                std::string receiver = match[12];

                std::cout << "name=" << signalName << " unit=" << unit << std::endl;
            } 
            else if ( std::regex_search( dbcLine, match, m_messageCommentRegExp ))
            {
                std::string messageId = match[1];
                std::string comment = match[2];

                std::cout << "MsgComment msgId=[" << messageId << "] " << comment << std::endl; 
            }
            else if ( std::regex_search( dbcLine, match, m_signalCommentRegExp ))
            {
                std::string messageId = match[1];
                std::string signalName = match[2];
                std::string comment = match[3];

                std::cout << "SigComment msgId=[" << messageId << "] signalName=["<< signalName<< "] " << comment << std::endl; 
            }

            

            retVal = true;
        }
    }

    return retVal;
}