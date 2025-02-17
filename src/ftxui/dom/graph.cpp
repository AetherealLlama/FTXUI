#include <functional>  // for function
#include <memory>      // for make_shared
#include <vector>      // for vector

#include "ftxui/dom/elements.hpp"     // for GraphFunction, Element, graph
#include "ftxui/dom/node.hpp"         // for Node
#include "ftxui/dom/requirement.hpp"  // for Requirement
#include "ftxui/screen/box.hpp"       // for Box
#include "ftxui/screen/screen.hpp"    // for Screen

namespace ftxui {

// Microsoft's terminals often use fonts not handling the 8 unicode characters
// for representing the whole gauge. Fallback with less.
#if defined(FTXUI_MICROSOFT_TERMINAL_FALLBACK)
const wchar_t charset[] = L"  █ █████";
#else
const wchar_t charset[] = L" ▗▐▖▄▟▌▙█";
#endif

class Graph : public Node {
 public:
  Graph(GraphFunction graph_function) : graph_function_(graph_function) {}
  ~Graph() override {}

  void ComputeRequirement() override {
    requirement_.flex_grow_x = 1;
    requirement_.flex_grow_y = 1;
    requirement_.flex_shrink_x = 1;
    requirement_.flex_shrink_y = 1;
    requirement_.min_x = 3;
    requirement_.min_y = 3;
  }

  void Render(Screen& screen) override {
    int width = (box_.x_max - box_.x_min + 1) * 2;
    int height = (box_.y_max - box_.y_min + 1) * 2;
    auto data = graph_function_(width, height);
    int i = 0;
    for (int x = box_.x_min; x <= box_.x_max; ++x) {
      int height_1 = 2 * box_.y_max - data[i++];
      int height_2 = 2 * box_.y_max - data[i++];
      for (int y = box_.y_min; y <= box_.y_max; ++y) {
        int yy = 2 * y;
        int i_1 = yy < height_1 ? 0 : yy == height_1 ? 3 : 6;
        int i_2 = yy < height_2 ? 0 : yy == height_2 ? 1 : 2;
        wchar_t pix = charset[i_1 + i_2];
        screen.at(x, y) = pix;
      }
    }
  }

 private:
  GraphFunction graph_function_;
};

/// @brief Draw a graph using a GraphFunction.
/// @param graph_function the function to be called to get the data.
Element graph(GraphFunction graph_function) {
  return std::make_shared<Graph>(graph_function);
}

}  // namespace ftxui

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
