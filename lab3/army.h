#include "monster.h"
#ifndef ARMY_H
#define ARMY_H

struct army;

struct army *create_army();
void add_monster_to_army(struct army *army, struct monster *monster);
void display_army(struct army *army);
void delete_army(struct army *army);

#endif