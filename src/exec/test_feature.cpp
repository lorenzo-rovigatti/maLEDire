/*
 * main.cpp
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#include <lib/TextDisplay.h>

#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {
	auto one_second = std::chrono::milliseconds(1000);

	mldr::TextDisplay display(32, 16);

	display.draw();
	std::this_thread::sleep_for(one_second);

	display.set_h_line(0., 0., 1., 1);
	display.draw();
	std::this_thread::sleep_for(one_second);

	display.set_h_line(1., 0., 1., 1);
	display.draw();
	std::this_thread::sleep_for(one_second);

	display.set_v_line(0., 0., 1., 1);
	display.draw();
	std::this_thread::sleep_for(one_second);

	display.set_v_line(1., 0., 1., 1);
	display.draw();
	std::this_thread::sleep_for(one_second);

	return 0;
}
