package main

import (
	"fmt"
	"math"
)

func main() {
	a := IntFromFloat64(1111111111111111111111111111111111111)
	fmt.Println(a)

}

func IntFromFloat64(x float64) int {
	if math.MinInt32 <= x && x <= math.MaxInt64 {
		whole, fraction := math.Modf(x)
		if fraction >= 0.5 {
			whole++
		}
		return int(whole)
	}
	panic(fmt.Sprintf("%g is out of the int32 range", x))
}
