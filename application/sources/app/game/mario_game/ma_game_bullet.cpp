#include "ma_game_bullet.h"
#include "ma_game_mario.h"
#include "ma_game_mushroom.h"
// #include "ma_game_block.h"
#include "scr_mario_game.h"

ma_game_bullet_t bullet;


void ma_game_bullet_setup() {
    bullet.x = 0;
    bullet.y = 0;
    bullet.visible = BLACK;
    bullet.already = false;
    bullet.isFirst = true;
}

void ma_game_bullet_spawn() {
    if (mario.state == FIRE) {
        if ((bullet.isFirst || bullet.already)) {
            bullet.x = mario.x + SIZE_BITMAP_MARIO_X;
            bullet.y = mario.y + SIZE_BITMAP_MARIO_Y/2;
            bullet.visible = WHITE;
            bullet.isFirst = false;
        }
    }
}

void ma_game_bullet_update() {
    if (bullet.visible == WHITE) {
        bullet.x += 5;
        if (bullet.x >= LCD_WIDTH) {
            bullet.x = mario.x + SIZE_BITMAP_MARIO_X;
            bullet.already = true;
            bullet.visible = BLACK;
        } else {
            bullet.already = false;
        }
    }
}

void ma_game_bullet_reset() {
    bullet.visible = BLACK;
    bullet.already = false;
    bullet.isFirst = true;
}

void ma_game_bullet_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_BULLET_SETUP: {
        APP_DBG_SIG("MA_GAME_BULLET_SETUP\n");
        ma_game_bullet_setup();
    }
        break;
    case MA_GAME_BULLET_SPAWN: {
        APP_DBG_SIG("MA_GAME_BULLET_SPAWN\n");
        ma_game_bullet_spawn();
    }
        break;
    case MA_GAME_BULLET_UPDATE: {
        APP_DBG_SIG("MA_GAME_BULLET_UPDATE\n");
        ma_game_bullet_update();
    }
        break;
    case MA_GAME_BULLET_RESET: {
        APP_DBG_SIG("MA_GAME_BULLET_RESET\n");
        ma_game_bullet_reset();
    }
        break;    
    default:
        break;
    }
}