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
#include "../utils/types.hpp"

class UIElement
{
protected:
  SDLW::Rect bounding_box_;

public:
  UIElement() = delete;
  UIElement(i32 x, i32 y, i32 w, i32 h);
  ~UIElement();

  virtual void update() = 0;
  virtual void render(SDLW::Renderer& renderer) const = 0;
};

#endif // TEMPEST_ATARI_UIELEMENT_HPP