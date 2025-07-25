// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "shuffle.h"
#include "stdlib.h"
#include "bogglegui.h"
#include "lexicon.h"
#include "hashset.h"
#include "queue"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    bool dfsSearch(int x, int y, int index, string & word, Vector<Vector<bool>> & st);
    void dfsSearchAll(int x, int y, Set<string> & res, string & str, Vector<Vector<bool>> & st);

private:
    // TODO: add any other member functions/variables necessary
    Grid<char> Board;
    int Dimension;
    Lexicon Dictionary, Found;
    queue<string> New;
    int dx[8] = {-1,0,1,-1,1,-1,0,1}, dy[8] = {-1,-1,-1,0,0,1,1,1};
    int humanScore = 0;
};

#endif // _boggle_h
