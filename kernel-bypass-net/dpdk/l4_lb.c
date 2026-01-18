#include "l4_lb.h"

struct backend backends[MAX_BACKENDS] = {
    {0x0100000A, 8080}, // 10.0.0.1
    {0x0200000A, 8080}, // 10.0.0.2
};

uint16_t backend_count = 2;

uint16_t select_backend(uint32_t hash)
{
    return hash % backend_count;
}
