#include "CValueIntegrator.h"

namespace DBCProcessor
{
CValueIntegrator::CValueIntegrator( float integrationFactor )
: m_currentValue(0)
, m_integrationFactor(integrationFactor)
{

}
  
float CValueIntegrator::ProcessValue( const float value )
{
  m_currentValue += m_integrationFactor * value;
  return m_currentValue;
}
}