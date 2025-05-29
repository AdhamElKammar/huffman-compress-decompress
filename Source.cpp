#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

struct HuffmanNode {
	unsigned char character;
	int freq;
	HuffmanNode* left, * right;
	HuffmanNode() {
		character = NULL;
		freq = 0;
		left = NULL;
		right = NULL;
	}
	HuffmanNode(char _character, int _freq) {
		character = _character;
		freq = _freq;
		left = NULL;
		right = NULL;
	}
};

//template <typename T> 
class MinHeap
{
	HuffmanNode* arr;
	int size; //actual size
	int capacity; //Max Cap


	int getLeftChildIndex(int parentIndex)
	{
		return 2 * parentIndex + 1;
	}
	int getRightChildIndex(int parentIndex)
	{
		return 2 * parentIndex + 2;
	}
	int getParentIndex(int childIndex)
	{
		return (childIndex - 1) / 2;
	}

	bool hasLeftChild(int parentIndex)
	{
		if (getLeftChildIndex(parentIndex) < size)
			return true;
		return false;
	}
	bool hasRightChild(int parentIndex)
	{
		if (getRightChildIndex(parentIndex) < size)
			return true;
		return false;
	}

	bool hasParent(int childIndex)
	{
		if (getParentIndex(childIndex) >= 0)
			return true;
		return false;
	}

	void swap(int i1, int i2)
	{
		HuffmanNode t = arr[i1];
		arr[i1] = arr[i2];
		arr[i2] = t;
	}

	void ensureHeapCapacity()
	{
		if (size < capacity)
			return;

		HuffmanNode* newArr = new (std::nothrow)HuffmanNode[capacity * 2];
		if (newArr != NULL)
		{
			capacity *= 2;
			for (int i = 0; i < size; i++)
				newArr[i] = arr[i];

			delete[] arr;
			arr = newArr;
		}
	}

	void heapifyDown()
	{
		int index = 0;
		while (hasLeftChild(index))
		{
			int smallestChildIndex = getLeftChildIndex(index);
			if (hasRightChild(index) && arr[getRightChildIndex(index)].freq <
				arr[smallestChildIndex].freq)
			{
				smallestChildIndex = getRightChildIndex(index);
			}

			if (arr[index].freq < arr[smallestChildIndex].freq)
				break;

			else
			{
				swap(index, smallestChildIndex);
				index = smallestChildIndex;
			}
		}
	}
	void heapifyUp()
	{
		int index = size - 1;
		while (hasParent(index) && arr[getParentIndex(index)].freq >
			arr[index].freq)
		{
			swap(getParentIndex(index), index);
			index = getParentIndex(index);
		}
	}

public:
	MinHeap()
	{
		capacity = 10;
		size = 0;
		arr = new (nothrow) HuffmanNode[capacity];
	}

	~MinHeap()
	{
		delete[] arr;
	}

	int getSize()
	{
		return size;
	}

	bool poll(HuffmanNode* item = NULL)
	{
		if (size == 0)
			return false;

		if (item != NULL)
			*item = arr[0];

		arr[0] = arr[size - 1];
		size--;
		heapifyDown();
		return true;
	}
	void add(HuffmanNode* item)
	{
		ensureHeapCapacity();

		arr[size] = *item;
		size++;

		heapifyUp();
	}
};
void getFrequenciesFromFile(string _filePath, MinHeap* _minHeap)
{
	// Array to store frequencies
	long long arr[256] = { 0 };
	// Open file in binary mode
	ifstream file(_filePath, ios::binary);
	if (!file.is_open()) {
		cout << "File not found" << endl;
		return;
	}

	// Read file character by character and add frequencies to freq array
	char c;
	while (file.get(c)) {
		arr[(unsigned char)c]++;
	}
	file.close();

	// Creating the priority queue of huffman nodes
	for (int i = 0; i < 256; i++) {
		if (arr[i] > 0) {
			_minHeap->add(new HuffmanNode(i, arr[i]));

		}
	}
}

HuffmanNode* generateHuffmanTree(MinHeap* _minHeap) {
	while (_minHeap->getSize() > 1)
	{
		//Allocate the two nodes
		HuffmanNode* node1 = new HuffmanNode();

		HuffmanNode* node2 = new HuffmanNode();

		//Poll two nodes from heap
		_minHeap->poll(node1);

		_minHeap->poll(node2);


		//Link parent node with the two nodes
		HuffmanNode* parent = new HuffmanNode();

		parent->left = node1;

		parent->right = node2;

		//Parent node character is a random character up to 255
		parent->character = 0;

		//Parent node freq is sum of two linked nodes
		parent->freq = node1->freq + node2->freq;

		//Add to heap again and iterate over the process
		_minHeap->add(parent);
	}

	HuffmanNode* rootHuffman = new HuffmanNode();
	_minHeap->poll(rootHuffman);
	return rootHuffman;
}


