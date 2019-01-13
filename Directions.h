#pragma once

enum class Directions { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
enum class InputKeys { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, MOUSELEFT = 4, MOUSERIGHT = 5, E = 6, TAB = 7, Q = 8, X = 9 };
enum class Others { RESET = -1 };
enum class Weapons { MELEE = 0, DISTANCE = 1 };
const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 40;
const int ITEMS_AMOUNT = 49;
const int MAX_ENEMIES_NUMBER = 30;
