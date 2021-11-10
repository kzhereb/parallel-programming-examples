/*
 * matrix_multiply.cpp
 *
 *  Created on: Oct 13, 2021
 *      Author: KZ
 */

#include "doctest.h"

#include <iostream>
#include <vector>
#include <thread>
#include <cassert>

int* create_matrix(std::size_t size) {
	int* result = new int[size*size];
	return result;
}

void init_diagonal(std::size_t size, int* matrix, int value) {
	for(std::size_t i = 0; i < size; i++) {
			for (std::size_t j = 0; j < size; j++) {
				matrix[i*size+j] = (i==j) ? value : 0;
			}
	}
}

bool is_equal(std::size_t size, int* left, int* right) {
	for(std::size_t i = 0; i < size; i++) {
			for (std::size_t j = 0; j < size; j++) {
				if (left[i*size+j] != right[i*size+j] ) { return false;}
			}
	}
	return true;
}


void matrix_multiply_sequential(std::size_t size, int* input_A, int* input_B, int* output_C) {
	for(std::size_t i = 0; i < size; i++) {
			for (std::size_t j = 0; j < size; j++) {
				output_C[i*size+j] = 0;
			}
	}
	for(std::size_t i = 0; i < size; i++) {
		for (std::size_t j = 0; j < size; j++) {
			for (std::size_t k = 0; k < size; k++) {
				output_C[i*size + j] += input_A[i*size + k] * input_B[k*size+j];
			}
		}
	}
}

void multiply_on_single_thread(std::size_t size, int* input_A, int* input_B, int* output_C, std::size_t from, std::size_t to) {
	for(std::size_t i = from; i < to; i++) {
			for (std::size_t j = 0; j < size; j++) {
				output_C[i*size+j] = 0;
			}
	}
	for(std::size_t i = from; i < to; i++) {
		for (std::size_t j = 0; j < size; j++) {
			for (std::size_t k = 0; k < size; k++) {
				output_C[i*size + j] += input_A[i*size + k] * input_B[k*size+j];
			}
		}
	}
}

void matrix_multiply_threads(std::size_t size, int* input_A, int* input_B, int* output_C, unsigned thread_num = 0) {
	unsigned thread_count = (thread_num == 0)? std::thread::hardware_concurrency() : thread_num;
	assert(thread_count > 0);
	//std::cout<<thread_count<<std::endl;

	std::vector<std::thread> threads;
	std::size_t block_size = size/thread_count;
	std::size_t from = 0;
	for (std::size_t i = 0; i< thread_count; i++) {
		std::size_t to = from + block_size;
		if (to > size) { to = size;}

		threads.push_back(std::thread(multiply_on_single_thread,
				size, input_A, input_B, output_C,
				from, to));

		from = to;
	}

	for (std::thread & th : threads) {
		if (th.joinable()) { th.join(); }
	}

}

TEST_CASE("matrix multiply") {
	std::size_t size = 100;
	int* A = create_matrix(size);
	int* B = create_matrix(size);
	int* C = create_matrix(size);
	init_diagonal(size, A, 5);
	init_diagonal(size, B, 3);

	SUBCASE("sequential") {
		matrix_multiply_sequential(size, A, B, C);
	}
	SUBCASE("threads") {
		matrix_multiply_threads(size, A, B, C);
	}

	int* expected = create_matrix(size);
	init_diagonal(size, expected, 15);

	CHECK(is_equal(size, C, expected));

	delete[] A;
	delete[] B;
	delete[] C;
	delete[] expected;
}


