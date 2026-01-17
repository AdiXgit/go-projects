package grpcserver

import (
	"md_stream_engine/engine"
	pb "md_stream_engine/proto"
)

type Server struct {
	pb.UnimplementedMDStreamServer
	engine *engine.Engine
}

func New(engine *engine.Engine) *Server {
	return &Server{engine: engine}
}

func (s *Server) StreamResults(
	req *pb.SubscribeRequest,
	stream pb.MDStream_StreamResultsServer,
) error {
	for res := range s.engine.Output() {
		err := stream.Send(&pb.Result{
			Symbol: res.Symbol,
			Value:  res.Value,
		})
		if err != nil {
			return err
		}
	}
	return nil
}
