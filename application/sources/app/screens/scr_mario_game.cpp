#include "scr_mario_game.h"
#include "ma_game_mario.h"
#include "ma_game_mushroom.h"
#include "ma_game_brick.h"
#include "ma_game_block.h"
#include "ma_game_mushroomsuper.h"
#include "ma_game_fireflower.h"
#include "ma_game_bullet.h"
#include "ma_game_boss.h"
#include "ma_game_boss_bullet.h"
#include "ma_game_warning.h"

// #define DEBUG_BOSS

/*****************************************************************************/
/* Variable Declaration - Mario game screen */
/*****************************************************************************/
uint8_t ma_game_state; 
uint16_t count_map_width;
uint16_t camera_x;
uint8_t brick_question_blink;
uint32_t ma_game_score= 0;
static ma_game_score_t gamescore;
// ma_game_fire_flower_t fireflower;
// ma_game_setting_t settingsetup;

/*****************************************************************************/
/* View - Mario game screen*/
/*****************************************************************************/
void ma_game_ground_display(){
	int32_t brick_screen_x = (int32_t)brick.x - (int32_t)camera_x;
    int32_t hole_left  = brick_screen_x - SIZE_BRICK_X / 2;
    int32_t hole_right = brick_screen_x + SIZE_BRICK_X + SIZE_BRICK_X / 2;
	int32_t mario_left_screen  = (int32_t)mario.x - (int32_t)camera_x;
	int32_t mario_right_screen = mario_left_screen + SIZE_BITMAP_MARIO_X_SMALL;
    for (int i=0; i<24; i++) {
		int x = 4 + i * 5 - (camera_x % 5);
		// if (i == ??) continue;
		if (x >= hole_left && x <= hole_right) {
            continue;
        }
        view_render.fillCircle(x, LCD_HEIGHT-10, 1, WHITE);
    }
   	// if (mario.on_ground == 1
    //     && mario_left_screen  >= hole_left
    //     && mario_right_screen <= hole_right) {
    // }
}

void ma_game_warning_display() {
	if (warning.visible == WHITE) {
		view_render.drawBitmap(warning.x, warning.y, bitmap_warning, 25, 25, WHITE);
	}
}

void ma_game_frame_display() {
	view_render.drawRect(0, 0, 128, 64, WHITE);
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(150, 64-10);
	view_render.print(ma_game_score);
	// view_reder.fillCircile
}

void ma_game_mario_display() {
	if (mario.visible == WHITE) {
		switch (mario.state)
		{
			case SMALL: {
				view_render.drawBitmap(mario.x, mario.y, bitmap_mario_small, 10, 13, WHITE);
				// mario.state = SMALL;
				// mario.isBig = false;
				// mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y_SMALL;
				// mario.x = mario_x;
				/* code */

			}
				break;
			case BIG: {
				view_render.drawBitmap(mario.x, mario.y, bitmap_mario, 20, 25, WHITE);
				// mario.state = BIG;
			}
				break;
			case FIRE: {
				// view_render.drawBitmap(mario.x, mario.y, bitmap_mario, 20, 25, WHITE);
				// mario.state = FIRE;
				if (brick_question_blink % 2 == 0) {
					view_render.drawBitmap(mario.x, mario.y, bitmap_mario, 20, 25, WHITE);
				} else {
					view_render.drawBitmap(mario.x, mario.y, bitmap_mario_fire, 20, 25, WHITE);
				}
			}
				break;
			default:
				break;
		}
	}
}

void ma_game_brick_display() {
	if (brick.visible == WHITE) {
		int32_t draw_x = (int32_t)brick.x - (int32_t) camera_x;
		if (draw_x > LCD_WIDTH || draw_x < 0) return;
		view_render.drawBitmap(draw_x, brick.y, bitmap_block_brick, 10, 10, WHITE);
	}
}

void ma_game_block_display() {
	for (uint8_t i = 0; i < NUM_BLOCKS; i++) {
		ma_game_block_t & b = block[i];
		int32_t draw_x = (int32_t)b.x - (int32_t)camera_x;
		if (b.visible == WHITE) {
			if (draw_x > LCD_WIDTH || draw_x < 0) continue;
			if (b.type == BLOCK_QUESTION) {
				if (b.active == true) {
					if (brick_question_blink % 2 == 0) {
						view_render.drawBitmap(draw_x, b.y, bitmap_block_question, 10, 10, WHITE);
					} else {
						view_render.drawBitmap(draw_x, b.y, bitmap_block_question_blink, 10, 10, WHITE);
					}
				}
				else {
					view_render.drawBitmap(draw_x, b.y, bitmap_block_brick, 10, 10, WHITE);
				}
			}
			else {
				view_render.drawBitmap(draw_x, b.y, bitmap_block_brick, 10, 10, WHITE);
			}
		}
	}
}

