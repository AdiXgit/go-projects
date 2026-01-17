#include <rte_mempool.h>
#include <rte_lcore.h>

#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250

struct rte_mempool *create_mempool_numa(
    const char *name,
    unsigned socket_id)
{
    return rte_pktmbuf_pool_create(
        name,
        NUM_MBUFS,
        MBUF_CACHE_SIZE,
        0,
        RTE_MBUF_DEFAULT_BUF_SIZE,
        socket_id);
}
