package d1

import (
	"AdventOfCode/utils"
	"fmt"
	"io/ioutil"
	"math"
	"strings"
)

// Compute -> Do whatwe
func Compute() {

	/*
		Fuel required(module) = floor(M_mod / 3) - 2
	*/

	input, err := ioutil.ReadFile("2019/D1/input.txt")
	utils.Check(err)
	strInput := string(input)

	numListStr := strings.Split(strInput, "\r\n")
	numListInt := utils.GetIntFromStrings(numListStr)

	modFuels := utils.ApplyIToI(numListInt, getFuelForMass)

	result := utils.SumI(modFuels)

	fmt.Println(result)

}

func getFuelForMass(mass int32) int32 {
	fuel := int32(math.Floor(float64(mass/3)) - 2)

	if fuel > 0 {
		return fuel + getFuelForMass(fuel)
	}

	return 0
}
