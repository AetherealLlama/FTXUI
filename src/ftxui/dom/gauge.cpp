#include <memory>  // for make_shared

#include "ftxui/dom/elements.hpp"     // for Element, gauge
#include "ftxui/dom/node.hpp"         // for Node
#include "ftxui/dom/requirement.hpp"  // for Requirement
#include "ftxui/screen/box.hpp"       // for Box
#include "ftxui/screen/screen.hpp"    // for Screen

namespace ftxui {

#if defined(FTXUI_MICROSOFT_TERMINAL_FALLBACK)
// Microsoft's terminals often use fonts not handling the 8 unicode characters
// for representing the whole gauge. Fallback with less.
static wchar_t charset[] = L"    ▌▌▌███";
#else
static wchar_t charset[] = L"  ▏▎▍▌▋▊▉█";
#endif

class Gauge : public Node {
 public:
  Gauge(float progress) : progress_(progress) {}
  ~Gauge() override {}

  void ComputeRequirement() override {
    requirement_.flex_grow_x = 1;
    requirement_.flex_grow_y = 0;
    requirement_.flex_shrink_x = 1;
    requirement_.flex_shrink_y = 0;
    requirement_.min_x = 1;
    requirement_.min_y = 1;
  }

  void Render(Screen& screen) override {
    float y = box_.y_min;
    float limit = box_.x_min + progress_ * (box_.x_max - box_.x_min + 1);
    int limit_int = limit;
    int x = box_.x_min;
    while (x < limit_int)
      screen.at(x++, y) = charset[9];
    screen.at(x++, y) = charset[int(9 * (limit - limit_int))];
    while (x <= box_.x_max)
      screen.at(x++, y) = charset[0];
  }

 private:
  float progress_;
};

/// @brief Draw a high definition progress bar.
/// @param progress The proportion of the area to be filled. Belong to [0,1].
/// @ingroup dom
///
/// ### Example
///
/// A gauge. It can be used to represent a progress bar.
/// ~~~cpp
/// border(gauge(0.5))
/// ~~~
///
/// #### Output
///
/// ~~~bash
/// ┌──────────────────────────────────────────────────────────────────────────┐
/// │█████████████████████████████████████                                     │
/// └──────────────────────────────────────────────────────────────────────────┘
/// ~~~
Element gauge(float progress) {
  return std::make_shared<Gauge>(progress);
}

}  // namespace ftxui

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
