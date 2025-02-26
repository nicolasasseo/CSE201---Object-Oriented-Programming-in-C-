#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include "army.h"
#include "monster.h"
int main(int argc, char *argv[])
{
  struct army *army = create_army();
  struct monster **monsters = malloc(10 * sizeof(struct monster));
  for (int i = 0; i < 10; i++)
  {
    char name[NAME_SIZE];
    snprintf(name, sizeof(name), "Pikachu-%d", i);
    monsters[i] = create_monster(name, 78);
    add_monster_to_army(army, monsters[i]);
  }

  display_army(army);

  delete_army(army);

  // * Previous questions
  // for (int i = 0; i < 10; i++)
  // {
  //   printf("Monster %d:\n", i + 1);
  //   display_monster(monsters[i]);
  // }
  // for (int i = 0; i < 10; i++)
  // {
  //   delete_monster(monsters[i]);
  // }
  // free(monsters);
}
