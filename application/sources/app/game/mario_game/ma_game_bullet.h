#ifndef __MA_GAME_BULLET_H__
#define __MA_GAME_BULLET_H__

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


#define SIZE_BITMAP_BULLET_X (8)

#define SIZE_BITMAP_BULLET_Y (5)

typedef struct {
    bool visible;
    uint32_t x, y;
    bool already;
    bool isFirst;
} ma_game_bullet_t;

extern ma_game_bullet_t bullet;

#endif //__MA_GAME_BULLET_H__