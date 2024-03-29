/*
 * TestDisplay.cpp
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#include "TextDisplay.h"

#include "Snake.h"

#include <iostream>
#include <thread>

namespace mldr {

TextDisplay::TextDisplay(coordinates dim, std::chrono::nanoseconds pause_for, std::shared_ptr<Snake> world) :
				_dimension(dim),
				_pause_for(pause_for),
				_world(world) {
	_canvas.resize(_dimension[0] * _dimension[1], 0);
}

TextDisplay::~TextDisplay() {

}

void TextDisplay::clear_canvas() {
	std::fill(_canvas.begin(), _canvas.end(), 0);
}

void TextDisplay::draw() {
	clear_canvas();

	// move the cursor to the beginning so as to overwrite the last output
	if(!_never_drawn) {
		int output_dim = _dimension[1] + 1;

		std::cout << "\r";
		for(int i = 0; i < output_dim; i++) {
			std::cout << "\033[1A";
		}
	}

	// fill the canvas
	for(auto &segment : _world->segments) {
		int idx = _idx(segment[0], segment[1]);
		_canvas[idx] = 1;
	}

	for(auto &food_bit : _world->food) {
		int idx = _idx(food_bit[0], food_bit[1]);
		_canvas[idx] = 2;
	}

	// print the score line
	std::cout << _world->score_line();
	// and the canvas
	for(int i = 0; i < _dimension[1]; i++) {
		for(int j = 0; j < _dimension[0]; j++) {
			int idx = _idx(j, i);
			switch(_canvas[idx]) {
			case 1:
				std::cout << "o ";
				break;
			case 2:
				std::cout << "x ";
				break;
			default:
				std::cout << ". ";
				break;
			}
		}
		std::cout << std::endl;
	}

	_never_drawn = false;

	std::this_thread::sleep_for(_pause_for);
}

int TextDisplay::_idx(int col, int row) {
	return row * _dimension[0] + col;
}

} /* namespace mldr */
