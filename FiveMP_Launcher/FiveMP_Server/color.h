#pragma once

class Color {
private:
	int red, green, blue;

public:
	Color(int red = 0, int green = 0, int blue = 0);
	int r() const;
	int g() const;
	int b() const;
	void set(int red, int green, int blue);
};