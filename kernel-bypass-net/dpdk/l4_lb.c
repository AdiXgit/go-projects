#include <stdint.h>

#define MAX_BACKENDS 4

uint16_t select_backend(uint32_t hash)
{
    return hash % MAX_BACKENDS;
}
