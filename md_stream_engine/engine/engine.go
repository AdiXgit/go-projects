package engine

import (
	"context"
	"sync"

	"md_stream_engine/types"
)

type Processor func(types.Tick) types.Result

type Config struct {
	Workers int
	Buffer  int
}

type Engine struct {
	input   chan types.Tick
	output  chan types.Result
	ctx     context.Context
	cancel  context.CancelFunc
	wg      sync.WaitGroup
	workers int
}
