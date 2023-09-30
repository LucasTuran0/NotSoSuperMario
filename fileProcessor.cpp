
#include "fileProcessor.h"
#include <iostream>

fileProcessor::fileProcessor() {        //default constructor
    outFile.open("output.txt", ios::out);
    if(!outFile.is_open()) {
        cerr << "Unable to open output file" << endl;
    }
}

fileProcessor::~fileProcessor() {       //overloaded constructor
    if(outFile.is_open()){
        outFile << "fileProcessor has been deallocated" << endl;
        outFile.close();
    }
}

void fileProcessor::write(string content) {
    if(outFile.is_open()){
        outFile << content << endl;
    }
}

void fileProcessor::fileOut() {     //this redirects all cout statements into an output.txt file
    streambuf *coutbuf = cout.rdbuf(); 
    cout.rdbuf(outFile.rdbuf());
}
