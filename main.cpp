#include <iostream>
#include <vector>
#include <string>
#include "Algorithm.h"
#include "Naive.h"
#include "ReadFile.h"
#include "Test.h"
#include <chrono>
#include <filesystem>
#include "GetData.h"

namespace fs = std::filesystem;
using namespace std;
using namespace std::chrono;

void testAlgorithm(struct Data data);
void updateDataInFiles(struct Data data, microseconds durationNaive, microseconds durationAlgorithm,
                       vector<size_t> matches);
void copyPosP_matchToFile(const vector<size_t>& matches, string fileName, bool isParameterized);
void analysisFileColumnNames(char* fileName);

int main(int argc, char** argv) {
    vector<struct Data> dataList = GetListToTest(argv[1]);
    for (auto data : dataList) {
        testAlgorithm(data);
    }

    return 0;
}

void testAlgorithm(struct Data data) {
    vector<size_t> matchesNaive;
    matchesNaive.reserve(data.text.size());
    auto start = high_resolution_clock::now(); // Get starting timepoint
    if (data.isParameterized) {
        naive<true>(matchesNaive, data.text.data(), data.text.size(), data.pattern.data(), data.pattern.size(),
                    data.size_ab);
    } else {
        naive<false>(matchesNaive, data.text.data(), data.text.size(), data.pattern.data(), data.pattern.size(),
                     data.size_ab);
    }
    auto stop = high_resolution_clock::now(); // Get ending timepoint
    auto durationNaive = duration_cast<microseconds>(stop - start);

    //algorithm
    vector<size_t> matchesAlgorithm;
    matchesAlgorithm.reserve(data.text.size());
    start = high_resolution_clock::now(); // Get starting timepoint
    if (data.isParameterized) {
        Algorithm<true> *algorithm = new Algorithm<true>(data.text.data(), data.text.size(), data.pattern.data(),
                                                         data.pattern.size(), data.size_ab);
        algorithm->runAlgorithm(matchesAlgorithm);
    } else {
        Algorithm<false> *algorithm = new Algorithm<false>(data.text.data(), data.text.size(), data.pattern.data(),
                                                           data.pattern.size(), data.size_ab);
        algorithm->runAlgorithm(matchesAlgorithm);
    }
    stop = high_resolution_clock::now(); // Get ending timepoint
    auto durationAlgorithm = duration_cast<microseconds>(stop - start);

    updateDataInFiles(data, durationNaive, durationAlgorithm, matchesAlgorithm);
}

void updateDataInFiles(struct Data data, microseconds durationNaive, microseconds durationAlgorithm,
        vector<size_t> matches) {
    //time of each algorithm
    auto naiveTime = durationNaive.count();
    auto algoTime = durationAlgorithm.count();

    fstream fout;
    if (data.isParameterized) {
        analysisFileColumnNames("analysisParameterized.csv");
        fout.open("analysisParameterized.csv", ios::out | ios::app);
    } else {
        analysisFileColumnNames("analysisExact.csv");
        fout.open("analysisExact.csv", ios::out | ios::app);
    }
    //add info to the file

    //columns:Name of text file, Name of pattern file, Length of text, Length of pattern, Size of alphabet,
    //      Time taken by naive, Time taken by algorithm, How much faster is the algorithm, Number of matches,
    fout <<data.textName+"," <<data.patternName+"," << data.text.size() << "," << data.pattern.size() << "," <<
    data.size_ab << "," << naiveTime << ","
         << algoTime << "," << (static_cast<float>(naiveTime) / algoTime) << "," << matches.size() << "," << "\n";
    fout.close();

    string matchPosFileName = "TextLen" + to_string(data.text.size()) + "PatternLen"+ to_string(data.pattern.size())
            + "ab" + to_string(data.size_ab) + ".txt";
    copyPosP_matchToFile(matches, matchPosFileName, data.isParameterized);
}

/*
 * add the positions of the matches to a file
 */
void copyPosP_matchToFile(const vector<size_t>& matches, string fileName, bool isParameterized) {
    const char* dir;
    if (isParameterized) {
        dir = "matchPositionsParameterized";
    } else {
        dir = "matchPositionsNaive";
    }
    struct stat sb;
    if (stat(dir, &sb) != 0) { //directory does not exist. need to create it
        namespace fs = std::filesystem;
        fs::create_directories(dir);
    }
    //write match positions to file
    ofstream myfile;
    myfile.open(string (dir) + "/" + fileName);
    for (auto v : matches) {
        myfile<<v<<" ";
    }
    myfile.close();
}

/*
 * create analysis file with names to the columns
 */
void analysisFileColumnNames(char* fileName) {
    struct stat sb;
    if (stat(fileName, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        return; //file already exists. No need to add column names

    fstream fout;
    fout.open(fileName, ios::out | ios::app);
    fout<<"Name of text file,"<<"Name of pattern file,"<<"Length of text,"<<"Length of pattern,"<<"Size of alphabet,"
        <<"Time taken by naive,"<<"Time taken by algorithm,"<<"How much faster is the algorithm,"<<"Number of matches\n";
    fout.close();
}