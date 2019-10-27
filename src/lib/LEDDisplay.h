/*
 * LEDDisplay.h
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#ifndef SRC_LIB_LEDDISPLAY_H_
#define SRC_LIB_LEDDISPLAY_H_

namespace mldr {

class LEDDisplay {
public:
	LEDDisplay();
	virtual ~LEDDisplay();

	void draw();
};

} /* namespace mldr */

#endif /* SRC_LIB_LEDDISPLAY_H_ */
