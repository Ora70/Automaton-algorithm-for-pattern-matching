#include "Test.h"

void testTexts() {
    vector<size_t> text1 = {1, 2, 3, 1, 3};
    vector<size_t> pattern1 = {1, 2, 3, 2};
    vector<size_t> matches1 = {1};
    vector<size_t> pattern2 = {3, 1, 3};
    vector<size_t> matches2 = {2};
    cout<<"test 1:"<<endl;
    test(true, text1, pattern1, matches1, 4);
    cout<<"test 2:"<<endl;
    test(false, text1, pattern2, matches2, 4);
    vector<size_t> text3 = {3,4,5,4,5,4,3,4,3};
    vector<size_t> pattern3 = {1,2,1};
    vector<size_t> matches3 = {1,2,3,5,6};
    cout<<"test 3:"<<endl;
    test(true, text3, pattern3, matches3, 7);
}

void test(bool isParameterized,  vector<size_t> text,  vector<size_t> pattern,  vector<size_t> matches, size_t size_ab) {
    vector<size_t> matchesNaive;
    matchesNaive.reserve(text.size());
    if (isParameterized) {
        naive<true>(matchesNaive, text.data(), text.size(), pattern.data(), pattern.size(), size_ab);
    } else {
        naive<false>(matchesNaive, text.data(), text.size(), pattern.data(), pattern.size(), size_ab);
    }

    vector<size_t> matchesAlgorithm;
    matchesAlgorithm.reserve(text.size());
    if (isParameterized) {
        Algorithm<true> *algorithm = new Algorithm<true>(text.data(), text.size(), pattern.data(), pattern.size(), size_ab);
        algorithm->runAlgorithm(matchesAlgorithm);
    } else {
        Algorithm<false> *algorithm = new Algorithm<false>(text.data(), text.size(), pattern.data(), pattern.size(), size_ab);
        algorithm->runAlgorithm(matchesAlgorithm);
    }

    if (matchesAlgorithm == matches && matchesNaive == matches) {
        cout << "test passed" << endl;
    } else {
        cout << "failed" << endl;
        printResults(matchesNaive, matchesAlgorithm, matches);
    }
}

void printResults(vector<size_t> resultNaive, vector<size_t> resultAlgo, vector<size_t> trueResult) {
    cout<<"algorithm:"<<endl;
    for (auto i : resultAlgo) {
        cout<<i<<",";
    }
    cout<<endl;
    cout<<"naive"<<endl;
    for (auto j : resultNaive) {
        cout<<j<<",";
    }
    cout<<endl;
    cout<<"expected"<<endl;
    for (auto j : trueResult) {
        cout<<j<<",";
    }
    cout<<endl<<endl;
}

