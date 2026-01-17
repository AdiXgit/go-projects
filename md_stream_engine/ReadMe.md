# MD Stream Engine

A **high‑performance, concurrent market‑data streaming engine** written in **Go**, exposing a **gRPC streaming API** that can be consumed by **Python clients**.

This project demonstrates how real‑world trading and data‑engineering systems separate:

*   a fast **data plane** (Go)
    
*   from a flexible **strategy / analysis plane** (Python)
    

* * *

## 🚀 What This Project Does

*   Generates market‑data ticks (simulated)
    
*   Processes them concurrently using a **worker pool** in Go
    
*   Streams processed results to clients via **gRPC**
    
*   Allows **Python clients** to subscribe and consume results in real time
    

* * *

## 🧠 Architecture Overview

    Market Feed  →  Go Engine (workers & channels)
                      ↓
                 gRPC Streaming Server
                      ↓
                 Python Client (strategy / ML)
    

*   **Go** handles throughput, concurrency, and networking
    
*   **Python** focuses on analysis, strategy, or ML
    

* * *

## 📂 Project Structure

    md_stream_engine/
    ├── cmd/server/        # Server entry point
    ├── engine/            # Core concurrent processing engine
    ├── grpcserver/        # gRPC server implementation
    ├── proto/             # Protobuf contract + generated code
    ├── types/             # Shared domain types
    ├── python_client/     # Python gRPC client
    ├── go.mod
    └── go.sum
    

* * *

## ⚙️ Prerequisites

### In WSL / Linux

*   Go (≥ 1.22)
    
*   Python 3.10+
    
*   protoc (Protocol Buffers compiler)
    

* * *

## ▶️ How to Run

### 1️⃣ Start the Go server (WSL)

    cd md_stream_engine
    go run cmd/server/main.go
    

You should see:

    ✅ gRPC server listening on :50051
    

* * *

### 2️⃣ Run the Python client

    cd python_client
    python3 -m venv .venv
    source .venv/bin/activate
    pip install grpcio grpcio-tools
    python client.py
    

Expected output:

    [PY] AAPL -> 1500
    [PY] AAPL -> 1500
    

* * *

## 📡 gRPC API (Simplified)

    service MDStream {
      rpc StreamResults(SubscribeRequest)
          returns (stream Result);
    }
    

*   Client subscribes once
    
*   Server continuously pushes results
    

* * *

## 🧩 Key Concepts Demonstrated

*   Go concurrency (goroutines, channels, worker pools)
    
*   Backpressure via bounded channels
    
*   gRPC streaming (server → client)
    
*   Protobuf as a language‑agnostic contract
    
*   Go ↔ Python interoperability
    
*   Clean separation of concerns
    

* * *

## 🎯 Why This Project Matters

This architecture mirrors **real trading systems**, **telemetry pipelines**, and **distributed analytics engines**, where:

*   performance‑critical code runs in Go/C++
    
*   strategies and analytics run in Python
    

* * *

## 🛣 Future Extensions (Optional)

*   Bidirectional gRPC (orders from Python → Go)
    
*   Latency metrics (p50 / p99)
    
*   Real market data feeds
    
*   Docker / Kubernetes deployment
    

* * *

## 📌 Status

**v0.1 — Streaming engine fully functional**

* * *

## 👤 Author

Built as a systems‑engineering learning project focusing on concurrency, networking, and real‑world infrastructure design.
