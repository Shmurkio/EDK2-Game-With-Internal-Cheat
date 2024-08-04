#include "GameCheat.hpp"

EFI_TEXT_CLEAR_SCREEN clr = nullptr;

typedef void (*win_game_t)();

EFI_STATUS EFIAPI efi_text_clear_screen_hook(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *prtc)
{
    /* Clear the shell */
    EFI_STATUS status = clr(prtc);

    /* Scan memory for win_game() function */
    uint64_t address = mem::find_pattern(reinterpret_cast<void *>(reinterpret_cast<uint64_t>(_ReturnAddress()) - 0x1000), 0x5F5E1000, "48 83 EC 28 48 8B 05 ? ? 00 00");

    if (address)
    {
        /* Unhook */
        gST->ConOut->ClearScreen = clr;

        /* Cast address to win_game function and call it to win the game */
        win_game_t win_game = reinterpret_cast<win_game_t>(address);
        win_game();
    }

    return status;
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    clr = gST->ConOut->ClearScreen;
    gST->ConOut->ClearScreen = efi_text_clear_screen_hook;
    
    printf("Note: Cheat will get unloaded after playing the game to avoid loops.\n");

    return EFI_SUCCESS;
}