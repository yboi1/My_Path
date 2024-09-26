package router

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func SetUpRouter() *gin.Engine {
	r := gin.Default()
	auth := r.Group("/api/auth")
	{
		auth.POST("/login", func(ctx *gin.Context) {
			ctx.AbortWithStatusJSON(http.StatusOK, gin.H{
				"message": "Login Ok",
			})
		})
		auth.POST("register", func(ctx *gin.Context) {
			ctx.AbortWithStatusJSON(http.StatusOK, gin.H{
				"message": "Register Ok",
			})
		})
	}
	return r
}
