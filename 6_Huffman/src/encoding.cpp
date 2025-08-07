// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need
#include "pqueue.h"
#include "functional"
#include "filelib.h"

Map<int, int> buildFrequencyTable(istream& input) {
    // TODO: implement this function
    Map<int, int> freqTable;   // this is just a placeholder so it will compile
    char ch;
    while(input.get(ch)) freqTable[ch] ++;
    freqTable[PSEUDO_EOF] = 1;
    return freqTable;          // this is just a placeholder so it will compile
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // TODO: implement this function
    PriorityQueue<HuffmanNode*> pq;
    for(const auto& key : freqTable) {
        HuffmanNode* node = new HuffmanNode (key,freqTable[key]);
        pq.enqueue(node,node->count);
    }
    while(pq.size() != 1) {
        HuffmanNode* chLeft = pq.dequeue();
        HuffmanNode* chRight = pq.dequeue();
        HuffmanNode* newRoot = new HuffmanNode;
        newRoot->zero = chLeft;
        newRoot->one = chRight;
        newRoot->count = chLeft->count + chRight->count;
        pq.enqueue(newRoot,newRoot->count);
    }
    return pq.dequeue();
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    function<void(HuffmanNode*,string)> dfs = [&](HuffmanNode* node, string encode) {
        if(node->isLeaf()) {
            encodingMap[node->character] = encode;
            return ;
        }
        dfs(node->zero, encode + "0");
        dfs(node->one, encode + "1");
    };
    dfs(encodingTree, "");
    return encodingMap;             // this is just a placeholder so it will compile
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
    char ch;
    while(input.get(ch)) {
        string bits = encodingMap[ch];
        for(char bit : bits) output.writeBit(bit - '0');
    }

    string eofBits = encodingMap[PSEUDO_EOF];
    for(char bit : eofBits) output.writeBit(bit - '0');
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
    HuffmanNode* curr = encodingTree;
    while(true) {
        int bit = input.readBit();
        curr = bit ? curr->one : curr->zero;

        if(curr->isLeaf()) {
            if(curr->character == PSEUDO_EOF) break;
            output.put(curr->character);
            curr = encodingTree;
        }
    }
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    Map<int, int> freqTable = buildFrequencyTable(input);
    rewindStream(input);
    output << freqTable;
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    Map<int, string> encodingMap = buildEncodingMap(encodingTree);

    encodeData(input,encodingMap,output);
    freeTree(encodingTree);
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    Map<int, int> freqTable;
    input >> freqTable;
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);

    decodeData(input,encodingTree,output);
    freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
    if(node == nullptr) return;

    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}


/*
Possible Extra Features
Though your solution to this assignment must match all of the specifications mentioned previously, you are allowed and encouraged to add extra features to your program if you’d like to go beyond the basic assignment. Here are some ideas for extra features that you could add to your program.

Encouraged Extension: MyMap

One of the key data structures required by the Huffman Encoding algorithm is a map - specifically, a map from int to int that represents the frequency table of characters in files you wish to compress. As an extension, write your own implementation of the MyMap class that is a map data structure with keys and values of type int. The starter code contains the files MyMap.h/.cpp where you can implement this - please make copies of your other files when you modify them so that this extension does not conflict with the required assignment. Your challenge, if you choose to accept it, is to implement MyMap and then use it in place of a regular Map for your frequency table. The class exports the following public methods, which you will need to implement:

Name	Description	Runtime
MyMap()	Constructor for your map	O(1)
~MyMap()	Destructor for your map. Clears all heap-allocated memory.	O(N)
void put(int key, int value)	Associates key with value in your map, replacing existing values if need be.	O(1)
int get(int key)	Returns the value associated with key in your map. Throws a string exception if the key is not in the map.	O(1)
bool containsKey(int key)	Returns a boolean indicating whether or not key is a key in your map.	O(1)
Vector<int> keys()	Returns a Vector of all the keys in your map.	O(N)
These methods represent the methods required for one possible implementation of Huffman Compression, but you are free to implement other public methods for use in your assignment. As a general guide, refer to the Stanford HashMap documentation for other methods you might want to implement. We provide a method int hashFunction() which you may use when hashing key-value pairs into your map, as well as overloaded operators for << and >>. You can also choose to implement rehashing in your map if the load factor exceeds a particular threshold. For testing, the class exports the sanityCheck() method that tests your map to ensure that the previously mentioned public methods behave as specified. It's not comprehensive - depending on the specifics of your implementation, you are allowed and encouraged to modify the method to better suit you - and is a useful way to check whether your map behaves as intended.

To get you started implementing this, you should use an array of buckets into which key-value pairs are hashed. Each bucket in the array must be the head of a linked list of key-value pairs. You are provided with the following struct to help you with this:

struct key_val_pair {
    int key;
    int value;
    key_val_pair* next;
};
We also provide you with a helper method to create an array of buckets for you:

bucketArray createBucketArray(int nBuckets)	Returns an array of key_val_pair* with size nBuckets. All elements are set to nullptr initially.
Note that the bucketArray type is simply a typedef (synonym) for the type key_val_pair**, that is, pointers to pointers to key_val_pairs. While this certainly looks grisly, we simply use key_val_pair** to refer to an array of key_val_pair*s, just as we use int* to refer to an array of type int. For the purposes of this assignment, you need not worry about any of this - you can simply work with the bucketArray type by doing something like:

bucketArray buckets = createBucketArray(8);
key_val_pair* head = buckets[4]; // access an element in the array
Buckets[3] = new key_val_pair; // set an element in the array
You may also add other extra features to your implementation. Here are some other ideas:

1.Make the encoding table more efficient: Our implementation of the encoding table at the start of each file is not at all efficient, and for small files can take up a lot of space. Try to see if you can find a better way of encoding the data. If you’re feeling up for a challenge, try looking up succinct data structures and see if you can write out the encoding tree using one bit per node and one byte per character!
2.Add support for encryption in addition to encodingWithout knowledge of the encoding table, it’s impossible to decode compressed files. Update the encoding table code so that it prompts for a password or uses some other technique to make it hard for Bad People to decompress the data.
3.Implement a more advanced compression algorithm:Huffman encoding is a good compression algorithm, but there are much better alternatives in many cases. Try researching and implementing a more advanced algorithm, like LZW, in addition to Huffman coding.
4.Gracefully handle bad input files:The normal version of the program doesn’t work very well if you feed it bogus input, such as a file that wasn’t created by your own algorithm. Make your code more robust by making it able to detect whether a file is valid or invalid and react accordingly. One possible way of doing this would be to insert special bits/bytes near the start of the file that indicate a header flag or check-sum. You can test to see whether these bit patterns are present, and if not, you know the file is bogus.
5.Other:If you have your own creative idea for an extra feature, ask your SL and/or the instructor about it.
Indicating that you have done extra features:

If you complete any extra features, then in the comment heading on the top of your program, please list all extra features that you worked on and where in the code they can be found (what functions, lines, etc. so that the grader can easily identify them).

Submitting a program with extra features:

Since we use automated testing for part of our grading process, it is important that you submit a program that conforms to the preceding spec, even if you want to do extra features. If your feature(s) cause your program to change the output that it produces in such a way that it no longer matches the expected sample output test cases provided, you should submit two versions of your program file: a first one named life.cpp without any extra features added (or with all necessary features disabled or commented out), and a second one named life-extra.cpp with the extra features enabled. Please distinguish them in by explaining which is which in the comment header. Our submission system saves every submission you make, so if you make more than one we will be able to view all of them; your previously submitted files will not be lost or overwritten.
*/
