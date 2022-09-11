#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CCANMessageProcessor.h>

class MessageProcessorTest : public ::testing::Test
{
public:
  void SetUp()
  {
    std::vector<std::string> dbcFilePaths;
    dbcFilePaths.push_back("../test/testData/basic.dbc");
    canProcessor.Initialize(dbcFilePaths);
  }

  CCANMessageProcessor canProcessor;
};

TEST_F( MessageProcessorTest , ProcessMessageByID )
{
  uint64_t canData = 0x8877665544332211;
  const auto& message = canProcessor.ProcessMessage( 0x00F00400 , canData);
  auto engineSpeedSignalIter = message.GetSignalValue().find("EngineSpeed");

  EXPECT_EQ( message.GetMessageName(), "EEC1");
  EXPECT_EQ( message.GetMessageId(), 0xF00400);
  EXPECT_EQ( message.GetPGN(), 0xF004);

  EXPECT_EQ( message.GetRawData(), "8877665544332211");
  EXPECT_TRUE( engineSpeedSignalIter !=  message.GetSignalValue().end() );
  EXPECT_EQ( engineSpeedSignalIter->second.GetName() , "EngineSpeed" );
}

TEST_F( MessageProcessorTest , ProcessUnkownMessage )
{
  uint64_t canData = 0x8877665544332211;
  const auto& message = canProcessor.ProcessMessage( 0x00F00500 , canData);

  EXPECT_EQ( message.GetSignalValue().size(), 0 );
  EXPECT_EQ( message.GetMessageName(), "Generic");
  EXPECT_EQ( message.GetMessageId(), 0x00F00500);
  EXPECT_EQ( message.GetPGN(), 0x00F005);
  EXPECT_EQ( message.GetRawData(), "8877665544332211");
}



TEST_F( MessageProcessorTest , ProcessMessageByPGN )
{
  uint64_t canData = 0x8877665544332211;
  const auto& message = canProcessor.ProcessMessageByPGN( 0x00F004 , canData);
  auto engineSpeedSignalIter = message.GetSignalValue().find("EngineSpeed");

  EXPECT_EQ( message.GetMessageName(), "EEC1");
  EXPECT_EQ( message.GetPGN(), 0x00F004);
  EXPECT_EQ( message.GetRawData(), "8877665544332211");
  EXPECT_TRUE( engineSpeedSignalIter !=  message.GetSignalValue().end() );
  EXPECT_EQ( engineSpeedSignalIter->second.GetName() , "EngineSpeed" );

}

TEST_F( MessageProcessorTest , ProcessUnkownMessageByPGN )
{
  uint64_t canData = 0x8877665544332211;
  const auto& message = canProcessor.ProcessMessageByPGN( 0x00F005 , canData);

  EXPECT_EQ( message.GetSignalValue().size(), 0 );
  EXPECT_EQ( message.GetMessageName(), "Generic");
  EXPECT_EQ( message.GetPGN(), 0x00F005);
  EXPECT_EQ( message.GetRawData(), "8877665544332211");
}
