// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "simpio.h"
#include "Boggle.h"
#include "console.h"
#include "cctype"
#include "bogglegui.h"
using namespace std;

bool boardTextValid(string boardText)
{
    if(boardText.length() != 16)
    {
        cout << "That is not a valid 16-letter board string. Try again." << endl;
        return true;
    }
    for(const auto & item : boardText)
        if(!isalpha(item))
        {
            cout << "That is not a valid 16-letter board string. Try again." << endl;
            return true;
        }
    return false;
}

Boggle getBoggle(Lexicon & dictionary)
{
    if(getYesOrNo("Do you want to generate a random board?"))
    {
        Boggle board(dictionary,"");
        return board;
    }
    else{
        string boardText;
        do{
            boardText = getLine("Type the 16 letters to appear on the board:");
        }while(boardTextValid(boardText));
        Boggle board(dictionary,boardText);
        return board;
    }
}

void getGUI(Boggle board,int dimension)
{
    BoggleGUI::initialize(dimension,dimension);
    string Text;
    for(int i = 0 ; i < dimension ; i ++)
        for(int j = 0 ; j < dimension ; j ++)
        {
            Text += board.getLetter(i,j);
        }
    cout << Text << endl;
    BoggleGUI::labelAllCubes(Text);
}

void playOneGame(Lexicon& dictionary) {
    // TODO:
    if(BoggleGUI::isInitialized()) BoggleGUI::reset();
    int dimension = 4;
    Boggle board = getBoggle(dictionary);
    getGUI(board,dimension);
    clearConsole();

    Vector<string> Found;
    int hScore = 0;
    BoggleGUI::setStatusMessage("It's your turn!");
    cout << "It's your turn!" << endl;
    while(true) {
        cout << board << endl;
        cout << "Your words (" << Found.size() <<  "): " << Found << endl;
        hScore = board.getScoreHuman();
        cout << "Your score: " << hScore << endl;
        BoggleGUI::setScore(hScore,BoggleGUI::HUMAN);
        string word = getLine("Type a word (or Enter to stop):");
        BoggleGUI::clearHighlighting();
        if(word == "") break;
        clearConsole();
        while(!board.checkWord(word) || !board.humanWordSearch(word)) {
            if(!board.checkWord(word)) {
                cout << "You must enter an unfound 4+ letter word from the dictionary." << endl;
                cout << board << endl;
                cout << "Your words (" << Found.size() <<  "): " << Found << endl;
                cout << "Your score: " << hScore << endl;
            }
            else if(!board.humanWordSearch(word)) {
                cout << "That word can't be formed on this board." << endl;
                cout << board << endl;
                cout << "Your words (" << Found.size() <<  "): " << Found << endl;
                cout << "Your score: " << hScore << endl;
            }
            word = getLine("Type a word (or Enter to stop):");
            if(word == "") break;
            clearConsole();
        }
        cout << "You found a new word! " << " \"" << toUpperCase(word) << "\" " << endl;
        BoggleGUI::setStatusMessage("You found a new word! \"" + word + "\"");
        BoggleGUI::recordWord(word,BoggleGUI::HUMAN);
        Found.add(toUpperCase(word));
    }

    cout << endl;
    cout << "It's my turn!" << endl;
    cout << "My words" << "(" << board.computerWordSearch().size() << "):" << board.computerWordSearch() << endl;
    for(const auto & item : board.computerWordSearch()) {
        BoggleGUI::recordWord(item,BoggleGUI::COMPUTER);
    }
    int cScore = board.getScoreComputer();
    cout << "My score:" << cScore << endl;
    BoggleGUI::setScore(cScore,BoggleGUI::COMPUTER);

    if(board.getScoreHuman() >= cScore) {
        cout << "WOW, you defeated me! Congratulations!" << endl;
        BoggleGUI::setStatusMessage("WOW, you defeated me! Congratulations!");
    }
    else if(board.getScoreHuman() < cScore) {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
        BoggleGUI::setStatusMessage("Ha ha ha, I destroyed you. Better luck next time, puny human!");
    }

}

// Problem : 似乎StanFrodCpp-Library中的 Set 有100的大小上限，导致超出99以后的有的词无法显示

