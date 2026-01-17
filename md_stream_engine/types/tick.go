package types

type Tick struct {
	Symbol string
	Price  float64
	Volume int64
	Ts     int64
}
