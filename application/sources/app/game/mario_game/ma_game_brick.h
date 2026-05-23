#ifndef __MA_GAME_BRICK_H__
#define __MA_GAME_BRICK_H__

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

#define SIZE_BRICK_X (10)
#define SIZE_BRICK_Y (10)
#define BRICK_X_INTERVAL (100)

#define BRICK_AXIS_Y (33)
typedef struct {
    bool visible;
    uint32_t x, y;
} ma_game_brick_t;

extern ma_game_brick_t brick;

#endif //__MA_GAME_BRICK_H__