/**
 * @file UIElement.cpp
 * @author Tarek Kunze(https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "UIElement.hpp"

UIElement::UIElement()
  : bounding_box_{ 0, 0, 0, 0 }
{}

UIElement::UIElement(i32 x, i32 y, i32 w, i32 h)
  : bounding_box_{ x, y, w, h }
{}

UIElement::~UIElement() {}