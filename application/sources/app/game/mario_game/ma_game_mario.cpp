#include "ma_game_mario.h"
#include "ma_game_mushroom.h"
#include "ma_game_block.h"
#include "ma_game_mushroomsuper.h"
ma_game_mario_t mario;
static uint32_t mario_y=AXIS_Y_MARIO_SMALL;
static uint32_t mario_x=AXIS_X_MARIO;
// uint8_t isJumping = 0;
void ma_game_mario_setup(){
    mario.x = AXIS_X_MARIO;
    mario.y = AXIS_Y_MARIO_SMALL;
    mario.visible = WHITE;
    mario.on_ground = 1;
    // mario.action_image = 0;
    // mario_y = AXIS_Y_MARIO_SMALL;
    // mario_x = AXIS_X_MARIO;
    mario.isBig = false;
}

void ma_game_mario_crash() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].visible == WHITE) {
            if (mario.visible == WHITE) {
                if ((SIZE_BITMAP_MARIO_X_SMALL > abs(mushroom[i].x - mario.x))) {
                    if (mario.on_ground == 1) {
                        mario.visible = BLACK;
                        task_post_pure_msg(MA_GAME_SCREEN_ID, MA_GAME_RESET);
                    }
                }
            }
        }
    }
}

void ma_game_mario_update() {
    if (ma_game_state == GAME_PLAY) {
        mario.y = mario_y;
        mario.x = mario_x;
    }
}

void ma_game_mario_up(){
    bool mario_hit_block = false;
    for (uint8_t i=0; i< NUM_BLOCKS; i++) {
        ma_game_block_t & b = block[i];
        if (b.visible == WHITE) {
            if ((SIZE_BITMAP_BLOCK_X > abs(b.x -camera_x - mario.x))) {
                if (mario.on_ground == 1) {
                    mario_y = b.y + SIZE_BITMAP_BLOCK_Y;
                    mario_hit_block = true;
                    break;
                }
            }
        }
    }
    if (!mario_hit_block) {
        if (mario.isBig) {
            mario_y -= STEP_MARIO_AXIS_Y;
        }
        else {
            mario_y -= STEP_MARIO_AXIS_Y_SMALL;
        }
    }
    mario.on_ground = 0;
    if (mario_y == 0) {mario_y = AXIS_Y_MARIO;}
}

void ma_game_mario_right(){
    mario_x += 5;
    count_map_width += 5;
    if (mario_x >= (int)LCD_WIDTH/2 - SIZE_BITMAP_MARIO_X_SMALL) {
        mario_x = (int)LCD_WIDTH/2 - SIZE_BITMAP_MARIO_X_SMALL;
        camera_x += 5;
    }
    if (count_map_width == 500) {
        // task_post_pure_msg(MA_GAME_BOSS_ID, MA_GAME_BOSS_SPAWN);
        //
        count_map_width = 0;
    }
    if (mario_x == LCD_WIDTH-SIZE_BITMAP_MARIO_X_SMALL) {mario_x = AXIS_X_MARIO;}
}

void ma_game_mario_left(){
    if (mario.on_ground == 1) {
        mario_x -= 5;
        count_map_width -= 5;
        if (mario_x == 0) {mario_x = AXIS_X_MARIO;}
    }
}

void ma_game_mario_down(){
    if (mario.on_ground == 0 ) {
        mario_y += STEP_MARIO_AXIS_Y_DOWN;
        if (mario.isBig) {
            if (mario_y >= LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y) {
                mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y;
                mario.on_ground = 1;

            }
        }
        else {
            if (mario_y >= LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y_SMALL) {
                mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y_SMALL;
                mario.on_ground = 1;
            }
        }
    }
}

void ma_game_mario_reset() {
    mario.x = AXIS_X_MARIO;
    mario.y = AXIS_Y_MARIO_SMALL;
    mario.visible = BLACK;
    mario_y = AXIS_Y_MARIO_SMALL;
}

void ma_game_mario_get_big() {
    if (mushroom_super.visible == WHITE) {
        if (SIZE_BITMAP_MUSHROOMSUPER_X > abs(mushroom_super.x -camera_x- mario.x)) {
            if (mario.on_ground == 1) {
                mario.isBig = true;
                mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y;
                task_post_pure_msg(MA_GAME_MUSHROOMSUPER_ID, MA_GAME_MUSHROOMSUPER_RESET);
                // mario.x = mario_x;
            }
        }
    }
    // mario.isBig = true;
}


void ma_game_mario_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_MARIO_SETUP: {
        APP_DBG_SIG("MA_GAME_MARIO_SETUP\n");
        ma_game_mario_setup();
    }
        break;

    case MA_GAME_MARIO_UPDATE: {
        APP_DBG_SIG("MA_GAME_MARIO_UPDATE\n");
        ma_game_mario_update();
    }
        break;

    case MA_GAME_MARIO_UP: {
        APP_DBG_SIG("MA_GAME_MARIO_UP\n");
        ma_game_mario_up();
    }
        break;
    case MA_GAME_MARIO_LEFT: {
        APP_DBG_SIG("MA_GAME_MARIO_LEFT\n");
        ma_game_mario_left();
    }
        break;

    case MA_GAME_MARIO_RIGHT: {
        APP_DBG_SIG("MA_GAME_MARIO_RIGHT\n");
        ma_game_mario_right();
    }
        break;

    case MA_GAME_MARIO_DOWN: {
        APP_DBG_SIG("MA_GAME_MARIO_DOWN\n");
        ma_game_mario_down();
    }
        break;

    case MA_GAME_MARIO_CRASH: {
        APP_DBG_SIG("MA_GAME_MARIO_CRASH\n");
        ma_game_mario_crash();
    }
        break;
    case MA_GAME_MARIO_GET_BIG: {
        APP_DBG_SIG("MA_GAME_MARIO_GET_BIG\n");
        ma_game_mario_get_big();
    }
        break;
    case MA_GAME_MARIO_RESET: {
        APP_DBG_SIG("MA_GAME_MARIO_RESET\n");
        ma_game_mario_reset();
    }
        break;

    default:
        break;
    }
}