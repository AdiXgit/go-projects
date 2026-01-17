package grpcserver

import (
	"net"

	pb "md_stream_engine/proto"

	"google.golang.org/grpc"
)

func Start(addr string, srv *Server) error {
	lis, err := net.Listen("tcp", addr)
	if err != nil {
		return err
	}

	g := grpc.NewServer()
	pb.RegisterMDStreamServer(g, srv)
	return g.Serve(lis)
}
