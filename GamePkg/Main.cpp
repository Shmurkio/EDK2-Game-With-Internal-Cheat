#include "Game.hpp"

void *win_game_address = nullptr; // Required for cheat

namespace game
{
    int player_row = 0, player_col = 0;

    void clr()
    {
        gST->ConOut->ClearScreen(gST->ConOut);
    }

    void disable_cursor()
    {
        gST->ConOut->EnableCursor(gST->ConOut, false);
    }

    void enable_cursor()
    {
        gST->ConOut->EnableCursor(gST->ConOut, true);
    }

    void set_pos(int col, int row)
    {
        gST->ConOut->SetCursorPosition(gST->ConOut, col, row);
    }

    void print_map(std::vector<std::vector<char>>& map)
    {
        for (const auto& row : map)
        {
            for (char cell : row)
            {
                printf("%c ", cell);
            }
            
            printf("\n");
        }
    }

    void lose_game()
    {
        clr();
        set_pos(0, 0);
        enable_cursor();
        printf("Youd died! RIP!\n");
        exit(0);
    }

    void win_game()
    {
        clr();
        set_pos(0, 0);
        enable_cursor();
        printf("You won!\n");
        exit(0);
    }

    void move_player(char direction, std::vector<std::vector<char>>& map)
    {
        int new_row= player_row, new_col = player_col;

        switch (direction)
        {
        case 'w': // Up
            new_row--;
            break;
        case 's': // Down
            new_row++;
            break;
        case 'a': // Left
            new_col--;
            break;
        case 'd': // Right
            new_col++;
            break;
        default:
            return;
        }

        if (new_row < 0 || new_row >= map.size() || new_col < 0 || new_col >= map[0].size() || map[new_row][new_col] == '#') // Return if field is a wall (#)
        {
            return;
        }

        map[player_row][player_col] = '.';

        player_row = new_row;
        player_col = new_col;

        if (map[player_row][player_col] == ' ') // Lose if field is a hole ( )
        {
            lose_game();
        }
        else if (map[player_row][player_col] == 'X') // Win if field is treasure (X)
        {
            win_game();
        }
        

        map[player_row][player_col] = '*';

        set_pos(0, 1);
        print_map(map);
    }

    void cancel_game()
    {
        clr();
        set_pos(0, 0);
        enable_cursor();
        printf("Game canceled!\n");
    }

    void start_game(std::vector<std::vector<char>>& map)
    {
        clr();
        disable_cursor();
        set_pos(0, 0);
        printf("'*' = Player, '.' = Path, '#' = Wall, ' ' = Hole, , 'X' = Treasure [Esc = Exit]");
        set_pos(0, 1);
        map[0][0] = '*';
        print_map(map);

        EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *con_in_ex = nullptr;
        EFI_STATUS status = gBS->HandleProtocol(gST->ConsoleInHandle, &gEfiSimpleTextInputExProtocolGuid, reinterpret_cast<void **>(&con_in_ex));

        if (EFI_ERROR(status))
        {
            return;
        }

        EFI_INPUT_KEY key;
        EFI_KEY_DATA key_data;

        for (;;)
        {
            status = con_in_ex->ReadKeyStrokeEx(con_in_ex, &key_data);

            if (status == EFI_SUCCESS)
            {
                key = key_data.Key;

                if (key.UnicodeChar == L'w' || key.UnicodeChar == L'd' || key.UnicodeChar == L's' || key.UnicodeChar == L'a')
                {
                    move_player(static_cast<char>(key.UnicodeChar), map);
                }
                else if (key.ScanCode == SCAN_ESC)
                {
                    cancel_game();
                    break;
                }
            }
        }
    }
}

int main()
{
    win_game_address = reinterpret_cast<void *>(game::win_game); // Required for cheat

    std::vector<std::vector<char>> map = 
    {
        {'.', '.', '.', '#', '#', '.', '.', '.', '.', '.'},
        {'.', '#', '.', '.', '.', '.', '#', '.', '.', '.'},
        {'#', '.', '.', ' ', '#', '.', '.', '.', '.', '.'},
        {'#', '.', '.', '.', '.', ' ', '.', '#', '.', '.'},
        {'.', ' ', '#', '.', '#', '.', ' ', '.', '.', '.'},
        {'.', '.', '.', '#', '.', '.', '.', '#', '.', '.'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '#', '.', '.', '#', '.', ' ', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', 'X'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}
    };

    game::start_game(map);

    return 0;
}