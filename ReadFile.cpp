#include "ReadFile.h"

vector<unsigned int> readNumberFile(const string& filename) {
    vector<unsigned int> arr;
    fstream file;
    string word, t, q;
    file.open(filename.c_str());

    // extracting numbers from the file
    while (file >> word)
    {
        unsigned num = stoul(word);
        arr.push_back(num);
    }
    return arr;
}

vector<unsigned int> readDNA(const string& filename) {
    vector<unsigned int> arr;
    // Create a text string, which is used to output the text file
    string temp;
    // Read from the text file
    ifstream myfile(filename);
    char letter;
    if (myfile.is_open()) {
        while (!myfile.eof()) {
            myfile >> letter;
            switch (letter) {
                case 'A':
                case 'a':
                    arr.push_back(0);
                    break;
                case 'C':
                case 'c':
                    arr.push_back(1);
                    break;
                case 'G':
                case 'g':
                    arr.push_back(2);
                    break;
                case 'T':
                case 't':
                    arr.push_back(3);
                    break;
                default:
                    break;
            }
        }
    }
    arr.pop_back();

    myfile.close();
    return arr;
}
