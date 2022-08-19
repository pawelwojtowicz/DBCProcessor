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

  uint64_t canData = 0x1122334455667788;


  EXPECT_TRUE( canProcessor.ProcessCANMessage( 0x00FD7D00, canData) ) ;
}

