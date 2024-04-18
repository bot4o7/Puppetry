#pragma once

#ifdef CP_PLATFORM_WINDOWS
#else
#    error Only Support Windows Now.
#endif

#ifdef CP_CPU_64
#else
#    error Only Support x64 Now.
#endif

#ifdef BOT4O7_DEBUG

#include "../utils/log.h"

#endif

