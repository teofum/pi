#include <stdlib.h>
#include <string.h>

#include "socialADT.h"

#define BLOCK_SIZE 16

typedef struct related_node {
  const char *name;
  struct related_node *tail;
} related_node;

typedef struct related_node *related_list;

typedef struct person_node {
  const char *name;
  related_list related;
  struct person_node *tail;
} person_node;

typedef struct person_node *person_list;

typedef struct socialCDT {
  person_list persons;
} socialCDT;

socialADT social_new(void) {
  socialADT social = calloc(1, sizeof(socialCDT));
  return social;
}

static void free_related(related_node *related) {
  if (related) {
    free(related->name);
    free_related(related->tail);
    free(related);
  }
}

static void free_person(person_node *person) {
  if (person) {
    free(person->name);
    free_related(person->related);
    free_person(person->tail);
    free(person);
  }
}

void social_free(socialADT soc) {
  free_person(soc->persons);
  free(soc);
}

static person_node *new_person(const char *name, person_node *tail) {
  person_node *node = malloc(sizeof(person_node));
  node->name = strdup(name);
  node->related = NULL;
  node->tail = tail;
  return node;
}

static person_node *add_person(person_node *person, const char *name) {
  if (!person) return new_person(name, NULL);

  int name_cmp = strcmp(person->name, name);
  if (name_cmp == 0) return person; // Person with this name exists, do nothing
  if (name_cmp > 0) return new_person(name, person); // Insert

  person->tail = add_person(person->tail, name); // Skip
  return person;
}

void social_add_person(socialADT soc, const char *name) {
  soc->persons = add_person(soc->persons, name);
}

static person_node *find_person(person_node *person, const char *name) {
  if (!person) return NULL;

  int name_cmp = strcmp(person->name, name);
  if (name_cmp == 0) return person;
  if (name_cmp > 0) return NULL;

  return find_person(person->tail, name);
}

static related_node *new_related(const char *name, related_node *tail) {
  related_node *node = malloc(sizeof(related_node));
  node->name = strdup(name);
  node->tail = tail;
  return node;
}

static related_node *add_related(related_node *related, const char *name) {
  if (!related) return new_related(name, NULL);

  int name_cmp = strcmp(related->name, name);
  if (name_cmp > 0) return new_related(name, related); // Insert

  related->tail = add_related(related->tail, name); // Skip
  return related;
}

void social_add_related(socialADT soc, const char *name, const char *related) {
  person_node *person = find_person(soc->persons, name);
  if (!person) return;

  person->related = add_related(person->related, related);
}

char **social_get_related(const socialADT soc, const char *name) {
  char **names = NULL;
  size_t size = 0;

  person_node *person = find_person(soc->persons, name);
  if (person) {
    related_node *related = person->related;
    while (related) {
      if (size % BLOCK_SIZE == 0)
        names = realloc(names, (size + BLOCK_SIZE) * sizeof(char *));
      names[size++] = strdup(related->name);
      related = related->tail;
    }
  }

  names = realloc(names, (size + 1) * sizeof(char *));
  names[size] = NULL; // null terminator
  return names;
}

char **social_get_persons(const socialADT soc) {
  char **names = NULL;
  size_t size = 0;

  person_node *person = soc->persons;
  while (person) {
    if (size % BLOCK_SIZE == 0)
      names = realloc(names, (size + BLOCK_SIZE) * sizeof(char *));
    names[size++] = strdup(person->name);
    person = person->tail;
  }

  names = realloc(names, (size + 1) * sizeof(char *));
  names[size] = NULL; // null terminator
  return names;
}
