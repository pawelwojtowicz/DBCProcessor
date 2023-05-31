#include <gtest/gtest.h>
#include <CValueIntegrator.h>

TEST( CValueIntegratorTest , Basic )
{
  DBCProcessor::CValueIntegrator integrator(10);

  EXPECT_EQ( static_cast<int>(integrator.ProcessValue( 0.3) ) , 3 );
  EXPECT_EQ( static_cast<int>(integrator.ProcessValue( 0.4)) , 7 );
  EXPECT_EQ( static_cast<int>(integrator.ProcessValue( 0.5)) , 12 );
  EXPECT_EQ( static_cast<int>(integrator.ProcessValue( 0.6)) , 18 );
  EXPECT_EQ( static_cast<int>(integrator.ProcessValue( 0.7)) , 25 );
  EXPECT_EQ( static_cast<int>(integrator.ProcessValue( 0.8)) , 33 );
}
