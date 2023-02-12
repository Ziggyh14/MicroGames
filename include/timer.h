
//{{BLOCK(timer)

//======================================================================
//
//	timer, 256x64@4, 
//	+ palette 256 entries, not compressed
//	+ 256 tiles Metatiled by 8x8 not compressed
//	Total size: 512 + 8192 = 8704
//
//	Time-stamp: 2023-02-12, 01:15:19
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TIMER_H
#define GRIT_TIMER_H

#define timerTilesLen 8192
extern const unsigned int timerTiles[2048];

#define timerPalLen 512
extern const unsigned short timerPal[256];

#endif // GRIT_TIMER_H

//}}BLOCK(timer)
