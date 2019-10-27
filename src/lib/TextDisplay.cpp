/*
 * TestDisplay.cpp
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#include "TextDisplay.h"

#include <iostream>

namespace mldr {

TextDisplay::TextDisplay(int cols, int rows) :
	_cols(cols), _rows(rows) {
	_canvas.resize(_cols * _rows, 0);
}

TextDisplay::~TextDisplay() {

}

void TextDisplay::clear() {
	std::fill(_canvas.begin(), _canvas.end(), 0);
}

void TextDisplay::draw() {
	for(int i = 0; i < _rows; i++) {
		for(int j = 0; j < _cols; j++) {
			int idx = _idx(j, i);
			if(_canvas[idx]) {
				std::cout << " x";
			}
			else {
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
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