void generateHuffmanCodes(HuffmanNode* root, string huffmanCodes[256], string currentCode) {

	if (root == nullptr) return;

	// Leaf node represents a character.
	if (root->left == nullptr && root->right == nullptr) {
		huffmanCodes[root->character] = currentCode;
		return;
	}

	generateHuffmanCodes(root->left, huffmanCodes, currentCode + '0');

	generateHuffmanCodes(root->right, huffmanCodes, currentCode + '1');
}

MinHeap* testDisplayHeap(MinHeap* _minHeap)
{
	HuffmanNode node;
	MinHeap* tempHeap = new MinHeap();
	int count = _minHeap->getSize();
	for (int i = 0; i < count; i++)
	{
		// For testing purposes we dont want the original heap to poll, we just want to display
		_minHeap->poll(&node);
		tempHeap->add(&node);
		char ch = node.character;
		if (ch == ' ') {
			cout << "Character: [SPACE]";
		}
		else if (ch == '\n') {
			cout << "Character: '\\n'";
		}
		else if (ch == '\t') {
			cout << "Character: [TAB]";
		}
		else if (ch >= 32 && ch <= 126) {  // Printable ASCII
			cout << "Character: '" << ch << "'";
		}
		else {
			cout << "Character: [ASCII " << (int)(unsigned char)ch << "]";
		}
		cout << "   Frequency: " << node.freq << endl;
	}

	_minHeap = tempHeap;
	return _minHeap;
}
void testDisplayCodes(const string huffmanCodes[256])
{
	cout << "======== Huffman Codes ========" << endl;

	// Count how many codes we have
	int codesCount = 0;
	for (int i = 0; i < 256; i++) {
		if (huffmanCodes[i] != "") {
			codesCount++;
		}
	}

	cout << "Total unique characters: " << codesCount << endl << endl;

	// Display each code with formatting
	for (int i = 0; i < 256; i++) {
		if (huffmanCodes[i] != "") {
			unsigned char ch = i;
			// Format character display similar to testDisplayHeap
			if (ch == ' ') {
				cout << "Character: [SPACE]";
			}
			else if (ch == '\n') {
				cout << "Character: '\\n'";
			}
			else if (ch == '\t') {
				cout << "Character: [TAB]";
			}
			else if (ch >= 32 && ch <= 126) {  // Printable ASCII
				cout << "Character: '" << ch << "'";
			}
			else {
				cout << "Character: [ASCII " << (int)ch << "]";
			}

			// Print code and code length for analysis
			cout << "   Code: " << huffmanCodes[i]
				<< "   Length: " << huffmanCodes[i].length() << endl;
		}
	}
	cout << "===============================" << endl;
}

// Function to serialize the Huffman tree to a file for compression
void serializeTree(HuffmanNode* root, ofstream& output) {
	if (!root) {
		output.put(0); // Null marker
		return;
	}

	if (root->left == nullptr && root->right == nullptr) {
		output.put('1'); // Leaf marker
		output.put(root->character); // Character
	}
	else {
		output.put('2'); // Internal node marker
		serializeTree(root->left, output);
		serializeTree(root->right, output);
	}
}

// Function to deserialize the Huffman tree from a file for decompression
HuffmanNode* deserializeTree(ifstream& input) {
	char marker;
	input.get(marker);

	if (marker == '1') { // Leaf
		char data;
		input.get(data);
		return new HuffmanNode(data, 0);
	}
	else if (marker == '2') { // Internal
		HuffmanNode* node = new HuffmanNode('\0', 0);
		node->left = deserializeTree(input);
		node->right = deserializeTree(input);
		return node;
	}
	return nullptr;
}

