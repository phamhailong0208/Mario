#ifndef __MA_GAME_MUSHROOM_H__
#define __MA_GAME_MUSHROOM_H__

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


#define NUM_MUSHROOMS             (2)
#define SIZE_BITMAP_MUSHROOM_X    (12)
#define SIZE_BITMAP_MUSHROOM_Y    (12)
#define AXIS_Y_MUSHROOM          (39)

// enum mushroom_state {
//     DOWN =0,
//     RUN
// };



typedef struct {
    bool visible;
    uint32_t x, y;
    // mushroom_state state;
    bool isReset;
    // uint8_t action_image;
} ma_game_mushroom_t;

extern ma_game_mushroom_t mushroom[NUM_MUSHROOMS];

#endif //__MA_GAME_MUSHROOM_H__