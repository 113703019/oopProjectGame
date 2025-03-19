#ifndef _ASCIISPRITE_H_
#define _ASCIISPRITE_H_

const int kidSprites = 3;
const int artHeight = 6;
const int artWidth = 12;

char** asciiArt[kidSprites][artHeight][artWidth+1] = {{
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
}}

#endif
