#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <cstddef>
#include <numbers>
#include <cmath>

using namespace std;

struct location_t
{

  // Attributes
  ::string name;
  double latitude;
  double longitude;
  location_t **neighbors;
  size_t num_neighbors;

  // Constructor
  location_t(::string name, double latitude, double longitude)
      : name{name}, latitude{latitude}, longitude{longitude}, neighbors{nullptr}, num_neighbors{0} {}

  // Add neighbors
  void set_neighbors(location_t *list[])
  {
    neighbors = list;
    int i = 0;
    while (list[i] != nullptr)
    {
      i++;
    }
    num_neighbors = i;
  }

  // Destructor
  ~location_t()
  {
    delete[] neighbors;
  };

  // Compute distance between two locations
  double distance_to(location_t *to)
  {
    double radius = 6378;
    return radius * (std::numbers::pi / 2 - ::asin(::sin(to->latitude) * ::sin(latitude) + ::cos(to->longitude - longitude) * ::cos(to->latitude) * ::cos(latitude)));
  }
};

#endif