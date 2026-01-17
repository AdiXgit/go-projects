package engine

import (
	"context"
	"md_stream_engine/types"
)

func New(cfg Config) *Engine {
	ctx, cancel := context.WithCancel(context.Background())
	return &Engine{
		input:   make(chan types.Tick, cfg.Buffer),
		output:  make(chan types.Result, cfg.Buffer),
		ctx:     ctx,
		cancel:  cancel,
		workers: cfg.Workers,
	}
}

func (e *Engine) Ingest(t types.Tick) {
	e.input <- t
}

func (e *Engine) Output() <-chan types.Result {
	return e.output
}

func (e *Engine) Stop() {
	e.cancel()
	e.wg.Wait()
	close(e.output)
}
