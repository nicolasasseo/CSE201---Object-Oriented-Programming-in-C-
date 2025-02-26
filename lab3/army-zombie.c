#include <stdio.h>
#include <stdlib.h>
#include "monster.h"

// * Previous questions
// struct army
// {
//   struct monster **monsters; // a pointer to an array, where each element of the array is a pointer to a monster
//   int top;                   // where you have the last monster in the array
//   int capacity;              // the capacity of the array
//   int stars;
// };
// struct army *create_army()
// {
//   struct army *army = malloc(sizeof(struct army));
//   army->monsters = NULL;
//   army->top = -1;
//   army->capacity = 0;
//   army->stars = 0;
//   return army;
// }
// void add_monster_to_army(struct army *army, struct monster *monster)
// {
//   if (army->capacity == 0)
//   {
//     army->capacity = 1;
//     army->monsters = malloc(army->capacity * sizeof(struct monster *));
//   }
//   else if (army->capacity == army->top + 1)
//   {
//     army->capacity *= 2;
//     struct monster **new_monsters = realloc(army->monsters, sizeof(struct monster));
//     army->monsters = new_monsters;
//   }
//   army->monsters[army->top + 1] = monster;
//   army->top++;
// }

struct node
{
  struct monster *data;
  struct node *next;
};

struct army
{
  struct node *first;
  int stars;
};

struct army *create_army()
{
  struct army *army = malloc(sizeof(struct army));
  army->first = NULL;
  return army;
}

void add_monster_to_army(struct army *army, struct monster *monster)
{
  struct node *new_node = malloc(sizeof(struct node));
  new_node->data = monster;
  new_node->next = NULL;

  if (army->first == NULL)
  {
    army->first = new_node;
  }
  else
  {
    struct node *current = army->first;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = new_node;
  }
};

void display_army(struct army *army)
{
  printf("This is an army of %d stars \n", army->stars);
  struct node *current = army->first;
  while (current != NULL)
  {
    display_monster(current->data);
    current = current->next;
  }
}

void delete_army(struct army *army)
{
  struct node *current = army->first;
  while (current != NULL)
  {
    struct node *next = current->next;
    delete_monster(current->data);
    free(current);
    current = next;
  }
  free(army);
}