#include <stdio.h>
#include <stdlib.h>
#include "army.h"

struct army
{
  struct monster **monsters; // a pointer to an array, where each element of the array is a pointer to a monster
  int top;                   // where you have the last monster in the array
  int capacity;              // the capacity of the array
};

struct army *create_army()
{
  struct army *army = malloc(sizeof(struct army));
  army->monsters = NULL;
  army->top = -1;
  army->capacity = 0;
  return army;
}

void add_monster_to_army(struct army *army, struct monster *monster)
{
  if (army->capacity == 0)
  {
    army->capacity = 1;
    army->monsters = malloc(army->capacity * sizeof(struct monster *));
  }
  else if (army->capacity == army->top + 1)
  {
    army->capacity *= 2;
    struct monster **new_monsters = realloc(army->monsters, sizeof(struct monster));
    army->monsters = new_monsters;
  }
  army->monsters[army->top + 1] = monster;
  army->top++;
}

void display_army(struct army *army)
{
  for (int i = 0; i < army->top + 1; i++)
  {
    display_monster(army->monsters[i]);
  }
}

void delete_army(struct army *army)
{
  for (int i = 0; i < army->top + 1; i++)
  {
    delete_monster(army->monsters[i]);
  }
  free(army->monsters);
  free(army);
}