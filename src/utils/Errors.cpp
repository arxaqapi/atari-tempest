#include "Errors.hpp"

const char*
errors::not_implemented::what() const throw()
{
  return "Not implemented yet";
}

const char*
errors::not_tested::what() const throw()
{
  return "Not tested yet";
}

const char*
errors::non_valid_state_switch::what() const throw()
{
  return "The requested state switch is not valid";
}

const char*
errors::file_not_opened::what() const throw()
{
  return "Unable to open levels data file";
}

const char*
errors::non_valid_character_requested::what() const throw()
{
  return "Requested character not supported";
}

errors::sdl_error::sdl_error(const std::string& msg)
  : msg_{ msg }
{}

const char*
errors::sdl_error::what() const throw()
{
  return msg_.c_str();
}