#pragma once

float draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool bDrawRect = true, bool rescaleText = true);
void draw_text(float x, float y, const char* chSampleText, color_t color);
void draw_rect(float pos_x, float pos_y, float width, float height, int red, int green, int blue, int alpha);