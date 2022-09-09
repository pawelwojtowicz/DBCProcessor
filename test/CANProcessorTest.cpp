#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CCANMessageProcessor.h>

TEST( CCANMessageProcessor2 , Basic_BasicSignalNotification )
{
  CCANMessageProcessor canProcessor;

  std::vector<std::string> dbcFilePaths;
  dbcFilePaths.push_back("../test/testData/basic.dbc");
  canProcessor.Initialize(dbcFilePaths);

  uint64_t canData = 0x8877665544332211;

  const auto& message = canProcessor.ProcessMessage( 0x00F00400 , canData);

  EXPECT_EQ( message.GetMessageName(), "EEC1");
  EXPECT_EQ( message.GetMessageId(), 0xF00400);
  EXPECT_EQ( message.GetRawData(), "8877665544332211");
  
  auto engineSpeedSignalIter = message.GetSignalValue().find("EngineSpeed");

  EXPECT_TRUE( engineSpeedSignalIter !=  message.GetSignalValue().end() );

  EXPECT_EQ( engineSpeedSignalIter->second.GetName() , "EngineSpeed" );

}

TEST( CCANMessageProcessor2 , Basic_BasicSignalNotification2 )
{
  CCANMessageProcessor canProcessor;

  std::vector<std::string> dbcFilePaths;
  dbcFilePaths.push_back("../test/testData/basic.dbc");
  canProcessor.Initialize(dbcFilePaths);

  uint64_t canData = 0x8877665544332211;

  const auto& message = canProcessor.ProcessMessageByPGN( 0x00F004 , canData);

  EXPECT_EQ( message.GetMessageName(), "EEC1");
  EXPECT_EQ( message.GetMessageId(), 15729664);
  EXPECT_EQ( message.GetRawData(), "8877665544332211");
  
  auto engineSpeedSignalIter = message.GetSignalValue().find("EngineSpeed");

  EXPECT_TRUE( engineSpeedSignalIter !=  message.GetSignalValue().end() );

  EXPECT_EQ( engineSpeedSignalIter->second.GetName() , "EngineSpeed" );

}
