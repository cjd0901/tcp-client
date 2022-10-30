package main

import (
	"fmt"
	"io"
	"net"
)

func handleConn(conn net.Conn) {
	defer conn.Close()
	for {
		buffer := make([]byte, 1024)
		n, err := conn.Read(buffer)
		if err != nil {
			if err == io.EOF {
				return
			}
			fmt.Println(err)
			panic("read error")
		}
		fmt.Println(n, string(buffer[:n]))
		resp := []byte("hello from go server\n")
		_, err = conn.Write(resp)
		if err != nil {
			fmt.Println(err)
			panic("write error")
		}
	}
}

func main() {
	l, err := net.Listen("tcp", ":10000")
	if err != nil {
		panic("listen error")
	}
	for {
		conn, err := l.Accept()
		fmt.Println("conn established")
		if err != nil {
			panic("accept error")
		}
		go handleConn(conn)
	}
}
