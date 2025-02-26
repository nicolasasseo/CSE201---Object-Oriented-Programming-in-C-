#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H
#include "location.h"

struct node_t
{
  node_t *next;         // next node
  location_t *location; // city represented by node
  node_t *from;         // previous city visited
  double from_origin;   // actual distance
  double total;         // distance in a straight line
  bool visited;
  double dist_from_origin(node_t *from);
};

struct shortest_path_t
{
  node_t *head;     // set of nodes (a pointer to the first node of the set)
  node_t *base;     // current base
  location_t *from; // origin
  location_t *to;   // destination

  shortest_path_t(location_t *from, location_t *to)
      : head{new node_t{nullptr, from, nullptr, 0, 0, true}},
        base{head},
        from{from},
        to{to} { head->total = to->distance_to(from); }

  ~shortest_path_t()
  {
    node_t *current_node = head->next;
    node_t *node_to_free = head;
    while (current_node != nullptr)
    {
      delete node_to_free;
      node_to_free = current_node;
      current_node = current_node->next;
    }
    delete node_to_free;
  }

  void compute();
  void set_neighbors();
  node_t *last_node();
  node_t *list_location(location_t *city);
  void find_next();
  void display();
};

struct linked_list
{
  location_t *location;
  linked_list *from;
  double distance;
  ~linked_list();
};

#endif