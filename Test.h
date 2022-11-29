#ifndef KMP_TEST_H
#define KMP_TEST_H

#include <iostream>
#include <vector>
#include "Algorithm.h"
#include "Naive.h"
using namespace std;

void test(bool isParameterized,  vector<size_t> text,  vector<size_t> pattern,  vector<size_t> matches, size_t size_ab);
void testTexts();
void printResults(vector<size_t> resultNaive, vector<size_t> resultAlgo, vector<size_t> trueResult);

#endif //KMP_TEST_H
