/*H**********************************************************************
* FILENAME :    go_example.go
*
* DESCRIPTION :
*       Exhibits fuctionality of GO
*
* NOTES :
*       Need to install Google GO to system before you may compile
* 
* AUTHOR :    Brandon Pirtle        START DATE :    4 Jul 15
*                                   EDIT  DATE :   13 Dec 17
*
*H*/

// Go is an expressive, concurrent, garbage-collecting programming language.
// Go is a compiled language.
// Go has polymorphic functions.
// Go is typed functional programming.
// Go has easy to use multi-threading.

package main

import("fmt"   // formatted I/O
       "math") // math I hope

// func (name) (arguments) (return types) {}
func dat_math(x int) int {
    return x + 1
}

func double_return(x int, y float64) (int, float64){
    x = 10
    y = 100
    return x, y // returning 2 seperate values
}

func main() {
    fmt.Printf("Hello, world!\n")
    x := 0 // := for declaration
    fmt.Println("x is", x) // had to use Println for variable
    x = dat_math(x)
    fmt.Println("x after being passed into dat_math is", x)
    fmt.Println("x after being passed into dat_math again is", dat_math(x))
    y := -7.0
    fmt.Println("Absolute value of", y, "is", math.Abs(y))
    x, y = double_return(x, y) // assigning 2 variables values from function
    fmt.Printf("After double_return was called:\n")
    fmt.Println("x =", x, "\ny =", y)
}