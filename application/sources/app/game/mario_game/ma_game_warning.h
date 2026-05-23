#ifndef __MA_GAME_WARNING_H__
#define __MA_GAME_WARNING_H__

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




typedef struct {
    bool visible;
    uint32_t x,y;
} ma_game_warning_t;

extern ma_game_warning_t warning;

#endif //__MA_GAME_WARNING_H__