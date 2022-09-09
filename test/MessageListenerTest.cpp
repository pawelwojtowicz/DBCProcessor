#include <gtest/gtest.h>
#include <CCANMessageProcessor.h>
#include <IMessageListener.h>

class MessageObserver : public IMessageListener
{
public:
  virtual void NotifyMessageReceived( const CMessage& message)
  {
    dataReceived = true;
    receivedMessageId = message.GetMessageId();
    receivedName = message.GetMessageName();
  };

  bool dataReceived = false;
  unsigned int receivedMessageId = 0;
  std::string receivedName = "";
};


class MessageListenerTestFixture : public ::testing::Test
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

  MessageObserver messageObserver;

  CCANMessageProcessor canProcessor;
};

TEST_F( MessageListenerTestFixture , Basic_SubscribeAllMessages )
{
  canProcessor.SubscribeAllMessages( messageObserver);

  uint64_t canData = 0x1122334455667710;
  EXPECT_FALSE( messageObserver.dataReceived);
  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00FD7D00, canData) ) ;
  EXPECT_TRUE( messageObserver.dataReceived);
  EXPECT_EQ( messageObserver.receivedMessageId, 0x00FD7D00);
  EXPECT_EQ( messageObserver.receivedName,"FMS1");

}
