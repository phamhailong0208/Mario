#include "ma_game_mario.h"
#include "ma_game_mushroom.h"
#include "ma_game_block.h"
#include "ma_game_mushroomsuper.h"
#include "ma_game_fireflower.h"
#include "ma_game_boss_bullet.h"
#include "ma_game_brick.h"
// #include "ma"
#define MARIO_STATE 0

static uint32_t mario_y=0;
static int32_t mario_x=0;
ma_game_mario_t mario;

static bool mushroomSuperReady = false;
static bool fireflowerReady = false;
bool mario_on_brick = false;
// uint8_t isJumping = 0;

void ma_game_mario_setup() {
#if ( MARIO_STATE == 2) 
    mario_x = AXIS_X_MARIO;
    mario_y = AXIS_Y_MARIO;
    mario.state = FIRE;
#elif ( MARIO_STATE == 0)
    mario_x = AXIS_X_MARIO;
    mario_y = AXIS_Y_MARIO_SMALL;
    mario.state = SMALL;
#endif
    // mario.
    mario.visible = WHITE;
    mario.on_ground = 1;
    mario.on_brick = 0;
    // mario.state = FIRE;
}

// void check_mario_crash() {

// }

void ma_game_mario_crash() {
    switch (mario.state) {
        case SMALL: {
            // check_mario_crash();
            for (uint8_t i = 0; i < NUM_MUSHROOMS; i++) {
                if (mushroom[i].visible == WHITE) {
                    if (mario.visible == WHITE) {
                        if (mario.on_ground == 1 && mushroom[i].isDown == false) {
                            if (SIZE_BITMAP_MARIO_X_SMALL > abs(mushroom[i].x - mario.x)) {
                                // mario.visible = BLACK;
                                task_post_pure_msg(MA_GAME_SCREEN_ID, MA_GAME_RESET);
                            }
                        }
                    }
                }
            }
        }
            break;
        case BIG: {
            for (uint8_t i=0; i < NUM_MUSHROOMS; i++) {
                if (mushroom[i].visible == WHITE) {
                    if (mario.visible == WHITE) {
                        if (mario.on_ground == 1 && mushroom[i].isDown == false) {
                            if (SIZE_BITMAP_MARIO_X > abs(mushroom[i].x - mario.x)) {
                                mario.state = SMALL;
                                mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y_SMALL;
                                task_post_pure_msg(MA_GAME_MUSHROOM_ID, MA_GAME_MUSHROOM_RESET);
                            }
                        }
                    }
                }
            }
        }
            break;
        case FIRE: {
           for (uint8_t i=0; i < NUM_MUSHROOMS; i++) {
                if (mushroom[i].visible == WHITE) {
                    if (mario.visible == WHITE) {
                        if (mario.on_ground == 1 && mushroom[i].isDown == false) {
                            if (SIZE_BITMAP_MARIO_X > abs(mushroom[i].x - mario.x)) {
                                mario.state = BIG;
                                task_post_pure_msg(MA_GAME_MUSHROOM_ID, MA_GAME_MUSHROOM_RESET);
                            }
                        }
                    }
                }
            }
        }   
            break; 
        default:
            break;
    }
}

void ma_game_mario_boss_bullet_crash() {
    if (mario.visible == WHITE) {
        for (uint8_t i = 0; i < boss_bullet.size(); i++) {
            if (boss_bullet[i].visible == WHITE) {
                switch (mario.state)
                {
                    case SMALL: {
                        if (SIZE_BITMAP_MARIO_X_SMALL/2 > abs(mario.x - boss_bullet[i].x)) {
                            if (SIZE_BITMAP_MARIO_Y_SMALL/2 >abs(mario.y - boss_bullet[i].y)) {
                                task_post_pure_msg(MA_GAME_SCREEN_ID, MA_GAME_RESET);
                            }
                        }
                    }
                        break;
                    case BIG: {
                        if (SIZE_BITMAP_MARIO_X/2 > abs(mario.x - boss_bullet[i].x)) {
                            if (SIZE_BITMAP_MARIO_Y/2 >abs(mario.y - boss_bullet[i].y)) {
                                mario.state = SMALL;
                                mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y_SMALL;
                                boss_bullet.erase(boss_bullet.begin() + i);
                            }
                        }
                    }
                        break;
                    case FIRE: {
                        if (SIZE_BITMAP_MARIO_X/2 > abs(mario.x - boss_bullet[i].x)) {
                            if (SIZE_BITMAP_MARIO_Y/2 >abs(mario.y - boss_bullet[i].y)) {
                                mario.state = BIG;
                                boss_bullet.erase(boss_bullet.begin() + i);
                            }
                        }
                    }   
                        break;             
                    default:
                        break;
                }
            }
        }
    }
}

