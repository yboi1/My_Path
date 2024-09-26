package main

import (
	"fmt"

	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/mysql"
)

type Model struct {
	ID   int64
	Name string `gorm:"default:'boyi'"`
	Age  int64
	// CreateAt	time.Time
	// UpdateAt	time.Time
	// DeleteAt	gorm.DeletedAt `gorm:"index"`
}

func main() {
	db, err := gorm.Open("mysql", "root:root1234@(127.0.0.1:13306)/db1?charset=utf8mb4&parseTime=True&loc=Local")
	if err != nil {
		panic(err)
	}
	defer db.Close()

	db.AutoMigrate(&Model{})

	model := Model{Name: "bo", Age: 18}
	db.NewRecord(model) // 判断主键是否存在
	db.Create(&model)   // 创建
	db.NewRecord(model)

	model2 := Model{Name: "yi", Age: 20}
	db.NewRecord(model) // 判断主键是否存在
	db.Create(&model2)  // 创建
	db.NewRecord(model)

	// 为Instert语句添加扩展SQL选项
	// db.Set("gorm:insert_option", "ON CONFLICT").Create(&model2)
	// INSERT INTO products (name, code) VALUES ("name", "code") ON CONFLICT;

	db.First(&model)
	fmt.Println(model)

	db.Take(&model)
	fmt.Println(model)

	db.Last(&model)
	fmt.Println(model)

	var models Model
	db.First(&models, 2)
	fmt.Println(models)

	db.Where("name = ?", "bo").First(&model)
	fmt.Println(model)
}
