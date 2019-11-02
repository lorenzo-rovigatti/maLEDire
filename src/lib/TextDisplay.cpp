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

void TextDisplay::clear() {
	std::fill(_canvas.begin(), _canvas.end(), 0);
}

void TextDisplay::draw() {
	// move the cursor to the beginning so as to overwrite the last output
	if(!_never_drawn) {
		std::cout << "\r";
		for(int i = 0; i < _dimension[1]; i++) {
			std::cout << "\033[1A";
		}
	}

	clear();
	for(auto segment : _world->segments) {
		int idx = _idx(segment[0], segment[1]);
		_canvas[idx] = 1;
	}

	for(int i = 0; i < _dimension[1]; i++) {
		for(int j = 0; j < _dimension[0]; j++) {
			int idx = _idx(j, i);
			if(_canvas[idx]) {
				std::cout << "o ";
			}
			else {
				std::cout << ". ";
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
