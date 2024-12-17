/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include<iostream>
#include "console.h"
#include "simpio.h"

#include"filelib.h"
#include"grid.h"
#include"vector.h"
#include<fstream>
#include<string>

#include"map.h"
#include"hashmap.h"
#include"lexicon.h"
#include"timer.h"
#include"set.h"
#include"hashset.h"
#include"queue.h"
#include"stack.h"
#include <random>
#include"math.h"
#include "strlib.h"

#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include"gwindow.h"

using namespace std;

int main()
{
    ifstream f;
    string line,num;
    f.open("open");
    getline(f,line);
    cout << line << endl;
    getline(f,line);
    cout << line << endl;
    f.close();
    return 0;
}


/*Lecture 09  Backtracking

void diceSumHelper(int dice,int desiredSum,int sum,Vector<int> &num)
{
    if((sum >= desiredSum && dice > 0) || (sum + dice * 6 < desiredSum)) return ; //剪枝

    if(!dice) //边界问题 Base Case
    {
        if(sum == desiredSum)
        {
            for(auto c : num) cout<<c<<' ';
            cout<<endl;
        }
        return ;//return 放在外边!!!
    }

    for(int i = 1 ; i < 7 ; i ++)
    {
        //"choose i"
        dice --;
        sum += i;
        num.add(i);
        diceSumHelper(dice,desiredSum,sum,num);
        //"un - choose i" 还原现场
        int ed_idx = num.size() - 1;
        num.remove(ed_idx);
        sum -= i;
        dice ++;
    }
}

void diceSum(int dice, int desiredSum)
{
    Vector<int> num;
    diceSumHelper(dice,desiredSum,0,num);
}

int main()
{
    int dice,desiredSum;
    cin>>dice>>desiredSum;
    diceSum(dice,desiredSum);
    return 0;
}

*/


/*Lecture 08  Recursion Fractals


********************************************************

int main()
{
    char a[100];
    cin>> a + 1;
    cout<<a[0];
    return 0;
}



********************************************************

using namespace std;

char getOperator(string exp);
int getOppIndex(string exp);
string getLeftExp(string exp);
string getRightExp(string exp);
int evaluate(string exp);

int main() {
    while (true) {
        string expression = getLine("Please enter an expression to evaluate (ENTER to quit): ");
        if (expression.length() == 0) {
            break;
        }

        cout << evaluate(expression) << endl;
    }
    return 0;
}


 * Returns the value of this expression string as an integer.  The expression
 * must be either an integer or an operation contained in parentheses,
 * containing only + or * operators.

int evaluate(string exp) {
    if (stringIsInteger(exp)) {
        return stringToInteger(exp);
    } else {
        char op = getOperator(exp);
        string left = getLeftExp(exp);
        string right = getRightExp(exp);
        int leftResult = evaluate(left);
        int rightResult = evaluate(right);
        if (op == '+') {
            return leftResult + rightResult;
        } else {
            return leftResult * rightResult;
        }
    }
}

// Returns the top-level operator character in this expression (assumes operator exists).
char getOperator(string exp) {
    return exp[getOppIndex(exp)];
}


 * Returns the index of the top-level operator (+ or *) in this expression, or -1
 * if not found.

int getOppIndex(string exp) {
    int parens = 0;
    // ignore first left paren
    for (size_t i = 1; i < exp.length(); i++) {
        char c = exp[i];
        if (c == '(') {
            parens++;
        } else if (c == ')') {
            parens--;
        }
        if (parens == 0 && (c == '+' || c == '*')) {
            return i;
        }
    }

    return -1;
}

// Returns the substring until (but not including) the operator, without the start paren
string getLeftExp(string exp) {
    int oppIndex = getOppIndex(exp);
    return exp.substr(1, oppIndex - 1);
}

// Returns the substring from after the operator until the end, without the end paren
string getRightExp(string exp) {
    int oppIndex = getOppIndex(exp);
    return exp.substr(oppIndex + 1, exp.length() - (oppIndex +1) - 1);
}




********************************************************

void cantorSet(GWindow & gw,int x,int y,int length,int levels)
{
    if(levels == 0)
    {
        //base case
    }
    else{
        gw.drawLine(x,y,x + length,y);
        gw.drawLine(x,y + 1,x + length,y + 1);
        gw.drawLine(x,y + 2,x + length,y + 2);
        gw.drawLine(x,y + 3,x + length,y + 3);

        cantorSet(gw,x             ,y + 20,length/3,levels - 1);
        cantorSet(gw,x + 2*length/3,y + 20,length/3,levels - 1);
    }
}

int main()
{
    GWindow gw(1600,1600);
    gw.setWindowTitle("CantorSet");
    gw.setColor("blue");
    int x = getInteger("x = ");
    int y = getInteger("y = ");
    int length = getInteger("length = ");
    int levels = getInteger("levels = ");

    cantorSet(gw,x,y,length,levels);

    return 0;

}

********************************************************

void fractal(GWindow& gw,int x,int y,int size,int order)
{

    if(order >= 0)
    {
        fractal(gw,x-size/2,y-size/2,size/2,order - 1);

        fractal(gw,x+size/2,y+size/2,size/2,order - 1);

        gw.fillRect(x,y,size,size);

        fractal(gw,x+size/2,y-size/2,size/2,order - 1);

        fractal(gw,x-size/2,y+size/2,size/2,order - 1);
    }
}

int main()
{
    GWindow gw(800,600);
    gw.setTitle("Boxy fractal");
    gw.setColor("red");


    int x = getInteger("Type x :");
    int y = getInteger("Type y :");
    int size = getInteger("Type size :");
    int order = getInteger("Type order:");

    fractal(gw,x,y,size,order);

    return 0;

}

*/

