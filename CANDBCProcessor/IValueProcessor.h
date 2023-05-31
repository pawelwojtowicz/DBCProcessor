#pragma once

namespace DBCProcessor
{
class IValueProcessor
{
public:
  IValueProcessor() =default;
  virtual ~IValueProcessor() = default;

  virtual float ProcessValue( const float value ) = 0 ;
};
}