// Extra :
// 1.Make the Q a useful letter: The Q is largely useless unless it is adjacent to a U, so the real Boggle prints Qu together on a single face of the cube. You use both letters together, a strategy that not only makes the Q more playable but also allows you to increase your score because the combination counts as two letters.
// idea : 可对Q进行特判

// 2.Big Boggle: Once you have a working program, it should require only a few changes to support a variant that uses a 5 × 5 board. Word game aficionados generally agree that the original size was just a bit too small and scaling it up adds to the fun and challenge. This is a great exercise in verifying that your design is sufficiently organized and flexible to permit this adaptation. Our starter code declares two different cube arrays, one with the 16 cubes for the standard game and another with the 25 cubes for the bigger version.
// idea : 改Dimension

// 3.Embellish the GUI: The starter code comes with the source code for the Boggle GUI module, so you can modify it into a snazzier interface. For example, the current game merely highlights the word; it might be nice if it also drew lines or arrows marking the connections. Or you could use the Stanford C+ + library's gevent.h facilities to let the user assemble a word by clicking or dragging the mouse through the letter cubes, make it play sounds (some sound files also included in the res folder) etc.
// idea : 见 Stanford C+ + library's gevent.h

// 4.Board exploration: As you will learn, some Boggle boards are a lot more fruitful that others. Write some code to discover things about the possible boards. Is there an arrangement of the standard cubes that produces a board containing no words? What about an arrangement that produces a longest word, maybe even using all the cubes? What is the highest-scoring board you can construct? Recursion will be handy in trying out all the possible arrangements, but there are a lot of options (do the math on all the permutations...), so you may need to come up with some heuristics to direct your explorations.
// idea (From Chatgpt) :
//
//1. 找到无解的排列
//无解的排列，即通过某种排列，无法在字典中找到任何有效单词。为了寻找无解的排列，可以采用以下思路：
//A. 枚举所有排列
//由于 Boggle 游戏是基于一个固定的字母矩阵（通常是 4x4，即包含 16 个字母），所有字母的排列组合可能性虽然很大，但是有限的。我们可以通过递归的方式来枚举所有可能的字母排列，并检查每个排列是否能够生成有效单词。
//B. 检查是否有有效单词
//通过字典（或前缀树，Trie），对于每个排列生成的 Boggle 游戏板，我们可以使用 深度优先搜索（DFS） 来查找有效单词。每次生成一个单词时，检查是否在字典中存在：
//如果一个排列能够生成至少一个字典中的有效单词，那么这个排列就不是无解的。
//如果一个排列生成的所有单词都不在字典中，那么这个排列就是无解的。
//C. 优化：剪枝与提前停止
//前缀树（Trie）：在 DFS 搜索过程中，我们可以用前缀树来提前停止探索。比如，如果当前已生成的前缀不是字典中的任何有效前缀，那么就可以停止继续扩展这个前缀了，避免无效计算。
//剪枝：对于某些字母的排列，可能有些字母不适合做为字谜的起始字母，因为它们无法构成有效的字根。这些排列可以提前剪掉，减少计算量。
//
//2. 找到最高得分的排列
//最高得分的排列是指在所有可能的排列中，能够产生得分最高的字谜排列。得分通常由单词的长度决定，越长的单词得分越高。我们可以采取以下策略来寻找最高得分的排列：
//A. 暴力搜索所有排列
//可以通过枚举所有字母的排列，生成不同的 Boggle 游戏板，并检查每个排列能够产生的得分。对于每个排列，使用深度优先搜索（DFS）来查找所有有效单词，并计算它们的总得分。
//B. 剪枝与优化
//优先搜索长单词：通过优先访问字典中长度较长的单词，可以提高得分的可能性。
//动态规划：存储每个字母的最佳得分，从而避免重复计算。
//C. 最大化得分的策略
//为了提高得分，我们可以尝试以下策略：
//优化字母分布：将字母频率较高、能构成多种单词的字母放置在较为显眼的位置（如靠近中心）。
//优先选用常见字母：常见字母如 E、A 等可以提高找到单词的概率。
