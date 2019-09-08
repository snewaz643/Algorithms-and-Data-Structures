/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * dict1.c program: Main file of the Stage 1 
 * out to files
 * Usage: ./dict1 [input file] [output file]
 * input file: Trips by taxi and limousine delimited by comma(csv)
 * output file: search result
 * stdin: search keys one per line
 * stdout: keys mapping number of key comparisons
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

/* * * MAIN PILOT PROGRAM  FOR STAGE 1 * * */

int main(int argc, const char *argv[]) {
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
    char key[MAX_STRING_SIZE + 1] = {'\0'};
    List *list = NULL;
    
    // read and insert data into bst
    while (fgets(line, LINE_MAX, fileIn)){
        trips_record = lineParsing(line);
        bst = insert(bst, trips_record);
    }
    
    // initial specify the file to write out to
    writeInitialStage1(fileOut);
    
    // Read from the stdin the keys from the key file and search it,
    // writing all the matched trips data to the output file if any 
    // key is found, otherwise print out that the key was not found.
    // The number of key comparisons amout corresponding to the keyfiles 
    // put to stdout
    while(fgets(key, MAX_STRING_SIZE, stdin)){
        // remove newline char at the end
        strtok(key, "\n");
        comparisonCount = 0;
        // search for the key
        list = search(bst, key, &comparisonCount);
        if (list){
            // write out the trips record corresponding to the key
            traverseListWithAction(key, list, writeTripsStage1);
        }
        else{
            writeNotFound(key, fileOut);
        }
        printf("%s --> %d\n", key, comparisonCount);
    }
    
    // free all the pointers
    freeTree(bst);
    fclose(fileIn);
    fclose(fileOut);
    
    return 0;
}