#include "scr_chart_game.h"

/*****************************************************************************/
/* Variable Declaration - Charts game */
/*****************************************************************************/
static ma_game_score_t gamescore_chart;

/*****************************************************************************/
/* View - Charts game */
/*****************************************************************************/
static void view_scr_chart_game();

view_dynamic_t dyn_view_item_chart_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_chart_game
};

view_screen_t scr_chart_game = {
	&dyn_view_item_chart_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_chart_game() {
	view_render.clear();
	view_render.fillScreen(WHITE);
	view_render.fillRoundRect(1, 28, 126, 12, 5, 0);
	view_render.fillRoundRect(1, 51, 126, 12, 5, 0);
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(16, 30);
	view_render.print(gamescore_chart.score_1st);
	view_render.setCursor(86, 30);
	view_render.print(": 1st");
	view_render.setCursor(16, 54);
	view_render.print(gamescore_chart.score_3rd);
	view_render.setCursor(86, 54);
	view_render.print(": 3rd");
	view_render.setTextColor(BLACK);
	view_render.setCursor(16, 42);
	view_render.print(gamescore_chart.score_2nd);
	view_render.setCursor(86, 42);
	view_render.print(": 2nd");
}

/*****************************************************************************/
/* Handle - Charts game */
/*****************************************************************************/
void scr_chart_game_handler(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		view_render.initialize();
		view_render_display_on();
		// Read score 
		eeprom_read(	EEPROM_SCORE_START_ADDR, \
						(uint8_t*)&gamescore_chart, \
						sizeof(gamescore_chart));
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		SCREEN_TRAN(scr_menu_game_handler, &scr_menu_game);	
	}
		// BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_UP_LONG_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_LONG_PRESSED\n");
		// Reset score charts
		// gamescore_chart.score_1st = 0;
		// gamescore_chart.score_2nd = 0;
		// gamescore_chart.score_3rd = 0;
		// eeprom_write(	EEPROM_SCORE_START_ADDR, \
		// 				(uint8_t*)&gamescore_chart, \
		// 				sizeof(gamescore_chart));
	}
		// BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
		// SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
	}	
		// BUZZER_PlayTones(tones_cc);
		break;

	default:
		break;
	}
}