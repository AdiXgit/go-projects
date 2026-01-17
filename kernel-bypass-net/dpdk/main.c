#include <stdio.h>
#include <unistd.h>
#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_lcore.h>
#include "dpdk.h"
#include "numa.h"

#define RX_RING 1024
#define TX_RING 1024
#define BURST 32

extern uint64_t packets_rx;
extern uint64_t packets_tx;

int main(int argc, char **argv)
{
    rte_eal_init(argc, argv);

    uint16_t port = 0;
    unsigned lcore = rte_lcore_id();
    unsigned socket = rte_lcore_to_socket_id(lcore);

    printf("lcore=%u socket=%u\n", lcore, socket);

    struct rte_mempool *mp = create_mempool_numa("MBUF", socket);

    struct rte_eth_conf conf = {0};
    rte_eth_dev_configure(port, 1, 1, &conf);
    rte_eth_rx_queue_setup(port, 0, RX_RING,
                           socket, NULL, mp);
    rte_eth_tx_queue_setup(port, 0, TX_RING,
                           socket, NULL);
    rte_eth_dev_start(port);

    struct rte_mbuf *bufs[BURST];

    while (1)
    {
        uint16_t n = rte_eth_rx_burst(port, 0, bufs, BURST);
        packets_rx += n;

        for (int i = 0; i < n; i++)
        {
            uint32_t h = flow_hash(bufs[i]);
            uint16_t backend = select_backend(h);
            (void)backend;
            rte_eth_tx_burst(port, 0, &bufs[i], 1);
            packets_tx++;
        }
    }
}
