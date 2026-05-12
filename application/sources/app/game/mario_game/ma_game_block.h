#ifndef __MA_GAME_BLOCK_H__
#define __MA_GAME_BLOCK_H__

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

#define NUM_BLOCKS (3)
#define SIZE_BITMAP_BLOCK_X (10)
#define SIZE_BITMAP_BLOCK_Y (10)


enum BlockType { BLOCK_BRICK, BLOCK_QUESTION };

typedef struct {
    bool visible;
    uint32_t x, y;
    BlockType type;
    bool hit;
    bool active;
} ma_game_block_t;

extern ma_game_block_t block[NUM_BLOCKS];


#endif //__MA_GAME_BLOCK_H__
