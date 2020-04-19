package main

import (
	"io/ioutil"
	"math"

	"../../utils"
)

func main() {

	/*
		Fuel required(module) = floor(M_mod / 3) - 2
	*/

	input, err := ioutil.ReadFile("input.txt")
	utils.Check(err)
	str_input := string(input)

}

func getFuelForMass(mass int32) int32 {
	return int32(math.Floor(float64(mass/3)) - 2)
}
