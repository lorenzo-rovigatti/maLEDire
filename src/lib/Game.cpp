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

	_world = std::make_shared<Snake>(_dimension, _timestep);
}

Game::~Game() {
	if(_input_thread.joinable()) {
		_input_thread.join();
	}
}

void Game::start() {
	TextDisplay display(_dimension, _timestep / 2, _world);

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

		if(!_key_pressed.empty()) {
			std::lock_guard<std::mutex> lock(_mutex);
			auto key = _key_pressed.front();
			_key_pressed.pop();

			_world->use_input(key);

			if(key == 'q') {
				_quit = true;
			}
		}

		// update game logic as lag permits
		while(lag >= _timestep) {
			lag -= _timestep;
			_world->update();
		}

		if(_world->done()) {
			_quit = true;
		}

		// calculate how close or far we are from the next _timestep
//		auto alpha = (float) lag.count() / _timestep.count();
//		auto interpolated_state = interpolate(current_state, previous_state, alpha);
//		render(interpolated_state);

		display.draw();
	}

	std::cout << "GAME OVER" << std::endl;
}

void Game::_handle_input() {
	fd_set rfds;
	struct timeval tv;
	int retval;

	int us_timeout = std::chrono::duration_cast<std::chrono::microseconds>(_timestep).count();

	while(!_quit) {
		// these initialisations need to be carried out every time we want to use the select function
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		tv.tv_sec = 0;
		tv.tv_usec = us_timeout;
		retval = select(1, &rfds, NULL, NULL, &tv);
		if(retval) {
			std::lock_guard<std::mutex> lock(_mutex);
			char c = getchar();
			_key_pressed.emplace(c);
		}
	}
}

} /* namespace mldr */
