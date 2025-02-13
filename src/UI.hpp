#pragma once
#include "EventHandler.hpp"

class UI {
 public:
  static void draw(EventHandler &event_handler);
  static void draw_overlay();
  static void draw_control_window(EventHandler &event_handler);
  static void draw_combo(EventHandler &event_handler);
  static void draw_buttons(EventHandler &event_handler);
  static void draw_cursor();
  static void draw_speed_control(EventHandler &event_handler);
};
