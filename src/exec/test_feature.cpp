/*
 * main.cpp
 *
 *  Created on: Oct 27, 2019
 *      Author: lorenzo
 */

#include <lib/TextDisplay.h>

int main(int argc, char *argv[]) {
	mldr::TextDisplay display(32, 16);

	display.set_h_line(0., 0., 1., 1);
	display.set_h_line(1., 0., 1., 1);

	display.set_v_line(0., 0., 1., 1);
	display.set_v_line(1., 0., 1., 1);

	display.draw();

	return 0;
}
