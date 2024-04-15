#pragma once

#ifdef BOT4O7_PLATFORM_WINDOWS
#    ifdef BOT4O7_BUILD_DLL
#        define BOT4O7_API __declspec(dllexport)
#    else
#        define BOT4O7_API __declspec(dllimport)
#    endif
#else
#    error Only Support Windows Now.
#endif
