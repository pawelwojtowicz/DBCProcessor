#pragma once
#include <vector>
#include "IValueProcessor.h"

namespace DBCProcessor
{
class CLowPassFilter : public IValueProcessor
{
public:
  CLowPassFilter( const std::vector<float>& factors );

  float ProcessValue( const float value ) override;


private:
  int m_historySize;

  std::vector<float> m_factors;

  std::vector<float> m_data;

  int m_position;

  float m_denominator;

};

}