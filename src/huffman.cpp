#include "huffman.hpp"

void  huffman::compress(const std::filesystem::path& decompressedFile,const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, decompressedFile);

    std::vector<char> buffer = fileManager.getbuffer();//build buffer

    FreqTable.buildUsingBuffer(buffer);//build FrequencyTable

    auto binaryTree = buildHuffmanTree();
}

void huffman::decompress(const std::filesystem::path& compressedFile, const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, compressedFile);
}

Node* huffman::buildHuffmanTree() {
    auto freqMap = FreqTable.getFrequencyMap();

    auto cmp = [](Node* left, Node* right) { return left->frequency > right->frequency; };

    std::priority_queue <Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

    for(auto [c,freq] : freqMap){
        Node* newNode = new Node(c,freq);

        pq.push(newNode);
    }

    while(pq.size() >= 2){

        Node* l = pq.top(); //get smallest frequency
        pq.pop(); //remove it from priority queue

        Node* r = pq.top(); //get second smallest frequency
        pq.pop(); //remove it from priority queue

        //combine the two nodes frequency
        Node* combineNode = new Node(l,r);

        pq.push(combineNode); //push it back to priority queue
    }

    return pq.top(); //return the root node
}