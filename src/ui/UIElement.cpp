/**
 * @file UIElement.cpp
 * @author arxaqapi (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */

#include "UIElement.hpp"

UIElement::UIElement(i32 x, i32 y, i32 w, i32 h)
  : bounding_box_{ x, y, w, h }
{}

UIElement::~UIElement() {}