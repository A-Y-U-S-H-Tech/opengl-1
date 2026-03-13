#pragma once
struct color
{
    int R;
    int B;
    int G;
    int A;
};

extern struct color COLOR_RED;
extern struct color COLOR_BLUE;
extern struct color COLOR_GREEN;
extern struct color COLOR_BLACK;
extern struct color COLOR_WHITE;
extern struct color COLOR_LIGHT_GREY;
extern struct color COLOR_GRAY;
extern struct color COLOR_DARK_GRAY;
extern struct color COLOR_PINK;
extern struct color COLOR_PURPLE;
extern struct color COLOR_LIGHT_BLUE;
extern struct color COLOR_YELLO_GREEN;
extern struct color COLOR_YELLOW;
extern struct color COLOR_ORANGE;
extern struct color COLOR_BROWN;
extern struct color COLOR_PALE_PINK;
// (255,0,0,100)
// (0,255,0,100)
// (0,0,255,100)

void ColorNormalizer(struct color in_color,float out_color[4]);