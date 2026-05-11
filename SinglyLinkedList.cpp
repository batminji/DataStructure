// ========================================
// SinglyLinkedList.cpp
// - 싱글(단일) 연결 리스트 구현
// - STL 미사용 버전
// 
// - 각 노드는 데이터와 다음 노드를 가리키는 포인터만 가진다.
// 
// ========================================
#include <iostream>

struct Node
{
	int Data;
	Node* Next;
	Node(int InData) : Data(InData), Next(nullptr)
	{
	}
};

class SinglyLinkedList
{
private:
	Node* Head;
	Node* Tail;
	int Size;

public:
	SinglyLinkedList()
		: Head(nullptr), Size(0)
	{
	}

	~SinglyLinkedList()
	{
		while (Head != nullptr)
		{
			Node* Temp = Head;
			Head = Head->Next;
			delete Temp;
			Temp = nullptr;
		}
		// Head -> 1 -> 2 -> 3 -> nullptr
		// Temp -> Head -> 2 -> 3 -> nullptr
		// Temp -> Head -> 3 -> nullptr
		// ...
	}

	void PushFront(int InData)
	{
		Node* NewNode = new Node(InData);
		NewNode->Next = Head;
		Head = NewNode;
		++Size;
	}

	void PushBack(int InData)
	{
		Node* NewNode = new Node(InData);
		if (Head == nullptr)
		{
			Head = NewNode;
			Tail = NewNode;
		}
		else
		{
			Tail->Next = NewNode;
			Tail = NewNode;
		}
		++Size;
	}

	void Insert(int InData, int InIndex)
	{
		if (InIndex < 0 || InIndex > Size)
		{
			return;
		}
		if (InIndex == 0)
		{
			PushFront(InData);
			return;
		}

		Node* PrevNode = Head;
		for (int i = 0; i < InIndex - 1; ++i)
		{
			PrevNode = PrevNode->Next;
		}
		Node* NewNode = new Node(InData);
		NewNode->Next = PrevNode->Next;
		PrevNode->Next = NewNode;
		++Size;
	}

	void Remove(int InIndex)
	{
		if (InIndex < 0 || InIndex > Size)
		{
			return;
		}
		if (InIndex == 0)
		{
			Node* Temp = Head;
			Head = Head->Next;
			delete Temp;
			Temp = nullptr;
		}
		else
		{
			Node* PrevNode = Head;
			for (int i = 0; i < InIndex - 1; ++i)
			{
				PrevNode = PrevNode->Next;
			}
			Node* Temp = PrevNode->Next;
			PrevNode->Next = Temp->Next;
			delete Temp;
			Temp = nullptr;
		}
		--Size;
	}

	int Find(int InData)
	{
		Node* Current = Head;
		int Index = 0;
		while (Current != nullptr)
		{
			if (Current->Data == InData)
			{
				return Index;
			}
			Current = Current->Next;
			++Index;
		}

		return -1;
	}

	void PrintList()
	{
		Node* Current = Head;
		while (Current != nullptr)
		{
			std::cout << Current->Data << " -> ";
			Current = Current->Next;
		}
		std::cout << "nullptr" << std::endl;
	}

	inline int GetSize() const
	{
		return Size;
	}
};

int main()
{
	SinglyLinkedList List;
	List.PushBack(1);
	List.PushBack(2);
	List.PushBack(3);
	List.PrintList();

	List.Insert(0, 0);
	List.PrintList();
	List.Remove(1);
	List.PrintList();
	int Index = List.Find(2);

	std::cout << "Index of 2: " << Index << std::endl; // Output: Index of 2: 1
	return 0;
}