#include <custom/ui/color.h>

struct color COLOR_RED = {255,0,0,100};
struct color COLOR_BLUE = {0,32,255,100};
struct color COLOR_GREEN = {0,192,0,100};
struct color COLOR_BLACK = {0,0,0,100};
struct color COLOR_WHITE = {255,255,255,100};
struct color COLOR_LIGHT_GREY= {224,224,224,100};
struct color COLOR_GRAY = {128,128,128,100};
struct color COLOR_DARK_GRAY = {64,64,64,100};
struct color COLOR_PINK = {255,96,208,100};
struct color COLOR_PURPLE = {160,32,255,100};
struct color COLOR_LIGHT_BLUE ={80,208,255,100};
struct color COLOR_YELLO_GREEN ={96,255,128,100};
struct color COLOR_YELLOW ={225,224,32,100};
struct color COLOR_ORANGE ={255,160,16,100};
struct color COLOR_BROWN ={160,128,96,100};
struct color COLOR_PALE_PINK ={255,208,160,100};

void ColorNormalizer(struct color in_color,float out_color[4]){
    out_color[0] = in_color.R/255.0f;
    out_color[1] = in_color.G/255.0f;
    out_color[2] = in_color.B/255.0f;
    out_color[3] = in_color.A/100.0f;
}