void ma_game_mushroom_display() {
	if (mushroom[0].visible == WHITE) {
		// if (mushroom[0].x > )
		view_render.drawBitmap(mushroom[0].x, mushroom[0].y, bitmap_mushroom, 12, 12, WHITE);
	}
}

void ma_game_mushroom_super_display() {
	if (mushroom_super.visible == WHITE) {
		view_render.drawBitmap(mushroom_super.x-camera_x, mushroom_super.y, bitmap_mushroom_super, 10, 10, WHITE);
	}
}

void ma_game_fire_flower_display() {
	if (fireflower.visible == WHITE) {
		view_render.drawBitmap(fireflower.x-camera_x, fireflower.y, bitmap_fire_flower, 10, 10, WHITE);
	}
}

void ma_game_bullet_display() {
	if (bullet.visible == WHITE) {
		view_render.drawBitmap(bullet.x, bullet.y, bitmap_bullet, 8, 5, WHITE);
	}
}

void ma_game_boss_display() {
	if (boss.visible == WHITE) {
		view_render.drawBitmap(boss.x, boss.y, bitmap_boss, 25, 30, WHITE);
	}
}

void ma_game_boss_live_display() {
	if (boss.visible == WHITE) {
		for (uint8_t i=0; i < boss.live; i++) {
			view_render.fillCircle(104 + 4*i, LCD_HEIGHT-55, 2, WHITE);
		}
	}
	// for (uint8_t i=0; i < boss.live; i++) {
	// 	view_render.fillCircle(104 + 4*i, LCD_HEIGHT-55, 2, WHITE);
	// }
}

void ma_game_boss_bullet_display() {
	for (uint8_t i=0; i < boss_bullet.size(); i++) {
		if (boss_bullet[i].visible == WHITE) {
			view_render.drawCircle(boss_bullet[i].x, boss_bullet[i].y, 2, WHITE);
		}
	}
}

static void view_scr_mario_game();

view_dynamic_t dyn_view_item_mario_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_mario_game
};

