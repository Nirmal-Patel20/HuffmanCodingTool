#include "huffman.hpp"

void  huffman::compress(const std::filesystem::path& decompressedFile,const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, decompressedFile);

    std::vector<char> buffer = fileManager.getbuffer();//build buffer

    FreqTable.buildUsingBuffer(buffer);//build FrequencyTable

    binaryTreeRoot = buildHuffmanTree();//root of binarytree

    generateHuffmanCodes(binaryTreeRoot);

    std::vector<bool> bitstream = encode(buffer); //write encoded data to file

    fileManager.writeTohuffFile(bitstream, FreqTable.getFrequencyMap()); //write to huffman file

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

void huffman::generateHuffmanCodes(Node* Root, std::string prefix) {
    Node* current = Root;

    if(!current) return;

    if(!current->left && !current->right){
        huffmanCodes[current->symbol] = prefix;
    }

    generateHuffmanCodes(current->left, prefix + "0");
    generateHuffmanCodes(current->right, prefix + "1");
}

std::vector<bool> huffman::encode(std::vector<char>& buffer) const {
    std::vector<bool> encodeBits;

    for(const char& c : buffer){
        const std::string& prefix = huffmanCodes.at(c);
        for(char bit : prefix){
            encodeBits.push_back(bit == '1');
        }
    }

    return encodeBits;
}