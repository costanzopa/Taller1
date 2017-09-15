/*
 * Constants.h
 *
 *  Created on: 04/09/2016
 *      Author: pablo
 */

#ifndef SRC_COMMON_UTILS_CONSTANTS_H_
#define SRC_COMMON_UTILS_CONSTANTS_H_

namespace utils {
const std::string DISCONNECTED= "0";
const std::string CONNECTED = "1";
const std::string ERROR_MESSAGE = "error\n";
const std::string OK_MESSAGE = "ok\n";
const std::string CONNECT_MESSAGE = "conectar\n";
const std::string HAS_SPACE = "A";
const std::string NO_SPACE = "B";
const std::string DUMP_GAME_MESSAGES="dump\n";
const std::string GET_SCALES = "scales\n";
const std::string DISCONNECT_MESSAGE = "desconectar\n";
const std::string SINGLE_MESSAGE = "enviar\n";
const std::string MULTIPLE_MESSAGE = "enviar_multi\n";
const std::string RECIEVE_MESSAGES = "recibir\n";
const std::string START_GAME = "jugar\n";
const std::string QUIT_GAME = "quit\n";
const std::string GAME_READY = "listo_el_juego\n";
const std::string GAME_STARTED = "empezon\n";
const std::string END_OF_MESSAGES = "##END_OF_STREAM##";
const std::string DEFAULT_PATH_USER_FILE = "../users.txt";
const std::string DEFAULT_PATH_LOREM_FILE = "../loremFile";



const std::string NEW_CHARACTER = "NEW_CHARACTER";
const std::string NEW_BOSS = "NEW_BOSS";
const std::string NEW_ENEMY = "NEW_Enemy";
const std::string DYING_ENEMY = "D_ENEM";
const std::string DYING_BOSS = "D_Boss";
const std::string DYING_CHARACTER = "D_CHAR";
const std::string DISSAPEAR_ANIMATION = "D_ANIM";
const std::string EXISTING_ENEMY = "EXISTING_Enemy";
const std::string EXISTING_BOSS = "EXISTING_BOSS";
const std::string EXISTING_CHARACTER = "EXISTING_CHARACTER";
const std::string EXISTING_SINGLE_SHOT = "EXISTING_SS";
const std::string NEW_SINGLE_SHOT = "NEW_SS";
const std::string SINGLE_SHOT = "single";
const std::string SINGLE_AMMO = "sammo";
const std::string BONUS_KILL_ALL = "kill";
const std::string BONUS_HEAL = "heal";
const std::string FLAME_SHOT = "flame";
const std::string FLAME_AMMO = "fammo";
const std::string ZOMBIE_SHOT = "Zombie";
const std::string BIGEYES_SHOT = "eyes";
const std::string BIGEYES_BOMB = "eyes_bomb";
const std::string TANK_CANNON = "Tankanon";
const std::string ROCKET_SHOT = "rocket";
const std::string ROCKET_AMMO = "rammo";
const std::string NEW_ANIMATION = "NEW_ANIMATION";
const std::string NO_NEW_ACTION = "NO";
const std::string EXISTING_ANIMATION = "EXISTING_ANIMATION";
const std::string SERVER_USER_ID = "SERVER_ID";
const std::string BROADCASTER = "broadcast";
const std::string NEW_BACKGROUND_POSITION = "NEW_BACK";
const std::string RELOAD_GAME = "RELOAD_GAME";
const std::string NEW_INFO = "newInfo";
const std::string LEVEL_INFO = "lvlInfo";
const std::string END_LEVEL_INFO = "EndlvlInfo";
const std::string GAME_OVER = "gameOver";
const std::string CHARACTER_1_DIR = "Images/characters/sprites-char-1.png";
const std::string CHARACTER_2_DIR = "Images/characters/sprites-char-2.png";
const std::string CHARACTER_3_DIR = "Images/characters/sprites-char-3.png";
const std::string CHARACTER_4_DIR = "Images/characters/sprites-char-4.png";
const std::string CHARACTER_5_DIR = "Images/characters/sprites-char-5.png";
const std::string CHARACTER_6_DIR = "Images/characters/sprites-char-6.png";
const std::string CHARACTER_7_DIR = "Images/characters/sprites-char-7.png";
const std::string ENEMY_1_DIR = "Images/enemy/normal/FatZombie.png";
const std::string ENEMY_2_DIR = "Images/enemy/normal/Zombie3.png";
const std::string ENEMY_UFO = "Images/enemy/ufo.png";
const std::string ENEMY_TANK = "Images/enemy/ZombieTankFlipped.png";
const std::string ENEMY_EYES = "Images/enemy/big eyes.png";
const std::string BULLETS_DIR = "Images/bullets.png";
const std::string BONUS_DIR = "Images/bonus.png";
const std::string FAT_ZOMBIE_DIR = "Images/enemy/normal/FatZombie.png";
const std::string CHARACTER_1 = "red";
const std::string CHARACTER_2 = "blue";
const std::string CHARACTER_3 = "purple";
const std::string CHARACTER_4 = "green";
const std::string CHARACTER_5 = "white";
const std::string CHARACTER_6 = "black";
const std::string CHARACTER_7 = "cheat";
const std::string MISSING_CHARACTER = "Images/characters/missing-sprites.png";
const std::string BACKGROUND_DIR = "Images/fondos/nivel1puntos2/";
const std::string BACKGROUND_ERROR_DIR = "Images/fondos/error.png";
const std::string WAITING_IMG = "Images/fondos/esperando.png";
const std::string SET_BACKGROUND_DIR = "set_back";
const std::string BACKGROUND_SIZE = "back_size";

//KEYS

const std::string KEY_RELEASE_RIGHT = "RELEASE RIGHT";
const std::string KEY_RELEASE_LEFT = "RELEASE LEFT";
const std::string KEY_RELEASE_RELOAD = "RELEASE RELOAD";
const std::string KEY_CYCLE_NEXT = "CYCLE NEXT";
const std::string KEY_CYCLE_PREVIOUS = "CYCLE PREVIOUS";
const std::string KEY_PRESS_DOWN = "DOWN";
const std::string KEY_RELEASE_DOWN = "RELEASE DOWN";
const std::string KEY_PRESS_UP = "UP";
const std::string KEY_RELEASE_UP = "RELEASE UP";
const std::string KEY_PRESS_LEFT = "LEFT";
const std::string KEY_PRESS_RIGHT = "RIGHT";
const std::string KEY_PRESS_JUMP = "JUMP";
const std::string KEY_PRESS_SHOOT = "SHOOT";

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAX_QUEUE = 6;
const int LEVEL_LENGHT = 3500;
const int DEFAULT_LEVEL = 1;
const std::string DEFAULT_PORT = "15558";
const std::string ALL_USERS = "TODOS";
const std::string PORT_PARAM = "-port";
const std::string HOST_PARAM = "-host";
const std::string USR_PARAM = "-users";
const std::string CONNECTED_MESSAGE = "connected";
const int TIME_OUT = 10;
const std::string STAGE_FILE = "../../config/level1.xml";
const std::string STAGE_FILE_LVL2 = "../../config/level2.xml";
const std::string STAGE_FILE_LVL3 = "../../config/level3.xml";


}
#endif /* SRC_COMMON_UTILS_CONSTANTS_H_ */