/*Lecture 06  Recursion

********************************************************

//递归 : 回文数判断
//方法一
bool isPalindrome1(string str,int i)
{
    if(i >= str.size() - i) return true;
    if(str[i] == str[str.size() - 1 - i])
    {
        return isPalindrome(str,i + 1);
    }
    else
    {
        return false;
    }
}

//方法二:
bool isPalindrome2(string str)
{
    if(str.length() <= 1) return true;
    else{
        char first = str[0];
        char last = str[str.length() - 1];
        string middle = str.substr(1,str.length() - 2);
        return (first == last && isPalindrome2(middle));
    }
}



int main()
{
    string str = getLine("Type a string :");
    string strcopy = toLowerCase(str);
    int i = 0;
    bool a = isPalindrome1(strcopy,i);
    if(a == 0) cout<<"false"<<endl;
    else cout<<"true"<<endl;
    return 0;

}


********************************************************

int mystery(int n)
{
    if(n < 10)
    {
        return (10 * n) + n;
    }
    else{
        int a = mystery(n / 10);
        int b = mystery(n % 10);
        return (a * 100) + b;
    }

}

int main()
{
    int a = getInteger("Number : ");
    int result = mystery(a);
    cout<<result<<endl;
    return 0;
}

********************************************************


int factorial(int n)
{
    if( n <= 1) return 1;
    else{
        return n * factorial(n - 1);
    }
}

int main()
{
    int a = getInteger("计算n的factorial : ");
    int result = factorial(a);
    cout<<"阶乘为 : "<<result<<endl;
    return 0;
}


*/
/*Lecture 05      Set & Lexicon & Map


********************************************************

int main()
{
    Map<Vector<string>,Vector<string>> map;
    Vector<string> left,right;

    left.add("Hello");
    left.add("Welcome");
    right.add("nihao");

    map.put(left,right);

    cout<<map<<endl;

    right.add("keyi");

    cout<<map<<endl;

    right.clear();

    right.add("haoma");
    map.put(left,right);

    cout<<map<<endl;

    map[left] += "buhao";

    cout<<map<<endl;

    int a = map.containsKey(left);

    cout<<a<<endl;

    left.add("New");
    right.add("buhao");
    map.put(left,right);

    cout<<map<<endl;
    cout<<map.keys()<<endl;

    Vector<Vector<string>> keys = map.keys();
    cout<<keys[0]<<endl;

    int nums = 0,Num,times = 20;

    nums = randomInteger(0,10);
        cout<<nums<<endl;
    Num = nums;

        while (times--) {

            cout<<"Num : "<<Num<<endl;
            cout<<nums<<endl;

        }



    Vector<string> departrue;
    departrue.add(keys[0].toString());
    cout<<departrue<<endl;
    cout<<departrue[0]<<endl;

    keys[0].remove(0);
    cout<<keys[0]<<endl;

    return 0;
}

********************************************************

int main()
{
    Queue<Stack<string>> queue;
    Stack<string> stack;
    stack.push("Hello");
    queue.enqueue(stack);
    cout<<queue<<endl;

    stack.push("Welcome");
    queue.enqueue(stack);
    cout<<queue<<endl;

    return 0;
}

********************************************************

int neighbor(string ladder,Stack<string> & stack,Lexicon & lexicon,string word2,int num)
{
    char a = 'a',letter;
    string tmp;
    for(size_t i = 0; i < ladder.size();i++)
    {
        for(int j = 0; j < 14; j++)//15以上会爆栈
        {   num++;
            cout<<num<<endl;
            letter = a + j;
            tmp = ladder;
            tmp[i] = letter;
            if(tmp == word2)
            {
                stack.push(word2);
                return 1;
            }
            else if(tmp != ladder && lexicon.contains(tmp))
            {

                stack.push(tmp);
                int x = neighbor(tmp,stack,lexicon,word2,num);
                if(x == 1) return 1;
                else stack.pop();
            }
        }
    }
    return 0;
}



int main()
{
    Lexicon lexicon;
    Stack<string> stack;
    string ladder,word2;

    ladder = getLine("word1 : code ");
    word2 = getLine("word2 : data");

    //data date cate cade code

    lexicon.add("data");
    lexicon.add("date");
    lexicon.add("cate");
    lexicon.add("cade");
    lexicon.add("code");
    stack.push(ladder);
    int num = 0;

    int n = neighbor(ladder,stack,lexicon,word2,num);
    cout<<n<<stack.toString()<<endl;
    return 0;
}


********************************************************
int main()
{
    string word;
    word = getLine("Type a word : ");

    if(word == "") cout<<"quit"<<endl;
    else cout<<"here "<<word[0]<<" success "<<endl;



    char a = 'a';
    for(int i = 0;i < 26;i ++)
    {
        char num = a + i;
        cout<<a + i<<" "<<num<<endl;
    }


    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    cout<<queue.peek()<<endl;
    return 0;
}


********************************************************
int main()
{
    ifstream f;
    f.open("open.txt");
    Map<string,int> map;
    HashMap<string,int> hashmap;
    string word;
    while(f >> word)
    {
        word = toLowerCase(word);
        cout<<word<<endl;
        if(!map.containsKey(word)) map.put(word,1);
        else map[word]++;

        if(!hashmap.containsKey(word)) hashmap.put(word,1);
        else hashmap[word]++;
    }

    cout<<"Map : "<<endl;

    for(const string &words : map)
    {
        cout<<words<<" appears "<<map[words]<<" times "<<endl;
    }

    cout<<"Hashmap : "<<endl;

    for(const string &words : hashmap)
    {
        cout<<words<<" appears "<<hashmap[words]<<" times "<<endl;
    }


    while(true)
    {
        string wordsearch = toLowerCase(trim(getLine("Word to search for : ")));
        if(wordsearch == "")
        {
            break;
        }
        else{
            int count = map.get(wordsearch);
            cout<<wordsearch<<" occurs "<<count<<endl;
        }
    }
    return 0;
}



********************************************************

int main()
{
    Timer timer;
    timer.start();
    ifstream f;
    f.open("open.txt");
    HashSet<string> hashset;
    Set<string> set;
    Lexicon lexicon;
    string word;
    while(f >> word)
    {
        word = toLowerCase(word);
        cout<<word<<endl;
        hashset.add(word);
        set.add(word);
        lexicon.add(word);
    }

    cout<<"Unique Words : "<<hashset.size()<<endl;
    cout<<"Use "<<timer.stop()<<"ms"<<endl;

    cout<<hashset<<'\n'<<set<<endl;

    cout<<"Set : "<<endl;

    for(const string &words:set) cout<<"Here is a word: "<<words<<endl;

    cout<<"Hashset : "<<endl;

    for(const string &words:hashset) cout<<"Here is a word: "<<words<<endl;

    cout<<"Lexicon : "<<endl;

    for(const string &words:lexicon) cout<<"Here is a word: "<<words<<endl;

    return 0;
}



*/
/*Lecture 04   ATD

********************************************************


//Stutter
void stutter(Queue<char> & queue)
{
    int n = 0,length = queue.size();
    n = getInteger("How many copies?");
    Queue<char> queuecopy;
    for (int i = 0; i < length; i++)
    {
        char copy = queue.dequeue();
        for(int j = 0;j < n;j++)
        queuecopy.enqueue(copy);
    }

    while(!queuecopy.isEmpty())
    {
        char copy2 = queuecopy.dequeue();
        queue.enqueue(copy2);
    }

}


//Mirror:用Vector或Stack均可

void mirrorVector(Queue<char> & queue)
{
    Vector<char> queuecopy;
    while(!queue.isEmpty())
    {
        char copy = queue.dequeue();
        queuecopy.add(copy);
    }

    for(int i = queuecopy.size()-1;i >= 0;i--)
    {
        char copy2 = queuecopy[i];
        queuecopy.add(copy2);
    }

    for(int i = 0;i < queuecopy.size();i++)
    {
        queue.enqueue(queuecopy[i]);
    }
}

//使用了辅助queuecopy
void mirrorStack1(Queue<char> & queue)
{
    Stack<char> stack;
    Queue<char> queuecopy;
    queuecopy = queue;
    while(!queuecopy.isEmpty())
    {
        stack.push(queuecopy.dequeue());
    }

    while(!stack.isEmpty())
    {
        queue.enqueue(stack.pop());
    }
}

//不使用辅助queue
void mirrorStack2(Queue<char> & queue)
{
    int length = queue.size();
    Stack<char> stack;
    while(length--)
    {
        char word = queue.dequeue();
        stack.push(word);
        queue.enqueue(word);
    }

    while(!stack.isEmpty())
    {
        queue.enqueue(stack.pop());
    }
}


int main()
{
    Queue<char> queue;
    int n = getInteger("How many chars you want to enqueue?");
    for(int i = 0;i < n;i++)
    {
        char word;
        word = getChar("word:");
        queue.enqueue(word);
    }

    string option;
    do{
        option = getLine("Stutter or Mirror?");
    }while(!equalsIgnoreCase("Stutter",option) && !equalsIgnoreCase("Mirror",option));

    if(equalsIgnoreCase("Stutter",option)) stutter(queue);
    else if(equalsIgnoreCase("Mirror",option)) mirrorStack2(queue);

    cout<<queue.toString()<<endl;

    return 0;


}



********************************************************

int checkBalance(string str)
{
    Stack<char> stack;
    int check = 0;
    for(int i = 0;i < str.length();i++)
    {
        char c = str[i];
        if(c == '{' || c =='(')
        {
            stack.push(c);
        }

        else if(c == '}')
        {
            if(stack.isEmpty()) cout<<"Position "<<i + 1<<" redundancy of Right-Side symbols"<<endl,check++;
            else if(stack.peek() != '{')
            {
                cout<<"Position "<<i + 1<<" error.It need to be ')'. "<<endl;
                stack.pop();
                check++;
            }
            else stack.pop();
        }

        else if(c == ')')
        {
            if(stack.isEmpty()) cout<<"Position "<<i + 1<<" redundancy of Right-Side symbols"<<endl,check++;
            else if(stack.peek() != '(')
            {
                cout<<"Position "<<i + 1<<" error.It need to be '}'. "<<endl;
                stack.pop();
                check++;
            }
            else stack.pop();
        }
    }

    check += stack.size();
    if(stack.size() > 0) cout<<stack.size()<< " redundancy of Left-Side symbols" << endl;
    return check;
}


int main()
{
    string str;
    str = getLine("Put a string with '{' '}' '(' ')' : ");
    int check = checkBalance(str);
    if(check == 0) cout<<"str is balanced."<<endl;
    else cout<<check<<" positions error."<<endl;
    return 0;
}

*/

