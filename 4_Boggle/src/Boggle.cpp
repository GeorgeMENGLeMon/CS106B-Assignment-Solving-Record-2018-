// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    // TODO: implement
    Dimension = 4; // set Deimension
    Board.resize(Dimension,Dimension);
    Dictionary = dictionary;
    if(boardText.empty())
    {
        shuffle(CUBES,16);
        for (int i = 0; i < 16; ++i)
        {
            char ch = CUBES[i][randomInteger(0,5)];
            int row = i % 4 , col = i / 4;
            Board[row][col] = ch;
        }
    }
    else{
        boardText = toUpperCase(boardText);
        for (int i = 0; i < 16; ++i)
        {
            char ch = boardText[i];
            int row = i / 4 , col = i % 4;
            Board[row][col] = ch;
        }
    }
    cout << Board << endl;
}

char Boggle::getLetter(int row, int col) {
    // TODO: implement
    if(!Board.inBounds(row,col)) throw "Error";
    return Board[row][col];   // remove this
}

bool Boggle::checkWord(string word) {
    // TODO: implement
    word = toLowerCase(word);
    if(!Dictionary.contains(word)) return false;
    else if(word.size() > 16 || word.size() < 4) return false;
    else if(Found.contains(word)) return false;
    else return true;   // remove this
}

bool Boggle::dfsSearch(int i, int j, int index, string & word, Vector<Vector<bool>> & st) {
    if(index == word.size()) {
        Found.add(word);
        New.push(word);
        return true;
    }

    for(int k = 0 ; k < 8 ; k ++) {
        int x = i + dx[k] , y = j + dy[k];
        if(x >= 0 && x < Dimension && y >= 0 && y < Dimension) {
            if(Board[x][y] == word[index] && st[x][y] == false) {
                st[x][y] = true;
                BoggleGUI::setHighlighted(x,y,true);
                BoggleGUI::setAnimationDelay(100);
                if(dfsSearch(x,y,index + 1,word,st)) return true;
                BoggleGUI::setHighlighted(x,y,false);
                st[x][y] = false;
            }
        }
    }
    return false;
}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    word = toUpperCase(word);
    if(checkWord(word))
    {
        for(int i = 0 ; i < Dimension ; i ++)
            for(int j = 0 ; j < Dimension ; j ++) {
                if(Board[i][j] == word[0]) {
                    Vector<Vector<bool>> st(Dimension,Vector<bool>(Dimension,false));
                    st[i][j] = true;
                    BoggleGUI::setHighlighted(i,j,true);
                    if(dfsSearch(i,j,1,word,st)) return true;
                    BoggleGUI::setHighlighted(i,j,false);
                    st[i][j] = false;
                }
            }
    }
    return false;   // remove this
}

int Boggle::getScoreHuman() {
    // TODO: implement
    if(!New.empty()) {
        string str = New.front();
        New.pop();
        humanScore += str.size() - 3;
    }
    return humanScore;   // remove this
}

void Boggle::dfsSearchAll(int i, int j, Set<string> & res, string & str, Vector<Vector<bool>> & st) {
    if(Dictionary.contains(str) && !res.contains(str) && str.size() >= 4 && !Found.contains(str)) {
        res.add(str);
        return ;
    }

    for(int k = 0 ; k < 8 ; k ++) {
        int x = i + dx[k] , y = j + dy[k];
        if(x >= 0 && x < Dimension && y >= 0 && y < Dimension) {
            if(st[x][y] == false) {
                str += (Board[x][y]);
                st[x][y] = true;
                if(Dictionary.containsPrefix(str))
                    dfsSearchAll(x,y,res,str,st);
                st[x][y] = false;
                str.pop_back();
            }
        }
    }
    return ;
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    for(int i = 0 ; i < Dimension ; i ++)
        for(int j = 0 ; j < Dimension ; j ++) {
            Vector<Vector<bool>> st(Dimension,Vector<bool>(Dimension,false));
            string str = "";
            str += Board[i][j];
            st[i][j] = true;
            dfsSearchAll(i,j,result,str,st);
            st[i][j] = false;
        }
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    int computerScore = 0;
    for(const auto & str : computerWordSearch()) {
        computerScore += str.size() - 3;
    }
    return computerScore;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    for(int i = 0 ; i < boggle.Dimension ; i ++) {
        for(int j = 0 ; j < boggle.Dimension ; j ++) out << boggle.Board[i][j];
        out << endl;
    }
    return out;
}
