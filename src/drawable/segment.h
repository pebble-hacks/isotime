#pragma once

#include <pebble.h>
#include "isometric/isometric.h"

#define SEGMENT_MAX_HEIGHT 10
#define SEGMENT_SIZE GSize(10, 10)
#define SEGMENT_FLY_SPEED 10
#define SEGMENT_Z_MAX 200
#define SEGMENT_DELAY_COEFF 10

typedef struct {
  Vec3 origin;
  bool visible;
  int dz;
  GColor side_color;
  GColor face_color;
  int move_delay;
} Segment;

Segment* segment_create(Vec3 origin);

void segment_destroy(Segment *this);

void segment_logic(Segment *this);

void segment_render(Segment *this);

void segment_set_visible(Segment *this, bool visible, int index);

void segment_set_colors(Segment *this, GColor side_color, GColor face_color);
