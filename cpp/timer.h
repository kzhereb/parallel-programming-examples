/*
 * timer.h
 *
 *  Created on: Nov 24, 2021
 *      Author: KZ
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <string>
#include <iostream>

class Timer {
private:
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
	Timer(std::string name) {
		this->name = name;
		this->start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Timer " << name << ": "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(
						end - start).count() << "ms" << std::endl;
	}
};


#endif /* TIMER_H_ */
