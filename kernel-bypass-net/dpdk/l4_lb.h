#ifndef L4_LB_H
#define L4_LB_H

#include <stdint.h>

#define MAX_BACKENDS 16

struct backend
{
    uint32_t ip;   // network byte order
    uint16_t port; // network byte order
};

extern struct backend backends[MAX_BACKENDS];
extern uint16_t backend_count;

uint16_t select_backend(uint32_t hash);

#endif
