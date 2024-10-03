package main

import (
	"log"
	"net/http"
)

type server int

func (h *server) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	log.Println(r.URL.Path)
	log.Println("have a new connect") // log 是给服务器端端反馈
	w.Write([]byte("hello world!"))   // w 是给客户端的反馈
}

func main() {
	var s server
	http.ListenAndServe("localhost:9999", &s)
}
