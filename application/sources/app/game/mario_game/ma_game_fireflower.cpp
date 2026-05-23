#include "ma_game_fireflower.h"
#include "ma_game_mario.h"
#include "ma_game_block.h"
#include "scr_mario_game.h"

ma_game_fire_flower_t fireflower;


void ma_game_fireflower_setup() {
    fireflower.x = block[1].x;
    fireflower.y = block[1].y - 11;
    fireflower.visible = BLACK;
}

void ma_game_fireflower_spawn() {
    fireflower.x = block[1].x;
    fireflower.y = block[1].y  - 11;
    fireflower.visible = WHITE;
}

void ma_game_fireflower_update() {
    // if (fireflower.x - camera_x < 0) {
    //     fireflower.visible = BLACK;
    // }
    if (fireflower.visible == WHITE) {
        if (fireflower.x < block[2].x + SIZE_BITMAP_BLOCK_X) {
            fireflower.x += STEP_MUSHROOMSUPER_STEP_X;
        }
        // fireflower.x += STEP_MUSHROOMSUPER_STEP_X;
        if (fireflower.x >= block[2].x + SIZE_BITMAP_BLOCK_X) {
            fireflower.y += STEP_MUSHROOMSUPER_STEP_Y;
        }
        if (fireflower.y >= LCD_HEIGHT - SIZE_BITMAP_FIREFLOWER_Y - 10) {
            // fireflower.visible = BLACK;
            fireflower.y = LCD_HEIGHT - SIZE_BITMAP_FIREFLOWER_Y - 10;
            timer_remove_attr(MA_GAME_FIREFLOWER_ID, MA_GAME_FIREFLOWER_UPDATE);
            task_post_pure_msg(MA_GAME_MARIO_ID, MA_GAME_MARIO_FIREFLOWER_READY);
        }
    }
}

void ma_game_fireflower_reset() {
    fireflower.visible = BLACK;
}

void ma_game_fireflower_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_FIREFLOWER_SETUP: {
        APP_DBG_SIG("MA_GAME_FIREFLOWER_SETUP\n");
        ma_game_fireflower_setup();
    }
        break;
    case MA_GAME_FIREFLOWER_SPAWN: {
        APP_DBG_SIG("MA_GAME_FIREFLOWER_SPAWN\n");
        ma_game_fireflower_spawn();
        // Set timer for fire flower update
        timer_set(	MA_GAME_FIREFLOWER_ID, \
                    MA_GAME_FIREFLOWER_UPDATE, \
                    250, \
                    TIMER_PERIODIC);
    }
        break;
    case MA_GAME_FIREFLOWER_UPDATE: {
        APP_DBG_SIG("MA_GAME_FIREFLOWER_UPDATE\n");
        ma_game_fireflower_update();
    }
        break;
    case MA_GAME_FIREFLOWER_RESET: {
        APP_DBG_SIG("MA_GAME_FIREFLOWER_RESET\n");
        ma_game_fireflower_reset();
    }
        break;    
    default:
        break;
    }
}