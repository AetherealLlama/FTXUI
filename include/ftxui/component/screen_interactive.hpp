#ifndef FTXUI_COMPONENT_SCREEN_INTERACTIVE_HPP
#define FTXUI_COMPONENT_SCREEN_INTERACTIVE_HPP

#include <atomic>                        // for atomic
#include <ftxui/component/receiver.hpp>  // for Receiver, Sender
#include <functional>                    // for function
#include <memory>                        // for shared_ptr
#include <string>                        // for string

#include "ftxui/component/captured_mouse.hpp"  // for CapturedMouse
#include "ftxui/component/event.hpp"
#include "ftxui/screen/screen.hpp"  // for Screen

namespace ftxui {
class ComponentBase;

using Component = std::shared_ptr<ComponentBase>;
struct Event;

class ScreenInteractive : public Screen {
 public:
  static ScreenInteractive FixedSize(int dimx, int dimy);
  static ScreenInteractive Fullscreen();
  static ScreenInteractive FitComponent();
  static ScreenInteractive TerminalOutput();

  ~ScreenInteractive();
  void Loop(Component);
  std::function<void()> ExitLoopClosure();

  void PostEvent(Event event);
  CapturedMouse CaptureMouse();

 private:
  void Draw(Component component);
  void EventLoop(Component component);

  enum class Dimension {
    FitComponent,
    Fixed,
    Fullscreen,
    TerminalOutput,
  };
  Dimension dimension_ = Dimension::Fixed;
  bool use_alternative_screen_ = false;
  ScreenInteractive(int dimx,
                    int dimy,
                    Dimension dimension,
                    bool use_alternative_screen);

  Sender<Event> event_sender_;
  Receiver<Event> event_receiver_;

  std::string set_cursor_position;
  std::string reset_cursor_position;

  std::atomic<bool> quit_ = false;

  int cursor_x_ = 1;
  int cursor_y_ = 1;

  bool mouse_captured = false;
};

}  // namespace ftxui

#endif /* end of include guard: FTXUI_COMPONENT_SCREEN_INTERACTIVE_HPP */

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
