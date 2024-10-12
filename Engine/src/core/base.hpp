#pragma once

#define BIT(n) 1 << n
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) \
    { return this->fn(std::forward<decltype(args)>(args)...); }

#include "types.h"
#include "console_manager.hpp"