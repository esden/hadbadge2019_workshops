/* vim: ts=4 st=4 : */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "mach_defines.h"
#include "sdk.h"
#include "gfx_load.h"
#include "cache.h"

//Pointer to the framebuffer memory.
uint8_t *fbmem;

//The dimensions of the framebuffer
#define FB_WIDTH 512
#define FB_HEIGHT 320

//Convenience macros
#define COMP_COLOR(A, R, G, B) ((((A) & 0xFF) << 24) | \
								(((B) & 0xFF) << 16) | \
								(((G) & 0xFF) <<  8) | \
								(((R) & 0xFF) <<  0))
#define FB_PIX(X, Y) fbmem[(X) + ((Y) * FB_WIDTH)]

//Here is where the party begins
void main(int argc, char **argv) {

	// Blank out fb while we're loading stuff by disabling all layers. This
	// just shows the background color.
	GFX_REG(GFX_BGNDCOL_REG)=0x202020; //a soft gray
	GFX_REG(GFX_LAYEREN_REG)=0; //disable all gfx layers

	FILE *f;
	f=fopen("/dev/console", "w");
	setvbuf(f, NULL, _IONBF, 0); //make console line unbuffered
	// Note that without the setvbuf command, no characters would be printed
	// until 1024 characters are buffered. You normally don't want this.
	fprintf(f, "\033C"); //clear the console. Note '\033' is the escape character.
	fprintf(f, "HEY!");

	// Reenable the tile layer to show the above text
	GFX_REG(GFX_LAYEREN_REG)=GFX_LAYEREN_TILEA;

	// Wait until button A is released
	while (MISC_REG(MISC_BTN_REG)) ;
	//Wait until button A is pressed
	while ((MISC_REG(MISC_BTN_REG) & BUTTON_A)==0) ;
}
