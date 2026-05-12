#include "scr_peashooter.h"

static void view_scr_peashooter() {
    view_render.drawLine(0, LCD_HEIGHT, 	LCD_WIDTH, LCD_HEIGHT,		WHITE);
	// view_render.drawLine(0, LCD_HEIGHT-10, 	LCD_WIDTH, LCD_HEIGHT-10,	WHITE);
    for (int i=0; i<11; i++) {
        view_render.fillCircle(4 + i * 12, LCD_HEIGHT-10, 1, WHITE);
    }
	view_render.drawRect(0, 0, 128, 64, WHITE);
    view_render.drawBitmap(MARIO_X_POS, MARIO_Y_POS, bitmap_mario, 20, 25, WHITE);
    view_render.drawBitmap(MUSHROOM_X_POS, MUSHROOM_Y_POS, bitmap_mushroom, 16, 16, WHITE);
}

view_dynamic_t dyn_view_peashooter = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_peashooter
};

view_screen_t scr_peashooter = {
    &dyn_view_peashooter,
    ITEM_NULL,
    ITEM_NULL,
    .focus_item = 0,
};

void scr_peashooter_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        break;

    case AC_DISPLAY_BUTON_MODE_RELEASED: {
        SCREEN_TRAN(scr_idle_handle, &scr_idle);
    }
        break;

    default:
        break;
    }
}
