#pragma once
#include "IDBCVerifier.h"

class CVerifySignalOverlay : public IDBCVerifier
{
public:
  virtual bool VerifyMessage( const CMessageTemplate&  msgEntry ) override;
};