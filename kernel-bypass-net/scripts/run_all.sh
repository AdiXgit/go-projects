cd dpdk && make
sudo ./dpdk_app -l 0-1 --vdev=net_null0 &
cd ../go-control && go run cmd/controller/main.go
