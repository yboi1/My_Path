// package main

// import (
// 	"fmt"

// 	"github.com/jinzhu/gorm"
// 	_ "github.com/jinzhu/gorm/dialects/mysql"
// )

// // UserInfo 用户信息
// type UserInfo struct {
// 	ID     uint
// 	Name   string
// 	Gender string
// 	Hobby  string
// }

// func main() {
// 	db, err := gorm.Open("mysql", "root:root1234@(127.0.0.1:13306)/db1?charset=utf8mb4&parseTime=True&loc=Local")
// 	if err != nil {
// 		panic(err)
// 	}
// 	defer db.Close()

// 	// 自动迁移
// 	db.AutoMigrate(&UserInfo{})

// 	u1 := UserInfo{1, "七米", "男", "篮球"}
// 	u2 := UserInfo{2, "沙河娜扎", "女", "足球"}
// 	u3 := UserInfo{3, "boyi", "男", "编程"}
// 	// 创建记录
// 	db.Create(&u1)
// 	db.Create(&u2)
// 	db.Create(&u3)
// 	// 查询
// 	var u = new(UserInfo)
// 	db.First(u)
// 	fmt.Printf("%#v\n", u)

// 	var uu UserInfo
// 	db.Find(&uu, "hobby=?", "足球")
// 	fmt.Printf("%#v\n", uu)

// 	var sec UserInfo
// 	db.Find(&sec, "id=?", "3")
// 	fmt.Printf("%#v\n", sec)

// 	// 更新
// 	db.Model(&u).Update("hobby", "双色球")
// 	// 删除
// 	db.Delete(&u)
// 	db.Delete(&uu)
// 	db.Delete(&sec)
// }
