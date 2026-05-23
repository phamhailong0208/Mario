/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   13/08/2016
 ******************************************************************************
**/

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "ak.h"


#include "app_if.h"
#include "app_eeprom.h"
#include "app_data.h"

/*****************************************************************************/
/* SYSTEM task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	SYSTEM_AK_FLASH_UPDATE_REQ = AK_USER_DEFINE_SIG,
};

/*****************************************************************************/
/* FIRMWARE task define
 */
/*****************************************************************************/
/* define timer */
#define FW_PACKED_TIMEOUT_INTERVAL			(5000)
#define FW_UPDATE_REQ_INTERVAL				(5000)

/* define signal */
enum {
	FW_CRENT_APP_FW_INFO_REQ = AK_USER_DEFINE_SIG,
	FW_CRENT_BOOT_FW_INFO_REQ,
	FW_UPDATE_REQ,
	FW_UPDATE_SM_OK,
	FW_TRANSFER_REQ,
	FW_INTERNAL_UPDATE_APP_RES_OK,
	FW_INTERNAL_UPDATE_BOOT_RES_OK,
	FW_SAFE_MODE_RES_OK,
	FW_UPDATE_SM_BUSY,
	FW_PACKED_TIMEOUT,
	FW_CHECKING_REQ
};

/*****************************************************************************/
/*  LIFE task define
 */
/*****************************************************************************/
/* define timer */
#define AC_LIFE_TASK_TIMER_LED_LIFE_INTERVAL		(1000)

/* define signal */
enum {
	AC_LIFE_SYSTEM_CHECK = AK_USER_DEFINE_SIG,
};

/*****************************************************************************/
/*  SHELL task define
 */
/*****************************************************************************/
/* define timer */

/* define signal */
enum {
	AC_SHELL_LOGIN_CMD = AK_USER_DEFINE_SIG,
	AC_SHELL_REMOTE_CMD,
};

/*****************************************************************************/
/* IF task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	AC_IF_PURE_MSG_IN = AK_USER_DEFINE_SIG,
	AC_IF_PURE_MSG_OUT,
	AC_IF_COMMON_MSG_IN,
	AC_IF_COMMON_MSG_OUT,
	AC_IF_DYNAMIC_MSG_IN,
	AC_IF_DYNAMIC_MSG_OUT,
};

/*****************************************************************************/
/* UART_IF task define
 */
/*****************************************************************************/
/* timer signal */
/* define signal */

enum {
	AC_UART_IF_INIT = AK_USER_DEFINE_SIG,
	AC_UART_IF_PURE_MSG_OUT,
	AC_UART_IF_COMMON_MSG_OUT,
	AC_UART_IF_DYNAMIC_MSG_OUT,
	AC_UART_IF_PURE_MSG_IN,
	AC_UART_IF_COMMON_MSG_IN,
	AC_UART_IF_DYNAMIC_MSG_IN,
};

/*****************************************************************************/
/*  SCREENS task define
 */
/*****************************************************************************/
/* define timer */
#define AC_DISPLAY_INITIAL_INTERVAL									(100)
#define AC_DISPLAY_STARTUP_INTERVAL									(2000)
#define AC_DISPLAY_IDLE_INTERVAL									(20000)
#define AC_DISPLAY_LOGO_INTERVAL									(10000)
#define AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE_INTERAL				(150)

/* define signal */
enum {
	AC_DISPLAY_INITIAL = AK_USER_DEFINE_SIG,
	AC_DISPLAY_SHOW_LOGO,
	AC_DISPLAY_SHOW_IDLE,
	AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE,
	AC_DISPLAY_SHOW_FW_UPDATE,
	AC_DISPLAY_SHOW_FW_UPDATE_ERR,
};

/*****************************************************************************/
/*  BUTTON task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	AC_DISPLAY_BUTTON_MODE_PRESSED = 1,						
	AC_DISPLAY_BUTTON_MODE_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_MODE_RELEASED,
	AC_DISPLAY_BUTTON_UP_PRESSED,							
	AC_DISPLAY_BUTTON_UP_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_UP_RELEASED,
	AC_DISPLAY_BUTTON_DOWN_PRESSED,						
	AC_DISPLAY_BUTTON_DOWN_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_DOWN_RELEASED,
};

/*****************************************************************************/
/*  Archery game 'SCREEN' task define
 */
