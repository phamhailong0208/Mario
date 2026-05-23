#include "scr_menu_game.h"
#define NUMBER_MENU_ITEMS				(3)
#define MA_GAME_MENU_TEXT_AXIS_X        (90)
static uint8_t menu_index = 0;
// Menu items name
static char menu_items_name[NUMBER_MENU_ITEMS][30] = {
	"   Game Play   ",		// item 1
	"   Top        ",		// item 2
	"   Exit           ",	// item 3
};
uint8_t menu_items_icon_axis_y[3] = {
	30,							// icon frame 1
	42,							// icon frame 2
	54							// icon frame 3
};
/*****************************************************************************/
/* View - Menu game */
/*****************************************************************************/
static void view_scr_menu_game();

view_dynamic_t dyn_view_menu = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_menu_game
};

view_screen_t scr_menu_game = {
	&dyn_view_menu,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_menu_game() {
	// Frame White
    view_render.fillRect(0,0,128,64,BLACK); // clear screen
	view_render.setTextSize(1);
	for (uint8_t i = 0; i < 3; i++) {
		view_render.setTextColor(WHITE);
		view_render.setCursor(MA_GAME_MENU_TEXT_AXIS_X, menu_items_icon_axis_y[i]);
		view_render.print(menu_items_name[i]);
	}
    uint8_t cursor_y = 30 + (menu_index * 12); 
    view_render.setCursor(80, cursor_y);
    view_render.print(">");
}

// /*****************************************************************************/
// /* Handle - Menu game */
// /*****************************************************************************/
// void update_menu_screen_chosse() {
// 	// Frames location
// 	frame_white.axis_y =frame[screen_menu.location-screen_menu.screen].axis_y;
// 	frame[0].axis_y = 0;
// 	frame[1].axis_y = 22;
// 	frame[2].axis_y = 44;
// 	// update color menu
// 	menu_chosse._id = 1<<screen_menu.location;
// 	MENU_ITEMS_ICON_COLOR();
// 	// update scroll bar
// 	scroll_bar.axis_y = (SCREEN_MENU_H*screen_menu.location / NUMBER_MENU_ITEMS);
// }

void screen_tran_menu() {
	switch (menu_index) {
	case 0:	// item 1
			SCREEN_TRAN(scr_mario_game_handler,	&scr_mario_game	);
		break;
	case 1:	// item 2
			// SCREEN_TRAN(scr_chart_game_handler,	&scr_chart_game	);
            APP_DBG_SIG("item2");
		break;
	case 2:	// item 3
			SCREEN_TRAN(scr_idle_handle,		&scr_idle );
		break;
	
	default:
		break;
	}
}

void scr_menu_game_handler(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		view_render.initialize();
		view_render_display_on();
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		screen_tran_menu();

	}
		break;

	case AC_DISPLAY_BUTTON_UP_RELEASED: {
        APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
        if (menu_index > 0) menu_index--;
        else menu_index = 2; 
	}
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
        if (menu_index < 2) menu_index++;
        else menu_index = 0; 
	}
		break;

	default:
		break;
	}
}