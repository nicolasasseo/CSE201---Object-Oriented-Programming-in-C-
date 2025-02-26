#include "shortest_path.h"
#include <iostream>
#include <limits>

using namespace std;

linked_list::~linked_list()
{
  delete this;
}

node_t *shortest_path_t::list_location(location_t *city)
{
  for (node_t *node = head; node != nullptr; node = node->next)
  {
    if (node->location->name == city->name)
    {
      return node;
    }
  }
  return nullptr;
}

double node_t::dist_from_origin(node_t *from)
{
  return from->from_origin + location->distance_to(from->location);
}

node_t *shortest_path_t::last_node()
{
  node_t *current = head;
  while (current->next != nullptr)
  {
    current = current->next;
  }
  return current;
}

void shortest_path_t::set_neighbors()
{
  for (size_t i = 0; i < base->location->num_neighbors; i++)
  {
    node_t *neighbor = list_location(base->location->neighbors[i]);
    if (neighbor == nullptr)
    {
      node_t *new_n = new node_t{nullptr, base->location->neighbors[i], base, 0, 0, false};
      new_n->from_origin = new_n->dist_from_origin(base);
      new_n->total = new_n->from_origin + new_n->location->distance_to(to);
      new_n->visited = false;
      node_t *last = last_node();
      last->next = new_n;
    }
    else
    {
      if (neighbor->from_origin > neighbor->dist_from_origin(base))
      {
        neighbor->from_origin = neighbor->dist_from_origin(base);
        neighbor->total = neighbor->location->distance_to(to) + neighbor->from_origin;
        neighbor->from = base;
      }
    }
  }
}

void shortest_path_t::find_next()
{
  set_neighbors();
  double min_val = ::numeric_limits<double>::infinity();
  node_t *max_node = nullptr;
  for (node_t *current = head; current != nullptr; current = current->next)
  {
    if (current->visited == false && min_val > current->total)
    {
      max_node = current;
      min_val = current->total;
    }
  }
  base = max_node;
  if (base == nullptr)
  {
    cout << "No valid path found." << endl;
    exit(0);
  }
  else
  {
    base->visited = true;
  }
}

void shortest_path_t::compute()
{
  // from = origin. each step: select new starting point base (non visited w/ minimal total). visit each ngb of base. then: IF ngb never reached, create a node for the city ELSE the ngb was already visited w/ a longer path, update its node.

  while (base != nullptr)
  {
    cout << "Currently at: " << base->location->name << endl;
    if (base->location->name == to->name)
    {
      return;
    }
    find_next();
    if (base == nullptr)
    {
      cout << "No path found to the destination." << endl;
      return;
    }
  }
}

void shortest_path_t::display()
{
  if (base->location->name != to->name)
  {
    return;
  }
  linked_list *list = new linked_list{base->location, nullptr, base->from_origin};
  linked_list *before = list;
  for (node_t *current = base->from; current != nullptr; current = current->from)
  {
    linked_list *new_n = new linked_list{current->location, before, current->from_origin};
    before = new_n;
  }
  ::cout << "Path from " << from->name << " to " << to->name << "\n";
  while (before != nullptr)
  {
    ::cout << before->location->name << " at " << before->distance << "km from " << from->name << "\n";
    before = before->from;
  }
};