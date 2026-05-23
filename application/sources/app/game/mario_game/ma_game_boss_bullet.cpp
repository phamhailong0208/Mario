#include "ma_game_boss_bullet.h"
#include "ma_game_mario.h"
// #include "ma_game_mushroom.h"
// #include "ma_game_block.h"
#include "ma_game_boss.h"
#include "scr_mario_game.h"

vector<ma_game_boss_bullet_t> boss_bullet;

// void ma_game_boss_bullet_setup() {

// }

void ma_game_boss_bullet_spawn() {
    if(boss.visible == WHITE) {
        if (boss_bullet.size() < NUMS_BULLET) {
            ma_game_boss_bullet_t new_bullet(boss.x-2, boss.y + SIZE_BOSS_Y/2, WHITE);
            boss_bullet.push_back(new_bullet);
        }
    }
}

void ma_game_boss_bullet_update() {
    for(uint8_t i=0; i < boss_bullet.size(); i++){
        if (boss_bullet[i].visible == WHITE) {
            boss_bullet[i].x -= 5;
            if (boss_bullet[i].x <= 0) {
                boss_bullet.erase(boss_bullet.begin() + i);
            } 
        }
    }
}

void ma_game_boss_bullet_reset() {
	if (boss_bullet.size() != 0) {
		boss_bullet.clear();
		boss_bullet.shrink_to_fit();
	}
}


void ma_game_boss_bullet_handler(ak_msg_t* msg) {
    switch (msg->sig) {
        case MA_GAME_BOSS_BULLET_SPAWN: {
            APP_DBG_SIG("MA_GAME_BOSS_BULLET_SPAWN\n");
            ma_game_boss_bullet_spawn();
        }
            break;
        case MA_GAME_BOSS_BULLET_UPDATE: {
            APP_DBG_SIG("MA_GAME_BOSS_BULLET_UPDATE\n");
            ma_game_boss_bullet_update();
        }
            break;
        // case MA_GAME_BOSS_BULLET_CRASH: {
        //     APP_DBG_SIG("MA_GAME_BOSS_BULLET_CRASH\n");
        //     ma_game_boss_bullet_crash();
        // }   
            break;
        case MA_GAME_BOSS_BULLET_RESET: {
            APP_DBG_SIG("MA_GAME_BOSS_BULLET_RESET\n");
            ma_game_boss_bullet_reset();
        }
            break;    
        default:
            break;
    }
}