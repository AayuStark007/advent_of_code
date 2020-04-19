package utils

// Check -> check the error flag
func Check(e error) {
	if e != nil {
		panic(e)
	}
}
