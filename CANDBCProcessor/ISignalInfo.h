#pragma once
#include <string>

class ISignalInfo
{
public:
    ISignalInfo() {};
    virtual ~ISignalInfo() {};

    virtual const std::string& GetName() = 0;
    virtual const std::string& GetUnit() = 0;
    virtual const std::string GetProperty( const std::string& propertyName ) = 0;

};