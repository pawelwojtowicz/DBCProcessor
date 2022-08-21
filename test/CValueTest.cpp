#include <gtest/gtest.h>
#include <CSignalValueTemplate.h>

TEST( CValue , BasicValueTest )
{
  CSignalValueTemplate value("testValue",25, 0.125, 25,100,"m/s", "temp");
  value.UpdateValue(13);
  float floatValue(0);

  EXPECT_EQ( value.GetValue(floatValue), true) ;
  EXPECT_EQ( floatValue, 26.625) ;
}