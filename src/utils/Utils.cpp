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