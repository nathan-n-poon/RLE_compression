#include <string>
#include "io.h"
#include "rle.h"
#include <iostream>
using namespace std;

enum state { reset, readRaw, decompressed };



int main() {
    state s = reset;

    int uncompressedSize;
    int compressedSize;
    int decompressedSize;
    string uncompressedPath = "", compressedPath = "", decompressedPath = "";
    int8_t * uncompressedBuffer;
    int8_t * compressedBuffer;
    int8_t * decompressedBuffer;
    int8_t * temp;
    std::cout << "Start by creating a text file with the uncompressed array in it. Each byte should be separated by a single comma.\n" 
    "ie: 1,1,1,2,3,4,51,2,12,114,12,21,21,21,8\n"
    "Then supply the path to your text file using option 1. ie: C:\\Users\\nathan\\CLionProjects\\RLE_compression\\data.txt\n"
    "Also assign the paths to where the compressed array should be written to as well as the decompressed array\n"
    "Then compress the array with option 4. This will write the compressed array into the compressed file path.\n"
    "To decompress the array, slect option 5, which will write the decompressed array into the decompressed file path\n"
    "to verify the uncompressed and decompressed arrays are equal choose option 6. It will also tell you how many bytes are saved\n"
    "-------------------------------------------------------------------------------------------------------------------------------\n\n\n";
    while(1) {
        int menuChoice;
        cout << "[1] set uncompressed file path \n[2] set compressed file path \n[3] set decompressed file path \n"
                "[4] compress the raw data \n[5] decompress the compressed data \n[6] compression stats \n[7] quit \n";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                cout << "please enter the path to the uncompressed data file, as an absolute path: \n";
                cin >> uncompressedPath;
                break;
            case 2:
                cout << "please enter the path to the compressed data file, as an absolute path: \n";
                cin >> compressedPath;
                break;
            case 3:
                cout << "please enter the path to the decompressed data file, as an absolute path: \n";
                cin >> decompressedPath;
                break;
            case 4:
                if(uncompressedPath == "" || compressedPath == "") {
                    cout << "uncompressedPath or compressedPath is not set\n";
                    break;
                }
                cout << "reading data from uncompressed, and writing compressed version into compressed file path\n";
                temp = readRawData(uncompressedPath, ',', &uncompressedSize);
                uncompressedBuffer = new int8_t[uncompressedSize];
                for(int i = 0; i < uncompressedSize; i++) {
                    uncompressedBuffer[i] = temp[i];
                }
                compressedSize = compress(temp, uncompressedSize);
                compressedBuffer = temp;
                if(! writeData(compressedPath, ',', compressedSize, compressedBuffer)) {
                    cout <<"error writing compressed data to file \n";
                }
                break;
            case 5:
                cout << "decompressing data and writing into decompressed file path\n";
                compressedBuffer = readRawData(compressedPath, ',', &compressedSize);
                decompressedSize = decompress(compressedBuffer, compressedSize, decompressedBuffer);
                if(! writeData(decompressedPath, ',', decompressedSize, decompressedBuffer)) {
                    cout <<"error writing decompressed data to file \n";
                }
                break;
            case 6:
                if(uncompressedSize != decompressedSize) {
                    cout << "error in compression or decompression! \n";
                    return 0;
                }
                for(int i = 0; i < uncompressedSize; i++ ) {
                    if(uncompressedBuffer[i] != decompressedBuffer[i]) {
                        cout << "error in compression or decompression! \n";
                        return 0;
                    }
                }
                cout << "the compression ratio is: " << (float) ((float)compressedSize / (float)uncompressedSize) << endl;
                cout << "the difference in size is: " << uncompressedSize - compressedSize << endl;
                break;
            case 7:
                return 0;
            default:
                cout << "invalid choice \n";
                break;
        }

    }
    return 0;

//    int * data = readRawData(path, ',', size);
//    for(int i = 0; i < *size; i++) {
//        int datum = data[i];
//        cout << (int)datum << endl;
//    }
//
//    if(writeData("compress.txt", ',', *size, data));
//    return 0;
}
