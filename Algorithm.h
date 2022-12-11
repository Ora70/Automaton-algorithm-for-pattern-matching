#ifndef KMP_ALGORITHM_H
#define KMP_ALGORITHM_H

#include <list>
#include <iostream>
#include <vector>
using namespace std;

template <bool parameterized>
class Algorithm {
    size_t *text;
    size_t *pattern;
    size_t len_t;
    size_t len_p;
    vector<size_t> a;
    vector<size_t> automat;
    vector<size_t> lastSeenT;
    void createA(int size_ab);
    void createAutomat();
    bool compareAutomat(size_t j , size_t i);
    bool compareAlgorithm(size_t j , size_t i);

public:
    Algorithm(size_t *text, size_t len_t, size_t *pattern, size_t len_p, size_t size_ab);
    void runAlgorithm(vector<size_t> &matches);
};

template <bool parameterized> Algorithm<parameterized>::Algorithm(size_t *text, size_t len_t, size_t *pattern, size_t len_p, size_t size_ab) {
    this->pattern = pattern;
    this->text = text;
    this->len_p = len_p;
    this->len_t = len_t;
    if constexpr(parameterized) {
        this->createA(size_ab);
    }
    this->createAutomat();
    if constexpr(parameterized) {
        //initialize array of letters that will hold the last position in the text where each letter was seen during scan
        // of the text. At first len_t+1 because no letter was seen yet.
        this->lastSeenT.resize(size_ab);
        for (int i = 0; i < size_ab; i++) {
            lastSeenT[i] = len_t + 1;
        }
    }
}

/*
  * A in size len_p holds for each position i the biggest K<=i that the letter was in the pattern
  * Only used for parameterized algorithm
  */
template <bool parameterized> void Algorithm<parameterized>::createA(int size_ab) {
    this->a.resize(len_p);
    auto *lastSeen = new size_t[size_ab]; //to remember the last position a letter was in
    for (int i = 0; i < size_ab; i++) { //initialize last time all letters where seen to len_p+1. meaning no letter was seen
        lastSeen[i] = len_p+1;
    }
    for (size_t j = 0; j < len_p; j++) {
        size_t letter = pattern[j];
        if (lastSeen[letter] == len_p+1) { //first time the letter is seen
            a[j] = j;
        } else {
            a[j] = lastSeen[letter];
        }
        lastSeen[letter] = j; //update the last time so far the letter was seen to be j
    }
    delete[] lastSeen;
}

template <bool parameterized> void Algorithm<parameterized>::createAutomat() {
    this->automat.resize(len_p + 1);
    //fail arrow points to 0 in first
    automat[0] = automat[1] = 0;
    for (size_t i = 2; i < len_p + 1; i++) {
        size_t j = i - 1;
        while (true) {
            bool equal;
            if constexpr(parameterized) {
                equal = compareAutomat(automat[j], i - 1);
            } else {
                equal = (pattern[automat[j]] == pattern[i - 1]);
            }
            if (equal) {
                automat[i] = automat[j] + 1;
                break;
            } else {
                //reached the beginning of automat. fail arrow points to 0
                if (automat[j] == 0) {
                    automat[i] = 0;
                    break;
                } else {
                    j = automat[j];
                }
            }
        }
    }
}

template <bool parameterized> void Algorithm<parameterized>::runAlgorithm(vector<size_t> &matches) {
    size_t j = 0, i = 0; //j position in automat. i position in text
    while (i <len_t) {
        bool equal;
        if constexpr(parameterized) {
            equal = compareAlgorithm(i, j);
        } else {
            equal = (text[i] == pattern[j]);
        }
        if (equal) {
            if constexpr(parameterized) {
                lastSeenT[text[i]] = i; //update the last position that the letter text[i] was seen to be i
            }
            j++;
            i++;
            if (j == len_p) { //reached the end of automat - found a match
                j = automat[j];
                matches.push_back(i - len_p);
            }
        } else { //no match. fail arrow in automat
            if (j == 0) { //if j == 0 than always i moves forward
                if constexpr(parameterized) {
                    lastSeenT[text[i]] = i; //update the last position that the letter text[i] was seen to be i
                }
                i++;
            }
            j = automat[j];
        }
    }
}

/*
 * Only used for parameterized algorithm
 */
template <bool parameterized> bool Algorithm<parameterized>::compareAutomat(size_t j, size_t i) {
    if (a[i] == i || i - a[i] > j) { //new letter
        if (a[j] == j) { //also a new letter
            return true;
        } else { //for j not a new letter
            return false;
        }
    } else if ((i - a[i] <= j) && pattern[j] == pattern[j-i+a[i]]) { //old letter for both. same distance
        return true;
    }
    else {
        return false;
    }
}

/*
 * Only used for parameterized algorithm
 */
template <bool parameterized> bool Algorithm<parameterized>::compareAlgorithm(size_t j, size_t i) { // j in text. i in pattern
    //first time the letter was seen in pattern
    if (a[i] == i && (lastSeenT[text[j]] == len_t + 1 || lastSeenT[text[j]] < j - i)) {
        return true;
        //not the first time the letter was seen in the pattern
    } else if (a[i] != i && text[j] == text[j-i+a[i]]) {
        return true;
    } else {
        return false;
    }
}


#endif //KMP_ALGORITHM_H
