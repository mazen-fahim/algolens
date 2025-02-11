#include "UI.hpp"

#include "imgui.h"

bool UI::m_is_start_button_visible = true;
bool UI::m_is_reset_button_visible = true;
bool UI::m_is_stop_button_visible = false;
bool UI::m_is_resume_button_visible = false;

void UI::draw(EventHandler &event_handler) {
  ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and
                                  // append into it.

  ImGui::Text("This is some useful text.");  // Display some text (you can use a
                                             // format strings too)
  if (ImGui::Button("Start")) {
    event_handler.handle_start_button_click();
  }
  if (ImGui::Button("pause")) {
    event_handler.handle_pause_button_click();
  }
  if (ImGui::Button("Resume")) {
    event_handler.handle_resume_button_click();
  }
  if (ImGui::Button("Reset")) {
    event_handler.handle_reset_button_click();
  }

  ImGui::End();
}
