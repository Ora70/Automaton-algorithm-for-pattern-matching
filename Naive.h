#ifndef KMP_NAIVE_H
#define KMP_NAIVE_H

#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

static bool naiveCompare(size_t *p_match, size_t *t_match, size_t p, size_t t, int size_ab) {
    if (p_match[p] == size_ab+1 && t_match[t] == size_ab+1) {
        p_match[p] = t;
        t_match[t] = p;
        return true;
    } else if (p_match[p] == t) {
        return true;
    } return false;
}

template<bool parameterized>
static void naive(vector <size_t> &matches, size_t *text, size_t len_t, size_t *pattern, size_t len_p, int size_ab) {
        //create arrays to match letters in text and pattern. need 2 to make sure different letters do not get the same match
        //only used in paramerterized
        std::vector<size_t> p_match(size_ab), t_match(size_ab);

    //for every position in the text find p-match
    for (size_t i = 0; i <= len_t-len_p; i++) {
        if constexpr(parameterized) {
            //create arrays to match letters in text and pattern. need 2 to make sure different letters do not get the same match
            t_match.assign(size_ab, size_ab+1);
            p_match.assign(size_ab, size_ab+1);
        }
        bool match = true;
        //check for each letter if is matched
        for (size_t j = 0; j < len_p; j++) {
            bool equal;
            if constexpr(parameterized) {
                equal = (naiveCompare(p_match.data(), t_match.data(), pattern[j], text[i + j], size_ab) == false);
            } else {
                equal = (pattern[j] != text[i + j]);
            }
            if (equal) {
                match = false;
                break;
            }
        }
        if (match) { //add position to list of matches
            matches.push_back(i);
        }
    }
}

#endif //KMP_NAIVE_H
