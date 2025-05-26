#include <iostream>
#include <fstream>
using namespace std;

struct HuffmanNode {
	char character;
	int freq;
	HuffmanNode* left,* right;
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

HuffmanNode* generateHuffmanTree(MinHeap* _minHeap ) {
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


void generateHuffmanCodes(HuffmanNode* root, string huffmanCodes[256] ,string currentCode) {

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

int main()
{
	string huffmanCodes[256] = {""};
	MinHeap* minHeap = new MinHeap();	
	string filePath = "test.txt";
	/*cout << "Enter File Path: ";
	cin >> filePath;*/
	getFrequenciesFromFile(filePath, minHeap);
	minHeap = testDisplayHeap(minHeap);
	HuffmanNode* huffmanTree = generateHuffmanTree(minHeap);
	generateHuffmanCodes(huffmanTree, huffmanCodes, "");

	for (int i = 0; i < 256; i++)
	{
		if (huffmanCodes[i] != "")
		{
			cout << "Charcter: " << (unsigned char)i << "\tCode: " << huffmanCodes[i] << endl;
		}
	}

	int n;
	cin >> n;
	delete minHeap;
	return 0;
}