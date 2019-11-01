/*
 * main.cpp
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#include <lib/TextDisplay.h>

#include <lib/Game.h>

#include <termios.h>
#include <unistd.h>

// to use ns and ms
using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(100ms);

int main(int argc, char *argv[]) {
	mldr::Game game(timestep);

	game.start();

	return 0;
}
