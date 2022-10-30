package main

import (
	"fmt"
	"net"
)

func main() {
	conn, err := net.Dial("tcp", "localhost:10000")
	if err != nil {
		fmt.Println(err)
		panic("dial error")
	}
	defer conn.Close()
	data := []byte("message from go client")
	_, err = conn.Write(data)
	if err != nil {
		panic("write error")
	}

	buffer := make([]byte, 1024)
	n, err := conn.Read(buffer)
	if err != nil {
		panic("read error")
	}
	fmt.Println(n, string(buffer[:n]))
}
