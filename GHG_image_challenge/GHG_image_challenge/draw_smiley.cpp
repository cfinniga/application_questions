#include "pgm_image.h"
#include <string>
#include <fstream>

int main(int argc, char *argv[]) {
	std::string input_file_name;
	std::string output_file_name = "output.pgm";

	// Parse input arguments
	if (argc == 2) {
		input_file_name = argv[1];
	}
	else {
		std::cout << "Usage: draw_smiley input_file" << std::endl;
		return 0;
	}

	try {
		// read image
		std::ifstream input_file(input_file_name, std::ifstream::in);
		pgm_image input_image(input_file);

		// draw on image
		input_image.draw_smiley();

		// write image
		input_image.write_pgm_file(output_file_name);

	}
	catch (...) {
		std::cout << "Error: input file is corrupt" << std::endl;
	}

	return 0;
}