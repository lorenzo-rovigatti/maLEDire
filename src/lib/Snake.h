/*
 * Snake.h
 *
 *  Created on: Nov 1, 2019
 *      Author: lorenzo
 */

#ifndef SRC_LIB_SNAKE_H_
#define SRC_LIB_SNAKE_H_

#include <chrono>
#include <vector>
#include <array>

namespace mldr {

class Snake {
public:
	Snake(std::chrono::nanoseconds timestep);
	virtual ~Snake();

	void update();
	void use_input(char c);

	std::vector<std::array<float, 2>> segments;

private:
	std::array<float, 2> _current_direction;
	float _speed;
	float _dt;
};

} /* namespace mldr */

#endif /* SRC_LIB_SNAKE_H_ */
