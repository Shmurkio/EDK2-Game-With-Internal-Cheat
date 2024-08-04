#pragma once

#ifdef __cplusplus

extern "C"
{
    #endif

    #include <Uefi.h>
    #include <Library/UefiLib.h>
    #include <Library/UefiBootServicesTableLib.h>
    #include <Library/UefiApplicationEntryPoint.h>
    #include <Library/UefiRuntimeServicesTableLib.h>
    #include <stdio.h>
    #include <Library/ShellCEntryLib.h>
    #include <Library/BaseMemoryLib.h>
    #include <stdint.h>
    #include <stdlib.h>
    
    #ifdef __cplusplus
}

#endif

#include "LibCpp/defs.hpp"
#include "LibCpp/vector.hpp"
#include "LibCpp/stdexcept.hpp"
#include "LibCpp/new.hpp"