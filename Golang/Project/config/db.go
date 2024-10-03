package config

import (
	"boyi/global"
	"log"
	"time"

	"gorm.io/driver/mysql"
	"gorm.io/gorm"
)

// 完成数据库初始化操作, 连接数据库
func initDB() {
	dsn := AppConfig.Database.Dsn // 数据库连接配置
	db, err := gorm.Open(mysql.Open(dsn), &gorm.Config{})
	if err != nil {
		log.Fatalf("Failed to init database, err: %v", err)
	}

	sqlDB, err := db.DB()
	if err != nil {
		log.Fatalf("Failed to config database, err: %v", err)
	}

	sqlDB.SetMaxIdleConns(AppConfig.Database.MaxIdleConns) // 连接池中最大空闲数量
	sqlDB.SetMaxOpenConns(AppConfig.Database.MaxOpenConns) // 最大连接数量
	sqlDB.SetConnMaxLifetime(time.Hour)                    // 最大连接时间

	global.Db = db
}
