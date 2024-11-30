#pragma once

#include <map>
#include <vector>

// 0 - no field
// 1 - wall
// 2 - grass
// 3 - position for a box (aim)
// 4 - box
// 5 - player start position

enum FIELD : unsigned short { NO_FIELD = 0, WALL, GRASS, AIM, BOX, PLAYER };

static std::map<int, std::vector<std::vector<int>>> levelsMap = 
{
    {1,  {{0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 1, 2, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
          {1, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
          {1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0},
          {0, 0, 0, 0, 1, 2, 2, 2, 2, 4, 2, 1, 0, 0, 1, 3, 1, 0},
          {0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 1, 1, 0},
          {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}}},

    {2,  {{0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
          {0, 0, 0, 0, 1, 2, 2, 1, 0, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 3, 1, 0},
          {1, 1, 1, 1, 1, 2, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1, 0},
          {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1},
          {1, 5, 1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 2, 2, 2, 1, 2, 2, 2, 3, 1},
          {1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
          {0, 0, 0, 1, 2, 4, 2, 1, 0, 1, 2, 2, 2, 1, 2, 2, 1, 1, 1, 2, 1, 0},
          {0, 0, 0, 1, 2, 2, 2, 1, 0, 1, 2, 2, 1, 2, 2, 2, 1, 0, 1, 3, 1, 0},
          {0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}}},

    {3,  {{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
          {0, 0, 1, 1, 2, 1, 0, 1, 1, 1, 1},
          {0, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1},
          {1, 1, 2, 4, 2, 2, 2, 2, 2, 2, 1},
          {1, 2, 2, 2, 5, 4, 2, 1, 2, 2, 1},
          {1, 1, 1, 2, 4, 1, 1, 1, 2, 2, 1},
          {0, 0, 1, 2, 2, 1, 3, 3, 2, 2, 1},
          {0, 1, 1, 2, 1, 1, 3, 1, 2, 1, 1},
          {0, 1, 2, 2, 2, 2, 2, 2, 1, 1, 0},
          {0, 1, 2, 2, 2, 2, 2, 1, 1, 0, 0},
          {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}}},

    {4,  {{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
          {1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 0},
          {1, 3, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 4, 1, 2, 4, 2, 2, 2, 2, 1, 1},
          {1, 1, 2, 2, 2, 1, 4, 2, 1, 2, 4, 1, 2, 1, 1, 1, 2, 1, 2, 2, 3, 1},
          {1, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
          {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1},
          {0, 1, 2, 2, 1, 1, 1, 1, 3, 1, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0},
          {1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1},
          {1, 5, 2, 1, 0, 0, 1, 2, 2, 2, 1, 2, 2, 1, 3, 2, 2, 2, 2, 2, 2, 1},
          {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}},

    {5,  {{0, 1, 1, 0, 1, 1, 1, 1, 1},
          {1, 1, 2, 1, 1, 2, 3, 2, 1},
          {1, 2, 1, 1, 2, 4, 3, 2, 1},
          {0, 1, 1, 2, 4, 2, 2, 2, 1},
          {1, 1, 2, 4, 5, 2, 1, 1, 1},
          {1, 2, 4, 2, 2, 1, 1, 0, 0},
          {1, 3, 3, 2, 1, 1, 2, 1, 1},
          {1, 2, 2, 2, 1, 0, 1, 1, 0},
          {1, 1, 1, 1, 1, 0, 1, 0, 0}}},

    {6,  {{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
          {1, 5, 1, 2, 2, 3, 1, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0},
          {1, 2, 1, 2, 1, 2, 1, 3, 1, 2, 1, 1, 4, 2, 1, 0, 0, 0, 0, 0},
          {1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 1, 2, 1, 1, 0, 0, 1, 1, 1},
          {1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 4, 1, 2, 1, 1, 1, 1, 1, 3, 1},
          {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 1, 3, 1, 1, 2, 1},
          {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 1, 2, 2, 1, 2, 1},
          {1, 2, 1, 2, 1, 2, 4, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
          {1, 2, 2, 2, 1, 2, 2, 4, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}}},

    {7,  {{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
          {0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1},
          {0, 1, 5, 4, 2, 2, 1, 1, 3, 3, 2, 1},
          {1, 1, 1, 4, 1, 2, 2, 2, 2, 2, 2, 1},
          {1, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2, 1},
          {1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1},
          {1, 2, 2, 2, 1, 2, 2, 2, 1, 0, 0, 0},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}}},

    {8,  {{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
          {1, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 1},
          {1, 2, 2, 2, 4, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 3, 1},
          {1, 2, 4, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
          {1, 2, 2, 2, 2, 2, 1, 2, 1, 3, 2, 2, 2, 2, 2, 1, 2, 1, 1, 2, 2, 1},
          {1, 1, 2, 1, 2, 2, 1, 3, 1, 2, 1, 1, 2, 2, 2, 2, 4, 2, 2, 1, 1, 1},
          {1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1},
          {1, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 1},
          {1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1},
          {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0}}},

    {9,  {{1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
          {1, 2, 2, 1, 2, 2, 1, 1, 0, 0},
          {1, 2, 5, 2, 3, 2, 2, 1, 1, 1},
          {1, 2, 2, 1, 2, 1, 4, 2, 2, 1},
          {1, 1, 2, 2, 2, 1, 2, 4, 2, 1},
          {0, 1, 1, 1, 3, 1, 4, 2, 1, 1},
          {0, 0, 0, 1, 2, 2, 2, 2, 1, 0},
          {0, 0, 0, 1, 3, 2, 1, 1, 1, 0},
          {0, 0, 0, 1, 1, 1, 1, 0, 0, 0}}},

    {10, {{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
          {0, 0, 0, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 3, 1},
          {0, 0, 0, 1, 2, 1, 1, 2, 1, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
          {0, 0, 0, 1, 2, 1, 5, 2, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1},
          {1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 2, 1, 3, 2, 2, 2, 1, 1, 4, 1, 2, 1},
          {1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1},
          {1, 2, 4, 1, 1, 3, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1},
          {1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 0},
          {1, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 0},
          {1, 2, 1, 2, 1, 1, 2, 1, 4, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1},
          {1, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 3, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}},

    {11, {{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0},
          {1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 0, 0},
          {1, 2, 2, 2, 1, 1, 2, 1, 2, 1, 0, 0},
          {1, 2, 4, 5, 4, 2, 2, 2, 2, 1, 0, 0},
          {1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 0},
          {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
          {1, 2, 2, 2, 1, 1, 1, 2, 3, 3, 2, 1},
          {1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 1},
          {0, 0, 0, 0, 1, 2, 1, 2, 2, 1, 2, 1},
          {0, 0, 0, 0, 1, 2, 2, 1, 1, 2, 2, 1},
          {0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1},
          {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0}}},

    {12, {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
          {1, 3, 1, 2, 2, 3, 1, 1, 3, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 2, 2, 1},
          {1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
          {1, 2, 1, 1, 2, 1, 2, 2, 4, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 2, 1},
          {1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 2, 2, 1, 3, 1},
          {1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 5, 2, 2, 4, 2, 2, 4, 2, 2, 1, 1, 1},
          {1, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 1},
          {1, 2, 4, 2, 2, 2, 2, 2, 1, 2, 2, 4, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1},
          {1, 2, 1, 1, 2, 2, 4, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
          {1, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1},
          {1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}},

    {13, {{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 4, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 1, 1, 1, 2, 2, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 1, 2, 2, 4, 2, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {1, 1, 1, 2, 1, 2, 1, 1, 2, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
          {1, 2, 2, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 3, 3, 1},
          {1, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 1},
          {1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 5, 1, 1, 2, 2, 3, 3, 1},
          {0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}}},

    {14, {{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {0, 1, 5, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 2, 2, 2, 2, 2, 3, 1},
          {0, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
          {0, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 3, 1, 2, 2, 2, 2, 2, 1},
          {0, 1, 2, 1, 4, 1, 2, 1, 2, 4, 2, 1, 2, 2, 2, 2, 1, 4, 2, 1, 2, 2, 1},
          {0, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 4, 2, 1, 1},
          {1, 1, 4, 1, 1, 2, 2, 2, 3, 1, 2, 2, 2, 3, 1, 1, 1, 4, 1, 2, 2, 2, 1},
          {1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1},
          {1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 4, 1, 1, 2, 2, 1},
          {1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1},
          {0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}},

    {15, {{0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 1, 2, 2, 2, 1, 3, 1},
          {1, 1, 1, 2, 4, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 1, 4, 1, 2, 1},
          {1, 5, 2, 2, 1, 2, 2, 2, 2, 1, 1, 4, 1, 3, 2, 2, 2, 1, 2, 1, 2, 1},
          {1, 1, 2, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1},
          {0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1},
          {0, 1, 4, 1, 2, 4, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
          {1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1},
          {1, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1},
          {1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 4, 2, 2, 1},
          {1, 3, 2, 1, 1, 1, 1, 3, 1, 3, 2, 2, 2, 2, 2, 2, 3, 1, 2, 2, 1, 1},
          {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}}},

    {16, {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
          {1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 3, 1, 2, 2, 1, 3, 2, 2, 3, 1},
          {1, 2, 1, 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 4, 2, 1, 2, 2, 1, 2, 1},
          {1, 5, 1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 3, 1},
          {1, 2, 1, 2, 1, 2, 2, 1, 3, 2, 2, 2, 2, 1, 2, 4, 1, 2, 2, 2, 2, 1},
          {1, 2, 4, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1},
          {1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1, 2, 1, 2, 1},
          {1, 2, 1, 2, 2, 1, 2, 4, 2, 2, 2, 2, 1, 2, 4, 2, 1, 2, 2, 2, 2, 1},
          {1, 2, 4, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 1, 3, 1},
          {1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 1, 2, 1},
          {1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 3, 1, 2, 2, 2, 2, 1, 3, 1},
          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}}
};
