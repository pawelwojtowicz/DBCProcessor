#pragma once
#include "ILogger.h"

namespace Logger
{
class CSimpleLogger : public ILogger
{
public:
  CSimpleLogger();
  virtual ~CSimpleLogger();
private:
  void RecordDebugMessage( const CLoggerMsg& rLoggerMsg) override ;
private:
  int a;
};
}