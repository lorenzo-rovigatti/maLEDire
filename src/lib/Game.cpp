/*
 * Game.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: lorenzo
 */

#include "Game.h"

#include "TextDisplay.h"

#include <iostream>
#include <unistd.h>

// to use ns and ms
using namespace std::chrono_literals;

namespace mldr {

Game::Game(std::chrono::nanoseconds timestep) :
				_timestep(timestep) {
	tcgetattr(STDIN_FILENO, &_termios_struct);
	_termios_struct.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &_termios_struct);

	_world = std::make_shared<Snake>(_timestep);
}

Game::~Game() {

}

void Game::start() {
	TextDisplay display(32, 16, _timestep / 2, _world);

	using clock = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();

	auto thread = std::thread(std::bind(&Game::_handle_input, this));
	_input_thread.swap(thread);

	while(!_quit) {
		auto current_time = clock::now();
		auto delta_time = current_time - time_start;
		time_start = current_time;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		// update game logic as lag permits
		while(lag >= _timestep) {
			lag -= _timestep;
			_world->update();
		}

		// calculate how close or far we are from the next _timestep
//		auto alpha = (float) lag.count() / _timestep.count();
//		auto interpolated_state = interpolate(current_state, previous_state, alpha);
//		render(interpolated_state);

		display.draw();

		if(!_key_pressed.empty()) {
			auto key = _key_pressed.front();
			_key_pressed.pop();

			_world->use_input(key);
		}
	}
}

void Game::_handle_input() {
	while(!_quit) {
		char c = getchar();

		if(c == 'q') {
			_quit = true;
		}

		_key_pressed.emplace(c);
	}
}

} /* namespace mldr */
