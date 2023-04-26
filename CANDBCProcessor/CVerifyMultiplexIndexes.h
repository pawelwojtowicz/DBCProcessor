#pragma once
#include "IDBCVerifier.h"

class CVerifyMultiplexIndexes : public IDBCVerifier
{
public:
  virtual bool VerifyMessage( const CMessageTemplate&  msgEntry ) override;
};