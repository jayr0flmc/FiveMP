#include "stdafx.h"

Color::Color(int r, int g, int b) : red(r), green(g), blue(b) { }

int Color::r() const { return red; }
int Color::g() const { return green; }
int Color::b() const { return blue; }

void Color::set(int r, int g, int b) { this->red = r; this->green = g; this->blue = b; }
