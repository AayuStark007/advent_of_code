package d2

import (
	"2019/utils"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestIntcodeCompile(t *testing.T) {
	tables := []struct {
		inCode  []int32
		outCode []int32
	}{
		{[]int32{1, 0, 0, 0, 99}, []int32{2, 0, 0, 0, 99}},
		{[]int32{2, 3, 0, 3, 99}, []int32{2, 3, 0, 6, 99}},
		{[]int32{2, 4, 4, 5, 99, 0}, []int32{2, 4, 4, 5, 99, 9801}},
		{[]int32{1, 1, 1, 4, 99, 5, 6, 0, 99}, []int32{30, 1, 1, 4, 2, 5, 6, 0, 99}},
		{[]int32{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50}, []int32{3500, 9, 10, 70, 2, 3, 11, 0, 99, 30, 40, 50}},
	}

	for _, table := range tables {
		resultCode := compileIntCode(table.inCode)
		result, idx := utils.EqualsI(table.outCode, resultCode)

		assert.True(t, result, "Incorrect compiled code expected %d, got %d", table.outCode[idx], resultCode[idx])
	}
}
