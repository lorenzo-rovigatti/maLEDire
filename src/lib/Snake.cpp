/*
 * Snake.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: lorenzo
 */

#include "Snake.h"

#include <sstream>
#include <algorithm>

namespace mldr {

Snake::Snake(coordinates dim, std::chrono::nanoseconds timestep) :
				_dimension(dim),
				_current_direction(WEST),
				_speed(4.),
				_elapsed_time(0.) {
	_dt = std::chrono::duration_cast<std::chrono::duration<float>>(timestep).count();

	int x_centre = dim[0] / 2;
	segments.emplace_back(coordinates( { x_centre + 1, dim[1] / 2 }));
	segments.emplace_back(coordinates( { x_centre, dim[1] / 2 }));
	segments.emplace_back(coordinates( { x_centre - 1, dim[1] / 2 }));

	_directions[NORTH] = coordinates( { 0, -1 });
	_directions[EAST] = coordinates( { 1, 0 });
	_directions[SOUTH] = coordinates( { 0, 1 });
	_directions[WEST] = coordinates( { -1, 0 });

	_add_random_food();
}

Snake::~Snake() {

}

void Snake::use_input(char c) {
	switch(c) {
	case 'w':
		if(_current_direction != SOUTH) {
			_current_direction = NORTH;
		}
		break;
	case 'd':
		if(_current_direction != WEST) {
			_current_direction = EAST;
		}
		break;
	case 's':
		if(_current_direction != NORTH) {
			_current_direction = SOUTH;
		}
		break;
	case 'a':
		if(_current_direction != EAST) {
			_current_direction = WEST;
		}
		break;
	}
}

void Snake::update() {
	_elapsed_time += _dt;
	float delta_dist = _elapsed_time * _speed;

	if(delta_dist >= 1.) {
		auto delta = _directions[_current_direction];
		// prepare a new segment which is just the first one + delta
		auto new_segment_pos = segments.back();
		for(int i = 0; i < 2; i++) {
			new_segment_pos[i] += delta[i];
			// check if the new segment to be added is going out of bounds
			if(new_segment_pos[i] < 0 || new_segment_pos[i] >= _dimension[i]) {
				_done = true;
				return;
			}
		}

		// check if the new segment overlaps with the rest of the snake
		if(_overlaps_with_segments(new_segment_pos)) {
			_done = true;
			return;
		}

		// check if the new segment overlaps with some food
		auto overlapping_food = std::find(food.begin(), food.end(), new_segment_pos);
		if(overlapping_food != food.end()) {
			food.erase(overlapping_food);
			_add_random_food();
		}
		else {
			// remove the last segment
			segments.pop_front();
		}

		// add the new segment
		segments.push_back(new_segment_pos);

		_elapsed_time -= 1. / _speed;
	}
}

std::string Snake::score_line() {
	std::stringstream ss;

	ss << "Score: " << segments.size() << std::endl;

	return ss.str();
}

bool Snake::done() {
	return _done;
}

void Snake::_add_random_food() {
	coordinates new_food;
	do {
		new_food[0] = (int) (drand48() * _dimension[0]);
		new_food[1] = (int) (drand48() * _dimension[1]);
	} while(_overlaps_with_segments(new_food));

	food.emplace_back(new_food);
}

bool Snake::_overlaps_with_segments(coordinates &pos) {
	return std::find(segments.begin(), segments.end(), pos) != segments.end();
}

} /* namespace mldr */
