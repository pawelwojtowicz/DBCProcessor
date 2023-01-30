#include "CSimpleLogger.h"
#include "CLoggerMsg.h"
#include <iostream>


namespace Logger
{



CSimpleLogger::CSimpleLogger()
: a (0)
{
  CLoggerMsg::SetLogger(this);
}

CSimpleLogger::~CSimpleLogger()
{

}

void CSimpleLogger::RecordDebugMessage( const CLoggerMsg& rLoggerMsg)
{
  std::cout << rLoggerMsg.GetLogText() << std::endl;
}

}