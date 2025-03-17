package main

import (
	"fmt"
	"math/rand/v2"
)

func main() {
	x1 := rand.IntN(4)
	y1 := 0
	x2 := 0
	y2 := rand.IntN(4)
	fmt.Print("x1: ", x1, "\n")
	fmt.Print("y2: ", y2, "\n")

	b := x2 + y2
	fmt.Print("b: ", b, "\n")

	a := (b + y1) / x1
	fmt.Print("a: ", a, "\n")
}
