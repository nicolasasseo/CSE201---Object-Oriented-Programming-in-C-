#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monster.h"

struct monster *create_monster(char *name, int health)
{
  struct monster *m = malloc(sizeof(struct monster));
  strcpy(m->name, name);
  m->health = health;
  return m;
}

void display_monster(struct monster *m)
{
  printf("Monster: %s, Health: %d\n", m->name, m->health);
}

void delete_monster(struct monster *m)
{
  free(m);
}
