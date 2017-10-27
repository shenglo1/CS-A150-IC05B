#ifndef FLIPLINES_H
#define FLIPLINES_H

#include <string>
/**
    flipLines accepts the name of a file as its parameter.
    The function opens and writes to the console the 
    same file's contents with successive pairs of lines 
    reversed in order. If the file cannot be opened, then
    "Cannot open filename.txt" is printed to cerr, 
    with filename.txt replaced with the actual name.
    
    @param fname the name of the file to open and read from
*/
void flipLines(const std::string& fname);

#endif

