#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

class pgm_image
{
private:
	int length;
	int width;
	int max_colour_value;
	std::vector<int> data;

	void draw_pixel(int x, int y, int colour);
	void draw_line();
	void draw_circle(int x_center, int y_center, int radius);
	void draw_mouth(int x_center, int y_center, int radius);
	void draw_eyes(int x_center, int y_center, int radius);

public:
	int get_length();
	int get_width();
	int get_radius();
	int get_max_colour_value();
	void draw_smiley();
	void print_image();
	void write_pgm_file(std::string out_file_name);

	pgm_image();
	pgm_image(std::ifstream & image_string);
	~pgm_image();
};

