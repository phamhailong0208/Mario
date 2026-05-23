#ifndef __MA_GAME_BOSS_BULLET_H__
#define __MA_GAME_BOSS_BULLET_H__

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
#include <vector>

#define SIZE_BITMAP_BULLET_X (8)
#define SIZE_BITMAP_BULLET_Y (5)

#define NUMS_BULLET (3)

using namespace std;

// typedef struct {
//     bool visible;
//     uint32_t x, y;
//     // bool already;
//     // bool isFirst;
// } ma_game_boss_bullet_t;

class ma_game_boss_bullet_t {
private:
public:
	bool visible;
    int16_t x,y;
	ma_game_boss_bullet_t(int16_t x, int16_t y, bool visible) {
		this->x = x;
		this->y = y;
		this->visible = visible;
	}
};

// extern ma_game_boss_bullet_t;
extern vector<ma_game_boss_bullet_t> boss_bullet;
#endif //__MA_GAME_BOSS_BULLET_H__