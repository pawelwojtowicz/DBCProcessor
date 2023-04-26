#include <gtest/gtest.h>
#include <DBCInfo.h>
#include <CDBCInfoBuilder.h>
#include <CDBCVerifier.h>
#include <tuple>

using tTestParameters = std::tuple<std::string, bool>;
#define DBC_FILENAME 0
#define TEST_RESULT 1

class CDBCVerifierTest : public ::testing::TestWithParam<tTestParameters>
{
};

TEST_P( CDBCVerifierTest, DBCFileVerification)
{
  const std::string dbcFileName = std::get<DBC_FILENAME>( GetParam() );

  DBCInfo dbcInfo;

  CDBCInfoBuilder dbcBuilder(dbcInfo);
  dbcBuilder.BuildDBCInfo( std::vector<std::string>({ dbcFileName }));

  CDBCVerifier dbcVerifier( dbcInfo );
  EXPECT_EQ( dbcVerifier.VerifyDBCInfo() , std::get<TEST_RESULT>(GetParam() ) );
}

INSTANTIATE_TEST_CASE_P(
        DBCFileVerification,
        CDBCVerifierTest,
        ::testing::Values(
                tTestParameters( { std::string("../test/testData/verfication_overlayedSignals.dbc"), false } ),
                tTestParameters( { std::string("../test/testData/basic.dbc"), true } ),
                tTestParameters( { std::string("../test/testData/multiplexed_broken.dbc"), false } ),
                tTestParameters( { std::string("../test/testData/multiplexed.dbc"), true } ),
                tTestParameters( { std::string("../test/testData/basicExceeded.dbc"),false } )
        ));