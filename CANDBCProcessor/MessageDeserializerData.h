#pragma once
#include <cstdint>
#include <tuple>
#include <list>
#include "CSignal.h"
#include "CSignalValueTemplate.h"
#include "ISignalListener.h"

#define MULTIPLEXERID 0
#define SIGNAL 1
#define VALUE 2
#define LISTENERS 3

using tSignalListeners = std::list<ISignalListener*>;
using tSignalTuple = std::tuple<int,CSignal, CSignalValueTemplate, tSignalListeners>;
using tSignalList = std::list<tSignalTuple>;
