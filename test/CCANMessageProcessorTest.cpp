#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CCANMessageProcessor.h>
#include <ISignalListener.h>

class TestListener : public ISignalListener
{
public:
virtual void NotifySignaReceived( const unsigned int msgId, const CValue& value )
{
  msgId;
  OutputValue = value.GetValueFLOAT();
}

float OutputValue = -1;

};

static void InitializeProcessor( CCANMessageProcessor& processor )
{
  std::vector<std::string> dbcFilePaths;
  dbcFilePaths.push_back("../test/testData/basic.dbc");
  processor.Initialize(dbcFilePaths);
}

TEST( CCANMessageProcessor , Basic_ProcessKnownMessage )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  uint64_t canData = 0x1122334455667788;


  EXPECT_TRUE( canProcessor.ProcessCANMessage( 0x00F004, canData) ) ;
}

TEST( CCANMessageProcessor , Basic_ProcessUnknownMessage )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  uint64_t canData = 0x1122334455667788;


  EXPECT_FALSE( canProcessor.ProcessCANMessage( 0x00F001, canData) ) ;
}

TEST( CCANMessageProcessor , Basic_SubscribeKnownMessage )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  TestListener testUtility;
  EXPECT_TRUE( canProcessor.SubscribeCANSignal(0x00F004, "EngineSpeed",testUtility ) ) ;
}

TEST( CCANMessageProcessor , Basic_SubscribeUnknownMessage )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  TestListener testUtility;
  EXPECT_FALSE( canProcessor.SubscribeCANSignal(0x00F054, "EngineSpeed",testUtility ) ) ;
}

TEST( CCANMessageProcessor , Basic_SubscribeKnownMessageAndUknownSignal )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  TestListener testUtility;
  EXPECT_FALSE( canProcessor.SubscribeCANSignal(0x00F004, "GroundSpeed",testUtility ) ) ;
}

TEST( CCANMessageProcessor , Basic_BasicSignalNotification )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  uint64_t canData = 0x8877665544332211;

  TestListener testUtility;
  EXPECT_TRUE( canProcessor.SubscribeCANSignal(0x00F004, "EngineSpeed",testUtility ) ) ;
  EXPECT_EQ( testUtility.OutputValue, -1);
  EXPECT_TRUE( canProcessor.ProcessCANMessage(0x00F004,canData));
  EXPECT_EQ( testUtility.OutputValue, 2728.5);

}

TEST( CCANMessageProcessor , GeneralPropertyFoundProperty )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  EXPECT_EQ(canProcessor.GetProperty("ProtocolType"),"J1939");
}

TEST( CCANMessageProcessor , GeneralPropertyNotFoundProperty )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  EXPECT_EQ(canProcessor.GetProperty("ProtocolShout"),"");
}

TEST( CCANMessageProcessor , GeneralPropertyTypeFoundProperty )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  EXPECT_EQ(canProcessor.GetPropertyType("DatabaseCompiler"),"STRING");
}

TEST( CCANMessageProcessor , GeneralPropertyTypeNotFoundProperty )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  EXPECT_EQ(canProcessor.GetPropertyType("ProtocolShout"),"");
}
