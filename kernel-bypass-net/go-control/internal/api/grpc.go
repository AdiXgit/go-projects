package api

import (
	"log"
	"net"

	"google.golang.org/grpc"
)

func Start() {
	l, _ := net.Listen("tcp", ":50051")
	s := grpc.NewServer()
	log.Println("gRPC on :50051")
	s.Serve(l)
}
