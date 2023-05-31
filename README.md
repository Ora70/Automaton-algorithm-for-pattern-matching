# Automaton

In this project we implement the naïve algorithm and the Automaton algorithm for exact matching [1] and parameterized matching [2].
The program compares the running time of both algorithms and puts the results in a file.

input:

One argument which is the file path to a csv file with the running instructions:
Every line in the file represents all the arguments for a single test:

0.	Path to text
1.	Path to pattern
2.	Size of the alphabet
3.	Boolian – 1 if should test parameterized matching, 0 if should test exact matching
4.	Length of the pattern (if do not want to use the whole pattern in the path). This argument is optional

Output:
-	Csv file with the time taken by each algorithm and the number of matches
-	File with the positions of the matches in the text

------------------
[1] [Fast Pattern Matching in Strings](https://www.cs.jhu.edu/~misha/Spring23/Knuth77.pdf)

[2] [Alphabet dependence in parameterized matching](https://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=CA35471AA8FAA336FDFD6DE72EA8CA01?doi=10.1.1.58.1861&rep=rep1&type=pdf)
