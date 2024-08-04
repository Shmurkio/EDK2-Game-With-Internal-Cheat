#pragma once

#include <stdint.h>

#define IN_RANGE(x, a, b) (x >= a && x <= b)
#define GET_BITS(x) (IN_RANGE((x&(~0x20)),'A','F')?((x&(~0x20))-'A'+0xA):(IN_RANGE(x,'0','9')?x-'0':0))
#define GET_BYTE(a, b) (GET_BITS(a) << 4 | GET_BITS(b))

namespace mem
{
    uint64_t find_pattern(void *base_address, uint64_t size, const char *pattern)
    {
        uint8_t *first_match = nullptr;
        const char *current_pattern = pattern;
        uint8_t *start = static_cast<uint8_t *>(base_address);
        uint8_t *end = start + size;

        for (uint8_t *current = start; current < end; current++)
        {
            uint8_t byte = current_pattern[0];

            if (!byte)
            {
                return reinterpret_cast<uint64_t>(first_match);
            }

            if (byte == '\?' || *static_cast<uint8_t *>(current) == GET_BYTE(byte, current_pattern[1]))
            {
                if (!first_match)
                {
                    first_match = current;
                }

                if (!current_pattern[2])
                {
                    return reinterpret_cast<uint64_t>(first_match);
                }

                if (byte == '\?')
                {
                    current_pattern += 2;
                }
                else
                {
                    current_pattern += 3;
                }
            }
            else
            {
                current_pattern = pattern;
                first_match = nullptr;
            }
        }

        return 0;
    }
}