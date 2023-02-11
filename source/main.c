#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>
#include "macros.h"


//games return 1 to fail var if failed, 0 if succeded.
void *inflate(int time,int hits,int *fail);

void GAME_RETURN(){
    REG_DISPCNT = RESET_VRAM;
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG3;
}

void flashText(char * s);

int main(){

    int*fail;
    fail = malloc(sizeof (int));
/*
    //INIT BACKGROUND SPRITE
    memcpy(pal_bg_mem, brinPal, brinPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[0][0], brinTiles, brinTilesLen);
	// Load map into SBB 30
	memcpy(&se_mem[30][0], brinMap, brinMapLen);

*/
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;

    //INIT MENU TEXT
    tte_init_se_flashtext(0,BG_CBB(0)|BG_SBB(31));
    tte_write("#{P:35,55}");
    tte_write("Ziggy's Mega Micro Games!");

    tte_write("#{P:45,65}");
    tte_write("Press: Start");
    
    
    while(1){
        key_poll();
        if(key_hit(KEY_A)){
            tte_erase_screen();
            inflate(300,9,fail);
            if(*fail == 1){
            }
            else
            {
                tte_init_se_default(3,BG_CBB(1)|BG_SBB(30));
                tte_write("Succeed");
            }
        }
    }
    //REG_DISPCNT= RESET_VRAM;
    while(1);
    return 0;
}

void flashText(char * s){
    int i=0;
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG3;
    tte_init_se_flashtext(3,BG_CBB(0)|BG_SBB(31));
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
    REG_DISPCNT = RESET_VRAM;

    flashText("INFLATE!!!    ");

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    tte_init_se_default(0,BG_CBB(1)|BG_SBB(30));
   

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

    while(i<30){
        i++;
    }
    tte_erase_screen();
    GAME_RETURN();
    return 0;
}
