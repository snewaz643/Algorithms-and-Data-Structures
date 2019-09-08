/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * dict2.c program: Main file of the Stage 2 
 * Usage: ./dict1 [input file] [output file]
 * input file: Trips by taxi and limousine delimited by comma(csv)
 * output file: search result
 * stdin: search ids one per line
 * stdout: ids mapping number of key comparisons
 * Assignment 1 : Information Retrieval using Binary Search 
 *                Trees
 * Subject Code : COMP20003 
 * Subject Name : Algorithms and Data Structures
 * Written by : Syed Ahammad Newaz Saif 
 * Student ID : 684933 
 * Email Address : snewaz@student.unimelb.edu.au
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bstllist.h"
#include "trips.h"

/* * * HASH DEFINES * * */

#define LINE_MAX 256
#define MAX_ARGC 3

/* * * MAIN PILOT PROGRAM  FOR STAGE 2 * * */

int main(int argc, const char *argv[]){
    // get IO file names , print error if not present
    if (argc < MAX_ARGC){
        fprintf(stderr, "Warning, Usage: ./dict1 [input file] [output file]\n");
        exit(EXIT_FAILURE);
    }

    // open readin and readout files
    FILE *fileIn = fopen(argv[1], "r");
    FILE *fileOut = fopen(argv[2], "w");
    assert(fileIn);
    assert(fileOut);

    Bstree *bst = makedict();
    Trips *trips_record = NULL;
    char line[LINE_MAX + 1] = {'\0'};
    int comparisonCount = 0;
    char* PUlocationIDFile;
    char key[MAX_STRING_SIZE + 1] = {'\0'};

    // read and insert data into bst
    while (fgets(line, LINE_MAX, fileIn)){
        trips_record = lineParsing(line);
        bst = insert(bst, trips_record);
        comparisonCount++;
    }
    
    // Read from the stdin the ids from the ids file and search it.
    while(fgets(key, MAX_STRING_SIZE, stdin)){
        // remove newline char at the end
        PUlocationIDFile = strtok(key, "\n");
        search2(bst, key);
    }
    
    // An inorder traversal is then done printing out the number of 
    // key comparisons.
    printInorder(bst, PUlocationIDFile, fileOut);
    printf("%s --> %d\n", PUlocationIDFile, comparisonCount);
    
    // Free all pointers
    freeTree(bst);
    fclose(fileIn);
    fclose(fileOut);
    return 0;
}