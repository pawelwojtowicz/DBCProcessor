#include <gtest/gtest.h>
#include <CCANMessageProcessor.h>
#include "CMessageListenerMock.h"

using testing::_;

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

  testing::NiceMock<CMessageListenerMock> messageListener;;

  CCANMessageProcessor canProcessor;
};

TEST_F( MessageListenerTestFixture , Basic_SubscribeAllMessages )
{
  canProcessor.SubscribeAllMessages( messageListener);

  uint64_t canData = 0x1122334455667710;
  bool messageReceived(false);
  unsigned int receivedMsgId(0);
  std::string receivedMsgName("");

  ON_CALL( messageListener, NotifyMessageReceived(_) ).WillByDefault(testing::Invoke(
  [&] (const CMessage& message)
  {
    receivedMsgId = message.GetMessageId();
    receivedMsgName = message.GetMessageName();
    messageReceived = true;
  }
  ));


  EXPECT_TRUE( canProcessor.DispatchCANSignal( 0x00FD7D00, canData) ) ;
  EXPECT_TRUE( messageReceived);

  EXPECT_EQ( receivedMsgId, 0x00FD7D00);
  EXPECT_EQ( receivedMsgName,"FMS1");

}
