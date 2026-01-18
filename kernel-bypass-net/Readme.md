# Kernel Bypass L4 Load Balancer (DPDK + Go)

A minimal **kernel-bypass L4 load balancer** built using **DPDK (C)** for the data plane and **Go** for the control plane.  
The project demonstrates **userspace packet processing**, **stateless load balancing**, and **runtime control hooks**, validated using a custom traffic generator.

* * *

## Features

*   Kernel-bypass packet processing using **DPDK**
    
*   Poll-mode RX/TX (no kernel networking stack)
    
*   Stateless **L4 load balancing** (IPv4 + TCP/UDP)
    
*   5-tuple hashing for backend selection
    
*   Destination IP & port rewrite
    
*   Drop logic for traffic control
    
*   Live RX/TX/DROP packet counters
    
*   Custom UDP traffic generator
    
*   Runs on **WSL** using DPDK virtual device (`net_null`)
    

* * *

## Project Structure

`kernel-bypass-net/ ├── dpdk/ │   ├── main.c          # DPDK data plane (L4 load balancer) │   ├── l4_lb.c/h       # Backend table & selection logic │   ├── flow_hash.c    # 5-tuple hash │   ├── metrics.c/h    # RX / TX / DROP counters │   ├── numa.c/h       # NUMA-aware mempool creation │   ├── config.c/h     # Drop control flag │   ├── Makefile │ ├── traffic-generator/ │   ├── udp_gen.c      # High-rate UDP traffic generator │   ├── tcp_gen.go     # TCP traffic generator (optional) │   ├── Makefile │ ├── go-control/ │   └── controller/ │       └── main.go    # Simple Go control plane (REST API) │ └── README.md`

* * *

## Requirements

*   Linux / WSL2
    
*   DPDK (built from source)
    
*   GCC
    
*   Go (>= 1.20)
    

* * *

## Build & Run (WSL)

### 1\. Build DPDK Application

`cd dpdk make`

### 2\. Run DPDK Data Plane

`sudo ./dpdk_app -l 0-1 --vdev=net_null0 --no-huge`

Expected output:

`lcore=0 socket=0 [STATS] RX_PPS=XXXXX TX_PPS=XXXXX DROP=0`

* * *

### 3\. Run Traffic Generator (New Terminal)

`cd traffic-generator make ./udp_gen`

This sends UDP packets as fast as possible (no output by design).

* * *

### 4\. Verify System Behavior

`top`

You should see:

*   `dpdk_app` ~100% CPU
    
*   `udp_gen` ~100% CPU
    

This confirms poll-mode kernel-bypass behavior.

* * *

## Testing Drop Logic

Edit:

`dpdk/config.c`

`int drop_enabled = 1;`

Rebuild and run again.

Expected stats:

`[STATS] RX_PPS=40000 TX_PPS=0 DROP=40000`

Set `drop_enabled = 0` to disable dropping.

* * *

## Load Balancing Logic

*   Packets are hashed using a 5-tuple hash
    
*   Backend selected via modulo
    
*   Destination IP and L4 port rewritten
    
*   Stateless (no connection tracking)
    

Example backends:

`10.0.0.1:8080 10.0.0.2:8080`

* * *

## Control Plane (Go)

A minimal Go REST server provides hooks for:

*   Enabling/disabling drops
    
*   Adding/removing backends (extensible)
    

Run:

`cd go-control go run ./controller`

* * *

## Notes

*   `net_null` is used for functional testing on WSL
    
*   Packets do not leave the host (expected)
    
*   Same data plane runs on bare-metal Linux with real NICs
    

* * *

## What This Demonstrates

*   Understanding of kernel-bypass networking
    
*   High-performance packet processing
    
*   L4 load balancer internals
    
*   Separation of data plane and control plane
    
*   Systems-level debugging and validation
    

* * *

## Future Extensions

*   Live backend management via Go control plane
    
*   Health checks
    
*   Maglev / consistent hashing
    
*   Rate limiting
    
*   Bare-metal NIC deployment
