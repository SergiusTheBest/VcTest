#pragma once

// Set target os version
#include "targetver.h"

// Enabling STRICT
#ifndef STRICT
#define STRICT
#endif

// Allow use of type-limit macros
#define WINDOWS_ENABLE_CPLUSPLUS 

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN 

// System headers
#include <Windows.h>
#include <cchannel.h>
#include <cassert>
#include <sstream>