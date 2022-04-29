/**
 * @file Errors.cpp
 * @author Tarek Kunze (https://github.com/arxaqapi)
 * @version 0.1
 * @date 2022-04-29
 *
 * @copyright Copyright (c) 2022
 *
 * @brief
 */
#include "Errors.hpp"

const char*
errors::NotImplemented::what() const throw()
{
  return "Not implemented yet";
}

const char*
errors::NotTested::what() const throw()
{
  return "Not tested yet";
}

const char*
errors::NonValidStateSwitch::what() const throw()
{
  return "The requested state switch is not valid";
}

const char*
errors::FileNotOpened::what() const throw()
{
  return "Unable to open file";
}

const char*
errors::NonValidCharacterRequested::what() const throw()
{
  return "Requested character not supported";
}

errors::SdlError::SdlError(const std::string& msg)
  : msg_{ msg }
{}

const char*
errors::SdlError::what() const throw()
{
  return msg_.c_str();
}