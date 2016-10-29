/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* structures.h
* All functions that create/append/add/free/get/set structures.
***************************************************************/

#ifndef structuresHeader
#define structuresHeader

#include "defs.h"

typedef struct _node node;
typedef struct _list list;
typedef struct _element element;
typedef struct _vector vector;

node *create_node(item new_item, node *next_node);
item get_node_item(node *got_node);
node *get_next_node(node *got_node);
void free_node(node *got_node, void (*free_item)(item));

list *create_list();
node *get_head(list *got_list);
void set_head(list *got_list, node *got_head);
void push_item_to_list(list *got_list, item new_item);
size_t get_list_size(list *got_list);
void print_list(list *got_list, void (*print_item)(item));
void free_list(list *got_list, void (*free_item)(item));

#endif
