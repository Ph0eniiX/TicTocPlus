#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/cfg.h"
#include "messaging/msg.h"

//useful github for copying analog things: https://github.com/piggehperson/MotoMakerFace/blob/master/src/c/MotoMaker.c (thanks lavender!)

Window *main_window;
static Layer *clock_hands, *sec_hand, *bg_layer;

ClaySettings settings;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  layer_mark_dirty(clock_hands);
  layer_mark_dirty(sec_hand);
}

static void sub_to_time() {
  if(!settings.enable_seconds) {
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  } else {
    tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  }
}

void update_stuff() {
  update_time();
  sub_to_time();

  window_set_background_color(main_window, settings.bg_color);

  layer_mark_dirty(clock_hands);
  layer_mark_dirty(bg_layer);
  layer_mark_dirty(sec_hand);

  layer_set_hidden(sec_hand, !settings.enable_seconds);
  layer_set_hidden(bg_layer, !settings.enable_bg);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  window_set_background_color(main_window, settings.bg_color);
  
  update_time();

  bg_layer = layer_create(bounds);
  layer_set_update_proc(bg_layer, draw_hour_marks_update_proc);
  layer_add_child(window_layer, bg_layer);

  clock_hands = layer_create(bounds);
  layer_set_update_proc(clock_hands, hands_draw_update_proc);
  layer_add_child(window_layer, clock_hands);

  sec_hand = layer_create(bounds);
  layer_set_update_proc(sec_hand, draw_sec_update_proc);
  layer_add_child(window_layer, sec_hand);
}

static void main_window_unload() {
  layer_destroy(clock_hands);
}

static void init() {
  main_window = window_create();

  init_msg();
  load_settings();

  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);

  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(main_window, true);

  update_stuff();
}

static void deinit() {
  window_destroy(main_window);
  tick_timer_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
