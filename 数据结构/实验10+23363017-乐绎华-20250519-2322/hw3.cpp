#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <vector>
using namespace std;

// 哈夫曼树的结点结构
struct HuffmanNode {
    char data;              // 字符
    int frequency;          // 频率
    HuffmanNode* left;      // 左子结点
    HuffmanNode* right;     // 右子结点
    
    // 构造函数
    HuffmanNode(char data, int freq) : 
        data(data), frequency(freq), left(nullptr), right(nullptr) {}
    
    // 比较用于优先队列
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
};

// 自定义比较函数，用于优先队列
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// 计算字符频率
unordered_map<char, int> calculateFrequency(const string& text) {
    unordered_map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }
    return freqMap;
}

// 构建哈夫曼树
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    // 使用优先队列（小顶堆）
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    
    // 将所有叶子结点加入优先队列
    for (const auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // 构建哈夫曼树
    while (pq.size() > 1) {
        // 取出频率最小的两个结点
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        // 创建新的内部结点，频率为两个子结点的和
        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        
        // 将新结点放回优先队列
        pq.push(newNode);
    }
    
    // 返回树的根结点
    return pq.top();
}

// 生成哈夫曼编码
void generateCodes(HuffmanNode* root, const string& code, 
                  unordered_map<char, string>& codesMap) {
    if (root == nullptr) {
        return;
    }
    
    // 如果是叶子结点，添加编码到map
    if (root->left == nullptr && root->right == nullptr) {
        codesMap[root->data] = code;
    }
    
    // 递归左子树，编码添加'0'
    generateCodes(root->left, code + "0", codesMap);
    
    // 递归右子树，编码添加'1'
    generateCodes(root->right, code + "1", codesMap);
}

// 压缩文本
string compressText(const string& text, const unordered_map<char, string>& codesMap) {
    string compressed;
    for (char c : text) {
        compressed += codesMap.at(c);
    }
    return compressed;
}

// 解压缩文本
string decompressText(const string& compressed, HuffmanNode* root) {
    string decompressed;
    HuffmanNode* current = root;
    
    for (char bit : compressed) {
        // 根据位值选择左右分支
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        
        // 如果到达叶子结点，添加字符到结果，并重新从根开始
        if (current->left == nullptr && current->right == nullptr) {
            decompressed += current->data;
            current = root;
        }
    }
    
    return decompressed;
}

// 释放哈夫曼树内存
void freeHuffmanTree(HuffmanNode* root) {
    if (root == nullptr) {
        return;
    }
    
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

// 计算压缩比
double calculateCompressionRatio(const string& original, const string& compressed) {
    // 原始文本每个字符占8位
    double originalSize = original.length() * 8;
    double compressedSize = compressed.length();
    
    return (originalSize - compressedSize) / originalSize * 100.0;
}

// 将压缩后的二进制字符串转为字节串
vector<unsigned char> binaryStringToBytes(const string& binaryStr) {
    vector<unsigned char> bytes;
    for (size_t i = 0; i < binaryStr.length(); i += 8) {
        string byte = binaryStr.substr(i, 8);
        // 补齐不足8位的部分
        while (byte.length() < 8) {
            byte += '0';
        }
        bytes.push_back(static_cast<unsigned char>(bitset<8>(byte).to_ulong()));
    }
    return bytes;
}

// 打印哈夫曼编码表
void printHuffmanCodes(const unordered_map<char, string>& codesMap) {
    cout << "Huffman Code Table:" << endl;
    for (const auto& pair : codesMap) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }
    cout << endl;
}

int main() {
    // Example text (contains 26 English letters, can be replaced with file input)
    string text = "abcdefghijklmnopqrstuvwxyz";
    
    // Use a more representative sample text (with non-uniform frequencies)
    text = "the quick brown fox jumps over the lazy dog. "
           "this is a sample text to demonstrate huffman coding. "
           "efficient compression is achieved when character frequencies vary.";
    
    cout << "Original text size: " << text.length() << " bytes" << endl;
    
    // Calculate character frequencies
    unordered_map<char, int> freqMap = calculateFrequency(text);
    
    // Build Huffman tree
    HuffmanNode* root = buildHuffmanTree(freqMap);
    
    // Generate Huffman codes
    unordered_map<char, string> codesMap;
    generateCodes(root, "", codesMap);
    
    // Print Huffman codes
    printHuffmanCodes(codesMap);
    
    // Compress the text
    string compressed = compressText(text, codesMap);
    
    cout << "Compressed binary string (first 100 bits): " << compressed.substr(0, 100) << "..." << endl;
    cout << "Compressed bit length: " << compressed.length() << " bits"
         << " (" << (compressed.length() + 7) / 8 << " bytes)" << endl;
    
    // Decompress the text
    string decompressed = decompressText(compressed, root);
    
    // Verify decompression result
    cout << "Decompressed text (first 100 chars): " << decompressed.substr(0, 100) << endl;
    cout << "Is decompression correct: " << (text == decompressed ? "Yes" : "No") << endl;
    
    // Calculate and display compression ratio
    double compressionRatio = calculateCompressionRatio(text, compressed);
    cout << "Compression ratio: " << compressionRatio << "%" << endl;
    
    // Analyze average code length per character
    double totalBits = 0;
    int totalChars = 0;
    
    for (const auto& pair : freqMap) {
        totalBits += pair.second * codesMap[pair.first].length();
        totalChars += pair.second;
    }
    
    double avgBitsPerChar = totalBits / totalChars;
    cout << "Average bits per character: " << avgBitsPerChar << " bits" << endl;
    cout << "Savings compared to ASCII encoding (8 bits/char): " 
         << (8 - avgBitsPerChar) / 8 * 100 << "%" << endl;
    
    // Free Huffman tree memory
    freeHuffmanTree(root);
    
    return 0;
}
