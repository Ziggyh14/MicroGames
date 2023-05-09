
//{{BLOCK(frame)

//======================================================================
//
//	frame, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 14 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 32 + 448 + 2048 = 2528
//
//	Time-stamp: 2023-02-11, 19:25:15
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FRAME_H
#define GRIT_FRAME_H

#define frameTilesLen 448
extern const unsigned int frameTiles[112];

#define frameMapLen 2048
extern const unsigned short frameMap[1024];

#define framePalLen 32
extern const unsigned short framePal[16];

#endif // GRIT_FRAME_H

//}}BLOCK(frame)
