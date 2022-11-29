#ifndef KMP_READFILE_H
#define KMP_READFILE_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/*
 * read DNA file and create a vector of numbers
 */
vector<unsigned int> readDNA(const string& filename);
/*
 * read a file with unsigned numbers with a space separation the numbers and create a vector
 */
vector<unsigned int> readNumberFile(const string& filename);

#endif //KMP_READFILE_H
