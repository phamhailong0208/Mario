#include "ma_game_mushroom.h"
#include "ma_game_mario.h"
#include "scr_mario_game.h"
#include "ma_game_bullet.h"
#include "ma_game_brick.h"

ma_game_mushroom_t mushroom[NUM_MUSHROOMS];

uint32_t gen_random_pos_mushroom() {
    uint32_t new_x;
    new_x = (rand() % 40) + LCD_WIDTH;
    return new_x;
}

void ma_game_mushroom_setup() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        mushroom[i].y = AXIS_Y_MUSHROOM;
        uint32_t new_x = gen_random_pos_mushroom();
        mushroom[i].x = new_x;
        mushroom[i].visible = WHITE;
        mushroom[i].turnBack = false;
        mushroom[i].isDown = false;
    }
}

void ma_game_mushroom_run () {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].visible == WHITE) {
            if (SIZE_BRICK_X > abs(brick.x + SIZE_BRICK_X - camera_x - mushroom[i].x)) {
                // mushroom[i].turnBack = true;
                mushroom[i].turnBack = !mushroom[i].turnBack;
            }

            if (mushroom[i].isDown == false && mushroom[i].turnBack == false) mushroom[i].x -= 2;
            else if (mushroom[i].isDown == false && mushroom[i].turnBack == true) mushroom[i].x += 2;
            // // else if (mushroom[i].isDown == false && SIZE_BRICK_X > abs(brick.x - camera_x - mushroom[i].x)) mushroom[i].x +=2;
            if (mushroom[i].x + SIZE_BITMAP_MUSHROOM_X > LCD_WIDTH) {
                // mushroom[i].visible = BLACK;
                mushroom[i].turnBack = false;
            }
            // if (mushroom[i].isDown == false) mushroom[i].x -=2;
        }
    }
}


void ma_game_mushroom_crash() {
    switch (mario.state)
    {
        case SMALL: {
            if(mushroom[0].visible == WHITE) {
                if (mario.visible == WHITE) {
                    if ( (int)SIZE_BITMAP_MARIO_Y_SMALL/2 > abs(mushroom[0].x - mario.x)) {
                        if (mario.on_ground == 0) {
                            mushroom[0].isDown = true;
                            // ma_game_score += 100;
                        }
                    }
                }
            }
        }
            break;
        case BIG: {
            if( mushroom[0].visible == WHITE ) {
                if (mario.visible == WHITE) {
                    if ( (int)SIZE_BITMAP_MARIO_Y/2 > abs(mushroom[0].x - mario.x)) {
                        if (mario.on_ground == 0) {
                            mushroom[0].isDown = true;
                            // ma_game_score += 100;
                        }
                    }
                }
            }
        }   
            break;
        case FIRE: {
            if( mushroom[0].visible == WHITE ) {
                if (mario.visible == WHITE) {
                    if ( (int)SIZE_BITMAP_MARIO_Y/2 > abs(mushroom[0].x - mario.x)) {
                        if (mario.on_ground == 0) {
                            mushroom[0].isDown = true;
                            // ma_game_score += 100;
                        }
                    }
                }
            }
        }
            break;
        default:
            break;
    }
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].visible == WHITE) {
            if (mario.visible == WHITE) {
                if (((int)SIZE_BITMAP_MARIO_X_SMALL/2 > abs(mushroom[i].x - mario.x))) {
                    if (mario.on_ground == 0) {
                        mushroom[i].isDown = true;
                    }
                }
            }
        }
    }
}

void ma_game_mushroom_bullet_crash() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].visible == WHITE) {
            if (bullet.visible == WHITE) {
                if (((int)SIZE_BITMAP_MUSHROOM_X/2 > abs(mushroom[i].x - bullet.x))) {
                    if (SIZE_BITMAP_MUSHROOM_Y > abs(mushroom[i].y - bullet.y)) {
                        task_post_pure_msg(MA_GAME_MUSHROOM_ID, MA_GAME_MUSHROOM_RESET);
                        task_post_pure_msg(MA_GAME_BULLET_ID, MA_GAME_BULLET_RESET);
                    }
                }
            }
        }
    }
}

void ma_game_mushroom_reset() {
    mushroom[0].isDown = false;
    // mushroom[0].x = mushroom[0].y = 0;
    mushroom[0].visible = BLACK;
}

void ma_game_mushroom_spawn() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].visible == BLACK) {
            uint32_t new_x = gen_random_pos_mushroom();
            mushroom[i].x = new_x;
            mushroom[i].y = AXIS_Y_MUSHROOM;
            mushroom[i].visible = WHITE;
            mushroom[i].turnBack = false;
        }
    }
}

void ma_game_mushroom_down(){
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].isDown == true) {
            mushroom[i].y += STEP_MUSHROOM_AXIS_Y_DOWN;
            if (mushroom[i].y >= LCD_HEIGHT) {
                mushroom[i].y = AXIS_Y_MUSHROOM;
                mushroom[i].visible = BLACK;
                // mushroom[i].x = gen_random_pos_mushroom();
                mushroom[i].isDown = false;
                ma_game_score += 100;
            }
        }
    }
}

void ma_game_mushroom_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_MUSHROOM_SETUP: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_SETUP\n");
        ma_game_mushroom_setup();
    }
        break;

    case MA_GAME_MUSHROOM_RUN: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_RUN\n");
        ma_game_mushroom_run();
    }
        break;

    case MA_GAME_MUSHROOM_CRASH: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_CRASH\n");
        ma_game_mushroom_crash();
    }
        break;
    case MA_GAME_MUSHROOM_BULLET_CRASH: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_BULLET_CRASH\n");
        ma_game_mushroom_bullet_crash();
    }
        break;
    case MA_GAME_MUSHROOM_DOWN: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_DOWN\n");
        ma_game_mushroom_down();
    }
        break;

    case MA_GAME_MUSHROOM_RESPAWN: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_RESPAWN\n");
        ma_game_mushroom_spawn();
        // timer_remove_attr(MA_GAME_MUSHROOM_ID, MA_GAME_MUSHROOM_RESPAWN);
    }
        break;

    case MA_GAME_MUSHROOM_RESET: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_RESET\n");
        ma_game_mushroom_reset();
    }
        break;

    default:
        break;
    }
}