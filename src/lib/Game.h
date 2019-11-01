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
#include <memory>
#include <termios.h>

#include "Snake.h"

namespace mldr {

class Game {
public:
	Game(std::chrono::nanoseconds timestep);
	virtual ~Game();

	void start();

private:
	bool _handle_input();

	const std::chrono::nanoseconds _timestep;
	struct termios _termios_struct;
	std::shared_ptr<Snake> _world;
};

} /* namespace mldr */

#endif /* SRC_LIB_GAME_H_ */
