package metrics

import (
	"net/http"

	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
)

var packets = prometheus.NewCounter(
	prometheus.CounterOpts{
		Name: "packets_total",
		Help: "Packets processed",
	},
)

func Start() {
	prometheus.MustRegister(packets)
	http.Handle("/metrics", promhttp.Handler())
	http.ListenAndServe(":2112", nil)
}
