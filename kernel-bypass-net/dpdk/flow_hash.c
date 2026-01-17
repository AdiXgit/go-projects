#include <rte_mbuf.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_tcp.h>
#include <rte_udp.h>

uint32_t flow_hash(struct rte_mbuf *m)
{
    struct rte_ether_hdr *eth = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
    if (eth->ether_type != rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4))
        return 0;

    struct rte_ipv4_hdr *ip = (struct rte_ipv4_hdr *)(eth + 1);
    uint32_t h = ip->src_addr ^ ip->dst_addr ^ ip->next_proto_id;

    if (ip->next_proto_id == IPPROTO_TCP)
    {
        struct rte_tcp_hdr *tcp = (void *)(ip + 1);
        h ^= tcp->src_port ^ tcp->dst_port;
    }
    else if (ip->next_proto_id == IPPROTO_UDP)
    {
        struct rte_udp_hdr *udp = (void *)(ip + 1);
        h ^= udp->src_port ^ udp->dst_port;
    }
    return h;
}
