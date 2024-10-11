程序执行流程:

1.`r := gee.New()` 首先创建一个Engine对象, 其中包含Router成员, Router对象中包含roots(前缀树)和handler(处理函数)

2.

```
r.GET("/hello/:name", func(c *gee.Context) {
		// expect /hello/geektutu
		c.String(http.StatusOK, "hello %s, you're at %s\n", c.Param("name"), c.Path)
	})
```

注册路由表, 注册get专属的Router node中保存 hello 如果hello 后面跟数据 会自动翻译为name 通过param获得



3.

```
r.GET("/assets/*filepath", func(c *gee.Context) {
		c.JSON(http.StatusOK, gee.H{"filepath": c.Param("filepath")})
	})
```

加入到get 路由表中, 任何包含assets 的路劲, 后面的数据都会被翻译为filepath



分组控制 (Group)

使用GroupRouter包装Router, 在为Router初始化创建时, 添加分组特定的prefix来实现分组, 之后的中间件处理也依赖于prefix来判断 函数的作用范围



中间件处理函数

handle调用时, 不再是直接执行, 而是通过执行顺序将他们加入到handlers 函数数组中, 依次进行执行, 实现了添加自定义函数的功能, 自定义函数是否启用主要取决于他们的后缀
