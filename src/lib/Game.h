/*
 * Game.h
 *
 *  Created on: Nov 1, 2019
 *      Author: lorenzo
 */

#ifndef SRC_LIB_GAME_H_
#define SRC_LIB_GAME_H_

#include <chrono>
#include <vector>
#include <termios.h>

namespace mldr {

class Game {
public:
	Game(std::chrono::nanoseconds timestep);
	virtual ~Game();

	void start();

private:
	const std::chrono::nanoseconds _timestep;
	struct termios _termios_struct;

	bool _handle_input();
	virtual void _use_input(char c);
};

} /* namespace mldr */

#endif /* SRC_LIB_GAME_H_ */
