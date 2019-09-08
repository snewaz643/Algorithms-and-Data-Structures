/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  
 * Trips.h program: header file that reads lines from dict1 and 
 * dict2 and writes out to files
 * Assignment 1 : Information Retrieval using Binary Search 
 *                Trees
 * Subject Code : COMP20003 
 * Subject Name : Algorithms and Data Structures
 * Written by : Syed Ahammad Newaz Saif 
 * Student ID : 684933 
 * Email Address : snewaz@student.unimelb.edu.au
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TRIPS_H
#define TRIPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* * * HASH DEFINES * * */

#define MAX_STRING_SIZE 128
#define MAX_RECORD_INPUT 256

#define DELIMITER ","
#define NEWLINE "\n"

/* * * STRUCTURES * * */

typedef struct trips Trips;

struct trips{
    char *VendorID;
    char *passenger_count;
    char *trip_distance;
    char *RatecodeID;
    char *store_and_fwd_flag;
    char *PULocationID;
    char *DOLocationID;
    char *payment_type;
    char *fare_amount;
    char *extra;
    char *mta_tax;
    char *tip_amount;
    char *tolls_amount;
    char *improvement_surcharge;
    char *total_amount;
    char *PUdatetime;
    char *DOdatetime;
    char *trip_duration;
};

/* * * FUNCTION DEFINITIONS * * */

/* Take an array of the line from stdin and parse the 
   data into each files of trips data */
Trips *lineParsing(char line[]);

/* Initially write up a file that is given */
void writeInitialStage1(FILE *OutputFile);

/* Write the records of the trips to the existing previous output file
   and set the NewOutputFile as NULL */
void writeTripsStage1(const char *key, Trips *trips_record);

/* Writes out and prints to screen if the key -> PUdatetime is not found */
void writeNotFound(const char *PUdatetime, FILE* OutputFile);

#endif
