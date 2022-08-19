#pragma once
#include <string>

static const std::string emptyString = std::string();
static const int cMultiplexerIndexField = -1;

struct tSignalValueProperties
{
float offset;
float scale;
float min;
float max;
};
