package main

import (
    "fmt"
    "math"
    "math/rand/v2"
)


func main() {
    x1 := rand.IntN(100)
    y1 := rand.IntN(100)
    y2 := rand.IntN(100)
    x2 := rand.IntN(100)
    d := math.Sqrt(math.Pow(float64(x2-x1), 2)+math.Pow(float64(y2-y1), 2))
    fmt.Print("x1: ", x1, "\n")
    fmt.Print("x2: ", x2, "\n")
    fmt.Print("y1: ", y1, "\n")
    fmt.Print("y2: ", y2, "\n")
    
    fmt.Print("Distancia: ")
    fmt.Print(d)
}