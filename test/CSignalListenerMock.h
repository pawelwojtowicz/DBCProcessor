#pragma once
#include <gmock/gmock.h>
#include <ISignalListener.h>

class CSignalListenerMock : public ISignalListener
{
public:
  MOCK_METHOD(void, NotifySignalReceived, (const unsigned int msgId, const CValue& value), (override));
};
