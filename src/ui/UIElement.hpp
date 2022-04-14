/**
 * @file UIElement.hpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#ifndef TEMPEST_ATARI_UIELEMENT_HPP
#define TEMPEST_ATARI_UIELEMENT_HPP

#include "SDL2/SDL.h"

class UIElement
{
protected:
  SDL_Rect bounding_box_;

public:
  UIElement() = delete;
  // UIElement(const UIElement &) = delete;
  UIElement(int x, int y, int w, int h);
  ~UIElement();

  virtual void update() = 0;
  virtual void render(SDL_Renderer* r) const = 0;
};

#endif // TEMPEST_ATARI_UIELEMENT_HPP