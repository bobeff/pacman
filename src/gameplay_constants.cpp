#include "pch.h"
#include "gameplay_constants.h"

const float PACMAN_MOVE_TIME = 0.14f;

const float GHOST_MOVE_TIME = 0.15f;
const float GHOST_RUN_MOVE_TIME = 0.2f;

const float CHASE_TIME = 20.0f;
const float SCATTER_TIME = 10.0f;
const float RUN_TIME = 15.0f;
const float ABOUT_TO_STOP_RUN_TIME = 5.0f;

const float GAME_START_DELAY = 1.0f;
const float PACMAN_EATEN_DELAY = 1.0f;

const sf::Vector2i PACMAN_START_TILE(14, 26);

const sf::Vector2i RED_GHOST_START_TILE(14, 17);
const sf::Vector2i RED_GHOST_SCATTER_TARGET(25, 0);

const sf::Vector2i BLUE_GHOST_START_TILE(13, 17);
const sf::Vector2i BLUE_GHOST_SCATTER_TARGET(27, 35);

const sf::Vector2i PINK_GHOST_START_TILE(12, 17);
const sf::Vector2i PINK_GHOST_SCATTER_TARGET(2, 0);

const sf::Vector2i ORANGE_GHOST_START_TILE(15, 17);
const sf::Vector2i ORANGE_GHOST_SCATTER_TARGET(0, 35);

const sf::Vector2i GHOSTS_OUT_OF_HOUSE_TARGET(14, 14);
