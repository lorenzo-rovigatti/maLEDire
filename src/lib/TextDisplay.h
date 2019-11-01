/*
 * TestDisplay.h
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#ifndef SRC_LIB_TEXTDISPLAY_H_
#define SRC_LIB_TEXTDISPLAY_H_

#include <vector>
#include <cmath>
#include <chrono>
#include <memory>

namespace mldr {

class Snake;

class TextDisplay {
public:
	TextDisplay(int cols, int rows, std::chrono::nanoseconds pause_for, std::shared_ptr<Snake> world);
	virtual ~TextDisplay();

	void clear();
	void draw();

	void set_h_line(double v_pos, double from, double to, int new_value);
	void set_v_line(double h_pos, double from, double to, int new_value);

private:
	int _idx(int col, int row);
	int _hpos_to_int(double coord) {
		return std::round(coord * (_cols - 1));
	}
	int _vpos_to_int(double coord) {
		return std::round(coord * (_rows - 1));
	}

	int _cols;
	int _rows;
	std::chrono::nanoseconds _pause_for;
	bool _never_drawn = true;

	std::vector<int> _canvas;
	std::shared_ptr<Snake> _world;
};

} /* namespace mldr */

#endif /* SRC_LIB_TEXTDISPLAY_H_ */
