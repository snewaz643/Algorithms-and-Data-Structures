/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * bstllist.c program : This program has a set of programs for 
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

#include "bstllist.h"

/* * * FUNCTIONS * * */

/* Make a  dictionary in the binary search tree structure but here returning NULL */
Bstree *makedict(void){
    return NULL;
}

/* Simple insertion of data into a linked list */
void insertList(List *list, List *data){
    while (list->next){
        list = list->next;
    }
    list->next = data;
}

/* Compare the PUdatetime in the first linked list of a bst with the PUdatetime of 
   another linked list */
int compareBst(const Bstree *a, const List *linkedList){
    return strcmp(a->dataList->data->PUdatetime, linkedList->data->PUdatetime);
}

/* Compare the PUdatetime in the first linked list of a bst with another PUdatetime */
int compareNodeData(const Bstree *a, const char *key, int *comparisonCount){
    ++(*comparisonCount);
    return strcmp(a->dataList->data->PUdatetime, key);
}

/* Compare the PULocationID in the first linked list of a bst with another PULocationID */
int compareNodeData2(const Bstree *a, const char *PUlocationID){
    return strcmp(a->dataList->data->PULocationID, PUlocationID);
}


/* Given a binary tree, print its nodes in inorder */
void printInorder(Bstree* bstree, const char* PUlocationID, FILE *NewOutputFile) {
     if (bstree == NULL) {
          return; 
     }
     // first recurse on left child 
     printInorder(bstree->left, PUlocationID, NewOutputFile);
     // made a test to see if the left side was empty or not 
     // assert(bstree->left);
  
     //then print the data of node 
     if(compareNodeData2(bstree, PUlocationID) == 0){ 
         fprintf(NewOutputFile,"%s --> %s\n", PUlocationID, bstree -> dataList -> data -> PUdatetime);
     }
     // now recurse on right child 
     printInorder(bstree -> right, PUlocationID, NewOutputFile);
}


/* Recursively insert struct into tree */
Bstree *recursiveInsert(Bstree *current, List *dataList){
    // found NULL, record as the head of linked list
    if (current == NULL){
        // allocate memory and then set data and pointers
        current = calloc(1, sizeof(Bstree));
        assert(current);
        current->dataList = dataList;
        current->left = NULL;
        current->right = NULL;
    }else{
        // recursively compare till NULL or data with same name found
        int comparison = compareBst(current, dataList);
        if (comparison > 0){
            current->left = recursiveInsert(current->left, dataList);
        }
        else if (comparison < 0){
            current->right = recursiveInsert(current->right, dataList);
        }
        // there are some data with the same name, insert into linked list
        else {
            insertList(current->dataList, dataList);
        }
    }
    return current;
}

/* A parent binary tree is taken and the child is inserted at the correct place 
  return an item in a new tree with left/right pointers pointing to NULL. */
Bstree *insert(Bstree *parent, Trips *data){
    // create the struct for the data
    List *dataList = malloc(sizeof(List));
    assert(dataList);
    // add the linked list at the front connecting memory addresses
    dataList->data = data;
    dataList-> next = NULL;
    return recursiveInsert(parent, dataList);
}

/* Returns the pointer to the linked list of the first occurence of the key 
   updating comparisonCount */
List *search(const Bstree *parent, const char *key,int *comparisonCount){
    if (!parent){
        return NULL;
    }
    else{
        int comparison = compareNodeData(parent, key, comparisonCount);
        if (comparison > 0){
            return search(parent->left, key, comparisonCount);
        }
        else if (comparison < 0){
            return search(parent->right, key, comparisonCount);
        }
        else{
            return parent->dataList;
        }
    }
}

/* Returns the pointer to the linked list of the first occurence of the key */
List *search2(const Bstree *parent, const char *key){
    if (!parent){
        return NULL;
    }
    else{
        int comparison = compareNodeData2(parent, key);
        if (comparison > 0){
            return search2(parent->left, key);
        }
        else if (comparison < 0){
            return search2(parent->right, key);
        }
        else{
            return parent->dataList;
        }
    }
}

/* Traverses the list and performs action with the key */
void traverseListWithAction(const char *key, const List *list,
                            void action(const char *key, Trips *data)){
    if (!list){
        return;
    }
    else{
        action(key, list->data);
        traverseListWithAction(key, list->next, action);
    }
}

/* Frees a whole linked list and its containing data */
void freeList(List *list){
    if (!list){
        return;
    }else{
        // remove the next pointer then all the fields 
        // that are pointers occupying before free struct with its data
        // and finally the list
        freeList(list->next);
        free(list->data-> VendorID);
        free(list->data->passenger_count);
        free(list->data->trip_distance);
        free(list->data->RatecodeID);
        free(list->data->store_and_fwd_flag);
        free(list->data->PULocationID);
        free(list->data->DOLocationID);
        free(list->data->payment_type);
        free(list->data->fare_amount);
        free(list->data->extra);
        free(list->data->mta_tax);
        free(list->data->tip_amount);
        free(list->data->tolls_amount);
        free(list->data->improvement_surcharge);
        free(list->data->total_amount);
        free(list->data->PUdatetime);
        free(list->data->DOdatetime);
        free(list->data->trip_duration);
        free(list->data);
        free(list);
    }
}

/* Frees an entire tree */
void freeTree(Bstree *parent){
    if(!parent){
        return;
    }
    else{
        freeTree(parent->left);
        freeTree(parent->right);
        freeList(parent->dataList);
        free(parent);
    }
}