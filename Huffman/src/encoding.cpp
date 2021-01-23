// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "pqueue.h"
#include <string>
#include "filelib.h"
// TODO: include any other headers you need

Map<int, int> buildFrequencyTable(istream& input) {
    // TODO: implement this function
    Map<int, int> freqTable;
    string temp_input;
    getline(input, temp_input);
    for (char temp_input: temp_input){
        freqTable[temp_input]++;
    }
    freqTable[256]++;

    return freqTable;          // this is just a placeholder so it will compile
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pq;

    for(int cha : freqTable){
        HuffmanNode* Node = new HuffmanNode;
        Node->character = cha;
        Node->count = freqTable[cha];
        Node ->zero = NULL;
        Node ->one = NULL;
        pq.enqueue(Node, Node->count);
    }

    while(pq.size()>1){
        HuffmanNode* left = pq.dequeue();
        HuffmanNode* right = NULL;
        if (!pq.isEmpty()){
            right = pq.dequeue();
        }
        HuffmanNode* next_Node = new HuffmanNode;
        next_Node->one = right;
        next_Node->zero = left;
        next_Node->count = left->count+right->count;
        next_Node->character = NOT_A_CHAR;
        pq.enqueue(next_Node, next_Node->count);
    }


    return pq.dequeue();   // this is just a placeholder so it will compile
}

void buildEncodingMapHelper(HuffmanNode* tree, Map<int, string>& encodingMap, string prefix){
    if (tree->character != NOT_A_CHAR){
        encodingMap[tree->character] = prefix;
    }
    if (tree->zero!=NULL){
         buildEncodingMapHelper(tree->zero, encodingMap, prefix+"0");
    }
    if (tree->one!=NULL){
        buildEncodingMapHelper(tree->one, encodingMap, prefix+"1");
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {

    Map<int, string> encodingMap;
    buildEncodingMapHelper(encodingTree, encodingMap, "");
    return encodingMap;            // this is just a placeholder so it will compile
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    string each_code;
    char character;

    while(input.get(character)){
        each_code = encodingMap[character];
        for (int i = 0; each_code[i] != '\0'; i++){
            output.writeBit(each_code[i]-'0');
    }
    }
    each_code = encodingMap[PSEUDO_EOF];
    for (int i = 0; each_code[i] != '\0'; i++) {
        output.writeBit(each_code[i]-'0');
    }

}

void untraverseTree(Map<string,int>& decodingMap, string prefix, HuffmanNode* encodingTree) {
    if (encodingTree->character != NOT_A_CHAR) { // LEAF
        decodingMap[prefix] = encodingTree->character;
    }
    if (encodingTree->zero != NULL) { // if character is NOT_A_CHAR
        untraverseTree(decodingMap, prefix+"0", encodingTree->zero);
    }
    if (encodingTree->one != NULL) { // if character is NOT_A_CHAR
        untraverseTree(decodingMap, prefix+"1", encodingTree->one);
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
     Map<string,int> decodingMap;
     string prefix = "";
     //Storing deodingMap
     untraverseTree(decodingMap, prefix, encodingTree);
     string bitreadStr = "";
     while (true) {
         //Reading Bit by Bit
         int bitreadInt = input.readBit();
         //Add the additional bit
         bitreadStr += integerToString(bitreadInt);
         // If the Deoding Map has the bitstr
         if (decodingMap.containsKey(bitreadStr)) {
             int character = decodingMap[bitreadStr];
             //Break if end of the line
             if (character == PSEUDO_EOF) {
                 break;
             }
             else {
                 //Found character
                 output.put(character);
                 bitreadStr = "";
             }
         }
     }
 }

void compress(istream& input, obitstream& output) {
    //input the input
    //Freq
    //Tree
    //Map
    //output
    /*header==map
      encode(input)*/
    Map<int, int> freq_table_c= buildFrequencyTable(input);
    HuffmanNode* Tree_c = buildEncodingTree(freq_table_c);
    Map<int, string> encod_map = buildEncodingMap (Tree_c);
    output<<freq_table_c;
    rewindStream(input);
    freeTree(Tree_c);




}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    Map<int, int> freq_table_c;
    input>>freq_table_c;
    cout<<freq_table_c;
    HuffmanNode* Tree_c = buildEncodingTree(freq_table_c);
    decodeData(input, Tree_c, output);
    freeTree(Tree_c);

}

void freeTree(HuffmanNode* node) {

    if (node == NULL) {
        return;
    }
    freeTree(node->zero);
    freeTree(node->one);
    delete node;

}
