#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CDBCFileParser.h>
#include <IDBCEngineInit.h>

class DBCProcessorInitializerMock : public IDBCEngineInit
{
    MOCK_METHOD4(  AddMessage, void( const unsigned int canId , const std::string& name,  size_t size, const std::string& sender ) );
    MOCK_METHOD10( AddSignal, void (const std::string& ,
                            const unsigned int ,
                            const size_t ,
                            const int,
                            const float ,
                            const float ,
                            const float ,
                            const float ,
                            const std::string& ,
                            const std::string& ));
    MOCK_METHOD10( AddMultiplexedSignal, void (const std::string& ,
                            const unsigned int ,
                            const size_t ,
                            const int,
                            const float ,
                            const float ,
                            const float ,
                            const float ,
                            const std::string& ,
                            const std::string& ));
    MOCK_METHOD2( AddMessageDescription, void ( unsigned int msgId, const std::string& description) );
    MOCK_METHOD3( AddSignalDescription, void ( unsigned int msgId, const std::string& valueName, const std::string& description));
    MOCK_METHOD2( SetSignalPropertyType, void ( const std::string& valueName, const std::string& type ) );
    MOCK_METHOD2( SetMessagePropertyType, void ( const std::string& propertyName, const std::string& propertyValue));
    MOCK_METHOD2( SetGeneralPropertyType, void ( const std::string& propertyName, const std::string& propertyValue));
    MOCK_METHOD2( SetDefaultPropertyValue, void ( const std::string& propertyName, const std::string& defaultValue ));

    MOCK_METHOD3( SetMessageProperty, void ( const std::string& propertyName, const unsigned int msgId, const std::string& propertyValue ) );
    MOCK_METHOD4( SetSignalProperty, void( const std::string& propertyName, const unsigned int msgId, const std::string& signalName, const std::string& propertyValue));

};

TEST( CDBCFileParser , FileOpenSuccess )
{
    DBCProcessorInitializerMock dbcProcessorMock;
    CDBCFileParser dbcParser(dbcProcessorMock);

    EXPECT_TRUE( dbcParser.ReadDBCFile("SAE-J1939.dbc") );
}

