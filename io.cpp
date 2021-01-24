//
// Created by nathan on 2021-01-23.
//
#include "io.h"

int8_t * readRawData(string fileName, char delimiter, int * sizeRet)
{
    int size = 0;

    ifstream infile;
    infile.open (fileName);

    if (infile.is_open())
    {
        string datum;
        while (getline(infile, datum, delimiter))
            size++;

        int8_t * rawData = new int8_t[size];

        infile.clear();
        infile.seekg(0, ios::beg);

        int i = 0;
        while (getline(infile, datum, delimiter)) {
            rawData[i] = stoi(datum, nullptr, 10);
            i++;
        }
        *sizeRet = size;

        infile.close();
        return rawData;
    }
    cout << "Error opening file";
    *sizeRet = -1;
    return NULL;
}

bool writeData(string filename, char delimiter, int size, int8_t * data) {
    ofstream ofile;
    ofile.open (filename);
    if (ofile.is_open()) {
        for(int i = 0; i < size; i++) {
            ofile << static_cast<int>(data[i]);
            if(i != size - 1) ofile << delimiter;
        }
        ofile.close();
        return true;
    }
    else {
        cout << "file cannot be opened for writing\n";
        return false;
    }
}

