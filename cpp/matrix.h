/*
 * matrix.h
 *
 *  Created on: Nov 24, 2021
 *      Author: KZ
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

#include <thread>
#include <vector>
#include <cassert>

template<typename T>
T* create_matrix(std::size_t size) {
	T* result = new T[size*size];
	return result;
}

template<typename T>
void init_diagonal(std::size_t size, T* matrix, T value) {
	for(std::size_t i = 0; i < size; i++) {
			for (std::size_t j = 0; j < size; j++) {
				matrix[i*size+j] = (i==j) ? value : T(0);
			}
	}
}
template<typename T>
bool is_equal(std::size_t size, T* left, T* right) {
	for(std::size_t i = 0; i < size; i++) {
			for (std::size_t j = 0; j < size; j++) {
				if (left[i*size+j] != right[i*size+j] ) {
					std::cout<<"i="<<i<<", j="<<j<<",left[i,j]="<<left[i*size+j]<<",right[i,j]="<<right[i*size+j]<<std::endl;
					return false;}
			}
	}
	return true;
}

template<typename T>
void matrix_multiply_sequential(std::size_t size, T* input_A, T* input_B, T* output_C) {
	for(std::size_t i = 0; i < size; i++) {
			for (std::size_t j = 0; j < size; j++) {
				output_C[i*size+j] = T(0);
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

template<typename T>
void multiply_on_single_thread(std::size_t size, T* input_A, T* input_B, T* output_C, std::size_t from, std::size_t to) {
	for(std::size_t i = from; i < to; i++) {
			for (std::size_t j = 0; j < size; j++) {
				output_C[i*size+j] = T(0);
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

template<typename T>
void matrix_multiply_threads(std::size_t size, T* input_A, T* input_B, T* output_C, unsigned thread_num = 0) {
	unsigned thread_count = (thread_num == 0)? std::thread::hardware_concurrency() : thread_num;
	assert(thread_count > 0);
	//std::cout<<thread_count<<std::endl;

	std::vector<std::thread> threads;
	std::size_t block_size = size/thread_count;
	std::size_t from = 0;
	for (std::size_t i = 0; i< thread_count; i++) {
		std::size_t to = from + block_size;
		if (to > size) { to = size;}
		if (i == thread_count-1) { to = size;}

		//std::cout<<"i="<<i<<",from="<<from<<",to="<<to<<std::endl;

		threads.push_back(std::thread(multiply_on_single_thread<T>,
				size, input_A, input_B, output_C,
				from, to));

		from = to;
	}

	for (std::thread & th : threads) {
		if (th.joinable()) { th.join(); }
	}

}


#endif /* MATRIX_H_ */