view_screen_t scr_mario_game = {
	&dyn_view_item_mario_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_mario_game() {
	if (ma_game_state == GAME_PLAY) {
		ma_game_frame_display();
		ma_game_ground_display();
		ma_game_mario_display();
		ma_game_mushroom_display();
		ma_game_brick_display();
		ma_game_block_display();
		ma_game_mushroom_super_display();
		ma_game_fire_flower_display();
		ma_game_bullet_display();
		ma_game_boss_display();
		ma_game_boss_live_display();
		ma_game_boss_bullet_display();
		ma_game_warning_display();
	}
	else if (ma_game_state == GAME_WIN) {
		view_render.clear();
		view_render.setTextSize(2);
		view_render.setTextColor(WHITE);
		view_render.setCursor(17, 24);
		view_render.print("YOU WIN");
		view_render.update();
	}
	else if (ma_game_state == GAME_OVER) {
		view_render.clear();
		view_render.setTextSize(2);
		view_render.setTextColor(WHITE);
		view_render.setCursor(17, 24);
		view_render.print("YOU LOSE");
		view_render.update();
	}
}

/*****************************************************************************/
/* Handle - Mario game screen */
/*****************************************************************************/
// void ar_game_level_setup() {
// 	eeprom_read(	EEPROM_SETTING_START_ADDR, \
// 					(uint8_t*)&settingsetup, \
// 					sizeof(settingsetup));
// }

// void ar_game_time_tick_setup() {
// 	timer_set(	AC_TASK_DISPLAY_ID, \
// 				MA_GAME_TIME_TICK, \
// 				MA_GAME_TIME_TICK_INTERVAL, \
// 				TIMER_PERIODIC);
// }

void ma_game_save_and_reset_score() {
	// eeprom_write(	EEPROM_SCORE_PLAY_ADDR, \
	// 				(uint8_t*)&ma_game_score, \
	// 				sizeof(ma_game_score));
	gamescore.score_now = ma_game_score;
	ma_game_score = 0;
}

void rank_ranking() {
	if (gamescore.score_now > gamescore.score_1st) {
		gamescore.score_3rd = gamescore.score_2nd;
		gamescore.score_2nd = gamescore.score_1st;
		gamescore.score_1st = gamescore.score_now;
	}
	else if (gamescore.score_now > gamescore.score_2nd) {
		gamescore.score_3rd = gamescore.score_2nd;
		gamescore.score_2nd = gamescore.score_now;
	}
	else if (gamescore.score_now > gamescore.score_3rd) {
		gamescore.score_3rd = gamescore.score_now;
	}
}

void scr_mario_game_handler(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		task_post_pure_msg(MA_GAME_MARIO_ID, 	 	MA_GAME_MARIO_SETUP);
		#ifdef DEBUG_BOSS
			task_post_pure_msg(MA_GAME_MUSHROOM_ID,     MA_GAME_MUSHROOM_RESET);
			task_post_pure_msg(MA_GAME_BLOCK_ID,			MA_GAME_BLOCK_RESET);
		#else
			task_post_pure_msg(MA_GAME_MUSHROOM_ID, 	MA_GAME_MUSHROOM_SETUP);
			task_post_pure_msg(MA_GAME_BLOCK_ID, 	    MA_GAME_BLOCK_SETUP);
		#endif
		task_post_pure_msg(MA_GAME_BRICK_ID, 		MA_GAME_BRICK_SETUP);
		task_post_pure_msg(MA_GAME_MUSHROOMSUPER_ID,MA_GAME_MUSHROOMSUPER_SETUP);
		task_post_pure_msg(MA_GAME_FIREFLOWER_ID, 	MA_GAME_FIREFLOWER_SETUP);
		task_post_pure_msg(MA_GAME_BULLET_ID,		MA_GAME_BULLET_SETUP);
		task_post_pure_msg(MA_GAME_BOSS_ID,			MA_GAME_BOSS_SETUP);
		// Setup timer
		// Set timer for display
		timer_set(	AC_TASK_DISPLAY_ID, \
			MA_GAME_TIME_TICK, \
			MA_GAME_TIME_TICK_INTERVAL, \
			TIMER_PERIODIC);
		// Set timer for brick question blink
		timer_set (
			MA_GAME_SCREEN_ID, \
			MA_GAME_BRICK_QUESTION_BLINK, \
			250, \
			TIMER_PERIODIC
		);
		// Set timer for mushroom down
		timer_set( MA_GAME_MUSHROOM_ID, \
			MA_GAME_MUSHROOM_DOWN, \
			125, \
			TIMER_PERIODIC
		);
		// Set timer for mario down
    	timer_set(	MA_GAME_MARIO_ID, \
                MA_GAME_MARIO_DOWN, \
                250, \
        		TIMER_PERIODIC);
		// Set timer for bullet spawn
		timer_set(	MA_GAME_BULLET_ID, \
				 MA_GAME_BULLET_SPAWN, \
				1000, \
				TIMER_PERIODIC);
		// Set timer for boss fire spawn

		// Set timer for boss down

		timer_set( MA_GAME_BOSS_ID, \
				  MA_GAME_BOSS_DOWN, \
				  250, \
				  TIMER_PERIODIC
		);
		// State update
		ma_game_state = GAME_PLAY;
		camera_x = 0;
		count_map_width = 0;
		brick_question_blink = 0;
		eeprom_read(	EEPROM_SCORE_START_ADDR, \
						(uint8_t*)&gamescore, \
						sizeof(gamescore));
	}
		break;

	case MA_GAME_TIME_TICK: {
		APP_DBG_SIG("MA_GAME_TIME_TICK\n");
		// Time tick
		task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_UPDATE);
		task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_CRASH);
		task_post_pure_msg(MA_GAME_MARIO_ID,			MA_GAME_MARIO_BOSS_BULLET_CRASH);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 		MA_GAME_MUSHROOM_RUN);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 		MA_GAME_MUSHROOM_CRASH);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID,			MA_GAME_MUSHROOM_BULLET_CRASH);
		task_post_pure_msg(MA_GAME_BLOCK_ID, 		    MA_GAME_BLOCK_UPDATE);
		task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_GET_ITEM);
		task_post_pure_msg(MA_GAME_BULLET_ID,			MA_GAME_BULLET_UPDATE);
		task_post_pure_msg(MA_GAME_BOSS_ID,				MA_GAME_BOSS_UPDATE);
		task_post_pure_msg(MA_GAME_BOSS_ID,				MA_GAME_BOSS_GET_HIT);
		task_post_pure_msg(MA_GAME_BOSS_BULLET_ID,		MA_GAME_BOSS_BULLET_UPDATE);
		// task_post_pure_msg(MA_GAME_BOSS_BULLET_ID,		MA_GAME_BOSS_BULLET_CRASH);
		// brick_question_blink++;
		// task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_LEFT);

	}
		break;
	case MA_GAME_BRICK_QUESTION_BLINK: {
		APP_DBG_SIG("MA_GAME_BRICK_QUESTION_BLINK\n");
		brick_question_blink++;
	}
		break;
	case MA_GAME_WIN: {
		APP_DBG_SIG("MA_GAME_WIN\n");
		ma_game_state = GAME_WIN;
		task_post_pure_msg(MA_GAME_MARIO_ID, 		MA_GAME_MARIO_RESET);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 	MA_GAME_MUSHROOM_RESET);
		task_post_pure_msg(MA_GAME_BLOCK_ID,		MA_GAME_BLOCK_RESET);
		task_post_pure_msg(MA_GAME_MUSHROOMSUPER_ID,MA_GAME_MUSHROOMSUPER_RESET);
		task_post_pure_msg(MA_GAME_FIREFLOWER_ID,	MA_GAME_FIREFLOWER_RESET);
		task_post_pure_msg(MA_GAME_BULLET_ID,		MA_GAME_BULLET_RESET);
		task_post_pure_msg(MA_GAME_BOSS_ID,			MA_GAME_BOSS_RESET);
		task_post_pure_msg(MA_GAME_BOSS_BULLET_ID, 	MA_GAME_BOSS_BULLET_RESET);
		//save highscore
		ma_game_save_and_reset_score();
		// eeprom_read(	EEPROM_SCORE_PLAY_ADDR, \
		// 				(uint8_t*)&gamescore.score_now, \
		// 				sizeof(gamescore.score_now));
		// ranking
		rank_ranking();
		eeprom_write(	EEPROM_SCORE_START_ADDR, \
						(uint8_t*)&gamescore, \
						sizeof(gamescore));
	}
		break;
	case MA_GAME_RESET: {
		APP_DBG_SIG("MA_GAME_RESET\n");
		// Reset game Object
		task_post_pure_msg(MA_GAME_MARIO_ID, 		MA_GAME_MARIO_RESET);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 	MA_GAME_MUSHROOM_RESET);
		task_post_pure_msg(MA_GAME_BLOCK_ID,		MA_GAME_BLOCK_RESET);
		task_post_pure_msg(MA_GAME_MUSHROOMSUPER_ID,MA_GAME_MUSHROOMSUPER_RESET);
		task_post_pure_msg(MA_GAME_FIREFLOWER_ID,	MA_GAME_FIREFLOWER_RESET);
		task_post_pure_msg(MA_GAME_BULLET_ID,		MA_GAME_BULLET_RESET);
		task_post_pure_msg(MA_GAME_BOSS_ID,			MA_GAME_BOSS_RESET);
		task_post_pure_msg(MA_GAME_BOSS_BULLET_ID, 	MA_GAME_BOSS_BULLET_RESET);

		// Timer Exit
		timer_set(	AC_TASK_DISPLAY_ID, \
					MA_GAME_EXIT_GAME, \
					MA_GAME_TIME_EXIT_INTERVAL, \
					TIMER_ONE_SHOT);
		// Save and reset Score
		ma_game_save_and_reset_score();
		// eeprom_read(	EEPROM_SCORE_PLAY_ADDR, \
		// 				(uint8_t*)&gamescore.score_now, \
		// 				sizeof(gamescore.score_now));
		// State update
		ma_game_state = GAME_OVER;
		// ranking
		rank_ranking();
		eeprom_write(	EEPROM_SCORE_START_ADDR, \
						(uint8_t*)&gamescore, \
						sizeof(gamescore));
	}
		// BUZZER_PlayTones(tones_3beep);
		break;

	case MA_GAME_EXIT_GAME: {
		APP_DBG_SIG("MA_GAME_EXIT_GAME\n");
		// State update
		ma_game_state = GAME_OFF;
		timer_remove_attr(AC_TASK_DISPLAY_ID, MA_GAME_TIME_TICK);
		timer_remove_attr(MA_GAME_MARIO_ID, MA_GAME_MARIO_DOWN);
		timer_remove_attr(MA_GAME_MUSHROOM_ID, MA_GAME_MUSHROOM_DOWN);
		timer_remove_attr(MA_GAME_SCREEN_ID, MA_GAME_BRICK_QUESTION_BLINK);
		
		// timer_remove_attr(MA_GAME_MUSHROOM_ID, MA_GAME_MUSHROOM_DOWN);
		count_map_width = 0;
		// Change the screen
		// SCREEN_TRAN(scr_game_over_handle, &scr_game_over);		
	}
		break;

	default:
		break;
	}
}
