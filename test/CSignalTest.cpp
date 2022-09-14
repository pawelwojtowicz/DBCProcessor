#include <gtest/gtest.h>
#include <tuple>
#include <CSignal.h>

using tTestParameters = std::tuple<int, int, CSignal::eEndiannes, int>;

class SignalTestsFixture : public ::testing::TestWithParam<tTestParameters>
{

};

TEST_P( SignalTestsFixture, SignalValueExtraction)
{
  auto testParametersTuple = GetParam();

  int start(std::get<0>(testParametersTuple));
  int length(std::get<1>(testParametersTuple));
  CSignal::eEndiannes endian(std::get<2>(testParametersTuple));
  int expectedValue(std::get<3>(testParametersTuple));

  CSignal signalProcessor(start,length,endian);
  uint64_t candata = 0x1032547698BADCFE;
  uint64_t reversedCanData = 0xfedcba9876543210;

  EXPECT_EQ(static_cast<unsigned int>( signalProcessor.ExtractValue(candata, reversedCanData,8)), expectedValue);

}

INSTANTIATE_TEST_CASE_P(
        CSignalTests,
        SignalTestsFixture,
        ::testing::Values(
                tTestParameters({16,16, CSignal::bigEndian,0xDCBAUL} ),
                tTestParameters({16,16, CSignal::littleEndian,0x98BAUL} ),
                tTestParameters({18,4, CSignal::bigEndian,0x0E} ),
                tTestParameters({18,4, CSignal::littleEndian,0x0E} ),
                tTestParameters({8,16, CSignal::bigEndian,0xFEDC} ),
                tTestParameters({8,16, CSignal::littleEndian,0xBADC} ),
                tTestParameters({30,6, CSignal::bigEndian,0x2A} ),
                tTestParameters({30,6, CSignal::littleEndian,0x1A} ),
                tTestParameters({30,20, CSignal::bigEndian,0xB72EA} ),
                tTestParameters({30,20, CSignal::littleEndian,0x951DA} )
        ));