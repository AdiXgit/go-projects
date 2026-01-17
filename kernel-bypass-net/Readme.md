# Kernel-Bypass Network Service (Go + DPDK)

A NUMA-aware, kernel-bypass packet processing system using DPDK
with a Go control plane, traffic generators, and observability.

Designed and tested on WSL2 (vdev mode), production-ready for
bare-metal Linux.

## Features
- DPDK poll-mode RX/TX
- L4 load balancing (hash-based)
- NUMA-aware memory pools
- Go gRPC control plane
- Prometheus metrics
- Custom traffic generator
