#include "GetData.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include "ReadFile.h"
namespace fs = std::filesystem;

vector<vector<string>> getDataFromFile(const string& filePath) {
    vector<vector<string>> rows;
    fstream fin;

    fin.open(filePath, ios::in);

    while (fin) {
        rows.push_back(getNextLineAndSplitIntoTokens(fin));
        if (rows.back().size() < 4) {
            rows.pop_back();
        }
    }
    return rows;
}

vector<string> getNextLineAndSplitIntoTokens(fstream& fin) {
    vector<string> row;
    string line;
    getline(fin, line);

    stringstream s(line);
    string word;
    while (getline(s, word, ',')) {
        row.push_back(word);
    }
    return row;
}

struct Data createData(vector<string> tokens) {
    string textPath = tokens[0];
    string patternPath = tokens[1];
    fs::path pathToText = textPath;
    fs::path pathToPattern = patternPath;
    string textName = pathToText.filename().string();
    string patternName = pathToPattern.filename().string();
    vector<size_t> text = readNumberFile(textPath);
    vector<size_t> pattern = readNumberFile(patternPath);
    if (tokens.size() == 5) {
        pattern.resize(stoul(tokens[4]));
    }
    bool parameterized = false;
    if (tokens[3] == "1") {
        parameterized = true;
    }
    struct Data d = {text, pattern, textName, patternName, stoul(tokens[2]), parameterized};
    return d;
}

vector<struct Data> GetListToTest(const string& filePath) {
    vector<vector<string>> data = getDataFromFile(filePath);
    vector<struct Data> dataList;
    for (auto const line : data) {
        dataList.push_back(createData(line));
    }
    return dataList;
}