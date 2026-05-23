#include "ma_game_mushroomsuper.h"
#include "ma_game_mario.h"
#include "ma_game_block.h"
#include "scr_mario_game.h"

ma_game_mushroom_super_t mushroom_super;


void ma_game_mushroom_super_setup() {
    mushroom_super.y = block[1].y - 11;
    mushroom_super.x = block[1].x;
    mushroom_super.visible = BLACK;
    // mushroom_super.isMoving = false;
}

void ma_game_mushroom_super_spawn() {
    mushroom_super.x = block[1].x;
    mushroom_super.visible = WHITE;
    mushroom_super.y = block[1].y -11;
    // mushroom_super.isMoving = true;
}

void ma_game_mushroom_super_update() {
    // if (mushroom_super.x - camera_x < 0) {
    //     mushroom_super.visible = BLACK;
    // }
    if (mushroom_super.visible == WHITE) {
        if (mushroom_super.x < block[2].x + SIZE_BITMAP_BLOCK_X) {
            mushroom_super.x += STEP_MUSHROOMSUPER_STEP_X;
        }
        // mushroom_super.x += STEP_MUSHROOMSUPER_STEP_X;
        if (mushroom_super.x >= block[2].x + SIZE_BITMAP_BLOCK_X) {
            mushroom_super.y += STEP_MUSHROOMSUPER_STEP_Y;
        }
        if (mushroom_super.y >= LCD_HEIGHT - SIZE_BITMAP_MUSHROOMSUPER_Y - 10) {
            // mushroom_super.visible = BLACK;
            mushroom_super.y = LCD_HEIGHT - SIZE_BITMAP_MUSHROOMSUPER_Y - 10;
            // mushroom_super.isMoving = false;
            timer_remove_attr(MA_GAME_MUSHROOMSUPER_ID, MA_GAME_MUSHROOMSUPER_UPDATE);
            task_post_pure_msg(MA_GAME_MARIO_ID, MA_GAME_MARIO_MUSHROOMSUPER_READY);
        }
    }
}

void ma_game_mushroom_super_reset() {
    mushroom_super.visible = BLACK;
}

void ma_game_mushroom_super_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_MUSHROOMSUPER_SETUP: {
        APP_DBG_SIG("MA_GAME_MUSHROOMSUPER_SETUP\n");
        ma_game_mushroom_super_setup();
    }
        break;
    case MA_GAME_MUSHROOMSUPER_SPAWN: {
        APP_DBG_SIG("MA_GAME_MUSHROOMSUPER_SPAWN\n");
        ma_game_mushroom_super_spawn();
        timer_set(	MA_GAME_MUSHROOMSUPER_ID, \
                    MA_GAME_MUSHROOMSUPER_UPDATE, \
                    250, \
                    TIMER_PERIODIC);
        // Set timer for mushroom super update

    }
        break;
    case MA_GAME_MUSHROOMSUPER_UPDATE: {
        APP_DBG_SIG("MA_GAME_MUSHROOMSUPER_UPDATE\n");
        ma_game_mushroom_super_update();

     }
        break;
    case MA_GAME_MUSHROOMSUPER_RESET: {
        APP_DBG_SIG("MA_GAME_MUSHROOMSUPER_RESET\n");
        ma_game_mushroom_super_reset();
    }
        break;    
    default:
        break;
    }
}