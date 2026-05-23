#ifndef __MA_GAME_FIREFLOWER_H__
#define __MA_GAME_FIREFLOWER_H__

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


// #define NUM_MUSHROOMS             (2)
#define SIZE_BITMAP_FIREFLOWER_X    (10)
#define SIZE_BITMAP_FIREFLOWER_Y    (10)
#define STEP_MUSHROOMSUPER_STEP_X          (5)
#define STEP_MUSHROOMSUPER_STEP_Y          (5)


typedef struct {
    bool visible;
    uint32_t x, y;
} ma_game_fire_flower_t;

extern ma_game_fire_flower_t fireflower;

#endif //__MA_GAME_FIREFLOWER_H__