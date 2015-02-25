#include "pebble.h"
  
#define ACCEL_RATIO 0.5
#define ACCEL_STEP_MS 500

static Window *window;
static TextLayer *text_layer;
static BitmapLayer *image_layer;
static GBitmap *image;

enum {
  STATUS_KEY = 0,
  MESSAGE_KEY = 1
};

static void simple_image(void) {
  //window = window_create();
  //window_stack_push(window, true /* Animated */);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // This needs to be deinited on app exit which is when the event loop ends
  image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BUTT);

  // The bitmap layer holds the image for display
  image_layer = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(image_layer, image);
  bitmap_layer_set_alignment(image_layer, GAlignCenter);
  layer_add_child(window_layer, bitmap_layer_get_layer(image_layer));

}

void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  //vibes_short_pulse();
  //vibes_short_pulse();
  //send_message();
  text_layer_set_text(text_layer, "Shake for Surprise!");
  //text_layer_destroy(text_layer);
}

void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  //vibes_long_pulse();
  text_layer_set_text(text_layer, "Da Scrub Lords");
}

void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  //vibes_double_pulse();
  text_layer_set_text(text_layer, "HackIllinois 2014");
}

void click_config_provider(void *context) {
  const uint16_t repeat_interval_ms = 1000;
  window_single_repeating_click_subscribe(BUTTON_ID_SELECT, repeat_interval_ms, select_single_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_UP, repeat_interval_ms, up_single_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, repeat_interval_ms, down_single_click_handler);
}

//static void handle_accel(AccelData *accel_data, uint32_t num_samples) {
//}
void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  // Process tap on ACCEL_AXIS_X, ACCEL_AXIS_Y or ACCEL_AXIS_Z
  // Direction is 1 or -1
  if(axis == ACCEL_AXIS_Y)
  {
    vibes_short_pulse();
    simple_image();
  }
  if(axis == ACCEL_AXIS_X)
  {
    vibes_short_pulse();
    simple_image();
  }
   if(axis == ACCEL_AXIS_Z)
   {
     vibes_short_pulse();
     simple_image();
   }
}

int main(void) {
  window = window_create();
  window_stack_push(window, true /* Animated */ );
  //accel_data_service_subscribe(0, handle_accel);//subscribe to the accel service
  window_set_click_config_provider(window, click_config_provider);
  psleep(1000);
  
  accel_tap_service_subscribe(&accel_tap_handler);
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  text_layer = text_layer_create(bounds);
  char str[30];
  snprintf(str, 30, "Pebble Butt");
  text_layer_set_text(text_layer, str);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  app_event_loop();  
  //destructor of the main func
  accel_tap_service_unsubscribe();
  text_layer_destroy(text_layer);
  window_destroy(window);
}