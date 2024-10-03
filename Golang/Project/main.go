package main

import (
	"boyi/config"
	"boyi/router"
)

func main() {
	config.InitConfig()              // 完成数据库等初始化工作
	r := router.SetUpRouter()        // 路由接收
	r.Run(config.AppConfig.App.Port) // 启动服务
}
