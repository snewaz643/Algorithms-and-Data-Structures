/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * bstllist.h program : This header file has a set of programs for 
 * creating, inserting and searching binary search trees with 
 * linked list structure and free memory after use.
 * Assignment 1 : Information Retrieval using Binary Search 
 *                Trees
 * Subject Code : COMP20003 
 * Subject Name : Algorithms and Data Structures
 * Written by : Syed Ahammad Newaz Saif 
 * Student ID : 684933 
 * Email Address : snewaz@student.unimelb.edu.au
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BSTLLIST_H
#define BSTLLIST_H
#include "trips.h"

/* * * HASH DEFINES * * */

#define LINE_LENGTH 18

/* * * STRUCTURES * * */

typedef struct list List;
typedef struct bstree Bstree;

struct list {
    Trips *data;
    List *next;
};

struct bstree{
    List *dataList;
    Bstree *left;
    Bstree *right;
};

/* * * FUNCTION DEFINITIONS * * */

/* Make a  dictionary in the binary search tree structure but here returning NULL. */
Bstree *makedict(void);

/* Simple insertion of data into a linked list */
void insertList(List *list, List *data);

/* Compare the PUdatetime in the first linked list of a bst with the PUdatetime of 
   another linked list */
int compareBst(const Bstree *a, const List *linkedList);

/* Compares the PUdatetime in the first linked list of a bst with another PUdatetime */
int compareNodeData(const Bstree *a, const char *key, int *comparisonCount);

int compareNodeData2(const Bstree *a, const char *PUlocationID);

/* Given a binary tree, print its nodes in inorder */
void printInorder(Bstree* bstree, const char *PUlocationID, FILE *NewOutputFile);

/* Recursively insert struct into tree */
Bstree *recursiveInsert(Bstree *current, List *dataList);

/* A parent binary tree is taken and the child is inserted at the correct place 
  return an item in a new tree with left/right pointers pointing to NULL. */
Bstree *insert(Bstree *parent, Trips *data);

/* Returns the pointer to the linked list of the first occurence of the key 
   updating comparisonCount*/
List *search(const Bstree *parent, const char *key,int *comparisonCount);

/* Returns the pointer to the linked list of the first occurence of the key */
List *search2(const Bstree *parent, const char *key);

/* Traverses the list and performs action with the key */
void traverseListWithAction(const char *key, const List *list,
                            void action(const char *key, Trips *data));

/* Frees a whole linked list and its containing data */
void freeList(List *list);

/* Frees an entire tree */
void freeTree(Bstree *parent);

#endif
