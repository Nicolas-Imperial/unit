/*
 Copyright 2015 Nicolas Melot

 This file is part of Unit.

 QDM is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 QDM is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with QDM. If not, see <http://www.gnu.org/licenses/>.

*/


#include <stdio.h>
#include <stdlib.h>

#include <pelib/unit.h>

static int test_count, test_failure, test_assert;
static int assert_count, assert_failure;
static int passed, suite_passed;

void
test_commit()
{
	if(!passed) test_failure++;
	test_count++;
	suite_passed = suite_passed && passed;
}

void
test_fail()
{
	passed = 0;
}

void
assert_fail()
{
	passed = 0;
	assert_failure++;
}

void
assert_add()
{
	assert_count++;
	test_assert = 1;
}

void
test_reset()
{
	test_assert = 0;
	passed = 1;
}

int
test_asserted()
{
	return test_assert > 0;
}

int
test_passed()
{
	return passed;
}

int
main(int argc, char **argv)
{
	suite_passed = 1;
	test_count = 0;
	test_failure = 0;
	assert_count = 0;
	assert_failure = 0;

	// Initialize the test batch
	setup();
	if(!suite_passed)
	{
		printf("Test suite initialization failed.\n");
		return EXIT_FAILURE;
	}

	run();

	// Destroy the test environment
	test_reset();
	teardown();
	if(!passed)
	{
		printf("Test suite teardown failed.\n");
	}

	printf("\nSummary: %s\n", suite_passed ? "passed" : "failed");
	printf("%d assertions, %d failures\n", assert_count, assert_failure);
	printf("%d tests, %d failures\n", test_count, test_failure);

	// Return 0 if final is still one, else report an error
	return !suite_passed;
}

