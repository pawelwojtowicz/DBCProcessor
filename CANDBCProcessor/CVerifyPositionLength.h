#pragma once
#include "IDBCVerifier.h"

class CVerifyPositionLength : public IDBCVerifier
{
public:
  virtual bool VerifyMessage( const CMessageTemplate&  msgEntry ) override;
};