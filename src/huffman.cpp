#include "huffman.hpp"

void  huffman::compress(const std::filesystem::path& decompressedFile,const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, decompressedFile);

    std::vector<char> buffer = fileManager.getbuffer();//build buffer

    FreqTable.buildUsingBuffer(buffer);//build FrequencyTable

    binaryTreeRoot = buildHuffmanTree();//root of binarytree

    generateHuffmanCodes(binaryTreeRoot); //generate huffman codes

    std::vector<bool> bitstream = encode(buffer); //write encoded data to file

    fileManager.writeTohuffFile(bitstream, FreqTable.getFrequencyMap()); //write to huffman file

}

void huffman::decompress(const std::filesystem::path& compressedFile, const std::filesystem::path& outputFile) {
    fileManager fileManager(compressedFile, outputFile);

    auto freqAndBits = fileManager.readFromhuffFile();//get frequencyTable and bit stream

    const auto& bitstream = freqAndBits.second; //get bitstream

    FreqTable.setFrequencyMap(freqAndBits.first); //set frequency map

    binaryTreeRoot = buildHuffmanTree();//root of binarytree.\build\ninja-release\HuffmanCodingTool.exe --decompress "data/semple.huff"  

    auto decodedChars = decode(bitstream); //decode the bitstream
}

Node* huffman::buildHuffmanTree() {
    auto freqMap = FreqTable.getFrequencyMap();

    auto cmp = [](Node* left, Node* right) {
    if (left->frequency == right->frequency){
        return left->symbol > right->symbol; // tie-breaker: smaller char goes first
    }
    return left->frequency > right->frequency;};

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

void huffman::generateHuffmanCodes(Node* Root, std::vector<bool> codeSofar) {
    if (!Root) return;

    if (!Root->left && !Root->right) { // leaf node
        huffmanCodes[Root->symbol] = codeSofar;
        return;
    }

    if (Root->left) {
        auto leftCode = codeSofar;
        leftCode.push_back(false); // 0 for left
        generateHuffmanCodes(Root->left, leftCode);
    }

    if (Root->right) {
        auto rightCode = codeSofar;
        rightCode.push_back(true); // 1 for right
        generateHuffmanCodes(Root->right, rightCode);
    }
}

std::vector<bool> huffman::encode(const std::vector<char>& buffer) const {
    std::vector<bool> encodeBits;

    for (const char& c : buffer) {
        const auto& prefix = huffmanCodes.at(c);
        encodeBits.insert(encodeBits.end(), prefix.begin(), prefix.end());
    }

    return encodeBits;
}

std::vector<char> huffman::decode(const std::vector<bool>& bitstream) const {
    std::vector<char> decodedChars;
    Node* currentNode = binaryTreeRoot;

    for (bool bit : bitstream) {

        (bit == 0) ? currentNode = currentNode->left : currentNode = currentNode->right;

        // If we reach a leaf node, append the character and reset to root
        if (!currentNode->left && !currentNode->right) {
            decodedChars.push_back(currentNode->symbol);
            currentNode = binaryTreeRoot;
        }
    }

    return decodedChars;
}