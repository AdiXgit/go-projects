package main

import (
	"kernel-bypass/go-control/internal/api"
	"kernel-bypass/go-control/internal/metrics"
	"log"
)

func main() {
	go metrics.Start()
	api.Start()
	log.Println("Control plane running")
	select {}
}
