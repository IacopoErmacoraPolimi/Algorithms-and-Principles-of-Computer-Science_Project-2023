# WordChecker

This project was developed by Iacopo Ermacora (iacopoermacora@gmail.com) as part of the university exam for Algorithms, Principles of Computer Science, and Data Structures at Politecnico di Milano in 2022.

## Objective
The goal of this project is to build a system that checks the correspondence between the letters of two words of equal length. The words are considered as sequences of symbols, including lowercase (a-z) and uppercase (A-Z) alphabetic characters, numeric digits (0-9), as well as the symbols "-" (hyphen) and "_" (underscore).

## System Description
The system reads a sequence of information and instructions from the standard input and produces output strings based on different cases. The input sequence includes:
- A value `k` indicating the length of the words.
- An arbitrary sequence of words, each of length `k`, which constitutes the set of permissible words. It is assumed that the sequence of words does not contain duplicates.
- Following that, a sequence of "matches" is read from the standard input. Each match starts with the command "+nuova_partita" (Italian for "new game").
- The input sequence for each match (after the "+nuova_partita" command) is structured as follows:
  - A reference word (of length `k` characters).
  - It is assumed that the reference word belongs to the set of permissible words.
  - The maximum number `n` of words to be compared with the reference word.
  - A sequence of words (each of length `k` characters) to be compared with the reference word.
- Occasionally, the command "+stampa_filtrate" may appear in the input sequence. Its effect is explained later.
- Additionally, during a match or between matches, the commands "+inserisci_inizio" and "+inserisci_fine" can appear, enclosing a sequence of new words to be added to the set of permissible words.
- The added words are also of length `k`, and it is always assumed that there are no duplicate words (even with respect to the existing permissible words).

## Comparison Logic
For each word `p` read from the input, to be compared with the reference word `r`, the program writes a sequence of `k` characters to stdout using the following rules:
- Let `p[1]`, `p[2]`, ..., `p[k]` denote the characters of word `p`, `r[1]`, `r[2]`, ..., `r[k]` denote the characters of word `r`, and `res[1]`, `res[2]`, ..., `res[k]` denote the characters of the printed sequence.
- For each `1 ≤ i ≤ k`:
  - If `p[i]` is equal to `r[i]`, then `res[i]` is '+', indicating that `p[i]` is in the correct position.
  - If `p[i]` does not appear anywhere in `r`, then `res[i]` is '/', indicating that `p[i]` is not present in `r`.
  - If `p[i]` appears in `r` but not in the i-th position, then `res[i]` is '|' unless there are `ni` instances of `p[i]` in `r`, where `ni` is the number of instances of the character `p[i]` that are in the correct position. Moreover, there should be at least `ni - ci` characters equal to `p[i]` that are in the incorrect position before the i-th character in `p`, where `ci ≤ ni`.

For further clarification or access to the full project, please contact the developer, Iacopo Ermacora, at iacopoermacora@gmail.com.
