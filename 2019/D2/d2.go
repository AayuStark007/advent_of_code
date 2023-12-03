package d2

import (
	"2019/utils"
	"fmt"
	"io/ioutil"
	"strings"
)

// Compute -> Day 2 job
func Compute() {
	input, err := ioutil.ReadFile("./D2/input.txt")
	utils.Check(err)
	strInput := string(input)

	numListStr := strings.Split(strInput, ",")
	numListInt := utils.GetIntFromStrings(numListStr)

	numListInt[1] = 12
	numListInt[2] = 2

	result := compileIntCode(numListInt)

	fmt.Printf("Part1 Solution: %d\n", result[0])

	var target int32 = 19690720

	domain := len(numListInt) - 1

	for i := 0; i < domain; i++ {
		for j := 0; j < domain; j++ {
			numListInt[1] = int32(i)
			numListInt[2] = int32(j)

			if target == compileIntCode(numListInt)[0] {
				fmt.Printf("Part2 Solution noun: %d, verb: %d, result: %d", i, j, 100*i+j)
				break
			}
		}
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
