#include "CDBCFileParser.h"
#include "IDBCInfoBuilder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

const std::string dbcBigEndian = std::string("0");

CDBCFileParser::CDBCFileParser( IDBCInfoBuilder& engineInitializer )
: m_messageRegExp("^BO_ ([0-9]+) ([a-zA-Z0-1_]+): ([0-9]+) (.+)")
, m_signalRegExp("\\sSG_ ([a-zA-Z0-9_]+) : ([0-9]+)\\|([0-9]+)@([0-9]+)([+|-]) \\(([0-9\\.]+),([0-9\\.]+)\\) \\[([0-9\\.]+)\\|([0-9\\.]+)\\] \\\"(.*)\\\" (.*)")
, m_multiplexedSignalRegExp("\\sSG_ ([a-zA-Z0-9_]+) ([mM0-9]+) : ([0-9]+)\\|([0-9]+)@([0-9]+)([+|-]) \\(([0-9\\.]+),([0-9\\.]+)\\) \\[([0-9\\.]+)\\|([0-9\\.]+)\\] \\\"(.*)\\\" (.+)")
, m_messageCommentRegExp("^CM_ BO_ ([0-9]+) \\\"(.*)\\\"")
, m_signalCommentRegExp("^CM_ SG_ ([0-9]+) ([a-zA-Z0-9_]+) \\\"(.*)\\\";")
, m_signalPropertyTypeRegExp("^BA_DEF_ SG_\\s*\\\"([a-zA-Z0-9]*)\\\" (.*);")
, m_messagePropertyTypeRegExp("^BA_DEF_ BO_\\s*\\\"([a-zA-Z0-9]*)\\\" (.*);")
, m_generalPropertyTypeRegExp("^BA_DEF_\\s*\\\"([a-zA-Z0-9]*)\\\" (.*)[\\s];")
, m_valueDefaultPropertyRegExp("^BA_\\s*\\\"([a-zA-Z0-9]*)\\\" [\\\"\\s](.*)[\\\"\\s];")
, m_defineMsgProperty("^BA_\\s\\\"([a-zA-Z0-9]*)\\\" BO_ ([0-9]*) (.*);")
, m_defineSignalProperty("^BA_\\s\\\"([a-zA-Z0-9]*)\\\" SG_ ([0-9]*) ([a-zA-Z0-9_]*) (.*);")
, m_signalValueMapper("^VAL_ ([0-9]+) ([a-zA-Z0-9_]+) ((?:[0-9]+) (?:\\\".+\\\")\\s*)+;")
, m_versionInfo("^VERSION \\\"(\\w*)\\\"")
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
        const std::string& canID_s = match[1];
        const unsigned int canID = atoi( canID_s.c_str() );
        const std::string& name = match[2];
        const std::string& size_s = match[3];
        const size_t size = atoi( size_s.c_str() );
        const std::string& sender = match[4];

        m_rDBCProcessorInitializer.AddMessage(canID , name,  size, sender);
      }
      else if ( std::regex_search( dbcLine, match, m_signalRegExp ) )
      {
        const std::string& signalName = match[1];
        const std::string& bitStart_s = match[2];
        const unsigned int bitStart = atoi(bitStart_s.c_str());
        const std::string& length_s = match[3];
        const size_t length = atoi(length_s.c_str());
        const std::string& endiannes_s = match[4];
        int endiannes = atoi( endiannes_s.c_str()) ;
        const std::string& withSign = match[5];
        const std::string& scale_s = match[6];
        const float scale = atof(scale_s.c_str());
        const std::string& offset_s = match[7];
        const float offset = atof( offset_s.c_str());
        const std::string& min_s = match[8];
        const float min = atof( min_s.c_str() );
        const std::string& max_s = match[9];
        const float max = atof( max_s.c_str() );
        const std::string& unit = match[10];
        const std::string& receiver = match[11];

        tSignalValueProperties signalValueProperties;
        signalValueProperties.min = min;
        signalValueProperties.max = max;
        signalValueProperties.offset = offset;
        signalValueProperties.scale = scale;

        m_rDBCProcessorInitializer.AddSignal( signalName,
                                              bitStart,
                                              length,
                                              endiannes,
                                              signalValueProperties,
                                              unit,
                                              receiver );
      }
      else if ( std::regex_search( dbcLine, match, m_multiplexedSignalRegExp ) )
      {
        const std::string& signalName = match[1];
        const std::string& multiplexer = match[2];
        int multiplexerId = cMultiplexerIndexField;
        if ( multiplexer.length() > 1 )
        {
          if ( 'm' == multiplexer[0])
          {
            std::string index = multiplexer.substr(1);
            multiplexerId = atoi( index.c_str());
          }
        }

        const std::string& bitStart_s = match[3];
        const std::string& length_s = match[4];
        const std::string& endiannes_s = match[5];
        const std::string& withSign = match[6];
        const std::string& scale_s = match[7];
        const std::string& offset_s = match[8];
        const std::string& min_s = match[9];
        const std::string& max_s = match[10];
        const std::string& unit = match[11];
        const std::string& receiver = match[12];

        const unsigned int bitStart = atoi(bitStart_s.c_str());
        const size_t length = atoi(length_s.c_str());
        int  endiannes( atoi( endiannes_s.c_str() ) ) ;
        const float scale = atof(scale_s.c_str());
        const float offset = atof( offset_s.c_str());
        const float min = atof( min_s.c_str() );
        const float max = atof( max_s.c_str() );

        tSignalValueProperties signalValueProperties;
        signalValueProperties.min = min;
        signalValueProperties.max = max;
        signalValueProperties.offset = offset;
        signalValueProperties.scale = scale;


        m_rDBCProcessorInitializer.AddMultiplexedSignal(    signalName,
                                                            bitStart,
                                                            length,
                                                            endiannes,
                                                            signalValueProperties,
                                                            unit,
                                                            receiver,
                                                            multiplexerId );
      } 
      else if ( std::regex_search( dbcLine, match, m_messageCommentRegExp ))
      {
        const std::string& messageId_s = match[1];
        const unsigned int messageId = atoi(messageId_s.c_str());
        const std::string& comment = match[2];

        m_rDBCProcessorInitializer.AddMessageDescription( messageId, comment);
      }
      else if ( std::regex_search( dbcLine, match, m_signalCommentRegExp ))
      {
        const std::string& messageId_s = match[1];
        const unsigned int messageId = atoi(messageId_s.c_str());
        const std::string& signalName = match[2];
        const std::string& comment = match[3];

        m_rDBCProcessorInitializer.AddSignalDescription( messageId, signalName, comment);
      }
      else if (std::regex_search(dbcLine,match, m_signalPropertyTypeRegExp) )
      {
        const std::string& propertyName = match[1];
        const std::string& typeSpecs = match[2];

        m_rDBCProcessorInitializer.SetSignalPropertyType( propertyName, typeSpecs );
      }
      else if ( std::regex_search(dbcLine,match, m_messagePropertyTypeRegExp) )
      {
        const std::string& propertyName = match[1];
        const std::string& typeSpecs = match[2];

        m_rDBCProcessorInitializer.SetMessagePropertyType( propertyName, typeSpecs);
      }
      else if ( std::regex_search( dbcLine, match, m_generalPropertyTypeRegExp ) )
      {
        const std::string& propertyName = match[1];
        const std::string& typeSpecs = match[2];

        m_rDBCProcessorInitializer.SetGeneralPropertyType( propertyName, typeSpecs );
      }
      else if (  std::regex_search( dbcLine, match, m_valueDefaultPropertyRegExp ) )
      {
        const std::string& propertyName = match[1];
        const std::string& value = match[2];

        m_rDBCProcessorInitializer.SetDefaultPropertyValue( propertyName, value );
      }
      else if ( std::regex_search( dbcLine, match, m_defineMsgProperty ) )
      {
        const std::string& propertyName = match[1];
        const std::string& msgId_s = match[2];
        const unsigned int msgId = atoi( msgId_s.c_str() );
        const std::string& value = match[3];

        m_rDBCProcessorInitializer.SetMessageProperty( propertyName, msgId, value );
      }
      else if ( std::regex_search( dbcLine, match, m_defineSignalProperty ) )
      {
        const std::string& propertyName = match[1];
        const std::string& msgId_s = match[2];
        const unsigned int msgId = atoi( msgId_s.c_str() );
        const std::string& signalName = match[3];
        const std::string& value = match[4];

        m_rDBCProcessorInitializer.SetSignalProperty(propertyName, msgId, signalName, value);
      }
      else if ( std::regex_search( dbcLine, match, m_signalValueMapper) )
      {
        const std::string& msgId_s = match[1];
        const unsigned int msgId = atoi( msgId_s.c_str() );
        const std::string& signalName = match[2];
        const std::string& initializerString = match[3];

        m_rDBCProcessorInitializer.SetSignalValueDictionary(msgId,signalName,initializerString);
      }
      else if ( std::regex_search( dbcLine, match, m_versionInfo) )
      {
        m_rDBCProcessorInitializer.SetVersionInfo( match[1]);
      }
      retVal = true;
    }
  }

  return retVal;
}