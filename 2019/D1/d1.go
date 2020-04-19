package d1

import (
	"AdventOfCode/utils"
	"fmt"
	"io/ioutil"
	"math"
)

// Compute -> Do whatwe
func Compute() {

	/*
		Fuel required(module) = floor(M_mod / 3) - 2
	*/

	input, err := ioutil.ReadFile("2019/D1/input.txt")
	utils.Check(err)
	strInput := string(input)
	fmt.Println(strInput)
}

func getFuelForMass(mass int32) int32 {
	return int32(math.Floor(float64(mass/3)) - 2)
}
