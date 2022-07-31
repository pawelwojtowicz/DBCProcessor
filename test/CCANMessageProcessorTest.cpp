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
    value.GetValue(OutputValue);
  }

  float OutputValue = -1;

};

void InitializeProcessor( IDBCEngineInit& processor )
{
    processor.AddMessage( 0x00F004, "EEC1",8,"ECU");
    processor.AddSignal("EngineSpeed", 24,16, CSignal::littleEndian, 0.125 , 0, 0, 100,"m/s","*");
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
