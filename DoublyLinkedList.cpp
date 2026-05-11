// ========================================
// DoublyLinkedList.cpp
// - 이중(양방향) 연결 리스트 구현
// - STL 미사용 버전
// 
// - 각 노드는 Prev 포인터가 추가된다. -> 뒤로 갈 수 있음
// - 삭제 시 Prev를 따로 추적할 필요 없이 바로 접근이 가능하다
// ========================================

#include <iostream>

struct Node
{
	int Data;
	Node* Prev;
	Node* Next;
	Node(int InData)
		: Data(InData), Prev(nullptr), Next(nullptr)
	{
	}
};

class DoublyLinkedList
{
private:
	Node* Head;
	Node* Tail;
	int Size;

public:
	DoublyLinkedList()
		: Head(nullptr), Tail(nullptr), Size(0)
	{
	}

	~DoublyLinkedList()
	{
		while (Head != nullptr)
		{
			Node* Temp = Head;
			Head = Head->Next;
			delete Temp;
			Temp = nullptr;
		}
	}

	void PushFront(int InValue)
	{
		Node* NewNode = new Node(InValue);
		if (Head == nullptr)
		{
			Head = NewNode;
			Tail = NewNode;
		}
		else
		{
			NewNode->Next = Head;
			NewNode->Prev = NewNode;
			Head = NewNode;
		}
		++Size;
	}

	void PushBack(int InValue)
	{
		Node* NewNode = new Node(InValue);
		if (Tail == nullptr)
		{
			Head = NewNode;
			Tail = NewNode;
		}
		else
		{
			NewNode->Prev = Tail;
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
		if (InIndex == Size)
		{
			PushBack(InData);
			return;
		}

		Node* CurrentNode = Head;
		for (int i = 0; i < InIndex; ++i)
		{
			CurrentNode = CurrentNode->Next;
		}
		Node* NewNode = new Node(InData);
		NewNode->Prev = CurrentNode->Prev;
		NewNode->Next = CurrentNode;
		CurrentNode->Prev->Next = NewNode;
		CurrentNode->Prev = NewNode;
	}

	void PopFront()
	{
		if (Head == nullptr)
		{
			return;
		}
		Node* Temp = Head;
		if (Head == Tail)
		{
			Head = nullptr;
			Tail = nullptr;
		}
		else
		{
			Head = Head->Next;
			Head->Prev = nullptr;
		}
		delete Temp;
		Temp = nullptr;
		--Size;
	}

	void PopBack()
	{
		if (Head == nullptr)
		{
			return;
		}
		Node* Temp = Tail;
		if (Head == Tail)
		{
			Head = nullptr;
			Tail = nullptr;
		}
		else
		{
			Tail = Tail->Prev;
			Tail->Next = nullptr;
		}
		delete Temp;
		Temp = nullptr;
		--Size;
	}

	void Remove(int InIndex)
	{
		if (InIndex < 0 || InIndex > Size)
		{
			return;
		}
		if (InIndex == 0)
		{
			PopFront();
			return;
		}
		if (InIndex == Size)
		{
			PopBack();
			return;
		}
		Node* CurrentNode = Head;
		for (int i = 0; i < InIndex; ++i)
		{
			CurrentNode = CurrentNode->Next;
		}
		CurrentNode->Prev->Next = CurrentNode->Next;
		CurrentNode->Next->Prev = CurrentNode->Prev;
		delete CurrentNode;
		CurrentNode = nullptr;
	}

	int  Find(int InData)
	{
		Node* CurrentNode = Head;
		int Index = 0;
		while (CurrentNode != nullptr)
		{
			if (CurrentNode->Data == InData)
			{
				return Index;
			}
			CurrentNode = CurrentNode->Next;
			++Index;
		}
		return -1;
	}

	void Print()
	{
		Node* CurrentNode = Head;
		while (CurrentNode != nullptr)
		{
			std::cout << CurrentNode->Data << " ";
			CurrentNode = CurrentNode->Next;
		}
	}
};

int main()
{
	DoublyLinkedList List;
	List.PushBack(1);
	List.PushBack(2);
	List.PushBack(3);
	List.PushFront(0);
	List.Insert(4, 4);
	List.Print();
	std::cout << std::endl;
	List.Remove(2);
	List.Print();
	std::cout << std::endl;
	std::cout << "Find 3: " << List.Find(3) << std::endl;
	std::cout << "Find 5: " << List.Find(5) << std::endl;
	return 0;
}