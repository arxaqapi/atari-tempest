/**
 * @file SDLW.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-15
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#ifndef TEMPEST_ATARI_SDLW_HPP
#define TEMPEST_ATARI_SDLW_HPP

#include "../utils/types.hpp"
#include "SDL2/SDL.h"
#include <string>

namespace impl {
template<typename T, typename Enable = void>
class base_Rect;

template<typename T>
class base_Rect<T, std::enable_if_t<std::is_same<T, f32>::value>>
{
protected:
  SDL_FRect r_;
};

template<typename T>
class base_Rect<T, std::enable_if_t<std::is_same<T, i32>::value>>
{
protected:
  SDL_Rect r_;
};
}

namespace SDLW {
/// Forward declaration
class Renderer;

template<typename T>
class Rect_T : public impl::base_Rect<T>
{
  friend class Renderer;

public:
  Rect_T() = delete;
  Rect_T(T x, T y, T w, T h)
  {
    impl::base_Rect<T>::r_.x = x;
    impl::base_Rect<T>::r_.y = y;
    impl::base_Rect<T>::r_.w = w;
    impl::base_Rect<T>::r_.h = h;
  };
  ~Rect_T(){};

  T x() const { return impl::base_Rect<T>::r_.x; };
  T y() const { return impl::base_Rect<T>::r_.y; };
  T w() const { return impl::base_Rect<T>::r_.w; };
  T h() const { return impl::base_Rect<T>::r_.h; };
};

///////////////////

//// Window

class Window
{
  friend class Renderer;

private:
  SDL_Window* w_;

public:
  Window() = delete;
  Window(const SDLW::Window&) = delete;
  Window(const std::string& title, i32 x, i32 y, i32 w, i32 h, u32 flags);
  ~Window();
};

//// Renderer
class Renderer
{
private:
  SDL_Renderer* r_;

public:
  Renderer() = delete;
  Renderer(const SDLW::Renderer&) = delete;
  Renderer(SDLW::Window& window, i32 index, u32 flags);
  ~Renderer();

  void RenderDrawRect(const SDLW::Rect_T<i32>& rect);
  void RenderFillRect(const SDLW::Rect_T<i32>& rect);
  void RenderFillRectF(const SDLW::Rect_T<f32>& rect);

  void RenderDrawLineF(f32 x1, f32 y1, f32 x2, f32 y2);
  void RenderDrawLine(i32 x1, i32 y1, i32 x2, i32 y2);

  void SetRenderDrawColor(u8 r, u8 g, u8 b, u8 a);
  void RenderPresent();
  void RenderClear();
};

void
Init(u32 flags);
void
Quit();

// Time
u64
GetTicks64();
u64
GetPerformanceCounter();
void
Delay(u32 ms);
u64
GetPerformanceFrequency();

} // namespace SDLW

// SECTION: Extra
// struct SDL_FRect;
// SDL_Color
// struct SDL_Event; // override == operator
// SDL_Event SDL_PollEvent();

#endif