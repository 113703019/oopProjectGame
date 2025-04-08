#ifndef _ASCIISPRITE_H_
#define _ASCIISPRITE_H_

const int kidSprites = 4;
const int artHeight = 6;
const int artWidth = 12;
enum kidSprite {NORMAL,GOOD,BAD,TIRED};

const char asciiArt[kidSprites][artHeight][artWidth+1] = {{
	" /````````\\ ",
	"|          |",
	"(  |    |  )",
	" \\____^___/ ",
	"  <|   |\\   ",
	"   _| |_    "
},{
	" /````````\\ ",
	"|          |",
	"(  /\\   /\\ )",
	" \\____^___/ ",
	"  /|   |\\   ",
	"   _| |_    "
},{
	" /````````\\ ",
	"|          |",
	"(  \\    /  )",
	" \\____^___/ ",
	"  <|   |>   ",
	"   _| |_    "
},{
	" /````````\\ ",
	"|          |",
	"(  /    \\  )",
	" \\____^___/ ",
	"   |\\  |\\   ",
	"   _| |_    "
}};

#endif
