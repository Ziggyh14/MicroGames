#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>
#include "macros.h"

int *inflate(u16 time);

void flashText(char * s);

int main(){

    REG_DISPCNT= DCNT_MODE0 | DCNT_BG3;

    tte_init_se_flashtext(3,BG_CBB(0)|BG_SBB(31));
    tte_write("#{P:35,55}");
    tte_write("Ziggy's Mega Micro Games!");

    tte_write("#{P:45,65}");
    tte_write("Press: Start");
    
    
    while(1){
        key_poll();
        if(key_hit(KEY_A)){
            tte_erase_screen();
            flashText("INFLATE!!    ");
            flashText("FIGHT!!    ");
        }
    }
    //REG_DISPCNT= RESET_VRAM;
    while(1);
    return 0;
}

void flashText(char * s){
    int i=0;
    //REG_DISPCNT = DCNT_MODE0 | DCNT_BG3;
    tte_init_se_flashtext(3,BG_CBB(0)|BG_SBB(31));
    tte_write("#{P:0,20}");

    while(i<120){
        vid_vsync();
        if(i%5==0)
        {
            tte_write(s);
        }
        i++;

    }
    tte_erase_screen();
    


}

int* inflate(u16 time)
{

    REG_DISPCNT = RESET_VRAM;
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG3;

    tte_init_se_flashtext(3,BG_CBB(0)|BG_SBB(31));
    return 0;
}
