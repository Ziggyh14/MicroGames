#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>
#include "macros.h"



OBJ_ATTR obj_buffer[128];
OBJ_ATTR empty_buffer[128];

//games return 1 to fail var if failed, 0 if succeded.
void inflate(int time,int hits,int *fail);
void bite(int time,int speed,int *fail);
void catch_(int speed,int *fail);
void shake(int time,int hits,int *fail);

OBJ_ATTR *init_timer();
void updateTimer(int time,int count,OBJ_ATTR* TIMER);

void GameChoose(int time,int hits,int speed,int *fail){
    u16 r = rand();   
    switch(r%3){
        case 0:
            inflate(time,hits,fail);
            break;
        case 1:
            bite((time*0.75)/1,speed,fail);
            break;
        case 2:
            catch_(speed/2,fail);
            break;
        default:
        break;
    }
    return;
}

void GAME_RETURN(){
    //REG_DISPCNT = RESET_VRAM;
    oam_copy(oam_mem,empty_buffer,128);
    REG_DISPCNT= DCNT_MODE0 |DCNT_BG3|DCNT_BG0|DCNT_BG2;
}

void flashText(char * s);

int main(){

    int*fail;
    int x=0,y=20,i,lives=4,combo=0,ii=0;
    int time=300,speed=2,hits=8;
    fail = malloc(sizeof (int));

    //REG_TM2D=4000; -0x  
   // REG_TM2CNT= TM_FREQ_64;   // we're using the 1024 cycle timer
   // REG_TM3CNT= TM_ENABLE | TM_CASCADE;

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

    while(1){
    REG_DISPCNT= DCNT_MODE0 |DCNT_BG3|DCNT_BG0;


    //INIT MENU TEXT
    tte_write("#{P:35,55}");
    tte_write("Ziggy's Mega Micro Games!");

    tte_write("#{P:45,65}");
    tte_write("Press: A");

    while(1){
        vid_vsync();
        key_poll();
        if(key_hit(KEY_A)){
            tte_erase_screen();
            REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG3|DCNT_BG2;
            break;
        }
        x++;
        vid_vsync();
        REG_BG3HOFS= x;

        
    }

    
    while(lives>0){
        time = 240 - 30*(combo/5);
        speed = 2 + 1*(combo/5);
        hits = 6 + 1*(combo/5);
        GameChoose(time,hits,speed,fail);
        if(*fail == 1){
            lives--;
        }
        combo++;
        vid_vsync();
        tte_write("#{P:45,50}LIVES: ");
        *(u16 *)0x0600f996 =0xD010+(0x0001*lives);
       // tte_write("#{P:45,80}SCORE: ");
       // *(u16 *)0x0600fa96 =0xD010+(0x0001*combo);
        while(ii<30){
            ii++;
            vid_vsync();
        }
        tte_erase_screen();
        ii=0;
        time = (time%1)%90;
        
    }
    

    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG3;
    tte_write("\nYou LOOSE\n");
    tte_write("Press A to try again");

    //REG_DISPCNT= RESET_VRAM;
    while(1){
        key_poll();
        if(key_hit(KEY_A)){
            break;
        }
        x++;
        vid_vsync();
        REG_BG3HOFS= x;
    }
    tte_erase_screen();
    }
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

void inflate(int time,int hits, int *fail)
{
    int h=0,t=0,p=0,i=0;
    *fail = 1;
    //REG_DISPCNT = RESET_VRAM;
    

    flashText("PUMP!!    ");

    //SET UP SPRITE -------------------------------------------------
    memcpy(&tile_mem[4][0],tubeTiles,tubeTilesLen);
    memcpy32(pal_obj_bank[0],tubePal,16);
    memcpy32(&tile_mem[4][128],pumpTiles,512);
    memcpy16(pal_obj_bank[1],pumpPal,16);
    oam_init(obj_buffer, 128);
	REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D |DCNT_MODE0|DCNT_BG3|DCNT_BG2;
    OBJ_ATTR *guy = &obj_buffer[1];
    obj_set_attr(guy,ATTR0_TALL,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(0)|0);
    guy->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(guy, 100, 70);

    
    OBJ_ATTR *guy1 = &obj_buffer[2];
    obj_set_attr(guy1,ATTR0_TALL,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(0)|0);
    guy1->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(guy1, 60, 70);

    OBJ_ATTR *guy2 = &obj_buffer[3];
    obj_set_attr(guy2,ATTR0_TALL,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(0)|0);
    guy2->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(guy2, 140, 70);

    OBJ_ATTR *pump = &obj_buffer[4];
    obj_set_attr(pump,ATTR0_TALL,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(1)|128);
    pump->attr2= ATTR2_BUILD(128,1, 0);//tid, pb, ??
    obj_set_pos(pump, 170, 70);

    OBJ_ATTR* timer =  init_timer();
    vid_vsync();
    oam_copy(oam_mem, obj_buffer, 5);


    //tte_init_se_default(0,BG_CBB(0)|BG_SBB(31));
   

    while((h<hits) && (t<=time)){
        key_poll();
        if(key_hit(KEY_A)){
            pump->attr2= ATTR2_BUILD(128+32, 1, 0);//tid, pb, ??
            vid_vsync();
            oam_copy(oam_mem, obj_buffer, 5);	// only need to update one

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
                t=time;
                break;
            default:
                //tte_erase_line();
        }
        }
        t++;
        pump->attr2= ATTR2_BUILD(128, 1, 0);//tid, pb, ??

        updateTimer(time,t,timer);
        vid_vsync();
        oam_copy(oam_mem, obj_buffer, 5);	// only need to update one

    }

    while(i<30){
        vid_vsync();
        i++;
    }
    tte_erase_screen();
    GAME_RETURN();
    return;
}

