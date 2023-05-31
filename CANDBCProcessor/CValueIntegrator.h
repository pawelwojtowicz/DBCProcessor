#pragma once
#include "IValueProcessor.h"

namespace DBCProcessor
{

class CValueIntegrator : public IValueProcessor
{
public:
  CValueIntegrator( float integrationFactor );
  
  virtual float ProcessValue( const float value ) override;

private:
  float m_integrationFactor;

  float m_currentValue;
};

}