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

#include "defs.h"

namespace mldr {

class Snake;

class TextDisplay {
public:
	TextDisplay(coordinates dim, std::chrono::nanoseconds pause_for, std::shared_ptr<Snake> world);
	virtual ~TextDisplay();

	void clear_canvas();
	void draw();

private:
	int _idx(int col, int row);
	int _hpos_to_int(double coord) {
		return std::round(coord * (_dimension[0] - 1));
	}
	int _vpos_to_int(double coord) {
		return std::round(coord * (_dimension[1] - 1));
	}

	coordinates _dimension;
	std::chrono::nanoseconds _pause_for;
	bool _never_drawn = true;

	std::vector<int> _canvas;
	std::shared_ptr<Snake> _world;
};

} /* namespace mldr */

#endif /* SRC_LIB_TEXTDISPLAY_H_ */
