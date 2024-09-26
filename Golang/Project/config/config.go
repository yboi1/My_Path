package config

import (
	"fmt"

	"github.com/spf13/viper"
)

type Config struct {
	App struct {
		Name string
		Port string
	}
	Database struct {
		Dsn          string
		MaxIdleConns int
		MaxOpenConns int
	}
}

var AppConfig *Config

func InitConfig() {
	viper.SetConfigName("config")
	viper.SetConfigType("yml")
	viper.AddConfigPath("./config")

	if err := viper.ReadInConfig(); err != nil {
		fmt.Printf("ReadInConfig error : %v\n", err)
	}

	AppConfig = &Config{}

	if err := viper.Unmarshal(&AppConfig); err != nil {
		fmt.Printf("Unmarshal	 error : %v\n", err)
	}

	initDB()

}
