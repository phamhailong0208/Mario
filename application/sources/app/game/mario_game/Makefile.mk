CFLAGS		+= -I./sources/app/game/mario_game
CPPFLAGS	+= -I./sources/app/game/mario_game

VPATH += sources/app/game/mario_game

# CPP source files 
# Archery game 
SOURCES_CPP += sources/app/game/mario_game/ma_game_mario.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_mushroom.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_block.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_mushroomsuper.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_fireflower.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_bullet.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_boss.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_boss_bullet.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_brick.cpp
SOURCES_CPP += sources/app/game/mario_game/ma_game_warning.cpp