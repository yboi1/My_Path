package main

import (
	"fmt"
	"unicode"
)

var (
	LetterCount, digsitCount, otherCount = 0, 0, 0
	tmpChar                              = ""
)

func main() {
	fmt.Scanln(&tmpChar)
	for i := 0; i < len(tmpChar); i++ {
		switch {
		case unicode.IsDigit(rune(tmpChar[i])):
			digsitCount++
		case unicode.IsLetter(rune(tmpChar[i])):
			LetterCount++
		default:
			otherCount++
		}
		// if unicode.IsDigit(rune(tmpChar[i])) {
		// 	digsitCount++
		// } else if unicode.IsLetter(rune(tmpChar[i])) {
		// 	LetterCount++
		// } else {
		// 	otherCount++
		// }
	}
	fmt.Printf(("%d, %d, %d"), digsitCount, LetterCount, otherCount)
}
