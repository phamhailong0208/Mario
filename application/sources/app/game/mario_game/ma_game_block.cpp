#include "ma_game_block.h"
#include "ma_game_mario.h"
#include "ma_game_mushroomsuper.h"
ma_game_block_t block[NUM_BLOCKS];
void ma_game_block_setup() {
    block[0].x = 95;
    block[0].y = 18;
    block[0].type = BLOCK_BRICK;
    block[0].visible = WHITE;
    block[0].hit = false;
    block[0].active = false;

    block[1].x = 105;
    block[1].y = 18;
    block[1].type = BLOCK_QUESTION;
    block[1].visible = WHITE;
    block[1].hit = false;
    block[1].active = true;

    block[2].x = 115;
    block[2].y = 18;
    block[2].type = BLOCK_BRICK;
    block[2].visible = WHITE;
    block[2].hit = false;
    block[2].active = false;
}
void ma_game_block_update() {
    for (uint8_t i = 0; i < NUM_BLOCKS; i++) {
        ma_game_block_t & b = block[i];
        if (b.visible == WHITE) {
            if (mario.visible == WHITE) {
                if (b.hit) continue;
                if ((SIZE_BITMAP_BLOCK_X > abs(b.x -camera_x - mario.x))) {
                    if (mario.on_ground == 0) {
                        b.hit = true;
                        if (b.type == BLOCK_QUESTION && b.active == true) {
                            task_post_pure_msg(MA_GAME_MUSHROOMSUPER_ID, MA_GAME_MUSHROOMSUPER_SPAWN);
                            b.active = false;
                        }
                    }
                }
            }
        }
    }
    if (block[2].x - camera_x + SIZE_BITMAP_BLOCK_X < 0) {
        task_post_pure_msg(MA_GAME_BLOCK_ID, MA_GAME_BLOCK_RESPAWN);
    }
    // if (block[2].x + SIZE_BITMAP_BLOCK_X - camera_x < 0) {
    //     block[0].visible = block[1].visible = block[2].visible = BLACK;
    // }
}

void ma_game_block_respawn(){
    for (uint8_t i = 0; i < NUM_BLOCKS; i++) {
        block[i].visible = WHITE;
        block[i].hit = false;
        block[i].active = (block[i].type == BLOCK_QUESTION) ? true : false;
        block[i].x +=300;
    }
}

void ma_game_block_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_BLOCK_SETUP: {
        APP_DBG_SIG("MA_GAME_BLOCK_SETUP\n");
        ma_game_block_setup();
    }
        break;

    case MA_GAME_BLOCK_UPDATE: {
        APP_DBG_SIG("MA_GAME_BLOCK_UPDATE\n");
        ma_game_block_update();
    }
        break;
    case MA_GAME_BLOCK_RESPAWN: {
        APP_DBG_SIG("MA_GAME_BLOCK_RESPAWN\n");
        ma_game_block_respawn();
    }
        break;
    default:
        break;
    }
}