void bite(int time,int speed, int *fail){

    int t=0,x,y=64,i=0,m=1*speed;
    *fail = 1;
    x=(rand()%5)*20;

    flashText("BITE!!    ");

    memcpy32(&tile_mem[4][0],mouthTiles,1024);
    memcpy32(&tile_mem[4][128],cowTiles,512);
    memcpy16(pal_obj_bank[0],mouthPal,16);
    memcpy16(pal_obj_bank[3],cowPal,16);
    oam_init(obj_buffer, 128);

    OBJ_ATTR *mouth = &obj_buffer[1];
    obj_set_attr(mouth,ATTR0_SQUARE,ATTR1_SIZE_64x64,
                ATTR2_PALBANK(0)|0);
    mouth->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(mouth,150,50);

    OBJ_ATTR *cow = &obj_buffer[2];
    obj_set_attr(cow,ATTR0_WIDE,ATTR1_SIZE_32x64,
                ATTR2_PALBANK(3)|128);
    cow->attr2= ATTR2_BUILD(128, 3, 0);//tid, pb, ??
    obj_set_pos(cow,x,y);

    OBJ_ATTR *TIMER= init_timer();
    REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D |DCNT_MODE0|DCNT_BG3|DCNT_BG2;
    
    vid_vsync();
    oam_copy(oam_mem, obj_buffer, 3);

    
    while(t<=time){
        key_poll();
        if(x>=150){
            m=-1*speed;
        }
        if(x<=20){
            m=1*speed;
        }
        x+=m;
        obj_set_pos(cow,x,y);
        if(key_hit(KEY_A)){
            mouth->attr2= ATTR2_BUILD(64, 0, 0);//tid, pb, ??
            if(x>120){
                cow->attr2= ATTR2_BUILD(128+32, 3, 0);//tid, pb, ??
                *fail =0;
                
            }
            t=time;
        }
        vid_vsync();
        updateTimer(time,t,TIMER);
        oam_copy(oam_mem, obj_buffer, 3);
        t++;

    }
    while(i<30){
        if(x>=150){
            m=-1*speed;
        }
        if(x<=20){
            m=1*speed;
        }
        x+=m;
        obj_set_pos(cow,x,y);
        vid_vsync();
        oam_copy(oam_mem, obj_buffer, 3);

        i++;
    }
    GAME_RETURN();

    return;

}

