package router

import (
	"boyi/controllers"

	"github.com/gin-gonic/gin"
)

// 路由组的设置
func SetUpRouter() *gin.Engine {
	r := gin.Default()
	auth := r.Group("/api/auth")
	{
		auth.POST("/login", func(ctx *gin.Context) {
			controllers.Login(ctx)
			// ctx.AbortWithStatusJSON(http.StatusOK, gin.H{
			// 	"message": "Login Ok",
			// })
		})
		auth.POST("register", func(ctx *gin.Context) {
			controllers.Register(ctx)
			// ctx.AbortWithStatusJSON(http.StatusOK, gin.H{
			// 	"message": "Register Ok",
			// })
		})
	}
	return r
}
