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

UIElement::UIElement(int x, int y, int w, int h)
  : bounding_box_{ x, y, w, h }
{}

UIElement::~UIElement() {}