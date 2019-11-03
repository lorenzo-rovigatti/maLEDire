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
	std::string score_line();
	void use_input(char c);
	bool done();

	std::vector<coordinates> segments;

private:
	coordinates _dimension;
	coordinates _current_direction;
	float _speed;
	float _dt;
	float _elapsed_time;
	bool _done = false;
	int _score = 3;
};

} /* namespace mldr */

#endif /* SRC_LIB_SNAKE_H_ */
