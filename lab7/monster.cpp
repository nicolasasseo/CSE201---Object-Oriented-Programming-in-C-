#include <iostream>
#include <vector>

struct monster_t
{
  std::string name;
  int health;

  monster_t() : name(""), health(0) {}

  monster_t(const std::string &name, int health) : name(name), health(health) {}
};

std::ostream &operator<<(std::ostream &os, const monster_t &m)
{
  os << m.name << " (Health: " << m.health << ")";
  return os;
}

int main(int argc, char **argv)
{

  std::vector<monster_t> army;
  for (int i = 1; i < 11; i++)
  {
    std::string name = "Pikachu-" + std::to_string(i);
    army.push_back(monster_t(name, 60));
  }

  for (const auto &m : army)
  {
    std::cout << m << std::endl;
  }
  return 0;
}