void catch_(int speed,int *fail){

    int by=0,bx=0,px=125,py=100;
    *fail=1;
    flashText("CATCH!!    ");

    bx = 10+20*(rand()%8);
    init_timer();

    memcpy32(&tile_mem[4][0],paddleTiles,32);
    memcpy32(&tile_mem[4][4],ballTiles,128);
    memcpy16(pal_obj_bank[0],paddlePal,16);
    memcpy16(pal_obj_bank[3],ballPal,16);
    oam_init(obj_buffer, 128);

    OBJ_ATTR *paddle = &obj_buffer[1];
    obj_set_attr(paddle,ATTR0_WIDE,ATTR1_SIZE_32x8,
                ATTR2_PALBANK(0)|0);
    paddle->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(paddle,px,py);

    
    OBJ_ATTR *o = &obj_buffer[2];
    obj_set_attr(o,ATTR0_SQUARE,ATTR1_SIZE_32x32,
                ATTR2_PALBANK(3)|4);
        o->attr2= ATTR2_BUILD(4, 3, 0);//tid, pb, ??
        obj_set_pos(o,bx,by);
    
    REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D |DCNT_MODE0|DCNT_BG3|DCNT_BG2;
    vid_vsync();
    oam_copy(oam_mem, obj_buffer, 3);

    while(1){
        vid_vsync();
        by+=speed;
        key_poll();
        px += 2*key_tri_horz();
       
        if(by>=py-16){
            if(px>bx-32&&px<bx+32){
                *fail=0;
                break;
            }
            break;
        }


        obj_set_pos(paddle,px,py);
        obj_set_pos(o,bx,by);

        oam_copy(oam_mem, obj_buffer, 3);

    }
    GAME_RETURN();
    return;


}

void shake(int time,int hits,int *fail){

    int t=0,h=0,i=0;
    *fail =1;

    flashText("SHAKE!!    ");

    memcpy(&tile_mem[4][0],shakerTiles,tubeTilesLen);
    memcpy32(pal_obj_bank[0],shakerPal,16);
    oam_init(obj_buffer, 128);

	REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D |DCNT_MODE0|DCNT_BG3|DCNT_BG2;
    
    OBJ_ATTR *TIMER = init_timer();
    OBJ_ATTR *shaker = &obj_buffer[1];
    obj_set_attr(shaker,ATTR0_SQUARE,ATTR1_SIZE_64x64,
                ATTR2_PALBANK(0)|0);
    shaker->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??
    obj_set_pos(shaker, 50,36);

    OBJ_ATTR *glass = &obj_buffer[2];
    obj_set_attr(glass,ATTR0_SQUARE,ATTR1_SIZE_64x64,
                ATTR2_PALBANK(0)|192);
    glass->attr2= ATTR2_BUILD(192, 0, 0);//tid, pb, ??
    obj_set_pos(glass, 164, 100);

    vid_vsync();
    oam_copy(oam_mem, obj_buffer, 5);

    while((h<hits) && (t<=time)){
        key_poll();
        if(key_hit(KEY_A)){
            shaker->attr2= ATTR2_BUILD(64, 0, 0);//tid, pb, ??
            vid_vsync();
            oam_copy(oam_mem, obj_buffer, 3);
            h++;
            if(h=hits){
                shaker->attr2= ATTR2_BUILD(128, 0, 0);//tid, pb, ??
                *fail = 0;

            }else{
                shaker->attr2= ATTR2_BUILD(0, 0, 0);//tid, pb, ??

            }
        }
        t++;

        updateTimer(time,t,TIMER);
        vid_vsync();
        oam_copy(oam_mem, obj_buffer, 3);	// only need to update one

    }

    while(i<30){
        vid_vsync();
        i++;
    }
    GAME_RETURN();
    return;

}


OBJ_ATTR *init_timer(){
    memcpy(&tile_mem[5][0],timerTiles,timerTilesLen);
    memcpy16(pal_obj_bank[1],timerPal,32);
    OBJ_ATTR *t = &obj_buffer[0];
    obj_set_attr(t,ATTR0_SQUARE,ATTR1_SIZE_64x64,
                ATTR2_PALBANK(1)|512);
    t->attr2= ATTR2_BUILD(512, 1, 0);//tid, pb, ??
    obj_set_pos(t, 0, 0);
    //obj_hide(t);
    return t;
}

void updateTimer(int time,int count,OBJ_ATTR* TIMER){
    int p = count/(time/4);
    //if(p>=4){
    //    TIMER->attr2= ATTR2_BUILD(512, 1, 0);//tid, pb, ?
    //}
    TIMER->attr2= ATTR2_BUILD(((64*(p%4))+512), 1, 0);//tid, pb, ?
}