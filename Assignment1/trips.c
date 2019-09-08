/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Trips.c program: reads lines from dict1 and dict2 and writes 
 * out to files
 * Assignment 1 : Information Retrieval using Binary Search 
 *                Trees
 * Subject Code : COMP20003 
 * Subject Name : Algorithms and Data Structures
 * Written by : Syed Ahammad Newaz Saif 
 * Student ID : 684933 
 * Email Address : snewaz@student.unimelb.edu.au
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "trips.h"

/* * * FUNCTIONS * * */


/* Take an array of the line from stdin and parse the 
   data into each files of trips data */
Trips *lineParsing(char line[]){
    
    // create a new trip record to store relevant data to it. 
    Trips *data = malloc(sizeof(Trips));
    assert(data);
    char* buffer;
    
    // allocate exact memory needed for the fields 
    // using a buffer and the copy the string
    // commas separate field here
    buffer  = strtok(line,DELIMITER); 
    data -> VendorID  = malloc(strlen(buffer)+1);
    strcpy(data -> VendorID, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> passenger_count  = malloc(strlen(buffer)+1);
    strcpy(data -> passenger_count, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> trip_distance  = malloc(strlen(buffer)+1);
    strcpy(data -> trip_distance, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> RatecodeID = malloc(strlen(buffer)+1);
    strcpy(data -> RatecodeID, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> store_and_fwd_flag  = malloc(strlen(buffer)+1);
    strcpy(data -> store_and_fwd_flag, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> PULocationID  = malloc(strlen(buffer)+1);
    strcpy(data -> PULocationID, buffer);

    buffer  = strtok(NULL,DELIMITER);
    data -> DOLocationID  = malloc(strlen(buffer)+1);
    strcpy(data -> DOLocationID, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> payment_type  = malloc(strlen(buffer)+1);
    strcpy(data -> payment_type, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> fare_amount  = malloc(strlen(buffer)+1);
    strcpy(data -> fare_amount, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> extra  = malloc(strlen(buffer)+1);
    strcpy(data -> extra, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> mta_tax  = malloc(strlen(buffer)+1);
    strcpy(data -> mta_tax, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> tip_amount  = malloc(strlen(buffer)+1);
    strcpy(data -> tip_amount, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> tolls_amount  = malloc(strlen(buffer)+1);
    strcpy(data -> tolls_amount, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> improvement_surcharge  = malloc(strlen(buffer)+1);
    strcpy(data -> improvement_surcharge, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> total_amount  = malloc(strlen(buffer)+1);
    strcpy(data -> total_amount, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> PUdatetime  = malloc(strlen(buffer)+1);
    strcpy(data -> PUdatetime, buffer);
    
    buffer  = strtok(NULL,DELIMITER);
    data -> DOdatetime  = malloc(strlen(buffer)+1);
    strcpy(data -> DOdatetime, buffer);
    
    // parse the data with newline to store it
    buffer  = strtok(NULL,NEWLINE);
    data -> trip_duration  = malloc(strlen(buffer)+1);
    strcpy(data -> trip_duration, buffer);

    return data;
}

/* Write out to the file */
void writeToFileStage1(const char *key, Trips *trips_record, FILE *NewOutputFile){
    static FILE *OutputFile = NULL;
    
    // write out to a static file if no field specificed(initially)
    if(trips_record != NULL){
            fprintf(OutputFile, "%s --> VendorID: %s || passenger_count: %s || "
                "trip_distance: %s || RatecodeID: %s || store_and_fwd_flag: %s ||"
                " PULocationID: %s || DOLocationID: %s || payment_type: %s ||"
                " fare_amount: %s || extra: %s || mta_tax: %s || tip_amount: %s || "
                "tolls_amount: %s || improvement_surcharge: %s || total_amount: %s || " 
                "DOdatetime: %s || trip_duration: %s ||\n", trips_record -> PUdatetime,
                trips_record -> VendorID, trips_record -> passenger_count, trips_record -> trip_distance, 
                trips_record -> RatecodeID, trips_record -> store_and_fwd_flag, trips_record -> PULocationID,
                trips_record -> DOLocationID, trips_record -> payment_type, trips_record -> fare_amount,
                trips_record -> extra, trips_record -> mta_tax,trips_record -> tip_amount, 
                trips_record -> tolls_amount, trips_record -> improvement_surcharge, trips_record -> total_amount, 
                trips_record -> DOdatetime, trips_record -> trip_duration);
        return;

    }
    // copy over the existing output file
    if(NewOutputFile){
        OutputFile = NewOutputFile; 
    }
}

/* Initially write up a file that is given */
void writeInitialStage1(FILE *OutputFile){
    writeToFileStage1(NULL, NULL, OutputFile);
}

/* Write the records of the trips to the existing previous output file
   and set the NewOutputFile as NULL */
void writeTripsStage1(const char* key, Trips *trips_record){
    writeToFileStage1(key, trips_record, NULL);
}

/* Writes out and prints to screen if the key -> PUdatetime is not found */
void writeNotFound(const char *PUdatetime, FILE* OutputFile){
    fprintf(OutputFile, "%s --> NOTFOUND\n", PUdatetime);
}

