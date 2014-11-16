#define FPS 1000
#include "pebble.h"

static Window *window;

static Layer *layer;

static GBitmap *image;

static AppTimer *timer;

static int i = 0;

static void layer_update_callback(Layer *me, GContext* ctx) {
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image
  // will automatically tile. Which might be what *you* want.

  GRect bounds = image->bounds;

  graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 10, 5 }, .size = bounds.size });
  
  if ( i%8 != 0 ) // 7/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 25, 5 }, .size = bounds.size });
  
  if ( i%4 ) // 6/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 40, 5 }, .size = bounds.size });
  
  if ( i%8 != 3 && i%4 ) // 5/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 55, 5 }, .size = bounds.size });
  
  if ( i%2 ) // 4/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 70, 5 }, .size = bounds.size });
  
  if ( !( i%8 != 3 && i%4 ) ) // 3/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 85, 5 }, .size = bounds.size });
  
  if ( i%4 == 0 ) // 2/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 100, 5 }, .size = bounds.size });
  
  if ( i%8 == 0 ) // 1/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 115, 5 }, .size = bounds.size });

  ///////////////
  graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 10, 35 }, .size = bounds.size });
  
  if ( i%4 ) // 6/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 23, 35 }, .size = bounds.size });
  
  if ( i%2 ) // 4/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 36, 35 }, .size = bounds.size });
  
  if ( i%4 == 0 ) // 2/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 49, 35 }, .size = bounds.size });

  ///////////////
  graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 10, 65 }, .size = bounds.size });
  
  if ( i%2 ) // 4/8
    graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 23, 65 }, .size = bounds.size });
}

void on_timeout(void *data) {

  ++i;
  
  layer_mark_dirty(layer);

  timer = app_timer_register	(	1000 / FPS, on_timeout, NULL );
}

int main(void) {
  window = window_create();
  window_stack_push(window, true /* Animated */);

  // Init the layer for display the image
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, layer_update_callback);
  layer_add_child(window_layer, layer);

  image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NO_LITTER);
  
  timer = app_timer_register	(	1000 / FPS, on_timeout, NULL );

  app_event_loop();

  gbitmap_destroy(image);

  window_destroy(window);
  layer_destroy(layer);
}
