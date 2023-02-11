#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>
#include "macros.h"
#include "ziggyzig.h"


//games return 1 to fail var if failed, 0 if succeded.
void *inflate(int time,int hits,int *fail);

void GAME_RETURN(){
    //REG_DISPCNT = RESET_VRAM;
    REG_DISPCNT= DCNT_MODE0 |DCNT_BG3|DCNT_BG0;
}

void flashText(char * s);

int main(){

    int*fail;
    int x=0,y=20;
    fail = malloc(sizeof (int));
    tte_init_se_default(0,BG_CBB(0)|BG_SBB(31));
    
    //INIT BACKGROUND SPRITE
    memcpy(pal_bg_mem, ziggyzigPal, ziggyzigPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[1][0], ziggyzigTiles, ziggyzigTilesLen);
	// Load map into SBB 30
	memcpy(&se_mem[29][0], ziggyzigMap, ziggyzigMapLen);

    REG_BG3CNT= BG_CBB(1) | BG_SBB(29) | BG_4BPP | BG_REG_64x32;
    REG_BG3HOFS= x;
	REG_BG3VOFS= y;

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
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    tte_init_se_flashtext(0,BG_CBB(0)|BG_SBB(31));
    tte_write("#{P:0,20}");

    while(i<30){
        vid_vsync();
        if(i%5==0)
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

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    tte_init_se_default(0,BG_CBB(0)|BG_SBB(31));
   

    while((h<hits) && (t<=time)){
        vid_vsync();
        key_poll();
        if(key_hit(KEY_A)){
            h++;
            p = (h/(hits/3));
            switch(p){
            case 1:
                tte_write("#{P:0,50}ONE");
                break;
            case 2:
                tte_write("#{P:50,50}TWO");
                break;
            case 3:
                tte_write("#{P:100,50}THREEEEE!!");
                *fail = 0;
                break;
            default:
                tte_write("#{P:10,10}HIT");
                //tte_erase_line();
        }
        }
        t++;
    }

    while(i<60){
        vid_vsync();
        i++;
    }
    tte_erase_screen();
    GAME_RETURN();
    return 0;
}
