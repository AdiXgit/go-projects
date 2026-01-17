#ifndef DPDK_H
#define DPDK_H

#include <rte_mbuf.h>
#include <stdint.h>

uint32_t flow_hash(struct rte_mbuf *mbuf);
uint16_t select_backend(uint32_t hash);

#endif
