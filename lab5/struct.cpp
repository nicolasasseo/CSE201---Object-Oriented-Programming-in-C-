#include "struct.h"
#include <iostream>

using namespace std;

// Error code copied from lab instructions
void error(std::string str) __attribute__((noreturn));
void error(std::string str)
{
  std::cout << "Error: " << str << std::endl;
  exit(1);
}

node_t *node_t::eval(frame_t *frame)
{
  return this;
}

node_t *node_t::apply(list_t *list, frame_t *frame)
{
  error("for apply...");
}

list_t *node_t::as_list()
{
  error("for as_list...");
}

::string node_t::to_string()
{
  return "???";
}

uintptr_t node_t::int_value()
{
  error("node is not an integer");
}

bool node_t::is(string id)
{
  return false;
}

list_t::list_t()
    : elements{nullptr}, nb_elements{0}, capacity{0} {};

// Return list
list_t *list_t::as_list()
{
  return this;
}

// Return size
size_t list_t::size()
{
  return nb_elements;
}

// Returns element at index i
node_t *list_t::at(size_t i)
{
  if (i >= size())
  {
    error("index out of range");
  }
  return elements[i];
}

// Sets value at index i
void list_t::set_at(size_t i, node_t *value)
{
  if (i >= nb_elements)
  {
    error("index out of range");
  }
  elements[i] = value;
}

// Append new value to the list
void list_t::append(node_t *value)
{
  if (nb_elements == capacity)
  {
    size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;
    node_t **new_elements = new node_t *[new_capacity];
    for (size_t i = 0; i < nb_elements; i++)
    {
      new_elements[i] = elements[i];
    }
    delete[] elements;
    elements = new_elements;
    capacity = new_capacity;
  }
  elements[nb_elements++] = value;
};

// Returns string that rpz list in fully parenthesised notation
::string list_t::to_string()
{
  ::string res = "(";
  for (size_t i = 0; i < nb_elements; i++)
  {
    res += elements[i]->to_string();
    if (i < nb_elements - 1)
      res += " ";
  }
  res += ")";
  return res;
};

// Eval method
node_t *list_t::eval(frame_t *frame)
{
  if (nb_elements == 0)
  {
    error("no expression");
  }
  return elements[0]->eval(frame)->apply(this, frame);
}

integer_t::integer_t(uintptr_t val)
    : val{val} {};

string integer_t::to_string()
{
  return std::to_string(val);
};

uintptr_t integer_t::int_value()
{
  return val;
};

keyword_t::keyword_t(string id)
    : id{id} {};

string keyword_t::to_string()
{
  return "<" + id + ">";
}

add_t::add_t()
    : keyword_t{"+"} {};

node_t *add_t::apply(list_t *list, frame_t *frame)
{
  uintptr_t res = 0;
  for (size_t i = 1; i < list->nb_elements; i++)
  {
    res += list->at(i)->eval(frame)->int_value();
  }
  return new integer_t{res};
}

symbol_t::symbol_t(string id)
    : id{id} {}

bool symbol_t::is(string id)
{
  return this->id == id;
}

string symbol_t::to_string()
{
  return id;
}

node_t *symbol_t::eval(frame_t *frame)
{
  return frame->get(this);
}

void frame_t::set(node_t *sym, node_t *value)
{
  bool is_present = false;
  for (size_t i = 0; i < nb_elements; i++)
  {
    if (this->at(i)->as_list()->at(0)->is(sym->to_string()))
    {
      at(i)->as_list()->set_at(1, value);
      is_present = true;
    }
  }
  if (!is_present)
  {
    list_t *new_list = new list_t;
    new_list->append(sym);
    new_list->append(value);
    append(new_list);
  }
}

node_t *frame_t::get(node_t *sym)
{
  for (size_t i = 0; i < nb_elements; i++)
  {
    if (this->at(i)->as_list()->at(0)->is(sym->to_string()))
    {
      return at(i)->as_list()->at(1);
    }
  }
  error("Symbol does not exist in the frame");
}

::string set_t::to_string()
{
  return "set!";
}

node_t *set_t::apply(list_t *list, frame_t *frame)
{
  node_t *symbol = list->at(1);
  node_t *l = list->at(2);
  node_t *value = l->eval(frame);
  frame->set(symbol, value);
  return value;
}