void compress(HuffmanNode* _huffmanTree, string huffmanCodes[256], string _filePath)
{



	ifstream file(_filePath, ios::binary);
	if (!file.is_open())
	{
		cout << "Couldn't find input file";
		return;
	}
	// GET ORIGINAL FILE SIZE FIRST
	file.seekg(0, ios::end);
	long long originalSize = file.tellg();
	file.seekg(0, ios::beg);

	int dotIndex = _filePath.find('.');
	int lastBackSlashIndex = _filePath.find_last_of("\\/");
	string directory = _filePath.substr(0, lastBackSlashIndex + 1);
	string fileExtension = _filePath.substr(dotIndex, _filePath.length() - dotIndex);

	string _outputFilePath = "output" + fileExtension + ".ece2103";

	ofstream output(directory +  _outputFilePath, ios::binary);
	ofstream outputCodes(directory + "codes.cod", ios::binary);

	if (!output.is_open())
	{
		cout << "Couldn't create output file";
		return;
	}
	if (!outputCodes.is_open())
	{
		cout << "Couldn't create output codes file";
		return;
	}
	// Write the original size to output file
	output.write(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

	//Serialize the Huffman tree to the output file
	serializeTree(_huffmanTree, outputCodes);

	string curr = "";
	char c;

	// read input file character by character
	while (file.get(c))
	{
		string huffmanCode = huffmanCodes[(unsigned char)c];

		// process single bit in huffman code
		for (char bit : huffmanCode)
		{
			curr += bit;

			// when we have 8 bits, convert to byte and we write to outfut file
			if (curr.length() == 8)
			{
				bitset<8> bits(curr);
				unsigned char byte = (unsigned char)(bits.to_ulong());
				output.put(byte);
				curr = "";
			}
		}
	}

	// Handle padding
	if (!curr.empty())
	{
		// Pad with zeros at the end
		while (curr.length() < 8)
		{
			curr += '0';
		}

		bitset<8> bits(curr);
		unsigned char byte = (unsigned char)(bits.to_ulong());
		output.put(byte);
	}

	file.close();
	output.close();
	cout << "Compression complete. Output file: " << _outputFilePath << endl;
	cout << "Original file size: " << originalSize << " bytes" << endl;
}
void decompress(string _filePath, string _codesFilePath)
{
	ifstream file(_filePath, ios::binary);
	if (!file.is_open())
	{
		cout << "Couldn't find input file";
		return;
	}

	int lastBackSlashIndex = _filePath.find_last_of("\\/");
	string directory = _filePath.substr(0, lastBackSlashIndex + 1);

	ifstream codesFile(directory + _codesFilePath, ios::binary);

	if (!codesFile.is_open())
	{
		cout << "Couldn't find codes file";
		return;
	}
	// Read original size
	long long originalSize;
	if (!file.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize))) {
		cout << "Error: Could not read original file size" << endl;
		return;
	}

	cout << "Expected to decompress " << originalSize << " bytes" << endl;
	HuffmanNode* huffmanTree = deserializeTree(codesFile);
	if (!huffmanTree) {
		cout << "Error: Failed to deserialize Huffman tree" << endl;
		return;
	}

	//output filename
	cout << _filePath.length() << endl << endl;

	cout << _filePath << endl << endl;
	int dotIndex = _filePath.find_last_of('.');
	cout << dotIndex << endl << endl;

	string baseFileName = _filePath.substr(lastBackSlashIndex + 1, dotIndex - (lastBackSlashIndex + 1));
	cout << baseFileName << endl;
	string outputFileName = "decompressed_" + baseFileName;

	//cout << directory + outputFileName << endl;
	ofstream output(directory + outputFileName, ios::binary);
	if (!output.is_open())
	{
		cout << "Couldn't create output file";
		return;
	}
	HuffmanNode* currentNode = huffmanTree;
	char byte;
	long long decodedCount = 0;
	while (file.get(byte) && decodedCount < originalSize)
	{
		bitset<8> bits(byte);
		for (int i = 7; i >= 0; i--)
		{
			if (bits[i] == 0)
			{
				currentNode = currentNode->left;
			}
			else if (bits[i] == 1)
			{
				currentNode = currentNode->right;
			}

			// Check if we've reached a leaf node
			if (currentNode && currentNode->left == nullptr && currentNode->right == nullptr)
			{
				output.put(currentNode->character);
				decodedCount++;
				currentNode = huffmanTree;  // Reset to root
				// Progress indicator for large files - El AI oltlto y3mlha
				if (decodedCount % 1000 == 0) {
					cout << "Decoded: " << decodedCount << "/" << originalSize << " bytes\r" << flush;
				}
				// Stope when we decoded all original chars
				if (decodedCount >= originalSize) {
					break;
				}
			}

			// Safety check
			if (!currentNode) {
				cout << "Error: Invalid tree traversal";
				break;
			}
		}
	}
	file.close();
	codesFile.close();
	output.close();
	cout << "\nDecompression complete!" << endl;
	cout << "Output file: " << outputFileName << endl;
	cout << "Decoded " << decodedCount << " characters (expected: " << originalSize << ")" << endl;

	if (decodedCount == originalSize) {
		cout << "SUCCESS: File decompressed correctly!" << endl;
	}
	else {
		cout << "WARNING: Decoded count doesn't match expected size!" << endl;
	}

	delete huffmanTree;

}

int main(int argc, char* argv[])
{
	if (argc != 3)  
	{
		cout << "Error in arguments! " << endl;
		return -1;
	}

	string command = argv[1];
	string filename = argv[2];

	if (command == "-c")
	{
		// Compression
		string huffmanCodes[256] = { "" };
		MinHeap* minHeap = new MinHeap();

		getFrequenciesFromFile(filename, minHeap);  // Use argv[2]
		minHeap = testDisplayHeap(minHeap);
		HuffmanNode* huffmanTree = generateHuffmanTree(minHeap);
		generateHuffmanCodes(huffmanTree, huffmanCodes, "");
		testDisplayCodes(huffmanCodes);

		compress(huffmanTree, huffmanCodes, filename);

		delete minHeap;
	}
	else if (command == "-d")
	{
		decompress(filename, "codes.cod");
	}
	else
	{
		cout << "Invalid command. Use -c for compress or -d for decompress followed by filename" << endl;
		return -1;
	}

	return 0;
}