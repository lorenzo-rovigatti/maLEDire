/*
 * Snake.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: lorenzo
 */

#include "Snake.h"

namespace mldr {

Snake::Snake(coordinates dim, std::chrono::nanoseconds timestep) :
				_current_direction( { 0, 1 }),
				_speed(2.),
				_elapsed_time(0.) {
	_dt = std::chrono::duration_cast<std::chrono::duration<float>>(timestep).count();
	segments.push_back(coordinates( { dim[0] / 2, dim[1] / 2 }));
}

Snake::~Snake() {

}

void Snake::use_input(char c) {
	switch(c) {
	case 'w':
		_current_direction[0] = 0;
		_current_direction[1] = -1;
		break;
	case 'd':
		_current_direction[0] = 1;
		_current_direction[1] = 0;
		break;
	case 's':
		_current_direction[0] = 0;
		_current_direction[1] = 1;
		break;
	case 'a':
		_current_direction[0] = -1;
		_current_direction[1] = 0;
		break;
	}
}

void Snake::update() {
	_elapsed_time += _dt;
	float delta = _elapsed_time * _speed;

	if(delta >= 1.) {
		for(auto &segment : segments) {
			segment[0] += _current_direction[0];
			segment[1] += _current_direction[1];
		}

		_elapsed_time = 0.;
	}

}

} /* namespace mldr */
