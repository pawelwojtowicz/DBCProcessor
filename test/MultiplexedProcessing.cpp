#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CSignalListenerMock.h"

#include <CCANMessageProcessor.h>
#include <iostream>

using testing::_;

class MultiplexedProcessing : public ::testing::Test
{
public:
  void SetUp( ) 
  {
    std::vector<std::string> dbcFilePaths;
    dbcFilePaths.push_back("../test/testData/multiplexed.dbc");

    canProcessor.Initialize(dbcFilePaths);  
  }

  void TearDown( )
  { 
  }

  testing::NiceMock<CSignalListenerMock> signalListener;

  CCANMessageProcessor canProcessor;
};


TEST_F( MultiplexedProcessing , Basic_ProcessKnownMessage )
{
  uint64_t canData = 0x1122334455667710;

  unsigned int receivedMessageId(0);
  std::string signalName("");
  std::string signalValueString("");
  ON_CALL( signalListener, NotifySignalReceived(_,_) ).WillByDefault(testing::Invoke(
    [&] (const unsigned int msgId, const CValue& value)
    {
      receivedMessageId = msgId;
      signalName = value.GetName();
      signalValueString = value.GetValueSTRING();
    }
  ));


  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "01_CollingAirConditioning", signalListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "16_ReadFogLights", signalListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "31_SteeringFailure", signalListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "46_AuxillaryAirPressure", signalListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "61_EngineEmissionFilter", signalListener));

  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( receivedMessageId, 0x00FD7D00);
  EXPECT_EQ( signalName, "01_CollingAirConditioning");
  EXPECT_EQ( signalValueString, "Inside");
  
  canData = 0x1122334455667711;
  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( signalName, "16_ReadFogLights");
  EXPECT_EQ( signalValueString, "1.000000");

  canData = 0x2122334455667732;
  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( signalName, "31_SteeringFailure");
  EXPECT_EQ( signalValueString, "3.000000");
  
  canData = 0x3122334455667743;
  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( signalName, "46_AuxillaryAirPressure");
  EXPECT_EQ( signalValueString, "HereAndThere");

  canData = 0x4122334455667744;
  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( signalName, "61_EngineEmissionFilter");
}