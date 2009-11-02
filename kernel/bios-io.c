typedef unsigned short uint16_t;

typedef union _screen_character
{
	uint16_t word;
	struct _character
	{
		unsigned character  : 8;
		unsigned background : 4;
		unsigned foreground : 4;
	} character;
} screen_character;

static screen_character* screen = (screen_character*)0x0000b800;
static uint16_t screenIndex;

void koutinit ( void )
{
	screenIndex = 0;
}

void kputs ( const char* line )
{
	uint16_t remainingLineLength = 160;
	char ch;
	while (ch = *line)
	{
		screen[screenIndex].character.character = ch;
		screen[screenIndex].character.background = 0x0;
		screen[screenIndex].character.foreground = 0xF;
		screenIndex++;
		remainingLineLength--;
	}
	screenIndex += remainingLineLength;
}
