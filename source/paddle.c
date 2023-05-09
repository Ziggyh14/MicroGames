
//{{BLOCK(paddle)

//======================================================================
//
//	paddle, 32x8@4, 
//	+ palette 256 entries, not compressed
//	+ 4 tiles Metatiled by 4x1 not compressed
//	Total size: 512 + 128 = 640
//
//	Time-stamp: 2023-02-12, 05:36:30
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int paddleTiles[32] __attribute__((aligned(4))) __attribute__((visibility("hidden")))=
{
	0x22222222,0x11111112,0x11111112,0x11111112,0x11111112,0x11111112,0x11111112,0x22222222,
	0x22222222,0x11111111,0x11110111,0x11111111,0x11311111,0x33311111,0x11111111,0x22222222,
	0x22222222,0x11111111,0x11113111,0x11111111,0x11111131,0x11111133,0x11111111,0x22222222,
	0x22222222,0x21111111,0x21111111,0x21111111,0x21111111,0x21111111,0x21111111,0x22222222,
};

const unsigned short paddlePal[16] __attribute__((aligned(4))) __attribute__((visibility("hidden")))=
{
	0x0000,0x009F,0x0003,0x0001,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};

//}}BLOCK(paddle)
