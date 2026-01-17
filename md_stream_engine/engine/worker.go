package engine

func (e *Engine) Start(proc Processor) {
	for i := 0; i < e.workers; i++ {
		e.wg.Add(1)
		go func() {
			defer e.wg.Done()
			for {
				select {
				case <-e.ctx.Done():
					return
				case t := <-e.input:
					e.output <- proc(t)
				}
			}
		}()
	}
}
