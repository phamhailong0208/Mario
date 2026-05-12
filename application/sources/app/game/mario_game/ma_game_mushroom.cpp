#include "ma_game_mushroom.h"
#include "ma_game_mario.h"
#include "scr_mario_game.h"

ma_game_mushroom_t mushroom[NUM_MUSHROOMS];

uint32_t gen_random_pos_mushroom(uint8_t i) {
    uint32_t new_x;
    bool ok;
    do {
        ok = true;
        new_x = (rand() % 60) + 150;
        for (uint8_t j = 0; j < i; j++) {
            // if (j == i) continue;
            if (abs((int)new_x - (int)mushroom[j].x) < 40) {
                ok = false;
                break;
            }
        }
    } while (!ok);
    return new_x;
}

void ma_game_mushroom_setup() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        mushroom[i].isReset = false;
        mushroom[i].y = AXIS_Y_MUSHROOM;
        uint32_t new_x = gen_random_pos_mushroom(i);
        mushroom[i].x = new_x;
        mushroom[i].visible = WHITE;
    }
}

void ma_game_mushroom_run () {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].visible == WHITE) {
            mushroom[i].x -= 2;
            if (mushroom[i].x == 0) {
                    uint32_t new_x = gen_random_pos_mushroom(i);
                    mushroom[i].x = new_x;
                }
            }
        }
}


void ma_game_mushroom_crash() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (mushroom[i].visible == WHITE) {
            if (mario.visible == WHITE) {
                if ((SIZE_BITMAP_MARIO_X_SMALL > abs(mushroom[i].x - mario.x))) {
                    if (mario.on_ground == 0) {
                        // mushroom[i].visible = BLACK;
                        // mushroom[i].state = DOWN;
                        mushroom[i].visible = BLACK;                      
                        // timer_set(  MA_GAME_MUSHROOM_ID, \
                        //             MA_GAME_MUSHROOM_RESPAWN, \
                        //             4000, \
                        // TIMER_PERIODIC);
                    }
                }
            }
        }
    }
}

void ma_game_mushroom_reset() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        // mushroom[i].x = (rand() % 60) + 150;
        mushroom[i].isReset = true;
        mushroom[i].visible = BLACK;
        // mushroom[i].action_image = rand() % 3 + 1;
    }
}

void ma_game_mushroom_spawn() {
    for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        if (!mushroom[i].isReset && mushroom[i].visible == BLACK) {
            uint32_t new_x = gen_random_pos_mushroom(i);
            mushroom[i].x = new_x;
            mushroom[i].visible = WHITE;
        }
    }
}

void ma_game_mushroom_handle(ak_msg_t* msg) {
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

    case MA_GAME_MUSHROOM_DOWN: {
        APP_DBG_SIG("MA_GAME_MUSHROOM_DOWN\n");
        // for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
        //     if (mushroom[i].state == DOWN) {
        //         mushroom[i].y += STEP_MUSHROOM_AXIS_Y_DOWN;
        //         if (mushroom[i].y >= LCD_HEIGHT) {
        //             mushroom[i].y = AXIS_Y_MUSHROOM;
        //             mushroom[i].visible = BLACK;
        //         }
        //     }
        // }
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