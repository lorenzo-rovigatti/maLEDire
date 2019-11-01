/*
 * TestDisplay.cpp
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#include "TextDisplay.h"

#include <iostream>
#include <thread>

namespace mldr {

TextDisplay::TextDisplay(int cols, int rows, std::chrono::nanoseconds pause_for) :
				_cols(cols),
				_rows(rows),
				_pause_for(pause_for) {
	_canvas.resize(_cols * _rows, 0);
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
		for(int i = 0; i < _rows; i++) {
			std::cout << "\033[1A";
		}
	}

	for(int i = 0; i < _rows; i++) {
		for(int j = 0; j < _cols; j++) {
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

void TextDisplay::set_h_line(double v_pos, double from, double to, int new_value) {
	int row = _vpos_to_int(v_pos);
	int i_from = _hpos_to_int(from);
	int i_to = _hpos_to_int(to);

	for(int i = i_from; i <= i_to; i++) {
		int idx = _idx(i, row);
		_canvas[idx] = new_value;
	}
}

void TextDisplay::set_v_line(double h_pos, double from, double to, int new_value) {
	int col = _hpos_to_int(h_pos);
	int i_from = _vpos_to_int(from);
	int i_to = _vpos_to_int(to);

	for(int i = i_from; i <= i_to; i++) {
		int idx = _idx(col, i);
		_canvas[idx] = new_value;
	}
}

int TextDisplay::_idx(int col, int row) {
	return row * _cols + col;
}

} /* namespace mldr */
