#ifndef NUMA_H
#define NUMA_H

#include <rte_mempool.h>

struct rte_mempool *create_mempool_numa(
    const char *name,
    unsigned socket_id);

#endif
