#pragma once
#include <iostream>
#include <time.h>

// �ȈՃx���`�}�[�N
class Bench {
private:
	clock_t s, e;
public:
	void start() {
		s = clock();
	}
	void end() {
		e = clock();
		result();
	}
	void result() {
		std::cout << "time = " << e - s << "ms." << std::endl;
	}
};