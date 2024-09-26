package main

import (
	"boyi/config"
	"boyi/router"
)

func main() {
	config.InitConfig()
	r := router.SetUpRouter()
	r.Run(config.AppConfig.App.Port)
}
