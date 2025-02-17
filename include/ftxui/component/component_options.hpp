#ifndef FTXUI_COMPONENT_COMPONENT_OPTIONS_HPP
#define FTXUI_COMPONENT_COMPONENT_OPTIONS_HPP

#include <ftxui/dom/elements.hpp>
#include <ftxui/util/ref.hpp>

namespace ftxui {

/// @brief Option for the Menu component.
/// @ingroup component
struct MenuOption {
  Decorator style_normal = nothing;    /// style.
  Decorator style_focused = inverted;  /// Style when focused.
  Decorator style_selected = bold;     /// Style when selected.
  Decorator style_selected_focused =
      Decorator(inverted) | bold;  /// Style when selected and focused.

  /// Called when the selected entry changes.
  std::function<void()> on_change = [] {};
  /// Called when the user presses enter.
  std::function<void()> on_enter = [] {};

  Ref<int> focused_entry = 0;
};

/// @brief Option for the Button component.
/// @ingroup component
struct ButtonOption {
  /// Whether to show a border around the button.
  bool border = true;
};

/// @brief Option for the Checkbox component.
/// @ingroup component
struct CheckboxOption {
  std::wstring style_checked = L"▣ ";    /// Prefix for a "checked" state.
  std::wstring style_unchecked = L"☐ ";  /// Prefix for a "unchecked" state.
  Decorator style_focused = inverted;    /// Decorator used when focused.
  Decorator style_unfocused = nothing;   /// Decorator used when unfocused.

  /// Called when the user change the state.
  std::function<void()> on_change = []() {};
};

/// @brief Option for the Input component.
/// @ingroup component
struct InputOption {
  /// Called when the content changes.
  std::function<void()> on_change = [] {};
  /// Called when the user presses enter.
  std::function<void()> on_enter = [] {};

  Ref<int> cursor_position = 0;
};

/// @brief Option for the Radiobox component.
/// @ingroup component
struct RadioboxOption {
  std::wstring style_checked = L"◉ ";    /// Prefix for a "checked" state.
  std::wstring style_unchecked = L"○ ";  /// Prefix for a "unchecked" state.
  Decorator style_focused = inverted;    /// Decorator used when focused.
  Decorator style_unfocused = nothing;   /// Decorator used when unfocused.

  /// Called when the selected entry changes.
  std::function<void()> on_change = []() {};

  Ref<int> focused_entry = 0;
};

/// @brief Option for the Toggle component.
/// @ingroup component
struct ToggleOption {
  Decorator style_normal = nothing;    /// style.
  Decorator style_focused = inverted;  /// Style when focused.
  Decorator style_selected = bold;     /// Style when selected.
  Decorator style_selected_focused =
      Decorator(inverted) | bold;  /// Style when selected and focused.

  /// Called when the selected entry changes.
  std::function<void()> on_change = [] {};
  /// Called when the user presses enter.
  std::function<void()> on_enter = [] {};

  Ref<int> focused_entry = 0;
};

}  // namespace ftxui

#endif /* end of include guard: FTXUI_COMPONENT_COMPONENT_OPTIONS_HPP */

// Copyright 2021 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
