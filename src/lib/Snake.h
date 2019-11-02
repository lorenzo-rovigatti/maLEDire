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

#include "defs.h"

namespace mldr {

class Snake {
public:
	Snake(coordinates dim, std::chrono::nanoseconds timestep);
	virtual ~Snake();

	void update();
	void use_input(char c);

	std::vector<coordinates> segments;

private:
	coordinates _current_direction;
	float _speed;
	float _dt;
	float _elapsed_time;
};

} /* namespace mldr */

#endif /* SRC_LIB_SNAKE_H_ */