/*Lecture 03    I/O Steams   Vector & Grid

********************************************************
//好的随机数的生成
int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> dist(1, 3);

    for (int i=0; i<16; ++i)
        std::cout << (int)dist(mt) << "\n";
    return 0;
}

********************************************************

void getFile(ifstream &f,string &name)
{
    name = promptUserForFilename("put name : ");
    f.open(name);
    if(f.fail()) cout<<"fail"<<endl;
    f.close();
}


int main()
{
    ifstream f;
    string name;
    getFile(f,name);
    return 0;
}



********************************************************

int main()
{
    //创建一个文件 (手动加 .txt 后缀)
    string filename = getLine("Please input the file name: ");
    ofstream outfile(filename);

    if(fileExists(filename))
        cout<<"file create successed!"<<endl;
    outfile.close();


    //写入
    ofstream f;
    openFile(f,filename);
    if(f.fail())
    {
        cout<<"Open Failure"<<endl;
    }
    f<<"This is a test"<<'\n'<<"Welcome"<<'\n'<<"CS106B"<<endl;
    f.close();

    //读取
    ifstream r;
    openFile(r,filename); //r.open(filename);
    if(r.fail())
    {
        cout<<"Open Failure"<<endl;
    }

    string line;
    int lines = 0;

    while(getline(r,line))
    {
        lines++;
        cout<<"Line"<<lines<<":";
        cout<<line<<endl;
    }

    r.close();
    return 0;
}




********************************************************

int main()
{
    Grid<int> matrix(3,3);
    matrix = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    cout<<matrix.toString()<<endl;

    for(int value:matrix)
        cout<<value;

    cout<<endl;

    for(int i = 0;i<matrix.numRows();i++)
        for(int j = 0;j<matrix.numCols();j++)
            cout<<matrix[i][j];

    cout<<endl;

    for(int a = 0;a<matrix.numCols();a++)
        for(int b = 0;b<matrix.numRows();b++)
            cout<<matrix[b][a];
    return 0;
}


********************************************************

int main()
{
    ifstream input;
    input.open("open.txt");
    if(input.fail())
    {
        cout<<"Open Failure"<<endl;
    }

    string token;
    int words = 0;
    Vector<string> AllWords;
    while(input >> token)
        cout<<token<<endl,
            words++,
            AllWords.add(token);
    cout<<"The total words : "<<words<<endl;
    cout<<"All Words : "<<AllWords<<endl;

    for(int i = AllWords.size() - 1;i >= 0;i--)
        cout<<AllWords[i]<<endl;

    for(string all:AllWords)
        cout<<all<<endl;
    input.close();
    return 0;
}



********************************************************

int main()
{
    ifstream input;
    input.open("open.txt");
    if(input.fail())
    {
        cout<<"Open Failure"<<endl;
        return 0;
    }
    string line;
    int lines = 0;
        while(getline(input,line))
        cout<<line<<endl,lines++;
        cout<<"total lines : "<<lines<<endl;

        input.clear();
        input.seekg(0);

    string token;
    int words = 0;
        while(input >> token)
        cout<<token<<endl,
        words++;
        cout<<"The total words : "<<words<<endl;

        input.close();
    return 0;

}
*/

