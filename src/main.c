#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_five_layer;
static TextLayer *s_oclock_layer;
static TextLayer *s_somewhere_layer;

static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_five_layer      = text_layer_create(GRect(0, 26, bounds.size.w, 50));
  s_oclock_layer    = text_layer_create(GRect(0, 60, bounds.size.w, 50));
  s_somewhere_layer = text_layer_create(GRect(0, 94, bounds.size.w, 50));

  // Improve the layout to be more like a watchface

  text_layer_set_background_color(s_five_layer, GColorClear);
  text_layer_set_background_color(s_oclock_layer, GColorClear);
  text_layer_set_background_color(s_somewhere_layer, GColorClear);

  text_layer_set_text_color(s_five_layer, GColorBlack);
  text_layer_set_text_color(s_oclock_layer, GColorBlack);
  text_layer_set_text_color(s_somewhere_layer, GColorBlack);

  text_layer_set_text(s_five_layer, "It's five");
  text_layer_set_text(s_oclock_layer, "o'clock");
  text_layer_set_text(s_somewhere_layer, "somewhere!");

  text_layer_set_font(s_five_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_font(s_oclock_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_font(s_somewhere_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));

  text_layer_set_text_alignment(s_five_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_oclock_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_somewhere_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_five_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_oclock_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_somewhere_layer));
}


static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_five_layer);
  text_layer_destroy(s_oclock_layer);
  text_layer_destroy(s_somewhere_layer);
}


static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}


int main(void) {
  init();
  app_event_loop();
  deinit();
}
