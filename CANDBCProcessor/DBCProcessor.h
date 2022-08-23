#pragma once
#include <map>
#include <string>

using tPropertyMap = std::map<std::string, std::string>;

static const std::string emptyString = std::string();
static const int cMultiplexerIndexField = -1;
static const int cStaticIndexField = -2;

struct tSignalValueProperties
{
float offset;
float scale;
float min;
float max;
};
