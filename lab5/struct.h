#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <stdint.h>

using namespace std;

struct list_t;
struct frame_t;

// Definition of node_t
struct node_t
{
  virtual node_t *eval(frame_t *frame);
  virtual node_t *apply(list_t *list, frame_t *frame);
  virtual ::string to_string();
  virtual list_t *as_list();
  virtual uintptr_t int_value();
  virtual bool is(string id);
};

// Definition of list_t
struct list_t : node_t
{
  node_t **elements;  // points to an array where each elt is a pointer to a node
  size_t nb_elements; // number of elts in array
  size_t capacity;    // total capacity of array
  list_t();
  list_t *as_list();
  size_t size();
  node_t *at(size_t i);
  void set_at(size_t i, node_t *value);
  void append(node_t *value);
  ::string to_string();
  node_t *eval(frame_t *frame);
};

// Definition of integer_t
struct integer_t : node_t
{
  uintptr_t val;
  integer_t(uintptr_t val);
  ::string to_string();
  uintptr_t int_value();
};

// Keyword structure
struct keyword_t : node_t
{
  ::string id;            // identifier
  keyword_t(::string id); // constructor
  ::string to_string();   // convert id to <id>
};

// Add_t structure (child of keyword)
struct add_t : keyword_t
{
  add_t();
  node_t *apply(list_t *list, frame_t *frame);
};

// Symbol structure
struct symbol_t : node_t
{
  ::string id;           // identifier
  symbol_t(::string id); // constructor
  bool is(string id);
  string to_string();
  node_t *eval(frame_t *frame);
};

// Frame
struct frame_t : list_t
{
  void set(node_t *sym, node_t *value);
  node_t *get(node_t *sym);
};

struct set_t : node_t
{
  node_t *apply(list_t *list, frame_t *frame);
  ::string to_string();
};

#endif