/*Lecture 02   Fuction String
********************************************************

void coutspace(int i)
{
    for(int j = 0;j < i;j++)
        cout<<' ';
}


void nameDiamond(string s)
{
    for(int i = 0;i<s.size();i++)
    {
        cout<<s.substr(0,i)<<endl;
    }

    for(int i = 0;i<s.size();i++)
    {
        coutspace(i);
        cout<<s.substr(i)<<endl;
    }
}

int main(void)
{
    string s;
    cin>>s;
    nameDiamond(s);
    return 0;
}


********************************************************

int main()
{
    string str0 = "Well";
    string str1 = "Hello";
    string str2 = "CS106B";
    string str3;

    str1 += str2;
    cout<<"+:"<<str1<<endl;//字符串的相加 （减法会报错）

    str2.append(" Welcome");
    cout<<"s1.append(s2):"<<str2<<endl;//append

    int x = str1.compare(str2);
    int y = str1.compare(1,3,str0,1,3);
    int z = str1.compare(1,4,str0,1,3);
    cout<<"x = "<<x<<' '<<"y = "<<y<<' '<<"z = "<<z<<endl;//compare  比较字符串长度



    str1.erase(2,2);
    cout<<"s1.erase(index,length):"<<str1.at(1)<<' '<<str1.at(2)<<' '<<str1[3]<<' '<<str1<<endl;//erase

    int a = str0.find("l");
    int b = str0.rfind("l");
    int c = str0.find("a");
    cout<<"a = "<<a<<' '<<"b = "<<b<<' '<<"c = "<<c<<endl;//find rfind
    cout<<"string::npos = "<<string::npos<<endl;

    str1.insert(4," Welcome TO ");
    cout<<"str1 = "<<str1<<endl;//insert

    int d = str1.size();
    int e = str0.length();
    cout<<"d = "<<d<<' '<<"e = "<<e<<endl;//size length

    str0.replace(str0.rfind("l"),5,"lcome");
    cout<<"str0 = "<<str0<<endl;//replace

    string s0 = str0.substr(1,7);
    cout<<"s0 = "<<s0<<endl;//substr


    return 0;
}


********************************************************

void Caculateroots(int a,int b,int c)
{
    int delta,x1,x2;

    if(a == 0 && b == 0)
    {
        cout<<"coutless solution"<<endl;
        return;
    }
    else if(a == 0 && b != 0)
    {
        int tmp = -c/b;
        cout<<"x = "<<tmp<<endl;
        return;
    }

    delta = b*b - 4*a*c;

    if(delta < 0)
    {
        cout<<"The equation has no solution"<<endl;
        return;
    }

    x1 = (-b+sqrt(delta))/(2*a);//need: #include"math.h" or #include<cmath>
    x2 = (-b-sqrt(delta))/(2*a);

    if(delta == 0)
    {
        cout<<"x1 = x2 = "<<x1<<endl;
        return;
    }
    cout<<"x1 = "<<x1<<' '<<"x2 = "<<x2<<endl;
}

int main()
{
    int a,b,c;
    cout<<"a = ";
    cin >>a;
    cout<<"b = ";
    cin >>b;
    cout<<"c = ";
    cin >>c;

    Caculateroots(a,b,c);

    return 0;

}


********************************************************

void swap(int&x,int&y)
{
    int tmp;
    tmp = x;
    x = y;
    y = tmp;
}

int main()
{
    int x,y;
    cout << "Put in two number you want to swap:";
    cin >> x >> y;
    swap(x,y);
    cout << x <<' ' << y <<endl;
    return 0;

}

********************************************************



void PrintLine(int width = 10,char letter = '*')//此处赋值为default
{
    for(int i = 0;i < width; i++)
        cout<<letter;
}

int main()
{
    int x;
    char y;
    cin>>x>>y;
    PrintLine(x,y);
    cout<<endl;
    PrintLine(x);//参数输入函数只能向右省略
    cout<<endl;
    PrintLine();//default
    return 0;
}
*/



/*Lecture 01
 int main()
{
    cout << "Hello" <<endl;
    string a = getLine("Name:");
    int b = getInteger("age:");
    cout <<"Welcomg you "<< a <<" who's age is"<< b <<endl;
    return 0;
}
*/

