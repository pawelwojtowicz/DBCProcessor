#pragma once
#include <gmock/gmock.h>
#include <IMessageListener.h>

class CMessageListenerMock : public IMessageListener
{
public:
  MOCK_METHOD(void, NotifyMessageReceived, (const CMessage& message), (override));
};
