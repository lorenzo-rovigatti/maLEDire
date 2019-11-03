/*
 * Snake.h
 *
 *  Created on: Nov 1, 2019
 *      Author: lorenzo
 */

#ifndef SRC_LIB_SNAKE_H_
#define SRC_LIB_SNAKE_H_

#include <chrono>
#include <list>
#include <map>
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

	std::list<coordinates> segments;
	std::vector<coordinates> food;

	enum Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST
	};

private:
	void _add_random_food();
	bool _overlaps_with_segments(coordinates &pos);

	coordinates _dimension;
	Direction _current_direction;
	std::map<Direction, coordinates> _directions;
	float _speed;
	float _dt;
	float _elapsed_time;
	bool _done = false;
};

} /* namespace mldr */

#endif /* SRC_LIB_SNAKE_H_ */
