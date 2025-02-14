#include "UI.hpp"

#include <iostream>

#include "App.hpp"
#include "EventHandler.hpp"
#include "imgui.h"

void UI::draw(EventHandler &event_handler) {
  App &app = App::get_instance();

  ImGui::StyleColorsLight();
  draw_control_window(event_handler);
  draw_speed_control(event_handler);
  draw_overlay();
}

void UI::draw_speed_control(EventHandler &event_handler) {
  App &app = App::get_instance();

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize;

  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImVec2 work_pos = viewport->WorkPos;
  ImVec2 work_size = viewport->WorkSize;
  ImVec2 window_pos, window_pos_pivot;
  window_pos.x = (work_pos.x + work_size.x * 0.5);
  window_pos.y = (work_pos.y + work_size.y);
  window_pos_pivot.x = 0.5f;
  window_pos_pivot.y = 1.0f;
  ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
  window_flags |= ImGuiWindowFlags_NoMove;
  ImGui::SetNextWindowBgAlpha(0.35f);

  ImGui::Begin("Speed Control", NULL, window_flags);
  static int speed = 100;
  ImGui::DragInt("Speed", &speed, 0.5, 0, 100, "%d%%",
                 ImGuiSliderFlags_AlwaysClamp);
  event_handler.handle_speed_change(speed);
  ImGui::End();
}

void UI::draw_overlay() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  Sort &sort = app.get_sort();
  static int location = 0;
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
      ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
      ImGuiWindowFlags_NoNav;
  const float PAD = 10.0f;
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImVec2 work_pos = viewport->WorkPos;
  ImVec2 work_size = viewport->WorkSize;
  ImVec2 window_pos, window_pos_pivot;
  window_pos.x = (work_pos.x + PAD);
  window_pos.y = (work_pos.y + PAD);
  window_pos_pivot.x = 0.0f;
  window_pos_pivot.y = 0.0f;
  ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
  window_flags |= ImGuiWindowFlags_NoMove;
  ImGui::SetNextWindowBgAlpha(0.35f);

  ImGui::Begin("Example: Simple overlay", NULL, window_flags);
  ImGui::Text("Algorithm: %s\n", app.get_current_algorithm().c_str());
  ImGui::Separator();

  if (app.is_pathfinding_algorithm(app.get_current_algorithm())) {
    if (app.get_algo_state() == AlgoState::ALGORITHM_RUN) {
      ImGui::ProgressBar(-1.0f * (float)ImGui::GetTime(), ImVec2(0.0f, 0.0f),
                         "Searching..");
    }

    if (app.get_algo_state() == AlgoState::PATH_RUN ||
        app.get_algo_state() == AlgoState::FINISH) {
      ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Target found");
      ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Path length = %d",
                         maze.get_path_length());
    } else if (app.get_algo_state() == AlgoState::FINISH_TARGET_NOT_FOUND) {
      ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Target not found");
      ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Path length = -1");
    }
  } else {
    if (app.get_algo_state() == AlgoState::ALGORITHM_RUN) {
      ImGui::ProgressBar(-1.0f * (float)ImGui::GetTime(), ImVec2(0.0f, 0.0f),
                         "Sorting..");
    }

    if (app.get_algo_state() == AlgoState::FINISH) {
      ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Elements sorted");
      ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),
                         "Number of comparisons = %d",
                         sort.get_number_of_comparisons());
    }
  }

  ImGui::End();
}

void UI::draw_control_window(EventHandler &event_handler) {
  App &app = App::get_instance();

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize;

  const float PAD = 10.0f;
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImVec2 work_pos = viewport->WorkPos;
  ImVec2 work_size = viewport->WorkSize;
  ImVec2 window_pos, window_pos_pivot;
  window_pos.x = (work_pos.x + work_size.x / 2);
  window_pos.y = (work_pos.y + PAD);
  window_pos_pivot.x = 0.5f;
  window_pos_pivot.y = 0.0f;
  ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
  window_flags |= ImGuiWindowFlags_NoMove;
  ImGui::SetNextWindowBgAlpha(0.35f);
  ImGui::Begin("Control Window", NULL, window_flags);

  /***** Draw Tabs *****/

  /***** Draw List *****/
  draw_combo(event_handler);
  draw_buttons(event_handler);
  ImGui::End();
}

void UI::draw_combo(EventHandler &event_handler) {
  App &app = App::get_instance();

  std::vector<std::string> algorithms = app.get_supported_algorithms();
  static int item_selected_idx_prv = 0;
  static int item_selected_idx = 0;
  std::string combo_preview_value = algorithms[item_selected_idx];
  if (ImGui::BeginCombo("Select Algorithm", combo_preview_value.c_str(),
                        ImGuiComboFlags_HeightLargest)) {
    for (int i = 0; i < algorithms.size(); i++) {
      const bool is_selected = (item_selected_idx == i);
      if (ImGui::Selectable(algorithms[i].c_str(), is_selected))
        item_selected_idx = i;

      if (is_selected) {
        ImGui::SetItemDefaultFocus();
      }
    }
    if (item_selected_idx != item_selected_idx_prv) {
      event_handler.handle_algorithm_change(algorithms[item_selected_idx]);
      std::cout << "change" << std::endl;
      item_selected_idx_prv = item_selected_idx;
    }
    ImGui::EndCombo();
  }
}

void UI::draw_buttons(EventHandler &event_handler) {
  App &app = App::get_instance();

  AlgoState algo_state = app.get_algo_state();
  if (algo_state == AlgoState::RESET) {
    if (ImGui::Button("Start")) event_handler.handle_start_button_click();
  } else if ((algo_state == AlgoState::ALGORITHM_RUN ||
              algo_state == AlgoState::PATH_RUN) &&
             (algo_state != AlgoState::FINISH ||
              algo_state != AlgoState::FINISH_TARGET_NOT_FOUND)) {
    if (ImGui::Button("Pause")) event_handler.handle_pause_button_click();
  } else if (algo_state == AlgoState::ALGORITHM_PAUSE ||
             algo_state == AlgoState::PATH_PAUSE) {
    if (ImGui::Button("Resume")) event_handler.handle_resume_button_click();
  }

  ImGui::SameLine();
  if (ImGui::Button("Reset")) {
    event_handler.handle_reset_button_click();
  }
}

void UI::draw_cursor() {
  App &app = App::get_instance();
  if (app.get_cursor_state() == CursorState::NOT_ALLOWED) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_NotAllowed);
  } else if (app.get_cursor_state() == CursorState::ARROW) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
  } else if (app.get_cursor_state() == CursorState::HAND) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
  } else if (app.get_cursor_state() == CursorState::RESIZE_ALL) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
  } else if (app.get_cursor_state() == CursorState::RESIZE_NWSE) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);
  } else if (app.get_cursor_state() == CursorState::RESIZE_NS) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
  } else if (app.get_cursor_state() == CursorState::RESIZE_EW) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
  } else if (app.get_cursor_state() == CursorState::RESIZE_NESW) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);
  } else if (app.get_cursor_state() == CursorState::TEXT_INPUT) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
  }
}
