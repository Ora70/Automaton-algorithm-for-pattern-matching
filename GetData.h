
#ifndef KMP_GETDATA_H
#define KMP_GETDATA_H

#include <vector>
#include <string>
using namespace std;

struct Data {
    vector<size_t> text;
    vector<size_t> pattern;
    const string textName;
    const string patternName;
    size_t size_ab;
    bool isParameterized;
};

vector<vector<string>> getDataFromFile(const string& filePath);
vector<string> getNextLineAndSplitIntoTokens(fstream& fin);
struct Data createData(vector<string> tokens);
vector<struct Data> GetListToTest(const string& filePath);

#endif //KMP_GETDATA_H
