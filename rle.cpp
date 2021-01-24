//
// Created by nathan on 2021-01-23.
//
#include "rle.h"

//helper function for inserting a run into the original array
//arguments:
//  trendCount: the length of a run of the same number. will be reset by this function
//  source: the array in which we are inserting the compressed run
//  insertPos: where in the array we should begin inserting the run. will be altered by the function to be after the newly inserted run
//  trend: the value of a run
//  insertion: value to be inserted if we are not on a run
void insert(int & trendCount, int8_t source[], int & insertPos, int8_t & trend, int8_t & insertion)
{
    //if a run was ended, insert length of run, dented by negative sign, followed by the value in the run
    if(trendCount > 1)
    {
        while(trendCount > 127) // deal with the case where there exist more than 127 contiguous copies of the same value
        {
            source[insertPos] = -1 * 127; // decrement by 127 at a time
            trendCount -= 127;
            insertPos += 1;
        }
        source[insertPos] = -1 * trendCount; // insert remaining length of run as negative number
        source[insertPos + 1] = trend; //now insert the actual repeated value
        trendCount = 1;
        insertPos += 2; // increment insertion position for the length and the value
    }
    else  //otherwise, if  we are not currently on a run, insert the last seen element
    {
        source[insertPos] = insertion;
        trendCount = 1;
        insertPos ++;
    }
}

//rle compression algorithm
//arguments:
//  data_ptr: pointer to bytes
//  data_size: size of array
//returns:
//  int: length of new array
int compress(int8_t *data_ptr, int data_size)
{
    int trendCount = 0;       //length of a run of the same value
    int insertPos = 0;        //where to insert compressed data
    int8_t trend = data_ptr[0];   //the repeated value in a run

    for(int i = 0; i < data_size; i++)
    {
        if(data_ptr[i] == trend) //if we are encountering a run of the same value
        {
            trendCount ++;
        }

        if (data_ptr[i] != trend) //if a run has ended, by different value
        {
            insert(trendCount, data_ptr, insertPos, trend, trend);
        }
        if ( i == data_size - 1) //if we reached the end of the array
        {
            insert(trendCount, data_ptr, insertPos, trend, data_ptr[i]);
        }
        trend = data_ptr[i];  //update trend
    }

    return insertPos;
}

//decompresses my compressed array
//arguments:
//  data_ptr: the compressed array
//  size: the length of the compressed array
//  sink: where to decompress into (not in place compression)
//returns:
//  int: size of decompressed array
int decompress(int8_t * data_ptr, int size, int8_t *& sink)
{
    int insertPos = 0;
    int origSize = 0;

    //determine size of original array, by adding all the lengths together
    //needed to allocate enough space for decompressed array
    for(int i = 0; i < size; i++) {
        if(data_ptr[i] >= 0) {
            origSize++;
        }
        else {
            while(data_ptr[i] < 0) {
                origSize += -1 * data_ptr[i];
                i++;
            }
        }
    }
    sink = new int8_t[origSize];

    bool endOfLength = false;       //this indicates whether or not we have just finished retrieving the length of a run
    for(int i = 0; i < size; i++)
    {
        if(data_ptr[i] < 0) // if a length
        {
            endOfLength = true;
            int k = i;      //iterator to get actual value of run specified by length
            while (data_ptr[k] < 0)
            {
                k++;
            }
            for(int j = 0; j < data_ptr[i] * -1; j++) //fill in length number of value
            {
                sink[insertPos] = data_ptr[k];
                insertPos++;
            }
        }
        if(data_ptr[i] >= 0 && endOfLength)     //if we have reached the end of a run
        {
            endOfLength = false;
            continue;
        }
        if(data_ptr[i] >= 0)        //otherwise, if we encounter a solo value
        {
            sink[insertPos] = data_ptr[i];
            insertPos++;
            endOfLength = false;
        }
    }
    return origSize;
}