void ma_game_mario_update() {
    if (ma_game_state == GAME_PLAY) {
        mario.y = mario_y;
        mario.x = mario_x;
        // if (SIZE_BRICK_X  > abs(brick.x - camera_x - mario.x)) {
        //     mario_on_brick = true;
        // }
        // if (SIZE_BRICK_X < abs(brick.x - camera_x - mario.x)) {
        //     mario_on_brick = false;
        //     mario.on_brick = 0;
        // }

        int32_t brick_screen_x = (int32_t)brick.x - (int32_t)camera_x;

        // Mép trái/phải của brick
        int32_t brick_left  = brick_screen_x;
        int32_t brick_right = brick_screen_x + (int32_t)SIZE_BRICK_X;

        // Mép trái/phải của mario
        int32_t mario_left  = (int32_t)mario.x;
        int32_t mario_right = (int32_t)mario.x + (int32_t)SIZE_BITMAP_MARIO_X_SMALL;

        // Còn overlap theo X → còn trên gạch
        bool overlap_x = (mario_right > brick_left) && (mario_left < brick_right);
        if (overlap_x) {
            mario_on_brick = true;
        } else {
            mario_on_brick = false;
            mario.on_brick = 0;
        }
        // gia su dem duoc 100px buoc thi cho no xuat hien cai gi ra
        if (count_map_width % 150 == 0 && count_map_width <= 300 && count_map_width != 0) {
            task_post_pure_msg(MA_GAME_BRICK_ID, MA_GAME_BRICK_RESPAWN);
        }
        // gia su dem duoc 200px buoc thi cho no xuat hien cai gi ra
        if (count_map_width % 200 == 0 && count_map_width <= 400 && count_map_width != 0) {
            task_post_pure_msg(MA_GAME_MUSHROOM_ID, MA_GAME_MUSHROOM_RESPAWN);
            task_post_pure_msg(MA_GAME_BLOCK_ID, MA_GAME_BLOCK_RESPAWN);
        }
        // if (mario.state != FIRE && count_map_width >600) {
        //     task_post_pure_msg(MA_GAME_BLOCK_ID, MA_GAME_BLOCK_RESPAWN);
        // }
        if (count_map_width == 600) {
            // task_post_pure_msg(MA_GAME_BOSS_ID, MA_GAME_BOSS_SPAWN);
            task_post_pure_msg(MA_GAME_WARNING_ID, MA_GAME_WARNING_SETUP);
            timer_set(MA_GAME_BOSS_ID, MA_GAME_BOSS_SPAWN, 3000, TIMER_ONE_SHOT);
            count_map_width = 0;
        }

    }
}

void ma_game_mario_up(){
    bool mario_hit_block = false;
    // bool mario_hit_brick = false;
    for (uint8_t i=0; i< NUM_BLOCKS; i++) {
        ma_game_block_t & b = block[i];
        if (b.visible == WHITE) {
            if ((SIZE_BITMAP_BLOCK_X > abs(b.x -camera_x - mario.x))) {
                if (mario.on_ground == 1) {
                    mario_y = b.y + SIZE_BITMAP_BLOCK_Y;
                    mario_hit_block = true;
                    break;
                }
            }
        }
    }
    if (!mario_hit_block) {
        if (mario.on_ground == 1) mario_y -= STEP_MARIO_AXIS_Y;
        if (mario_on_brick) mario.on_brick = 1;
    }
    mario.on_ground = 0;
}

void ma_game_mario_right(){
    if (mario_on_brick == true && mario.on_ground == 1) return;
    mario_x += 5;
    count_map_width += 5;
    if (mario_x >= (int)LCD_WIDTH/2 - SIZE_BITMAP_MARIO_X_SMALL) {
        mario_x = (int)LCD_WIDTH/2 - SIZE_BITMAP_MARIO_X_SMALL;
        camera_x += 5;
    }
    // if (mario.state != FIRE) {
    //     task_post_pure_msg(MA_GAME_BLOCK_ID, MA_GAME_BLOCK_RESPAWN);
    // }
}

void ma_game_mario_left(){
    if (mario_on_brick == true && mario.on_ground == 1) return;
    if (mario.on_ground == 1) {
        mario_x -= 5;
        if (mario_x <= 0) {
            mario_x = AXIS_X_MARIO;
        }
    }
}

