#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CCANMessageProcessor.h>
#include "CSignalListenerMock.h"

using testing::_;

class BasicProcessorTests : public testing::Test
{
public:
  void SetUp()
  {
    std::vector<std::string> dbcFilePaths;
    dbcFilePaths.push_back("../test/testData/basic.dbc");
    canProcessor.Initialize(dbcFilePaths);
  }

  testing::NiceMock<CSignalListenerMock> signalListener;

  CCANMessageProcessor canProcessor;
};


TEST_F( BasicProcessorTests , Basic_ProcessKnownMessage )
{
  uint64_t canData = 0x1122334455667788;

  EXPECT_EQ( canProcessor.GetDBCVersion(), "TEST_VERSION");
  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00F00400, canData) ) ;
}

TEST_F( BasicProcessorTests , Basic_ProcessUnknownMessage )
{
  uint64_t canData = 0x1122334455667788;
  EXPECT_FALSE( canProcessor.DispatchCANSignal( 0x00F001, canData) ) ;
}

TEST_F( BasicProcessorTests , Basic_SubscribeKnownMessage )
{
  EXPECT_TRUE( canProcessor.SubscribeCANSignal(0x00F00400, "EngineSpeed",signalListener ) ) ;
}

TEST_F( BasicProcessorTests , Basic_SubscribeUnknownMessage )
{
  EXPECT_FALSE( canProcessor.SubscribeCANSignal(0x00F054, "EngineSpeed",signalListener ) ) ;
}

TEST_F( BasicProcessorTests , Basic_SubscribeKnownMessageAndUknownSignal )
{
  EXPECT_FALSE( canProcessor.SubscribeCANSignal(0x00F00400, "GroundSpeed",signalListener ) ) ;
}

TEST_F( BasicProcessorTests , Basic_BasicSignalNotification )
{
  uint64_t canData = 0x8877665544332211;

  EXPECT_TRUE( canProcessor.SubscribeCANSignal(0x00F00400, "EngineSpeed",signalListener ) ) ;

  float signalValue(0);
  ON_CALL( signalListener, NotifySignalReceived(_,_) ).WillByDefault(testing::Invoke(
    [&] (const unsigned int msgId, const CValue& value)
    {
      signalValue = value.GetValueFLOAT();
    }
  ));

  EXPECT_TRUE( canProcessor.DispatchCANSignal(0x00F00400,canData));
  EXPECT_EQ( signalValue, 2728.5);
}

TEST_F( BasicProcessorTests , GeneralPropertyFoundProperty )
{
  EXPECT_EQ(canProcessor.GetProperty("ProtocolType"),"J1939");
}

TEST_F( BasicProcessorTests , GeneralPropertyNotFoundProperty )
{
  EXPECT_EQ(canProcessor.GetProperty("ProtocolShout"),"");
}

TEST_F( BasicProcessorTests , GeneralPropertyTypeFoundProperty )
{
  EXPECT_EQ(canProcessor.GetPropertyType("DatabaseCompiler"),"STRING");
}

TEST_F( BasicProcessorTests , GeneralPropertyTypeNotFoundProperty )
{
  EXPECT_EQ(canProcessor.GetPropertyType("ProtocolShout"),"");
}
