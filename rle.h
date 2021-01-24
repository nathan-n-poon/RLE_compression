//
// Created by nathan on 2021-01-23.
//
using namespace std;
#include <iostream>

#ifndef UNTITLED3_RLE_H
#define UNTITLED3_RLE_H

void insert(int & trendCount, int8_t source[], int & insertPos, int8_t & trend, int8_t & insertion);
int compress(int8_t *data_ptr, int data_size);
int decompress(int8_t * data_ptr, int size, int8_t *& sink);

#endif //UNTITLED3_RLE_H
