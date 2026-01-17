package main

import (
	"net"
)

func main() {
	for {
		c, _ := net.Dial("tcp", "127.0.0.1:9000")
		go func() {
			buf := make([]byte, 128)
			for {
				c.Write(buf)
			}
		}()
	}
}
