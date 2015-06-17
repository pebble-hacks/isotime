#include "main.h"

static Digit *s_digits[4];

static GColor s_bg_color, s_fg_color;
static int s_color_set;

static void pge_logic() {
  for(int i = 0; i < 4; i++) {
    digit_logic(s_digits[i]);
  }
}

#ifdef DRAW_BG
static void set_framebuffer_pixel(uint8_t* fb_addr, GSize fb_size, GPoint pixel, GColor color) {
  memset(&fb_addr[(pixel.y * fb_size.w) + pixel.x], (uint8_t)color.argb, 1);
}
#endif

static void pge_render(GContext *ctx) {
#ifdef BENCHMARK
  uint16_t start = time_ms(NULL, NULL);
#endif

  
#ifndef DRAW_BG
  pge_isometric_begin(ctx);
#else
  GBitmap *bg_fb = pge_isometric_begin(ctx);
  uint8_t *bg_fb_data = gbitmap_get_data(bg_fb);
  GSize bg_fb_size = gbitmap_get_bounds(bg_fb).size;
  for(int y = 0; y < 168; y++) {
    for(int x = 0; x < 144; x++) {
      memset(&bg_fb_data[(y * bg_fb_size.w) + x], (uint8_t)s_bg_color.argb, 1);
    }
  }
#endif

  for(int i = 0; i < 4; i++) {
    digit_render(s_digits[i]);
  }

  pge_isometric_finish(ctx);

#ifdef BENCHMARK
  uint16_t finish = time_ms(NULL, NULL);
  APP_LOG(APP_LOG_LEVEL_INFO, "Frame time: %d", (int)finish - start);
#endif
}

static void battery_saver(void *context) {
  pge_set_framerate(1);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  int hours = tick_time->tm_hour;
  int mins = tick_time->tm_min;

  if(hours < 10) {
    digit_set_value(s_digits[0], 0);
  } else {
    digit_set_value(s_digits[0], hours / 10);
  }
  digit_set_value(s_digits[1], hours % 10);

  if(mins < 10) {
    digit_set_value(s_digits[2], 0);
  } else {
    digit_set_value(s_digits[2], mins / 10);
  }
  digit_set_value(s_digits[3], mins % 10);

  // Pick new color set
  srand(time(NULL));
  int old_set = s_color_set;
  while(s_color_set == old_set) {
    s_color_set = rand() % NUM_COLOR_SETS;
  }
  switch(s_color_set) {
    case COLOR_SET_YELLOW:
      s_fg_color = FG_COL_YELLOW;
      s_bg_color = BG_COL_YELLOW;
      break;
    case COLOR_SET_RED:
      s_fg_color = FG_COL_RED;
      s_bg_color = BG_COL_RED;
      break;
    case COLOR_SET_BLUE:
      s_fg_color = FG_COL_BLUE;
      s_bg_color = BG_COL_BLUE;
      break;
    case COLOR_SET_GREEN:
      s_fg_color = FG_COL_GREEN;
      s_bg_color = BG_COL_GREEN;
      break;
  }

  for(int i = 0; i < 4; i++) {
    digit_set_colors(s_digits[i], s_fg_color, s_bg_color);
  }

  // Smooth transition
  pge_set_framerate(FRAME_RATE_HIGH);
  app_timer_register(4000, battery_saver, NULL);
}

void pge_init() {
  s_digits[0] = digit_create(GPoint(-HOURS_OFFSET, 0), 0);
  s_digits[1] = digit_create(GPoint(-HOURS_OFFSET + (5 * SEGMENT_SIZE.w), 0), 0);
  s_digits[2] = digit_create(GPoint(MINS_OFFSET, 7 * SEGMENT_SIZE.h), 0);
  s_digits[3] = digit_create(GPoint(MINS_OFFSET + (5 * SEGMENT_SIZE.w), 7 * SEGMENT_SIZE.h), 0);

  pge_isometric_set_projection_offset(GPoint(100, 45));
  pge_set_framerate(FRAME_RATE_HIGH);
  pge_begin(GColorBlack, pge_logic, pge_render, NULL);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  time_t temp = time(NULL); 
  struct tm *t = localtime(&temp);
  tick_handler(t, MINUTE_UNIT);
}

void pge_deinit() {
  pge_finish();

  for(int i = 0; i < 4; i++) {
    digit_destroy(s_digits[i]);
  }
}