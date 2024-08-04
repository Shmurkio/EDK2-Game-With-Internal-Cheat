#pragma once

/* Converts a wide string literal to an unsigned short pointer. */
#define Ew(str) reinterpret_cast<unsigned short *>(const_cast<wchar_t *>(L##str))

/* Macro to alias printf to Print with Ew applied, but only define it if not already defined. */
#ifndef printf
    #define printf(str, ...) Print(Ew(str), ##__VA_ARGS__)
#endif