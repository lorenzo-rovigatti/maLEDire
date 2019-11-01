/*
 * Snake.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: lorenzo
 */

#include "Snake.h"

namespace mldr {

Snake::Snake(std::chrono::nanoseconds timestep) :
	_current_direction({0., 1.}),
	_speed(0.1) {
	_dt = std::chrono::duration_cast<std::chrono::duration<float>>(timestep).count();
	segments.push_back({0.5, 0.5});
}

Snake::~Snake() {

}

void Snake::use_input(char c) {
	switch(c) {
	case 'w':
		_current_direction[0] = 0.;
		_current_direction[1] = -1.;
		break;
	case 'd':
		_current_direction[0] = 1.;
		_current_direction[1] = 0.;
		break;
	case 's':
		_current_direction[0] = 0.;
		_current_direction[1] = 1.;
		break;
	case 'a':
		_current_direction[0] = -1.;
		_current_direction[1] = 0.;
		break;
	}
}

void Snake::update() {
	float delta = _dt * _speed;

	for(auto &segment : segments) {
		segment[0] += _current_direction[0] * delta;
		segment[1] += _current_direction[1] * delta;
	}

}

} /* namespace mldr */
