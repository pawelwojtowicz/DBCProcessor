#pragma once
#include "DBCInfo.h"

class IDBCVerifier
{
public:
  virtual bool VerifyMessage( const CMessageTemplate&  msgEntry ) = 0;
};