#include "../include/frame_buffer.h"
#include "../include/system.h"

FrameBuffer::Writer::Writer(const unsigned char &foreground, const unsigned char &background)
{
    fg = foreground;
	bg = background;
}

// Implementation need to be done so that when we write new data it begin with cursor position
void FrameBuffer::Writer::print(char* str)
{
    char *vid_mem = START;
	for (int i = 0; str[i] != '\0'; i++)
	{
		vid_mem[i * 2] = str[i];
		vid_mem[(i * 2) + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
		cursorX++;
	}
	updateCursor();
}

// For now dont use it
void FrameBuffer::Writer::printHex(unsigned char val)
{
    char* x = "00";
    char* hex = "0123456789ABCDEF";
    x[0] = hex[(val >> 4) & 0xF];
    x[1] = hex[val & 0xF];
    FrameBuffer::Writer::print(x);
}

// Will be later used to give user option to set color theme for user shell (or console)
void FrameBuffer::Writer::colorTheme(const unsigned char &foreground, const unsigned char &background) 
{
	fg = foreground;
	bg = background;
}

// Updates the cursor
void FrameBuffer::Writer::updateCursor()
{
    unsigned position;

    position = cursorY * s_width + cursorX-1;                                                      

    outportb(0x3D4, 14);                                                                
    outportb(0x3D5, position >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, position);

	char *vid_mem = START;
	vid_mem[cursorX*2] = '_';
	vid_mem[(cursorX*2) + 1] = (((unsigned char)0x0 & 0x0f) << 4) | ((unsigned char)0xf & 0x0f);
}