package dpdk

import "net"

func Send(cmd string) error {
	c, err := net.Dial("unix", "/tmp/dpdk.sock")
	if err != nil {
		return err
	}
	defer c.Close()
	_, err = c.Write([]byte(cmd))
	return err
}
