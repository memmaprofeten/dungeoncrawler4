#include "item.hpp"

std::string Item::getname() const{
  return name;
}

int Item::gettype() const{
  return type;
}

float Item::getvalue() const{
  return value;
}
