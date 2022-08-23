#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CDBCFileParser.h>
#include <IDBCInfoBuilder.h>

class DBCProcessorInitializerMock : public IDBCInfoBuilder
{
  MOCK_METHOD4(  AddMessage, void( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender ) );
  MOCK_METHOD7( AddSignal, void (const std::string& ,
                          const unsigned int ,
                          const size_t ,
                          const int,
                          const tSignalValueProperties& valueProperties,
                          const std::string& ,
                          const std::string& ));
  MOCK_METHOD8( AddMultiplexedSignal, void (const std::string& ,
                          const unsigned int ,
                          const size_t ,
                          const int,
                          const tSignalValueProperties&,
                          const std::string& ,
                          const std::string& ,
                          const int ) );
  MOCK_METHOD2( AddMessageDescription, void ( unsigned int msgId, const std::string& description) );
  MOCK_METHOD3( AddSignalDescription, void ( unsigned int msgId, const std::string& valueName, const std::string& description));
  MOCK_METHOD2( SetSignalPropertyType, void ( const std::string& valueName, const std::string& type ) );
  MOCK_METHOD2( SetMessagePropertyType, void ( const std::string& propertyName, const std::string& propertyValue));
  MOCK_METHOD2( SetGeneralPropertyType, void ( const std::string& propertyName, const std::string& propertyValue));
  MOCK_METHOD2( SetDefaultPropertyValue, void ( const std::string& propertyName, const std::string& defaultValue ));

  MOCK_METHOD3( SetMessageProperty, void ( const std::string& propertyName, const unsigned int msgId, const std::string& propertyValue ) );
  MOCK_METHOD4( SetSignalProperty, void( const std::string& propertyName, const unsigned int msgId, const std::string& signalName, const std::string& propertyValue));
  MOCK_METHOD3( SetSignalValueDictionary, void ( const int msgId, const std::string& signalName, const std::string& initlizerString) );
};

TEST( CDBCFileParser , FileOpenSuccess )
{
  DBCProcessorInitializerMock dbcProcessorMock;
  CDBCFileParser dbcParser(dbcProcessorMock);

 //   EXPECT_TRUE( dbcParser.ReadDBCFile("SAE-J1939.dbc") );
}

