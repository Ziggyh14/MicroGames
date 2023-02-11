#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>
#include "macros.h"
#include "ziggyzig.h"
#include "frame.h"
#include "metr.h"
#include "tube.h"


OBJ_ATTR obj_buffer[128];

//games return 1 to fail var if failed, 0 if succeded.
void *inflate(int time,int hits,int *fail);

void GAME_RETURN(){
    //REG_DISPCNT = RESET_VRAM;
    REG_DISPCNT= DCNT_MODE0 |DCNT_BG3|DCNT_BG0;
}

void flashText(char * s);

int main(){

    int*fail;
    int x=0,y=20,i;
    fail = malloc(sizeof (int));
    tte_init_se_default(0,BG_CBB(0)|BG_SBB(31));
    
    //INIT BACKGROUND SPRITE
    memcpy(&pal_bg_bank[0], ziggyzigPal, ziggyzigPalLen);
    memcpy(&pal_bg_bank[1],framePal,framePalLen);
    
    
    // Load tiles into CBB 0
	memcpy(&tile_mem[1][0], ziggyzigTiles, ziggyzigTilesLen);
	// Load map into SBB 30
	memcpy(&se_mem[29][0], ziggyzigMap, ziggyzigMapLen);

    memcpy(&se_mem[28][0],frameMap,frameMapLen);
    for(i=0;i<frameMapLen/2;i++)
    {
        se_mem[28][i] |=  0x1000;
    }

    memcpy(&tile_mem[2][0],frameTiles,frameTilesLen);

    REG_BG3CNT= BG_CBB(1) | BG_SBB(29) | BG_4BPP | BG_REG_64x32;
    REG_BG2CNT= BG_CBB(2) | BG_SBB(28) | BG_4BPP | BG_REG_32x32;
    REG_BG3HOFS= x;
	REG_BG3VOFS= y;
    REG_BG2HOFS= 8;
    REG_BG2VOFS= 245;

    //INIT MENU TEXT
    tte_write("#{P:35,55}");
    tte_write("Ziggy's Mega Micro Games!");

    tte_write("#{P:45,65}");
    tte_write("Press: Start");

    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG3;

    //INIT MENU TEXT
    
    while(1){
        vid_vsync();
        key_poll();
        if(key_hit(KEY_A)){
            tte_erase_screen();
            REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG3|  DCNT_BG2;
            inflate(300,9,fail);
            if(*fail == 1){
            }
            else
            {
                tte_init_se_default(0,BG_CBB(0)|BG_SBB(31));
                tte_write("Succeed");
            }
        }
        x++;
        REG_BG3HOFS= x;


    }
    //REG_DISPCNT= RESET_VRAM;
    while(1);
    return 0;
}

void flashText(char * s){
    int i=0;
    //REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG3;
    tte_init_se_flashtext(0,BG_CBB(0)|BG_SBB(31));
    tte_write("#{P:20,40}");

    while(i<45){
        vid_vsync();
        if(i%4==0)
        {
            tte_write(s);
            
        }
        i++;
    }
    tte_erase_screen();
    


}

void *inflate(int time,int hits, int *fail)
{
    int h=0,t=0,p=0,i=0;
    *fail = 1;
    //REG_DISPCNT = RESET_VRAM;
    

    flashText("INFLATE!!!    ");

    //SET UP SPRITE -------------------------------------------------
    memcpy(&tile_mem[4][0],tubeTiles,tubeTilesLen);
    memcpy(pal_obj_mem,tubePal,tubePalLen);
    oam_init(obj_buffer, 128);
	REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D |DCNT_MODE0|DCNT_BG3|DCNT_BG2;
    OBJ_ATTR *guy = &obj_buffer[0];
    obj_set_attr(guy,ATTR0_TALL,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(0)|0);
    guy->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(guy, 100, 70);

    
    OBJ_ATTR *guy1 = &obj_buffer[1];
    obj_set_attr(guy1,ATTR0_TALL,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(0)|0);
    guy1->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(guy1, 60, 70);

    OBJ_ATTR *guy2 = &obj_buffer[2];
    obj_set_attr(guy2,ATTR0_TALL,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(0)|0);
    guy2->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(guy2, 140, 70);


    vid_vsync();
    oam_copy(oam_mem, obj_buffer, 3);	// only need to update one


    //tte_init_se_default(0,BG_CBB(0)|BG_SBB(31));
   

    while((h<hits) && (t<=time)){
        vid_vsync();
        key_poll();
        if(key_hit(KEY_A)){
            h++;
            p = (h/(hits/3));
            switch(p){
            case 1:
                guy->attr2= ATTR2_BUILD(32, 0, 0);//tid, pb, ??
                guy1->attr2= ATTR2_BUILD(32, 0, 0);//tid, pb, ??
                guy2->attr2= ATTR2_BUILD(32, 0, 0);//tid, pb, ??

                break;
            case 2:
                guy->attr2= ATTR2_BUILD(64, 0, 0);//tid, pb, ??
                guy1->attr2= ATTR2_BUILD(64, 0, 0);//tid, pb, ??
                guy2->attr2= ATTR2_BUILD(64, 0, 0);//tid, pb, ??

                break;
            case 3:
                guy->attr2= ATTR2_BUILD(96, 0, 0);//tid, pb, ??
                guy1->attr2= ATTR2_BUILD(96, 0, 0);//tid, pb, ??
                guy2->attr2= ATTR2_BUILD(96, 0, 0);//tid, pb, ??
                *fail = 0;
                break;
            default:
                //tte_erase_line();
        }
        }
        t++;
        oam_copy(oam_mem, obj_buffer, 3);	// only need to update one

    }

    while(i<30){
        vid_vsync();
        i++;
    }
    tte_erase_screen();
    GAME_RETURN();
    return 0;
}
