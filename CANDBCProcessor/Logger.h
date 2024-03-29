#pragma once

#define ERROR   0x08
#define WARNING 0x04
#define INFO    0x02
#define DETAIL  0x01

#define ALL ( ERROR | WARNING | INFO | DETAIL )

#ifdef WITH_LOGGER

#include "CLoggerMsg.h"

#define LOG( zone, logMsg )                                   \
    {                                                         \
      if ( Logger::CLoggerMsg::ZoneEnabled( zone ) )          \
      {                                                       \
        Logger::CLoggerMsg msg( zone, __FILE__, __LINE__);    \
        msg.LogText  logMsg ;                                 \
      }                                                       \
    }                                                         \

#else
  #define LOG( zone, logMsg )
#endif