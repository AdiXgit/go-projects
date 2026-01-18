#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <rte_eal.h>
#include <rte_ethdev.h>
#include <rte_lcore.h>

#include "dpdk.h"
#include "numa.h"
#include "metrics.h"

#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_udp.h>
#include <rte_tcp.h>
#include "l4_lb.h"
#define RX_RING 1024
#define TX_RING 1024
#define BURST 32

static inline uint64_t now_sec()
{
    return time(NULL);
}

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

    rte_eth_rx_queue_setup(port, 0, RX_RING, socket, NULL, mp);
    rte_eth_tx_queue_setup(port, 0, TX_RING, socket, NULL);

    rte_eth_dev_start(port);

    struct rte_mbuf *bufs[BURST];

    while (1)
    {
        uint16_t n = rte_eth_rx_burst(port, 0, bufs, BURST);
        packets_rx += n;

        for (int i = 0; i < n; i++)
        {
            struct rte_mbuf *m = bufs[i];

            /* DROP LOGIC — CONTROL PLANE HOOK */
            if (drop_enabled)
            {
                packets_dropped++;
                rte_pktmbuf_free(m);
                continue;
            }

            uint32_t h = flow_hash(m);

            struct rte_ether_hdr *eth =
                rte_pktmbuf_mtod(m, struct rte_ether_hdr *);

            if (eth->ether_type != rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4))
                goto send;

            struct rte_ipv4_hdr *ip =
                (struct rte_ipv4_hdr *)(eth + 1);

            uint16_t backend = select_backend(h);
            struct backend *b = &backends[backend];

            /* Rewrite destination IP */
            ip->dst_addr = b->ip;

            /* Rewrite L4 destination port */
            if (ip->next_proto_id == IPPROTO_UDP)
            {
                struct rte_udp_hdr *udp =
                    (struct rte_udp_hdr *)((uint8_t *)ip + sizeof(*ip));
                udp->dst_port = rte_cpu_to_be_16(b->port);
            }
            else if (ip->next_proto_id == IPPROTO_TCP)
            {
                struct rte_tcp_hdr *tcp =
                    (struct rte_tcp_hdr *)((uint8_t *)ip + sizeof(*ip));
                tcp->dst_port = rte_cpu_to_be_16(b->port);
            }

        send:
            rte_eth_tx_burst(port, 0, &m, 1);
            packets_tx++;
        }
    }
}
