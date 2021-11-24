/*
 * matrix_multiply.cpp
 *
 *  Created on: Oct 13, 2021
 *      Author: KZ
 */

#include "matrix.h"
#include "timer.h"

#include "doctest.h"

#include <iostream>





TEST_CASE("matrix multiply") {
	std::size_t size = 295;
	int* A = create_matrix<int>(size);
	int* B = create_matrix<int>(size);
	int* C = create_matrix<int>(size);
	int valueA = 1234;
	int valueB = 567;
	init_diagonal(size, A, valueA);
	init_diagonal(size, B, valueB);

	SUBCASE("sequential") {

		for(std::size_t run = 0; run < 10; run++) {
			Timer timer{"sequential"};
			matrix_multiply_sequential(size, A, B, C);
		}
	}
	SUBCASE("threads") {

		for(std::size_t run = 0; run < 10; run++) {
			Timer timer{"threads"};
			matrix_multiply_threads(size, A, B, C);
		}
	}


	int* expected = create_matrix<int>(size);
	init_diagonal(size, expected, valueA*valueB);

	CHECK(is_equal(size, expected, C ));

	delete[] A;
	delete[] B;
	delete[] C;
	delete[] expected;
}


TEST_CASE("matrix multiply - double") {
	std::size_t size = 295;
	double* A = create_matrix<double>(size);
	double* B = create_matrix<double>(size);
	double* C = create_matrix<double>(size);
	double valueA = 12.34;
	double valueB = 0.567;
	init_diagonal(size, A, valueA);
	init_diagonal(size, B, valueB);

	SUBCASE("sequential") {

		for(std::size_t run = 0; run < 10; run++) {
			Timer timer{"sequential"};
			matrix_multiply_sequential(size, A, B, C);
		}
	}
	SUBCASE("threads") {

		for(std::size_t run = 0; run < 10; run++) {
			Timer timer{"threads"};
			matrix_multiply_threads(size, A, B, C);
		}
	}


	double* expected = create_matrix<double>(size);
	init_diagonal(size, expected, valueA*valueB);

	CHECK(is_equal(size, expected, C));

	delete[] A;
	delete[] B;
	delete[] C;
	delete[] expected;
}


