[Defines]
    PLATFORM_NAME = Game
    PLATFORM_GUID = 5E63DA69-4F36-4DE3-B9EF-8F414668AA96
    PLATFORM_VERSION = 1.0
    DSC_SPECIFICATION = 0x00010005
    SUPPORTED_ARCHITECTURES = X64
    BUILD_TARGETS = DEBUG|RELEASE
    OUTPUT_DIRECTORY = GamePkg/Build

[LibraryClasses]
    UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
    UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
    PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
    PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
    MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
    DebugLib|MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf
    BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
    BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
    UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
    DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
    UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
    RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf
    DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
    LibNetUtil|StdLib/LibC/NetUtil/NetUtil.inf
    LibC|StdLib/LibC/LibC.inf
    ShellCEntryLib|ShellPkg/Library/UefiShellCEntryLib/UefiShellCEntryLib.inf
    LibStdLib|StdLib/LibC/StdLib/StdLib.inf
    LibStdio|StdLib/LibC/Stdio/Stdio.inf
    LibString|StdLib/LibC/String/String.inf
    DevConsole|StdLib/LibC/Uefi/Devices/daConsole.inf
    LibWchar|StdLib/LibC/Wchar/Wchar.inf
    LibUefi|StdLib/LibC/Uefi/Uefi.inf
    LibIIO|StdLib/LibC/Uefi/InteractiveIO/IIO.inf
    ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
    LibLocale|StdLib/LibC/Locale/Locale.inf
    DevUtility|StdLib/LibC/Uefi/Devices/daUtility.inf
    LibContainer|StdLib/LibC/Containers/ContainerLib.inf
    LibTime|StdLib/LibC/Time/Time.inf
    LibGen|StdLib/PosixLib/Gen/LibGen.inf
    LibCType|StdLib/LibC/Ctype/Ctype.inf
    FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
    LibGdtoa|StdLib/LibC/gdtoa/gdtoa.inf
    LibSignal|StdLib/LibC/Signal/Signal.inf
    HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
    SortLib|MdeModulePkg/Library/UefiSortLib/UefiSortLib.inf
    UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
    IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf

[Components]
    GamePkg/Game.inf