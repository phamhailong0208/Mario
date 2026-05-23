#include "ma_game_brick.h"
#include "ma_game_mario.h"
// #include "ma_game_mushroomsuper.h"
ma_game_brick_t brick;
void ma_game_brick_setup() {
    brick.x = 65;
    brick.y = BRICK_AXIS_Y;
    brick.visible = WHITE;
}

void ma_game_brick_update() {
    // if (brick.visible == WHITE) {
    //     if (brick.x - camera_x <= 0) {
    //         brick.visible = BLACK;
    //     }
    // }
    return;
}

void ma_game_brick_respawn(){
    brick.visible = WHITE;
    brick.x = camera_x + LCD_WIDTH + (rand() % 30);
}

void ma_game_brick_reset() {
    brick.x = brick.y = 0;
    brick.visible = BLACK;
}

void ma_game_brick_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_BRICK_SETUP: {
        APP_DBG_SIG("MA_GAME_BRICK_SETUP\n");
        ma_game_brick_setup();
    }
        break;
    case MA_GAME_BRICK_UPDATE: {
        APP_DBG_SIG("MA_GAME_BRICK_UPDATE\n");
        ma_game_brick_update();
    }
        break;
    case MA_GAME_BLOCK_RESPAWN: {
        APP_DBG_SIG("MA_GAME_BRICK_RESPAWN\n");
        ma_game_brick_respawn();
    }
        break;
    case MA_GAME_BRICK_RESET: {
        APP_DBG_SIG("MA_GAME_BRICK_RESET\n");
        ma_game_brick_reset();
    }   
        break;
    default:
        break;
    }
}