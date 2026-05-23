#include "ma_game_warning.h"

ma_game_warning_t warning;


void ma_game_warning_setup() {
    warning.x = 51;
    warning.y = 19;
    warning.visible = WHITE;
}

void ma_game_warning_reset() {
    warning.visible = BLACK;
}

void ma_game_warning_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_WARNING_SETUP: {
        APP_DBG_SIG("MA_GAME_WARNING_SETUP\n");
        ma_game_warning_setup();
    }
        break;
    case MA_GAME_WARNING_RESET: {
        APP_DBG_SIG("MA_GAME_WARNING_RESET\n");
        ma_game_warning_reset();
    }
        break;   
    default:
        break;
    }
}