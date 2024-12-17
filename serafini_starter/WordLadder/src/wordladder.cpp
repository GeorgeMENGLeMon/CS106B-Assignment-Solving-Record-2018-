// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"

#include"queue.h"
#include"simpio.h"
#include"filelib.h"
#include"lexicon.h"
#include"hashset.h"

using namespace std;


void wordLadder(string word1,string word2,Lexicon &lexicon,Lexicon & lexiconfile);


//欢迎信息
void WelcomeMessage()
{
    cout<<"Welcome to CS 106B Word Ladder."<<'\n'
        <<"Please give me two English words, and I will change the"<<'\n'
        <<"first into the second by changing one letter at a time."<<endl;
}

//获取文件名
void getFile(string & filename)
{
    do{
        filename = getLine("Dictionary file name?");
        if(!fileExists(filename)) cout<<"Unable to open that file.  Try again."<<endl;
    }while(!fileExists(filename));
}


/*基础功能 : 1).Word1与Word2长度相同   2).Word1,Word2来自文件

void gettwoWords(Lexicon & lexiconfile,Lexicon & lexicon)
{
    string word1,word2;
    do{
        word1 = getLine("Word #1 (or Enter to quit):");
        word1 = toLowerCase(word1);
        if(word1 == "") return; //quit
        else if(!lexiconfile.contains(word1)) cout<<"Invalid word, please retype"<<endl;
    }while(!lexiconfile.contains(word1));

    do{
        word2 = getLine("Word #2 (or Enter to quit):");
        word2 = toLowerCase(word2);
        if(word2 == "") return; //quit
        else if(word2 == word1) cout<<"The two words must be different."<<endl;
        else if(word2.size() != word1.size()) cout<<"The two words must be the same length."<<endl;
        else if(!lexiconfile.contains(word2)) cout<<"Invalid word, please retype"<<endl;
    }while(!lexiconfile.contains(word2) && word2 == word1 && word2.size() != word1.size());


    wordLadder(word1,word2,lexicon,lexiconfile);
}
*/

//获取两个单词 : Word1 Word2
//以下为拓展功能
void gettwoWords(Lexicon & lexiconfile,Lexicon & lexicon)
{
    string word1,word2;

    word1 = getLine("Word #1 (or Enter to quit):");
    word1 = toLowerCase(word1);
    if(word1 == "") return; //quit

    do{
        word2 = getLine("Word #2 (or Enter to quit):");
        word2 = toLowerCase(word2);
        if(word2 == "") return; //quit
        else if(word2 == word1) cout<<"The two words must be different."<<endl;
    }while(word2 == word1);

    wordLadder(word1,word2,lexicon,lexiconfile);
}

/*基础功能
int neighbor(Queue<Stack<string>> & queue,Stack<string> stack,Lexicon & lexicon,string word2,HashSet<string> & hashset)
{
    char a = 'a',letter;
    string ladder,tmp;
    ladder = stack.peek();
    for(size_t i = 0; i < ladder.size();i++)
    {
        for(int j = 0; j < 26 ; j++)
        {
            letter = a + j;
            tmp = ladder;
            tmp[i] = letter;
            if(tmp == word2)
            {
                stack.push(tmp);
                hashset.add(tmp);
                queue.enqueue(stack);
                return 1;
            }
            else if(tmp != ladder && lexicon.contains(tmp) && !hashset.contains(tmp))
            {
                stack.push(tmp);
                hashset.add(tmp);
                queue.enqueue(stack);
                stack.pop();
            }
        }
    }
    return 0;
}
*/

