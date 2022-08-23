#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CCANMessageProcessor.h>
#include <ISignalListener.h>

#include <iostream>

class TestListener1 : public ISignalListener
{
public:
virtual void NotifySignaReceived( const unsigned int msgId, const CValue& value )
{
  ReceivedMsgId = msgId;
  OutputValue = value.GetValueINT();
  OutputValueString = value.GetValueSTRING();
  SignalName = value.GetName();
}

float OutputValue = -1;
int ReceivedMsgId = -1;
std::string SignalName = std::string();
std::string OutputValueString = std::string();
};

static void InitializeProcessor( CCANMessageProcessor& processor )
{
  std::vector<std::string> dbcFilePaths;
  dbcFilePaths.push_back("../test/testData/multiplexed.dbc");
  
  processor.Initialize(dbcFilePaths);
}

TEST( CCANMessageProcessor_MultiplexedProcessing , Basic_ProcessKnownMessage )
{
  CCANMessageProcessor canProcessor;
  InitializeProcessor( canProcessor);

  uint64_t canData = 0x1122334455667710;

  TestListener1 multiplexerListener;


  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "01_CollingAirConditioning", multiplexerListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "16_ReadFogLights", multiplexerListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "31_SteeringFailure", multiplexerListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "46_AuxillaryAirPressure", multiplexerListener));
  EXPECT_TRUE( canProcessor.SubscribeCANSignal( 0x00FD7D00, "61_EngineEmissionFilter", multiplexerListener));

  EXPECT_TRUE( canProcessor.ProcessCANMessage( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( multiplexerListener.ReceivedMsgId, 0x00FD7D00);
  EXPECT_EQ( multiplexerListener.SignalName, "01_CollingAirConditioning");
  EXPECT_EQ( multiplexerListener.OutputValueString, "Inside");
  
  canData = 0x1122334455667711;
  EXPECT_TRUE( canProcessor.ProcessCANMessage( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( multiplexerListener.SignalName, "16_ReadFogLights");
  EXPECT_EQ( multiplexerListener.OutputValueString, "1.000000");

  canData = 0x2122334455667732;
  EXPECT_TRUE( canProcessor.ProcessCANMessage( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( multiplexerListener.SignalName, "31_SteeringFailure");
  EXPECT_EQ( multiplexerListener.OutputValueString, "3.000000");
  
  canData = 0x3122334455667743;
  EXPECT_TRUE( canProcessor.ProcessCANMessage( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( multiplexerListener.SignalName, "46_AuxillaryAirPressure");
  EXPECT_EQ( multiplexerListener.OutputValueString, "HereAndThere");

  canData = 0x4122334455667744;
  EXPECT_TRUE( canProcessor.ProcessCANMessage( 0x00FD7D00, canData) ) ;
  EXPECT_EQ( multiplexerListener.SignalName, "61_EngineEmissionFilter");

}

