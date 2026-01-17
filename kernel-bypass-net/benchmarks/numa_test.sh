lscpu | grep NUMA
sudo ./dpdk_app -l 0-1 --socket-mem=1024 --vdev=net_null0
