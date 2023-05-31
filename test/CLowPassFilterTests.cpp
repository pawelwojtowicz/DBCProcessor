#include <gtest/gtest.h>
#include <CLowPassFilter.h>
#include <iostream>
#include <numeric>

static const float sf_testRescaler = 100000;

TEST( CLowPassFilterTest , History_1 )
{
  std::vector<float> factorsForFilter = { 0.5 };

  DBCProcessor::CLowPassFilter lowPassFilter(factorsForFilter);

  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.3)*sf_testRescaler) , 30000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.4)*sf_testRescaler) , 40000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.5)*sf_testRescaler) , 50000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.6)*sf_testRescaler) , 60000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.7)*sf_testRescaler) , 70000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.8)*sf_testRescaler) , 80000 );
}

TEST( CLowPassFilterTest , History_2 )
{
  std::vector<float> factorsForFilter = { 0.5, 0.5 };

  DBCProcessor::CLowPassFilter lowPassFilter(factorsForFilter);

  lowPassFilter.ProcessValue( 0.3);
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.4)*sf_testRescaler) , 35000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.5)*sf_testRescaler) , 45000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.6)*sf_testRescaler) , 55000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.8)*sf_testRescaler) , 70000 );
}

TEST( CLowPassFilterTest , History_3 )
{
  std::vector<float> factorsForFilter = { 0.5, 0.2, 0.1 };

  DBCProcessor::CLowPassFilter lowPassFilter(factorsForFilter);

  lowPassFilter.ProcessValue( 0.3);
  lowPassFilter.ProcessValue( 0.4);
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.5)*sf_testRescaler) , 45000 );
  EXPECT_EQ( static_cast<int>(lowPassFilter.ProcessValue( 0.6)*sf_testRescaler) , 55000 );
}