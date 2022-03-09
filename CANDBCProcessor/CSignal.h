#pragma once
#include <string>

class CSignal
{

private:
    std::string signalName
    int bitStart;
    int length
    std::string endiannes;
    bool withSign;
    int scale;
    int offset;
    int min;
    int max;
    std::string unit;
    std::string receiver;
};