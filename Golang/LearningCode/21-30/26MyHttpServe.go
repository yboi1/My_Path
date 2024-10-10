package main

import (
	"fmt"
	"net/http"
)

type Engine struct{}

func (e *Engine) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	switch r.URL.Path {
	case "/":
		{
			fmt.Fprintf(w, "URL.Path : %q\n", r.URL.Path)
		}
	case "/hello":
		{
			for k, v := range r.Header {
				fmt.Fprintf(w, "Header[%q] = %q\n", k, v)
			}
		}
	default:
		{
			fmt.Fprintf(w, "ERROR 404 NOT FOUND %q\n", r.URL.Path)
		}
	}
}

func main() {
	engine := new(Engine)
	http.ListenAndServe(":9999", engine)
}