//查找相邻词  拓展功能 : 插入单词某位置一个字母 or 削减单词某位置
int neighbor(Queue<Stack<string>> & queue,Stack<string> stack,Lexicon & lexicon,string word2,HashSet<string> & hashset)
{
    char a = 'a',letter;
    string ladder,tmp,str;
    ladder = stack.peek();

    //查找同长度下,单词相邻词
    for(size_t i = 0; i < ladder.size();i++)
    {
        for(int j = 0; j < 26 ; j++)
        {
                letter = a + j;
                tmp = ladder;
                tmp[i] = letter;
                if(tmp == word2)
                {
                    stack.push(tmp);
                    hashset.add(tmp);
                    queue.enqueue(stack);
                    return 1;
                }
                else if(tmp != ladder && lexicon.contains(tmp) && !hashset.contains(tmp))
                {
                    stack.push(tmp);
                    hashset.add(tmp);
                    queue.enqueue(stack);
                    stack.pop();
                }
        }
    }

    //削减单词某位置
    if(word2.size() < ladder.size())
    {
        for(size_t i = 0;i < ladder.size();i++)
        {
            tmp = ladder;
            tmp.erase(i,1);
            if(tmp == word2)
            {
                stack.push(tmp);
                hashset.add(tmp);
                queue.enqueue(stack);
                return 1;
            }
            else if(tmp != ladder && lexicon.contains(tmp) && !hashset.contains(tmp))
            {
                stack.push(tmp);
                hashset.add(tmp);
                queue.enqueue(stack);
                stack.pop();
            }
        }
    }
    //插入单词某位置一个字母
    else if(word2.size() > ladder.size())
    {
        for(size_t i = 0;i < ladder.size();i++)
        {
            for(int j = 0; j < 26 ; j++)
            {
                letter = a + j;
                str = letter;
                tmp = ladder;
                tmp.insert(i,str);
                if(tmp == word2)
                {
                    stack.push(tmp);
                    hashset.add(tmp);
                    queue.enqueue(stack);
                    return 1;
                }
                else if(tmp != ladder && lexicon.contains(tmp) && !hashset.contains(tmp))
                {
                    stack.push(tmp);
                    hashset.add(tmp);
                    queue.enqueue(stack);
                    stack.pop();
                }
            }
        }
    }
    return 0;
}

/*基础功能
//Breadth-first search ("BFS")    广度优先搜索    最短路径
void wordLadder(string word1,string word2,Lexicon & lexicon,Lexicon & lexiconfile)
{
    Queue<Stack<string>> queue;
    Stack<string> stack;
    HashSet<string> hashset;
    stack.push(word1);
    queue.enqueue(stack);
    while(!queue.isEmpty())
    {

        stack = queue.dequeue();
        int destination = neighbor(queue,stack,lexicon,word2,hashset);

        if(destination == 1) break;
    }

    cout<<"A ladder from "<<word2<<" back to "<<word1<<" : "<<endl;
    cout<<word2<<" ";
    while(!stack.isEmpty())
    {
        cout<<stack.pop()<<" ";
    }
    cout<<"\n"<<endl;
    gettwoWords(lexiconfile,lexicon);
}
*/

//拓展功能: Word1与Word2长度不等



//查找       生成词梯
void wordLadder(string word1,string word2,Lexicon &lexicon,Lexicon & lexiconfile)
{
    Queue<Stack<string>> queue;
    Stack<string> stack;
    HashSet<string> hashset;
    stack.push(word1);
    queue.enqueue(stack);
    while(!queue.isEmpty())
    {

        stack = queue.dequeue();
        int destination = neighbor(queue,stack,lexicon,word2,hashset);

        if(destination == 1) break;
    }

    cout<<"A ladder from "<<word2<<" back to "<<word1<<" : "<<endl;
    cout<<word2<<" ";
    while(!stack.isEmpty())
    {
        cout<<stack.pop()<<" ";
    }
    cout<<"\n"<<endl;
    gettwoWords(lexiconfile,lexicon);
}


//主函数
int main() {
    WelcomeMessage();

    string filename;
    getFile(filename);

    Lexicon lexicon;
    lexicon.addWordsFromFile("dictionary.txt");//如果词梯要由EnglishWords搭成，就使用 "EnlishWords.txt"
                                               //果词梯要由dictionary的词搭成，就使用 "dictionary.txt"
    Lexicon lexiconfile;
    lexiconfile.addWordsFromFile(filename);


    gettwoWords(lexiconfile,lexicon);



    cout << "Have a nice day." << endl;
    return 0;
}
