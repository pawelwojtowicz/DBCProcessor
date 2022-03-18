#include "CDBCFileParser.h"
#include "IDBCEngineInit.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

CDBCFileParser::CDBCFileParser( IDBCEngineInit& engineInitializer )
: m_messageRegExp("^BO_ ([0-9]+) ([A-Z 0-1]+): ([0-9]+) (.+)")
, m_signalRegExp("\\sSG_ ([a-zA-Z0-9_]+) : ([0-9]+)\\|([0-9]+)@([0-9]+)([+|-]) \\(([0-9\\.]+),([0-9\\.]+)\\) \\[([0-9\\.]+)\\|([0-9\\.]+)\\] \\\"(.+)\\\" (.*)")
, m_multiplexedSignalRegExp("\\sSG_ ([a-zA-Z0-9_]+) ([mM0-9]+) : ([0-9]+)\\|([0-9]+)@([0-9]+)([+|-]) \\(([0-9\\.]+),([0-9\\.]+)\\) \\[([0-9\\.]+)\\|([0-9\\.]+)\\] \\\"(.*)\\\" (.+)")
, m_messageCommentRegExp("^CM_ BO_ ([0-9]+) \\\"(.*)\\\"")
, m_signalCommentRegExp("^CM_ SG_ ([0-9]+) ([a-zA-Z0-9_]+) \\\"(.*)\\\";")
, m_signalPropertyTypeRegExp("^BA_DEF_ SG_\\s*\\\"([a-zA-Z0-9]*)\\\" (.*);")
, m_messagePropertyTypeRegExp("^BA_DEF_ BO_\\s*\\\"([a-zA-Z0-9]*)\\\" (.*);")
, m_generalPropertyTypeRegExp("^BA_DEF_\\s*\\\"([a-zA-Z0-9]*)\\\" (.*)[\\s];")
, m_valueDefaultPropertyRegExp("^BA_\\s*\\\"([a-zA-Z0-9]*)\\\" [\\\"\\s](.*)[\\\"\\s];")
, m_defineMsgProperty("^BA_\\s\\\"([a-zA-Z0-9]*)\\\" BO_ ([0-9]*) (.*);")
, m_defineSignalProperty("^BA_\\s\\\"([a-zA-Z0-9]*)\\\" SG_ ([0-9]*) ([a-zA-Z0-9_]*) (.*);")
, m_rDBCProcessorInitializer( engineInitializer )
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
                const std::string& canID = match[1];
                const std::string& name = match[2];
                const std::string& size = match[3];
                const std::string& sender = match[4];

                //std::cout << "name=" << name << " sender=" << sender << std::endl;
            }
            else if ( std::regex_search( dbcLine, match, m_signalRegExp ) )
            {
                const std::string& signalName = match[1];
                const std::string& bitStart = match[2];
                const std::string& length = match[3];
                const std::string& endiannes = match[4];
                const std::string& withSign = match[5];
                const std::string& scale = match[6];
                const std::string& offset = match[7];
                const std::string& min = match[8];
                const std::string& max = match[9];
                const std::string& unit = match[10];
                const std::string& receiver = match[11];

                //std::cout << "Jest sygnal ";
                //std::cout << "name=" << signalName << " unit=" << unit << std::endl;
            }
            else if ( std::regex_search( dbcLine, match, m_multiplexedSignalRegExp ) )
            {
                const std::string& signalName = match[1];
                const std::string& multiplexer = match[2];
                const std::string& bitStart = match[3];
                const std::string& length = match[4];
                const std::string& endiannes = match[5];
                const std::string& withSign = match[6];
                const std::string& scale = match[7];
                const std::string& offset = match[8];
                const std::string& min = match[9];
                const std::string& max = match[10];
                const std::string& unit = match[11];
                const std::string& receiver = match[12];
                //std::cout << "Jest multiplexed sygnal " ;
                //std::cout << "name=" << signalName << " unit=" << unit << std::endl;
            } 
            else if ( std::regex_search( dbcLine, match, m_messageCommentRegExp ))
            {
                const std::string& messageId = match[1];
                const std::string& comment = match[2];

                //std::cout << "MsgComment msgId=[" << messageId << "] " << comment << std::endl; 
            }
            else if ( std::regex_search( dbcLine, match, m_signalCommentRegExp ))
            {
                const std::string& messageId = match[1];
                const std::string& signalName = match[2];
                const std::string& comment = match[3];

                //std::cout << "SigComment msgId=[" << messageId << "] signalName=["<< signalName<< "] " << comment << std::endl; 
            }
            else if (std::regex_search(dbcLine,match, m_signalPropertyTypeRegExp) )
            {
                const std::string& propertyName = match[1];
                const std::string& typeSpecs = match[2];

                std::cout << "Signal property definition " << propertyName << " typeSpecs=[" << typeSpecs << "]" << std::endl;
            }
            else if ( std::regex_search(dbcLine,match, m_messagePropertyTypeRegExp) )
            {
                const std::string& propertyName = match[1];
                const std::string& typeSpecs = match[2];

                //std::cout << "Message property definition " << propertyName << " typeSpecs=[" << typeSpecs << "]" << std::endl;
            }
            else if ( std::regex_search( dbcLine, match, m_generalPropertyTypeRegExp ) )
            {
                const std::string& propertyName = match[1];
                const std::string& typeSpecs = match[2];

                //std::cout << "General property definition " << propertyName << " typeSpecs=[" << typeSpecs << "]" << std::endl;
            }
            else if (  std::regex_search( dbcLine, match, m_valueDefaultPropertyRegExp ) )
            {
                const std::string& propertyName = match[1];
                const std::string& value = match[2];

                std::cout << "Default property definition " << propertyName << " value=[" << value << "]" << std::endl;
            }
            else if ( std::regex_search( dbcLine, match, m_defineMsgProperty ) )
            {
                const std::string& propertyName = match[1];
                const std::string& msgId = match[2];
                const std::string& value = match[3];

                std::cout << "Msg property " << propertyName << " msgId=[" << msgId << "] value=[" << value << "]" << std::endl; 
            }
            else if ( std::regex_search( dbcLine, match, m_defineSignalProperty ) )
            {
                const std::string& propertyName = match[1];
                const std::string& msgId = match[2];
                const std::string& signalName = match[3];
                const std::string& value = match[4];

                std::cout << "Msg property " << propertyName << " msgId=[" << msgId << "] signalName=["<< signalName <<  "] value=[" << value << "]" << std::endl; 
            }
            

            retVal = true;
        }
    }

    return retVal;
}