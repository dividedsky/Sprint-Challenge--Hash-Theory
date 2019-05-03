#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));

  // loop through tickets and create hash table
  for (int i = 0; i < length; i++) {
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }

  // set the current ticket by looking for the ht entry with NONE key
  char *current = hash_table_retrieve(ht, "NONE");
  /* while (hash_table_retrieve(ht, current) != "NONE") { */
  for (int i = 0; i < length; i++) {
    // while the current ticket has a destination, append value to list
    /* if (strcmp(hash_table_retrieve(ht, current), "NONE") == 0) { */
    /*   break; */
    /* } */
    *(route + i) = current;
    current = hash_table_retrieve(ht, current);
  }
  destroy_hash_table(ht);
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  /* fixing memory leak */
  /* print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE */
  char **route = reconstruct_trip(tickets, 3);
  print_route(route, 3);
  free(route);
  for (int i = 0; i < 3; i++) {
    free(tickets[i]);
  }
  free(tickets);

  return 0;
}
#endif
