#include <iostream>
#include "treemap.h"
#include <map>

int main(int argc, char **argv)
{
  std::map<lanister_t, account_t> map;
  map["Tyrion"] = 2;
  map["Jaime"] = 15;
  map["Cersei"] = 63;
  map["Tywin"] = 75;
  map["Kevan"] = 48;
  map["Lancel"] = 70;
  map["Alton"] = 54;
  map["Martyn"] = 32;
  map["Willem"] = 6;

  for (auto &[key, value] : map)
  {
    std::cout << key << " => " << value << std::endl;
  }

  account_t a = 42;
  a.note = "best client ever";
  std::cout << a << std::endl;
}