/*****************************************************************************/
/* define timer */
#define MA_GAME_TIME_TICK_INTERVAL									(100)
#define MA_GAME_TIME_EXIT_INTERVAL									(5000)
#define MA_GAME_MARIO_DOWN_INTERVAL									(600)
#define MA_GAME_MARIO_LEFT_INTERVAL									(300)
#define MA_GAME_MUSHROOM_DOWN_INTERVAL								(200)
#define MAP_WIDTH                                                   (1000)
/* define signal */
enum {
	MA_GAME_INITIAL_SETUP = AK_USER_DEFINE_SIG,
	MA_GAME_TIME_TICK = MA_GAME_DEFINE_SIG,
	MA_GAME_BRICK_QUESTION_BLINK,
	MA_GAME_WIN,
	MA_GAME_RESET,
	MA_GAME_EXIT_GAME,
};


/*****************************************************************************/
/*  Mario game 'MARIO' task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	MA_GAME_MARIO_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_MARIO_UPDATE,
	MA_GAME_MARIO_UP,
	MA_GAME_MARIO_RIGHT,
	MA_GAME_MARIO_LEFT,
	MA_GAME_MARIO_CRASH,
	MA_GAME_MARIO_BOSS_BULLET_CRASH,
	MA_GAME_MARIO_DOWN,
	MA_GAME_MARIO_GET_ITEM,
	MA_GAME_MARIO_MUSHROOMSUPER_READY,
	MA_GAME_MARIO_FIREFLOWER_READY,
	MA_GAME_MARIO_RESET,
};

/*****************************************************************************/
/*  Mario game 'MUSHROOM' task define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
enum {
	MA_GAME_MUSHROOM_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_MUSHROOM_RUN,
	MA_GAME_MUSHROOM_CRASH,
	MA_GAME_MUSHROOM_BULLET_CRASH,
	MA_GAME_MUSHROOM_DOWN,
	MA_GAME_MUSHROOM_RESPAWN,
	MA_GAME_MUSHROOM_RESET,
};
/*****************************************************************************/
/*  Mario game 'BRICK' task define
 */
/*****************************************************************************/
enum {
	MA_GAME_BRICK_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_BRICK_UPDATE,
	MA_GAME_BRICK_RESPAWN,
	MA_GAME_BRICK_RESET
};
/*****************************************************************************/
/*  Mario game 'WARNING' task define
 */
/*****************************************************************************/
enum {
	MA_GAME_WARNING_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_WARNING_RESET
};
/*****************************************************************************/
/*  Mario game 'BLOCK' task define
 */
/*****************************************************************************/
enum {
	MA_GAME_BLOCK_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_BLOCK_UPDATE,
	MA_GAME_BLOCK_RESPAWN,
	MA_GAME_BLOCK_RESET
};
/*****************************************************************************/
/*  Mario game 'MUSHROOMSUPER' task define
 */
/*****************************************************************************/
enum {
	MA_GAME_MUSHROOMSUPER_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_MUSHROOMSUPER_SPAWN,
	MA_GAME_MUSHROOMSUPER_UPDATE,
	MA_GAME_MUSHROOMSUPER_RESET,
};
/*****************************************************************************/
/*  Mario game 'FIREFLOWER' task define
 */
/*****************************************************************************/
enum {
	MA_GAME_FIREFLOWER_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_FIREFLOWER_SPAWN,
	MA_GAME_FIREFLOWER_UPDATE,
	MA_GAME_FIREFLOWER_RESET,
};
/*****************************************************************************/
/*  Mario game 'MARIO FIRE BULLET' task define
 */
/*****************************************************************************/
enum {
	MA_GAME_BULLET_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_BULLET_SPAWN,
	MA_GAME_BULLET_UPDATE,
	MA_GAME_BULLET_RESET,
};
/*****************************************************************************/
/*  Mario game 'BOSS' task define
 */
/*****************************************************************************/
enum {
	MA_GAME_BOSS_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_BOSS_SPAWN,
	MA_GAME_BOSS_GET_HIT,
	MA_GAME_BOSS_UPDATE,
	MA_GAME_BOSS_DOWN,
	MA_GAME_BOSS_RESET,
};
/*****************************************************************************/
/*  Mario game 'BOSS BULET' task define
 */
/*****************************************************************************/
enum {
	// MA_GAME_BOSS_BULLET_SETUP = MA_GAME_DEFINE_SIG,
	MA_GAME_BOSS_BULLET_SPAWN,
	MA_GAME_BOSS_BULLET_UPDATE,
	// MA_GAME_BOSS_BULLET_CRASH,
	MA_GAME_BOSS_BULLET_RESET,
};
/*****************************************************************************/
/*  app function declare
 */
/*****************************************************************************/
#define APP_MAGIC_NUMBER	0xAABBCCDD
#define APP_VER				{0, 0, 0, 3}

typedef struct {
	uint32_t magic_number;
	uint8_t version[4];
} app_info_t;

extern const app_info_t app_info;

extern void* app_get_boot_share_data();
extern int  main_app();

#ifdef __cplusplus
}
#endif

#endif //__APP_H__
