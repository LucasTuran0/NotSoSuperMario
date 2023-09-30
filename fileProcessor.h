

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <fstream>
#include <string>
using namespace std;

class fileProcessor{
public:
    fileProcessor();
    virtual ~fileProcessor();
    void write(string content);
    void fileOut();

private:
    ofstream outFile;
};

#endif