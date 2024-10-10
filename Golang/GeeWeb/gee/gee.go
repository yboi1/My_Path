package gee

import (
	"fmt"
	"net/http"
)

type HandleFunc func(http.ResponseWriter, *http.Request)

type Engine struct {
	Router map[string]HandleFunc
}

func New() *Engine {
	return &Engine{Router: make(map[string]HandleFunc)}
}

func (e *Engine) addRouter(method string, pattern string, handler HandleFunc) {
	key := method + "-" + pattern
	e.Router[key] = handler
}

func (e *Engine) GET(pattern string, handler HandleFunc) {
	e.addRouter("GET", pattern, handler)
}

func (e *Engine) POST(pattern string, handler HandleFunc) {
	e.addRouter("POST", pattern, handler)
}

func (e *Engine) Run(addr string) error {
	return http.ListenAndServe(addr, e)
}

func (e *Engine) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	key := r.Method + "-" + r.URL.Path
	if handler, ok := e.Router[key]; ok {
		handler(w, r)
	} else {
		fmt.Fprintf(w, "404 NOT FOUND: %s\n", r.URL.Path)
	}
}
