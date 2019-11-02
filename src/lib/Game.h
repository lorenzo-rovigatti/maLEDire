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

#include <mutex>
#include <thread>
#include <queue>

#include <termios.h>

#include "Snake.h"

namespace mldr {

class Game {
public:
	Game(std::chrono::nanoseconds timestep);
	virtual ~Game();

	void start();
	void quit();

private:
	void _handle_input();

	const std::chrono::nanoseconds _timestep;
	struct termios _termios_struct;
	std::shared_ptr<Snake> _world;
	bool _quit = false;

	std::queue<char> _key_pressed;
	std::thread _input_thread;
	std::mutex _mutex;
	coordinates _dimension = {32, 16};
};

} /* namespace mldr */

#endif /* SRC_LIB_GAME_H_ */
