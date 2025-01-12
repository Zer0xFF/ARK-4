#include "color.h"

#include <stdlib.h>
#include <time.h>

#include "scepaf.h"

u32 colors[] = {
	0x000000ff, // Default (random)
	0x000000ff, // Red
	0xa00000ff, // Light Red
	0x0000a5ff, // Orange
	0xa000a5ff, // Light Orange
	0x0000e6e6, // Yellow
	0xa000e6e6, // Light Yellow
	0x0000ff00, // Green
	0xa000b300, // Light Green
	0x00ff0000, // Blue
	0xa0ff0000, // Light Blue
	0x0082004b, // Indigo
	0xa082004b, // Light Indigo
	0x00ee82ee, // Violet
	0xa0ee82ee, // Light Violet
	0x00cbc0ff, // Pink
	0xa0cbc0ff, // Light Pink
	0x00993366, // Purple
	0xa0993366, // Light Purple
	0x00808000, // Teal
	0xa0808000, // Light Teal
	0x00cccc00, // Aqua
	0xa0cccc00, // Light Aqua
	0x00737373, // Grey
	0xa0737373, // Light Grey
	0x00000000, // Black
	0xa0000000, // Light Black
	0x00ffffff, // White
	0xafffffff, // Light White
};

static struct{
	u8 fg_color;
	u8 bg_color;
} random_colors[] = {
	{1, 11},
	{2, 11},
	{4, 11},
	{6, 11},
	{12, 11},
	{14, 11},
	{20, 11},
	{27, 11},
	{2, 12},
	{6, 12},
	{8, 12},
	{12, 12},
	{27, 12},
	{28, 12},
	{1, 14},
	{2, 14},
	{4, 14},
	{6, 14},
	{8, 14},
	{14, 14},
	{24, 14},
	{4, 8},
	{6, 8},
	{12, 8},
	{20, 8},
	{24, 8},
	{2, 8},
	{2, 9},
	{2, 25},
	{2, 26},
	{2, 28},
	{4, 8},
	{6, 8},
	{4, 12},
	{4, 13},
	{4, 15},
	{4, 17},
	{4, 18},
	{4, 19},
	{4, 20},
	{20, 20},
	{24, 20},
	{27, 20},
	{2, 22},
	{2, 23},
	{8, 23},
	{24, 23},
	{27, 23},
	{2, 24},
	{4, 24},
	{6, 24},
	{14, 24},
	{16, 24},
	{20, 24},
	{24, 24},
	{27, 24},
	{4, 25},
	{6, 25},
	{1, 25},
	{2, 25},
	{3, 25},
	{4, 25},
	{5, 25},
	{6, 25},
	{7, 25},
	{8, 25},
	{9, 25},
	{10, 25},
	{11, 25},
	{12, 25},
	{13, 25},
	{14, 25},
	{15, 25},
	{16, 25},
	{17, 25},
	{18, 25},
	{19, 25},
	{20, 25},
	{21, 25},
	{22, 25},
	{23, 25},
	{25, 25},
	{26, 25},
	{27, 25},
	{28, 25},
	{1, 26},
	{2, 26},
	{4, 26},
	{6, 26},
	{8, 26},
	{18, 26},
	{20, 26},
	{24, 26},
	{27, 26},
	{10, 12},
	{10, 20},
	{10, 24},
	{10, 27},
	{25, 7},
	{27, 7},
	{2, 2},
	{14, 2},
	{20, 2},
	{27, 3},
	{27, 5},
	{27, 7},
	{27, 8},
	{27, 9},
	{27, 11},
	{27, 25},
};


u32* color_data_pointer(void) {
	return (u32*)colors;
}

void color_check_random(vsh_Menu *vsh) {
	int picked;
	// Random Colors
	if ((vsh->config.ark_menu.vsh_fg_color || vsh->config.ark_menu.vsh_bg_color) == 0) {
		srand(time(NULL));
		picked = rand() % (sizeof(random_colors) / sizeof(random_colors[0]));
		vsh->config.ark_menu.vsh_fg_color = random_colors[picked].fg_color;
		vsh->config.ark_menu.vsh_bg_color = random_colors[picked].bg_color;
	}
}
