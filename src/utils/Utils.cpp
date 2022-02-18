#include "Utils.hpp"

const char*
utils::not_implemented::what() const throw()
{
  return "Not implemented yet";
}

const char*
utils::not_tested::what() const throw()
{
  return "Not tested yet";
}

const char*
utils::non_valid_state_switch::what() const throw()
{
  return "The requested state switch is not valid";
}
