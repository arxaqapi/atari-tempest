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

#include "../sdlw/SDLW.hpp"
class UIElement
{
protected:
  SDL_Rect bounding_box_; // TODO: Change Me !!

public:
  UIElement() = delete;
  UIElement(int x, int y, int w, int h);
  ~UIElement();

  virtual void update() = 0;
  virtual void render(SDLW::Renderer& renderer) const = 0;
};

#endif // TEMPEST_ATARI_UIELEMENT_HPP