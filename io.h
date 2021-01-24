//
// Created by natha on 2021-01-23.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#ifndef UNTITLED3_IO_H
#define UNTITLED3_IO_H



int8_t * readRawData(string fileName, char delimiter, int * sizeRet);
bool writeData(string filename, char delimiter, int size, int8_t * data);

#endif //UNTITLED3_IO_H
