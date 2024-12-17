// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include "console.h"

#include"simpio.h"
#include"filelib.h"
#include"map.h"
#include"hashmap.h"
#include"vector.h"
#include"hashset.h"
using namespace std;


//欢迎信息
void WelcomeMessage()
{
    cout<<"Welcome to CS 106B Random Writer ('N-Grams')."<<endl;
    cout<<"This program makes random text based on a document."<<endl;
    cout<<"Give me an input file and an 'N' value for groups"<<endl;
    cout<<"of words, and I'll create random text for you."<<endl;
}

//获取文件名 打开文件
void getFile(string & filename,ifstream & f)
{
    do{
        filename = getLine("Input file name?");
    }while(!fileExists(filename));

    f.open(filename);
    if(f.fail()) cout<<"Unable to open that file.  Try again."<<endl;
}


//获取 N 值
void getValue(int & N)
{
    do{
        N = getInteger("Value of N?");
        if(N < 2) cout<<"N must be 2 or greater."<<endl;
    }while(N < 2);
}

//建立Map
void buildMap(ifstream & f,int N,HashMap<Vector<string>,Vector<string>> & map,Vector<Vector<string>> & strat,HashSet<Vector<string>> & end)
{
    string word;
    Vector<string> window,mapping,iteration;
    //拓展功能 : 生成更好的“首尾”

    for(int i = 0; i < N - 1; i ++)
    {
        f >> word;
        window.add(word);
        iteration.add(word);
    }

    while(f >> word)
    {
        if(map.containsKey(window))
        {
            map[window] += word;
        }
        else{
            mapping.add(word);
            map.put(window,mapping);

            //收集开头key
            if(isupper(window[0][0])) strat.add(window);
        }

        window.remove(0);
        window.add(word);

        //收集结尾key
        if(word.back() =='.'
            || word.back() =='?'
            || word.back() =='!') end.add(window);

        mapping.clear();
    }

    //读取时迭代  "尾首相连"
    while(!iteration.isEmpty())
    {

        if(map.containsKey(window))
        {
            map[window] += iteration[0];
        }
        else{
            mapping.add(iteration[0]);
            map.put(window,mapping);
            mapping.clear();
        }

        window.remove(0);
        window.add(iteration[0]);
        iteration.remove(0);
    }
}


//生成随机句子
void generatingRandomtext(HashMap<Vector<string>,Vector<string>> & map,int N,Vector<Vector<string>> & strat,HashSet<Vector<string>> & end)
{
    int step = 0;
    do{
        step = getInteger("# of random words to generate (0 to quit)?");
        if(step == 0) return;
        else if(step < N) cout<<"Must be at least "<<N<<" words."<<endl;
    }while(step < N);

    step = step - N;
    int upperbound,Number,Num;
    Vector<string> departure,slide;

    //此为拓展功能 : 有首尾
    if(strat.size() != 0 && end.size() != 0)
    {
        Number = randomInteger(0,strat.size() - 1);

        for(int i = 0; i < N - 1;i++)
        {
            departure.add(strat[Number][i]);
        }

        do{
            upperbound = map[strat[Number]].size();

            Num = randomInteger(0,upperbound - 1);

            departure.add(toLowerCase(map[strat[Number]][Num]));

            strat[Number].add(map[strat[Number]][Num]);
            strat[Number].remove(0);
        }while(step--);

        if(departure[departure.size() - 1].back() != '.'
            || departure[departure.size() - 1].back() != '?'
            || departure[departure.size() - 1].back() != '!')
        {
            do{
                upperbound = map[strat[Number]].size();

                Num = randomInteger(0,upperbound - 1);

                departure.add(toLowerCase(map[strat[Number]][Num]));

                strat[Number].add(map[strat[Number]][Num]);
                strat[Number].remove(0);
            }while(!end.contains(strat[Number]));
        }

        for(int i = 0;i < departure.size();i++)
        {
            cout<<departure[i]<<" ";
        }
        return;

    }

    //此为原基础功能 : 无首尾
    else{
        Vector<Vector<string>> keys = map.keys();
        Number = randomInteger(0,keys.size() - 1);

        for(int i = 0; i < N - 1;i++)
        {
            departure.add(keys[Number][i]);
        }

        do{
            upperbound = map[keys[Number]].size();

            Num = randomInteger(0,upperbound - 1);

            departure.add(map[keys[Number]][Num]);

            keys[Number].add(map[keys[Number]][Num]);
            keys[Number].remove(0);
        }while(step--);

        cout<<"..."<<" ";
        for(int i = 0;i < departure.size();i++)
        {
            cout<<departure[i]<<" ";
        }
        cout<<"..."<<endl;

        return;
    }
}


/*质量更高的随机数
int RandomGenerating(int upperbound)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> rdn(0,upperbound);

    return (int)rdn(mt);
}
*/

int main() {
    WelcomeMessage();

    ifstream f;
    string filename;
    getFile(filename,f);

    int N = 0;
    getValue(N);

    HashMap<Vector<string>,Vector<string>> map;
    Vector<Vector<string>> strat;
    HashSet<Vector<string>> end;
    buildMap(f,N,map,strat,end);

    generatingRandomtext(map,N,strat,end);

    cout<<endl;
    cout << "Exiting." << endl;
    return 0;
}
