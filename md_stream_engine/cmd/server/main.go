package main

import (
	"log"
	"net"
	"time"

	"google.golang.org/grpc"

	"md_stream_engine/engine"
	"md_stream_engine/grpcserver"
	pb "md_stream_engine/proto"
	"md_stream_engine/types"
)

func main() {
	// 1️⃣ Create engine
	eng := engine.New(engine.Config{
		Workers: 4,
		Buffer:  1024,
	})

	eng.Start(func(t types.Tick) types.Result {
		return types.Result{
			Symbol: t.Symbol,
			Value:  t.Price * float64(t.Volume),
		}
	})

	// 2️⃣ Start fake market feed
	go func() {
		for {
			eng.Ingest(types.Tick{
				Symbol: "AAPL",
				Price:  150.0,
				Volume: 10,
				Ts:     time.Now().UnixNano(),
			})
			time.Sleep(500 * time.Millisecond)
		}
	}()

	// 3️⃣ Create listener EXPLICITLY
	lis, err := net.Listen("tcp", ":50051")
	if err != nil {
		log.Fatalf("❌ failed to listen: %v", err)
	}

	log.Println("✅ gRPC server listening on :50051")

	// 4️⃣ Start gRPC server in main thread
	grpcSrv := grpc.NewServer()
	pb.RegisterMDStreamServer(grpcSrv, grpcserver.New(eng))

	if err := grpcSrv.Serve(lis); err != nil {
		log.Fatalf("❌ gRPC server failed: %v", err)
	}
}
