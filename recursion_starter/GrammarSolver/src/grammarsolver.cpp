/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "hashmap.h"
#include "random.h"

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */

void grammarGenerateHelper(HashMap<string,Vector<string>> & map,string & str,string symbol)
{
    // base case:
    if(!map.containsKey(symbol))
    {
        str += symbol;
        str += " ";
        return ;
    }

    int num;
    if(map[symbol].size()) num = randomInteger(0,map[symbol].size() - 1);
    else num = 0;
    string s = map[symbol][num];
    s = trim(s);
    Vector<string> v = stringSplit(s," ");
    for(int i = 0 ; i < v.size() ; i ++)
    {
        grammarGenerateHelper(map,str,v[i]);
    }
    return ;
}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function

    // 读取文件 , 所有BNF存入图中
    string line;
    HashMap<string,Vector<string>> map;
    while(!input.eof())
    {
        int cnt = 0;
        getline(input,line);
        string non_terminal;
        char word;
        while(line[cnt] != ':')
            if(line[cnt] != ' ')
            {
                word = line[cnt ++];
                non_terminal += word;
            }
            else cnt ++;
        cnt += 3;
        string s;
        while(line[cnt])
        {
            word = line[cnt ++];
            s += word;
        }
        s = trim(s); // 删除首尾空格
        Vector<string> v = stringSplit(s,"|");

        // Extra Featrue 1:
        for(int i = 0 ; i < v.size() ; i ++) v[i] = trim(v[i]);
        map[non_terminal] = v;
        cout << non_terminal << ' ' << v << endl;
    }

    Vector<string> a;
    while(times --)
    {
        string str;
        grammarGenerateHelper(map,str,symbol);
        a.add(str);
    }
    return a;           // This is only here so it will compile
}


// Extra Feature 2 :
// 思路: 1.遍历所有key
//      2.每个key用dfs()搜到全部可能解，将所有解装入hashset中
//      3.输入要询问的句子，if判断其是否在hashset中，若不在，则该句子无可能来自该文件
