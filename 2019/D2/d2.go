package d2

import (
	"AdventOfCode/utils"
	"fmt"
	"io/ioutil"
	"strings"
)

// Compute -> Day 2 job
func Compute() {
	input, err := ioutil.ReadFile("2019/D2/input.txt")
	utils.Check(err)
	strInput := string(input)

	numListStr := strings.Split(strInput, ",")
	numListInt := utils.GetIntFromStrings(numListStr)

	numListInt[1] = 12
	numListInt[2] = 2

	result := compileIntCode(numListInt)

	fmt.Printf("Part1 Solution: %d\n", result[0])

	for i := 0; i <= 12; i++ {
		numListInt[1] = 12 //int32(i)
		numListInt[2] = int32(i)

		result = compileIntCode(numListInt)

		fmt.Printf("Part2 Candidate(%d, %d): %d\n", 12, i, result[0])
	}
}

func compileIntCode(code []int32) []int32 {
	var idx int32 = 0
	compiledCode := make([]int32, len(code))
	copy(compiledCode, code)

Loop:
	for {
		switch compiledCode[idx] {
		case 1:
			result := compiledCode[compiledCode[idx+1]] + compiledCode[compiledCode[idx+2]]
			compiledCode[compiledCode[idx+3]] = result
			break
		case 2:
			result := compiledCode[compiledCode[idx+1]] * compiledCode[compiledCode[idx+2]]
			compiledCode[compiledCode[idx+3]] = result
			break
		case 99:
			break Loop
		}

		idx = idx + 4
	}

	return compiledCode
}
