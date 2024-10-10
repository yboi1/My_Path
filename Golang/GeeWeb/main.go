package main

import (
	"fmt"
	"gee"
	"net/http"
)

func main() {
	r := gee.New()
	r.GET("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "URL.Path:%q\n", r.URL.Path)
	})
	r.GET("/hello", func(w http.ResponseWriter, r *http.Request) {
		for k, v := range r.Header {
			fmt.Fprintf(w, "Header[%q] is %q\n", k, v)
		}
	})
	r.GET("/boyi", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "Hello Boyi This Is My First Web\n")
	})
	r.Run(":9999")
}
