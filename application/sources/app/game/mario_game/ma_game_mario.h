#ifndef __MA_GAME_MARIO_H__
#define __MA_GAME_MARIO_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "scr_mario_game.h"
#define STEP_MARIO_AXIS_Y_SMALL     (20)
#define STEP_MARIO_AXIS_Y           (25)
#define STEP_MARIO_AXIS_X     (1)
#define STEP_MARIO_AXIS_Y_DOWN (5)
#define STEP_MUSHROOM_AXIS_Y_DOWN (5)
#define SIZE_BITMAP_MARIO_X_SMALL   (10)
#define SIZE_BITMAP_MARIO_Y_SMALL   (13)
#define SIZE_BITMAP_MARIO_X   (20)
#define SIZE_BITMAP_MARIO_Y   (25)
#define AXIS_X_MARIO          (5)
#define AXIS_Y_MARIO          (38 + SIZE_BITMAP_MARIO_Y_SMALL - SIZE_BITMAP_MARIO_Y)
#define AXIS_Y_MARIO_SMALL    (38)

typedef struct {
    bool visible;
    uint32_t x, y;
    // uint8_t action_image;
    bool isBig;
    uint8_t on_ground;
} ma_game_mario_t;

extern ma_game_mario_t mario;

// extern uint8_t isJumping;

#endif //__MA_GAME_MARIO_H__
