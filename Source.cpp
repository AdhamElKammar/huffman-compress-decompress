#include <iostream>
using namespace std;

template <typename T> 
class MinHeap
{
	T* arr;
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
		T t = arr[i1];
		arr[i1] = arr[i2];
		arr[i2] = t;
	}

	void ensureHeapCapacity()
	{
		if (size < capacity)
			return;

		T* newArr = new (std::nothrow)T[capacity * 2];
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
			if (hasRightChild(index) && arr[getRightChildIndex(index)] <
				arr[smallestChildIndex])
			{
				smallestChildIndex = getRightChildIndex(index);
			}

			if (arr[index] < arr[smallestChildIndex])
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
		while (hasParent(index) && arr[getParentIndex(index)] >
			arr[index])
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
		arr = new (std::nothrow) T[capacity];
	}

	bool poll(T* item = NULL)
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
	void add(int item)
	{
		ensureHeapCapacity();

		arr[size] = item;
		size++;

		heapifyUp();
	}
};

int main()
{

	return 0;
}