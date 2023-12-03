package d1

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestFuelCalc(t *testing.T) {
	tables := []struct {
		mass   int32
		expect int32
	}{
		{14, 2},
		{1969, 966},
		{100756, 50346},
	}

	for _, table := range tables {
		result := getFuelForMass(table.mass)
		assert.Equal(t, table.expect, result,
			"incorrect result for calculation of fuel for mass %d, expected %d, got %d ",
			table.mass,
			table.expect,
			result)
	}
}
