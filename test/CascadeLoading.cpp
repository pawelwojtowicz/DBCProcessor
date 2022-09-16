#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CCANMessageProcessor.h>

TEST( CascadeLoading , MergingMessage )
{
  std::vector<std::string> dbcList = { std::string( "../test/testData/cascadeLvl1.dbc") , std::string( "../test/testData/cascadeLvl2a.dbc")};

  CCANMessageProcessor canProcessor;

  canProcessor.Initialize(dbcList);

  uint64_t canData = 0x8877665544332211;

  const auto& message = canProcessor.ProcessMessage( 15729664 , canData);
  EXPECT_EQ( canProcessor.GetDBCVersion() , "cascadeLvl1//cascadeLvl2a");
  EXPECT_EQ( message.GetMessageName(), "EEC1");
  EXPECT_NE( message.GetSignalValue().end(), message.GetSignalValue().find("EngineSpeed") );
  EXPECT_NE( message.GetSignalValue().end(), message.GetSignalValue().find("VehicleSpeed"));
}

TEST( CascadeLoading , ReplacingMessage )
{
  std::vector<std::string> dbcList = { std::string( "../test/testData/cascadeLvl1.dbc") , std::string( "../test/testData/cascadeLvl2b.dbc")};

  CCANMessageProcessor canProcessor;

  canProcessor.Initialize(dbcList);

  uint64_t canData = 0x8877665544332211;

  const auto& message = canProcessor.ProcessMessage( 15729664 , canData);
  EXPECT_EQ( canProcessor.GetDBCVersion() , "cascadeLvl1//cascadeLvl2b");
  EXPECT_EQ( message.GetMessageName(), "REPLACEMENT");
  EXPECT_EQ( message.GetSignalValue().end(), message.GetSignalValue().find("EngineSpeed") );
  EXPECT_NE( message.GetSignalValue().end(), message.GetSignalValue().find("VehicleSpeed"));
}
