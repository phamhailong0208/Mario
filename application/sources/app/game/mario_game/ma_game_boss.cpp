#include "ma_game_boss.h"
#include "ma_game_mario.h"
#include "ma_game_bullet.h"
#include "scr_mario_game.h"

ma_game_boss_t boss;
static uint8_t count=0;
static bool finishedDown=false;
// #define DEBUG_BOSS
void ma_game_boss_setup() {
    boss.x = BOSS_AXIS_X;
    boss.y = BOSS_AXIS_Y;
    #ifdef DEBUG_BOSS
        boss.visible = WHITE;
    #else
        boss.visible = BLACK;
    #endif

    boss.state = LEFT;
    boss.live = 5;
}

void ma_game_boss_spawn() {
    if (boss.visible == BLACK) {
        boss.visible = WHITE;
    }
}

void boss_run_left() {
    boss.x -= 15;
}

void boss_run_right() {
    boss.x += 15;
}

void boss_jump() {
    if (boss.y == BOSS_AXIS_Y) {
        boss.y -= 20;
        finishedDown = false;
    }
}

void boss_shoot() {
    task_post_pure_msg(MA_GAME_BOSS_BULLET_ID, MA_GAME_BOSS_BULLET_SPAWN);
}

void ma_game_boss_update() {
    count ++;
    if (count == 10) {
        switch (boss.state)
        {
            case LEFT: {
                boss_run_left();
                if (rand()%2 == 1) boss_shoot();
                boss.state = RIGHT;
            }
                break;
            case RIGHT: {
                boss_run_right();
                if (rand()%2 == 1) boss_shoot();
                boss.state = JUMP;
            }
                break;
            case JUMP: {
                boss_jump();
                if (rand()%2 == 1) boss_shoot();
                boss.state = LEFT;
            }
            // case SHOOT: {
            //     if (finishedDown) {
         
            //     }
            //     boss_shoot();
            //     boss.state = LEFT;
            // }
                break;
            default:
                break;
        }
        count = 0;
    }
}

void ma_game_boss_down() {
    if (boss.y != BOSS_AXIS_Y) {
        boss.y += 10;
        if (boss.y >= BOSS_AXIS_Y) {
            boss.y = BOSS_AXIS_Y;
            finishedDown = true;
        }
    }
}

void ma_game_boss_bullet_get_hit() {
    if (boss.visible == WHITE) {
        if (bullet.visible == WHITE) {
            if (SIZE_BITMAP_BULLET_X > abs(bullet.x - boss.x)) {
                boss.live-- ;
                ma_game_score += 100;
                task_post_pure_msg(MA_GAME_BULLET_ID, MA_GAME_BULLET_RESET);
                if (boss.live == 0) {
                    // task_post_pure_msg(MA_GAME_BOSS_ID, MA_GAME_BOSS_RESET);
                    task_post_pure_msg(MA_GAME_SCREEN_ID, MA_GAME_WIN);
                }
            }
        }
    }
}

void ma_game_boss_reset() {
    boss.visible = BLACK;
    boss.state = LEFT;
}

void ma_game_boss_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_BOSS_SETUP: {
        APP_DBG_SIG("MA_GAME_BOSS_SETUP\n");
        ma_game_boss_setup();
    }
        break;
    case MA_GAME_BOSS_SPAWN: {
        APP_DBG_SIG("MA_GAME_BOSS_SPAWN\n");
        task_post_pure_msg(MA_GAME_WARNING_ID, MA_GAME_WARNING_RESET);
        ma_game_boss_spawn();
        
        timer_remove_attr(MA_GAME_BOSS_ID, MA_GAME_BOSS_SPAWN);
    }
        break;
    case MA_GAME_BOSS_GET_HIT: {
        APP_DBG_SIG("MA_GAME_BOSS_GET_HIT");
        ma_game_boss_bullet_get_hit();
    }
        break;
    case MA_GAME_BOSS_UPDATE: {
        APP_DBG_SIG("MA_GAME_BOSS_UPDATE\n");
        ma_game_boss_update();
    }
        break;
    case MA_GAME_BOSS_DOWN: {
        APP_DBG_SIG("MA_GAME_BOSS_DOWN\n");
        ma_game_boss_down();
    }
        break;
    case MA_GAME_BOSS_RESET: {
        APP_DBG_SIG("MA_GAME_BOSS_RESET\n");
        ma_game_boss_reset();
    }
        break;    
    default:
        break;
    }
}