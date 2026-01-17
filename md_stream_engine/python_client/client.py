import grpc
import mdstream_pb2
import mdstream_pb2_grpc

def main():
    channel = grpc.insecure_channel("localhost:50051")
    stub = mdstream_pb2_grpc.MDStreamStub(channel)

    for res in stub.StreamResults(mdstream_pb2.SubscribeRequest()):
        print(f"[PY] {res.symbol} -> {res.value}")

if __name__ == "__main__":
    main()
