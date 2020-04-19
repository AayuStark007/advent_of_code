package utils

import "strconv"

// Check -> check the error flag
func Check(e error) {
	if e != nil {
		panic(e)
	}
}

// ApplySToI -> Apply string to int32 mapping to string slice
func ApplySToI(vs []string, f func(string) int32) []int32 {
	vsm := make([]int32, len(vs))
	for i, v := range vs {
		vsm[i] = f(v)
	}

	return vsm
}

// ApplySToS -> Apply string to string mapping to string slice
func ApplySToS(vs []string, f func(string) string) []string {
	vsm := make([]string, len(vs))
	for i, v := range vs {
		vsm[i] = f(v)
	}

	return vsm
}

// ApplyIToI -> Apply int to int mapping
func ApplyIToI(vs []int32, f func(int32) int32) []int32 {
	vsm := make([]int32, len(vs))
	for i, v := range vs {
		vsm[i] = f(v)
	}

	return vsm
}

func SumI(vi []int32) int64 {
	var total int64 = 0

	for _, v := range vi {
		total += int64(v)
	}

	return total
}

// GetIntFromStrings -> Convert string slice to int slice
func GetIntFromStrings(vs []string) []int32 {
	res := ApplySToI(vs, func(v string) int32 {
		resInt, err := strconv.Atoi(v)
		Check(err)
		return int32(resInt)
	})

	return res
}
