#pragma once

#include <pebble.h>
#include "pge/pge.h"
#include "pge/modules/pge_isometric.h"

// #define DRAW_BG
// #define BENCHMARK

extern GColor g_fg_color;
extern GColor g_bg_color;

#include "drawable/segment.h"
#include "drawable/digit.h"

#define FRAME_RATE_HIGH PBL_IF_ROUND_ELSE(10, 30)
#define ANIM_TIMEOUT 10000

#define HOURS_OFFSET      40
#define MINS_OFFSET       25
#define PROJECTION_OFFSET PBL_IF_ROUND_ELSE(GPoint(120, 45), GPoint(100, 45))

#define COLOR_SET_YELLOW 0
#define COLOR_SET_RED    1
#define COLOR_SET_BLUE   2
#define COLOR_SET_GREEN  3
#define COLOR_SET_GRAY   4
#define NUM_COLOR_SETS   5

#define FG_COL_YELLOW PBL_IF_COLOR_ELSE(GColorOrange, GColorBlack)
#define BG_COL_YELLOW PBL_IF_COLOR_ELSE(GColorYellow, GColorWhite)
#define FG_COL_RED    PBL_IF_COLOR_ELSE(GColorDarkCandyAppleRed, GColorBlack)
#define BG_COL_RED    PBL_IF_COLOR_ELSE(GColorOrange, GColorWhite)
#define FG_COL_BLUE   PBL_IF_COLOR_ELSE(GColorBlue, GColorBlack)
#define BG_COL_BLUE   PBL_IF_COLOR_ELSE(GColorPictonBlue, GColorWhite)
#define FG_COL_GREEN  PBL_IF_COLOR_ELSE(GColorDarkGreen, GColorBlack)
#define BG_COL_GREEN  PBL_IF_COLOR_ELSE(GColorGreen, GColorWhite)
#define FG_COL_GRAY   PBL_IF_COLOR_ELSE(GColorDarkGray, GColorBlack)
#define BG_COL_GRAY   PBL_IF_COLOR_ELSE(GColorLightGray, GColorWhite)
