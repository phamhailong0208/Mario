#include "scr_mario_game.h"

#include "screens.h"

#include "ma_game_mario.h"
#include "ma_game_mushroom.h"
#include "ma_game_block.h"
#include "ma_game_mushroomsuper.h"
/*****************************************************************************/
/* Variable Declaration - Mario game screen */
/*****************************************************************************/
uint8_t ma_game_state; 
uint16_t count_map_width;
uint16_t camera_x;
// ma_game_setting_t settingsetup;

/*****************************************************************************/
/* View - Mario game screen*/
/*****************************************************************************/
void ma_game_ground_display(){
    for (int i=0; i<11; i++) {
		int x = 4 + i * 12 - (camera_x % 12);
        view_render.fillCircle(x, LCD_HEIGHT-10, 1, WHITE);
    }
}

void ma_game_frame_display() {
	view_render.drawRect(0, 0, 128, 64, WHITE);

	// view_reder.fillCircile
}

void ma_game_mario_display() {
	if (mario.visible == WHITE) {
		if (mario.isBig == false) {
			view_render.drawBitmap(mario.x, mario.y, bitmap_mario_small, 10, 13, WHITE);
		}else {
			view_render.drawBitmap(mario.x, mario.y, bitmap_mario, 20, 25, WHITE);
		}
		
	}
}

void ma_game_block_display() {
	for (uint8_t i = 0; i < NUM_BLOCKS; i++) {
		ma_game_block_t & b = block[i];
		if (b.visible == WHITE) {
			if (b.type == BLOCK_QUESTION) {
				if (b.active == true) {
					view_render.drawBitmap(b.x-camera_x, b.y, bitmap_block_question, 10, 10, WHITE);
				}
				else {
					view_render.drawBitmap(b.x-camera_x, b.y, bitmap_block_brick, 10, 10, WHITE);
				}
			}
			else {
				view_render.drawBitmap(b.x-camera_x, b.y, bitmap_block_brick, 10, 10, WHITE);
			}
		}
	}
}

void ma_game_mushroom_display() {
	for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
		if (mushroom[i].visible == WHITE) {
			view_render.drawBitmap(mushroom[i].x, mushroom[i].y, bitmap_mushroom, 12, 12, WHITE);
		}
	}
}

void ma_game_mushroom_super_display() {
	if (mushroom_super.visible == WHITE) {
		view_render.drawBitmap(mushroom_super.x-camera_x, mushroom_super.y, bitmap_mushroom_super, 10, 10, WHITE);
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
		ma_game_block_display();
		ma_game_mushroom_super_display();
	}
	else if (ma_game_state == GAME_OVER) {
		view_render.clear();
		view_render.setTextSize(2);
		view_render.setTextColor(WHITE);
		view_render.setCursor(17, 24);
		view_render.print("YOU LOSE");
	}
}

/*****************************************************************************/
/* Handle - Archery game screen */
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

// void ar_game_save_and_reset_score() {
// 	eeprom_write(	EEPROM_SCORE_PLAY_ADDR, \
// 					(uint8_t*)&ar_game_score, \
// 					sizeof(ar_game_score));
// 	ar_game_score = 10;
// }

void scr_mario_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		task_post_pure_msg(MA_GAME_MARIO_ID, 	 	MA_GAME_MARIO_SETUP);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 	MA_GAME_MUSHROOM_SETUP);
		// task_post_pure_msg(MA_GAME_MUSHROOM_ID,     MA_GAME_MUSHROOM_RESET);
		task_post_pure_msg(MA_GAME_BLOCK_ID, 	    MA_GAME_BLOCK_SETUP);
		task_post_pure_msg(MA_GAME_MUSHROOMSUPER_ID, MA_GAME_MUSHROOMSUPER_SETUP);
		// Setup timer
		// Set timer for display
		timer_set(	AC_TASK_DISPLAY_ID, \
			MA_GAME_TIME_TICK, \
			MA_GAME_TIME_TICK_INTERVAL, \
			TIMER_PERIODIC);
		// Set timer for Mario action down
		timer_set(	MA_GAME_MARIO_ID, \
			MA_GAME_MARIO_DOWN, \
			MA_GAME_MARIO_DOWN_INTERVAL, \
			TIMER_PERIODIC);

		timer_set( MA_GAME_MUSHROOM_ID, \
			MA_GAME_MUSHROOM_RESPAWN, \
			5000, \
			TIMER_PERIODIC
		);

		// State update
		ma_game_state = GAME_PLAY;
		camera_x = 0;
		count_map_width = 0;
	}
		break;

	case MA_GAME_TIME_TICK: {
		APP_DBG_SIG("MA_GAME_TIME_TICK\n");
		// Time tick
		task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_UPDATE);
		task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_CRASH);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 		MA_GAME_MUSHROOM_RUN);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 		MA_GAME_MUSHROOM_CRASH);
		task_post_pure_msg(MA_GAME_BLOCK_ID, 		    MA_GAME_BLOCK_UPDATE);
		task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_GET_BIG);
		// task_post_pure_msg(MA_GAME_MARIO_ID, 			MA_GAME_MARIO_LEFT);

	}
		break;

	case MA_GAME_RESET: {
		APP_DBG_SIG("MA_GAME_RESET\n");
		// Reset game Object
		task_post_pure_msg(MA_GAME_MARIO_ID, 		MA_GAME_MARIO_RESET);
		task_post_pure_msg(MA_GAME_MUSHROOM_ID, 	MA_GAME_MUSHROOM_RESET);
		// Timer Exit
		timer_set(	AC_TASK_DISPLAY_ID, \
					MA_GAME_EXIT_GAME, \
					MA_GAME_TIME_EXIT_INTERVAL, \
					TIMER_ONE_SHOT);
		// Save and reset Score
		// ar_game_save_and_reset_score();
		// State update
		ma_game_state = GAME_OVER;
	}
		BUZZER_PlayTones(tones_3beep);
		break;

	case MA_GAME_EXIT_GAME: {
		APP_DBG_SIG("MA_GAME_EXIT_GAME\n");
		// State update
		ma_game_state = GAME_OFF;
		timer_remove_attr(AC_TASK_DISPLAY_ID, MA_GAME_TIME_TICK);
		timer_remove_attr(MA_GAME_MARIO_ID, MA_GAME_MARIO_DOWN);
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
