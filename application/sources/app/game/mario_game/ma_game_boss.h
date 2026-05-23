#ifndef __MA_GAME_BOSS_H__
#define __MA_GAME_BOSS_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "buzzer.h"
#include "scr_mario_game.h"

#define SIZE_BOSS_X (25)
#define SIZE_BOSS_Y (30)

#define BOSS_AXIS_X (128-SIZE_BOSS_X-5)
#define BOSS_AXIS_Y (64-10-SIZE_BOSS_Y-3)

enum BossState {
    LEFT,
    RIGHT,
    JUMP,
    // SHOOT
};


typedef struct {
    bool visible;
    uint32_t x, y;
    BossState state;
    uint8_t live;
} ma_game_boss_t;

extern ma_game_boss_t boss;

#endif //__MA_GAME_BOSS_H__