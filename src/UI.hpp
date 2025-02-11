#pragma once
#include "EventHandler.hpp"

class UI {
 public:
  static void draw(EventHandler &event_handler);

 private:
  static bool m_is_start_button_visible;
  static bool m_is_stop_button_visible;
  static bool m_is_resume_button_visible;
  static bool m_is_reset_button_visible;
};
