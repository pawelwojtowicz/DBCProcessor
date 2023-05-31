#include "CLowPassFilter.h"
#include <numeric>
#include <iostream>

namespace DBCProcessor
{
CLowPassFilter::CLowPassFilter( const std::vector<float>& factors )
: m_historySize( factors.size() ) 
, m_factors(factors)
, m_data( m_historySize , 0)
, m_position(0)
, m_denominator( std::accumulate( factors.begin(),factors.end(), 0.0 ) )
{
}

float CLowPassFilter::ProcessValue( const float value )
{
  m_data[m_position] = value;
  float processedValue = 0;

  for ( int i = 0; i < m_historySize ; ++i )
  {
    int readPosition = (m_position-i>=0)?(m_position - i):(m_historySize-i);
    processedValue += m_factors[i]*m_data[readPosition];
  }
  m_position = (++m_position)%m_historySize;

  return (processedValue/m_denominator);
}



}