void ma_game_mario_down(){
    if (mario.on_ground == 0 && mario.on_brick == 0) {
        mario_y += STEP_MARIO_AXIS_Y_DOWN;
        switch (mario.state)
        {
            case SMALL: {
                if ((mario_y >= BRICK_AXIS_Y - SIZE_BITMAP_MARIO_Y_SMALL) && mario_on_brick) {
                    mario_y = BRICK_AXIS_Y - SIZE_BITMAP_MARIO_Y_SMALL;
                    mario.on_brick = 1;
                    mario.on_ground = 0;
                    // mario.on_ground = 1;
                }
                if (mario_y >= LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y_SMALL) {
                    mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y_SMALL;
                    mario.on_ground = 1;                
                }
            }
                break;
            case BIG: {
                if ((mario_y >= BRICK_AXIS_Y - SIZE_BITMAP_MARIO_Y) && mario_on_brick) {
                    mario_y = BRICK_AXIS_Y - SIZE_BITMAP_MARIO_Y;
                    mario.on_brick = 1;
                    mario.on_ground = 0;
                }
                if (mario_y >= LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y) {
                    mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y;
                    mario.on_ground = 1;                
                }
            }
                break;
            case FIRE: {
                if ((mario_y >= BRICK_AXIS_Y - SIZE_BITMAP_MARIO_Y) && mario_on_brick) {
                    mario_y = BRICK_AXIS_Y - SIZE_BITMAP_MARIO_Y;
                    mario.on_brick = 1;
                    mario.on_ground = 0;
                }
                if (mario_y >= LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y) {
                    mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y;
                    mario.on_ground = 1;                
                }
            }
                break;
            default:
                break;
        }
    }
}

void ma_game_mario_reset() {
    mario_x = AXIS_X_MARIO;
    mario.visible = BLACK;
    mario_y = AXIS_Y_MARIO_SMALL;
}

void ma_game_mario_get_item() {
    switch (mario.state) {
        case SMALL: {
            if (mushroom_super.visible == WHITE) {
                if (mario.on_ground == 1) {
                    if (SIZE_BITMAP_MUSHROOMSUPER_X > abs(mushroom_super.x -camera_x- mario.x)) {
                        if (mushroomSuperReady == true) {
                            mario_y = LCD_HEIGHT - 10 - SIZE_BITMAP_MARIO_Y;
                            mario.state = BIG;
                            mushroomSuperReady = false;
                            ma_game_score += 100;
                            task_post_pure_msg(MA_GAME_MUSHROOMSUPER_ID, MA_GAME_MUSHROOMSUPER_RESET);
                        }
                    }
                }
            }
        }
            break;
        case BIG: {
            if (fireflower.visible == WHITE) {
                if (mario.on_ground == 1) {
                    if (SIZE_BITMAP_FIREFLOWER_X > abs(fireflower.x -camera_x- mario.x)) {
                        if (fireflowerReady == true) {
                            mario.state = FIRE;
                            fireflowerReady = false;
                            ma_game_score += 100;
                            task_post_pure_msg(MA_GAME_FIREFLOWER_ID, MA_GAME_FIREFLOWER_RESET);
                        }
                    }
                }
            }
        }
            break;

        default:
            break;
    }
}


void ma_game_mario_handler(ak_msg_t* msg) {
    switch (msg->sig) {
    case MA_GAME_MARIO_SETUP: {
        APP_DBG_SIG("MA_GAME_MARIO_SETUP\n");
        ma_game_mario_setup();
    }
        break;

    case MA_GAME_MARIO_UPDATE: {
        APP_DBG_SIG("MA_GAME_MARIO_UPDATE\n");
        ma_game_mario_update();
    }
        break;

    case MA_GAME_MARIO_UP: {
        APP_DBG_SIG("MA_GAME_MARIO_UP\n");
        ma_game_mario_up();
    }
        break;
    case MA_GAME_MARIO_LEFT: {
        APP_DBG_SIG("MA_GAME_MARIO_LEFT\n");
        ma_game_mario_left();
    }
        break;

    case MA_GAME_MARIO_RIGHT: {
        APP_DBG_SIG("MA_GAME_MARIO_RIGHT\n");
        ma_game_mario_right();
    }
        break;

    case MA_GAME_MARIO_DOWN: {
        APP_DBG_SIG("MA_GAME_MARIO_DOWN\n");
        ma_game_mario_down();
    }
        break;

    case MA_GAME_MARIO_CRASH: {
        APP_DBG_SIG("MA_GAME_MARIO_CRASH\n");
        ma_game_mario_crash();
    }
        break;
    case MA_GAME_MARIO_BOSS_BULLET_CRASH: {
        APP_DBG_SIG("MA_GAME_MARIO_BOSS_BULLET_CRASH\n");
        ma_game_mario_boss_bullet_crash();
    }
    case MA_GAME_MARIO_GET_ITEM: {
        APP_DBG_SIG("MA_GAME_MARIO_GET_BIG\n");
        ma_game_mario_get_item();
    }
        break;
    case MA_GAME_MARIO_RESET: {
        APP_DBG_SIG("MA_GAME_MARIO_RESET\n");
        ma_game_mario_reset();
    }
        break;
    case MA_GAME_MARIO_MUSHROOMSUPER_READY: {
        APP_DBG_SIG("MA_GAME_MARIO_MUSHROOMSUPER_READY\n");
        mushroomSuperReady = true;
        // ma_game_mario_get_big();
    }
         break;
    case MA_GAME_MARIO_FIREFLOWER_READY: {
        APP_DBG_SIG("MA_GAME_MARIO_FIREFLOWER_READY\n");
        fireflowerReady = true;
    }
        break;
    default:
        break;
    }
}