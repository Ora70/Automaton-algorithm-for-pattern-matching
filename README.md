# Automaton

In this project we implement the naïve algorithm and the Automaton algorithm for exact matching and parameterized matching.
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

