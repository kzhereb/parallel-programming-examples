/*
 * matrix.h
 *
 *  Created on: Nov 24, 2021
 *      Author: KZ
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <thread>

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
				if (left[i*size+j] != right[i*size+j] ) { return false;}
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



#endif /* MATRIX_H_ */
