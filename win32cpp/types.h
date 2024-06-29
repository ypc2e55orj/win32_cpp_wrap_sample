#ifndef WIN32CPP_TYPES_H
#define WIN32CPP_TYPES_H

// Windows
#include <tchar.h>
#include <wtypes.h>

// C++
#include <string>

namespace win32cpp
{
    using tstring = std::basic_string<TCHAR>;
} // win32cpp

#endif // WIN32CPP_TYPES_H
