#include "pgm_image.h"
#include <iostream>

int pgm_image::get_length()
{
	return length;
}

int pgm_image::get_width()
{
	return width;
}

int pgm_image::get_radius()
{
	if (length > width) {
		return width / 2;
	}
	else {
		return length / 2;
	}
}

int pgm_image::get_max_colour_value()
{
	return max_colour_value;
}

void pgm_image::draw_pixel(int x, int y, int colour)
{
	this->data[x + y*width] = colour;
}

void pgm_image::draw_line()
{
	int counter = 0;
	for (int pixel : this->data) {
		if (counter >= this->width) {
			break;
		}
		pixel = this->max_colour_value;
	}
}

// Midpoint circle drawing algorithm taken from stackoverflow
void pgm_image::draw_circle(int x_center, int y_center, int radius)
{
	int x = radius;
	int y = 0;
	int colour = this->max_colour_value;
	int point = 1 - radius;

	draw_pixel(x + x_center, y + y_center, colour);

	// When radius is zero only a single 
	if (radius > 0)
	{
		draw_pixel(x + x_center, -y + y_center, colour);
		draw_pixel(y + x_center, x + y_center, colour);
		draw_pixel(-y + x_center, x + y_center, colour);

	}
	// Start drawing from (radius, 0), in the ccw direction
	while (x > y) {
		y++;
		if (point <= 0) {
			point = point + 2 * y + 1;
		}
		else {
			x--;
			point = point + 2 * y - 2 * x + 1;
		}
		draw_pixel(x + x_center, y + y_center, colour);
		draw_pixel(-x + x_center, y + y_center, colour);
		draw_pixel(x + x_center, -y + y_center, colour);
		draw_pixel(-x + x_center, -y + y_center, colour);

		if (x != y)
		{
			draw_pixel(y + x_center, x + y_center, colour);
			draw_pixel(-y + x_center, x + y_center, colour);
			draw_pixel(y + x_center, -x + y_center, colour);
			draw_pixel(-y + x_center, -x + y_center, colour);
		}
	}
}

void pgm_image::draw_mouth(int x_center, int y_center, int radius)
{
	int x = radius;
	int y = 0;
	int colour = this->max_colour_value;
	int point = 1 - radius;

	draw_pixel(x + x_center, y + y_center, colour);

	// When radius is zero only a single 
	if (radius > 0)
	{
		draw_pixel(x + x_center, -y + y_center, colour);
		draw_pixel(y + x_center, x + y_center, colour);
		draw_pixel(-y + x_center, x + y_center, colour);
	}

	// Start drawing from (radius, 0), in the ccw direction
	while (x > y) {
		y++;
		if (point <= 0) {
			point = point + 2 * y + 1;
		}
		else {
			x--;
			point = point + 2 * y - 2 * x + 1;
		}

		draw_pixel(x + x_center, y + y_center, colour);
		draw_pixel(-x + x_center, y + y_center, colour);

		if (x != y)
		{
			draw_pixel(y + x_center, x + y_center, colour);
			draw_pixel(-y + x_center, x + y_center, colour);
		}
	}
}

void pgm_image::draw_eyes(int x_center, int y_center, int radius)
{
	draw_pixel(x_center - radius, y_center, max_colour_value);
	draw_pixel(x_center + radius, y_center, max_colour_value);
}

void pgm_image::draw_smiley()
{
	int x_center = width / 2;
	int y_center = length / 2;
	int radius = get_radius();

	draw_circle(x_center, y_center, radius);
	draw_mouth(x_center, y_center, radius/2);
	draw_eyes(x_center, (length)/2, radius/4);
}

void pgm_image::print_image()
{
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << data[x + (y)*width] << ' ';
		}
		std::cout << '\n';
	}
}

void pgm_image::write_pgm_file(std::string output_file_name)
{
	std::string output_image_file;
	std::ofstream output_file(output_file_name);
	if (output_file.is_open())
	{
		output_file << "P2\n" << width << " " << length << "\n" << max_colour_value << "\n";
		for (int y = 0; y < length; y++) {
			for (int x = 0; x < width; x++) {
				output_file << data[x + (y)*width] << ' ';
			}
			output_file << '\n';
		}
		output_file.close();
	}
}

pgm_image::pgm_image()
{
	length = 0;
	width = 0;
	max_colour_value = 0;
}

pgm_image::pgm_image(std::ifstream & image_file)
{
	std::string line;

	// parse image type
	std::getline(image_file, line);

	// parse length and width
	std::getline(image_file, line);
	std::istringstream first_line(line);

	getline(first_line, line, ' ');
	width = stoi(line);

	getline(first_line, line);
	length = stoi(line);

	// parse image max value
	getline(image_file, line);
	this->max_colour_value = stoi(line);

	// parse image data
	for (line; std::getline(image_file, line); ) {
		std::istringstream image_line(line);
		std::string pixel;
		for (pixel; std::getline(image_line, pixel, ' ');) {
			try {
				if (pixel != "") {
					data.push_back(std::stoi(pixel));
				}
			}
			catch (...) {

			}
		}
	}

	if (data.size() != length*width) {
		throw 0;
	}
}


pgm_image::~pgm_image()
{
}
