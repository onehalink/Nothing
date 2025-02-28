#pragma once

#include "../CoreMinimal.h"



namespace Engine
{
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class LinkedList
	{
	public:
		struct Node
		{
			Node*	previous;
			Node*	next;

			T		value;


			Void LinkBefore(Node* node);
			Void LinkAfter(Node* node);
			Void Unlink();


			static Node* Create();
			static Void Delete(Node* node);
		private:
			using NodeAllocator = typename Allocator::template Rebind<Node>::Other;
		};


		LinkedList();
		LinkedList(LinkedList<T, Allocator>&& other);
		LinkedList(const LinkedList<T, Allocator>& other);
		~LinkedList();


		Void Add(Node* node);
		Void InsertAt(SizeType index, Node* node);
		Void RemoveAt(SizeType index, Bool releaseOwnedResource = true);

		Void Clear();


		Node* GetHead() const;
		Node* GetTail() const;
		SizeType GetNodeCount() const;


		LinkedList<T, Allocator>& operator=(LinkedList<T, Allocator>&& other);
		LinkedList<T, Allocator>& operator=(const LinkedList<T, Allocator>& other);

		Node* operator[](SizeType index);
		const Node* operator[](SizeType index) const;
	public:
		class Iterator
		{
		public:
			Iterator(Node* node);


			Node& operator*();
			Iterator& operator++();
			Iterator& operator--();
			Bool operator!=(Iterator other) const;
		private:
			Node* node;
		};


		Iterator begin();
		Iterator end();

		const Iterator begin() const;
		const Iterator end() const;
	private:
		Void CopyFrom(const LinkedList<T, Allocator>& other);
		Void SwapWith(LinkedList<T, Allocator>& other);
	private:
		Node*		head;
		Node*		tail;

		SizeType	nodeCount;
	};


#pragma region Details

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Node::LinkBefore(Node* node)
	{
		this->previous = node->previous;
		Node* previous = node->previous;
		if (previous)
			previous->next = this;

		this->next		= node;
		node->previous	= this;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Node::LinkAfter(Node* node)
	{
		this->next = node->next;
		Node* next = node->next;
		if (next)
			next->previous = this;

		this->previous	= node;
		node->next		= this;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Node::Unlink()
	{
		if (previous)
			previous->next = next;

		if (next)
			next->previous = previous;

		next = previous	= nullptr;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::Node::Create()
	{
		Node* result		= NodeAllocator().Allocate(1);
		result->previous	= nullptr;
		result->next		= nullptr;

		return result;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Node::Delete(Node* node)
	{
		NodeAllocator().Deallocate(node, 1);
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::LinkedList()
		: head(nullptr), tail(nullptr), nodeCount(0)
	{

	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::LinkedList(LinkedList<T, Allocator>&& other)
	{
		tail = head = nullptr;

		SwapWith(other);
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::LinkedList(const LinkedList<T, Allocator>& other)
	{
		CopyFrom(other);
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::~LinkedList()
	{
		Clear();
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Add(Node* node)
	{
		if ( nodeCount == 0 )
		{
			head = tail = node;
		}
		else
		{
			node->LinkAfter(tail);

			tail = node;
		}

		nodeCount++;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::InsertAt(SizeType index, Node* node)
	{
		if ( index == 0 )
		{
			node->LinkBefore(head);

			head = node;
		}
		else
		{
			node->LinkBefore( ( *this )[index] );
		}

		nodeCount++;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::RemoveAt(SizeType index, Bool releaseOwnedResource)
	{
		Node* removed = ( *this )[index];

		if ( index == 0 )
			head = removed->next;
		else if ( index == nodeCount - 1 )
			tail = removed->previous;

		removed->Unlink();
		nodeCount--;

		if (releaseOwnedResource)
			Node::Delete(removed);
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Clear()
	{
		Node* node = head;
		while (node)
		{
			Node* next = node->next;

			Node::Delete(node);

			node = next;
		}

		head = tail = nullptr;
		
		nodeCount = 0;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::GetHead() const
	{
		return head;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::GetTail() const
	{
		return tail;
	}

	template<typename T, typename Allocator>
	SizeType LinkedList<T, Allocator>::GetNodeCount() const
	{
		return nodeCount;
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>& LinkedList<T, Allocator>::operator=(LinkedList<T, Allocator>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>& LinkedList<T, Allocator>::operator=(const LinkedList<T, Allocator>& other)
	{
		Clear();
		CopyFrom(other);

		return *this;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::operator[](SizeType index)
	{
		if ( index + 1 <= nodeCount / 2 )
		{
			Node* result = head;
			for (SizeType iteration = 1; iteration <= index; iteration++)
				result = result->next;

			return result;
		}
		else
		{
			Node* result = tail;
			for (Int32 iteration = nodeCount - 2; iteration >= index; iteration--)
				result = result->previous;

			return result;
		}
	}

	template<typename T, typename Allocator>
	const typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::operator[](SizeType index) const
	{
		if ( index + 1 <= nodeCount / 2 )
		{
			Node* result = head;
			for (SizeType iteration = 1; iteration <= index; iteration++)
				result = result->next;

			return result;
		}
		else
		{
			Node* result = tail;
			for (Int32 iteration = nodeCount - 2; iteration >= index; iteration--)
				result = result->previous;

			return result;
		}
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::Iterator::Iterator(Node* node)
		: node(node)
	{

	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node& LinkedList<T, Allocator>::Iterator::operator*()
	{
		return *node;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Iterator& LinkedList<T, Allocator>::Iterator::operator++()
	{
		node = node->next;

		return *this;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Iterator& LinkedList<T, Allocator>::Iterator::operator--()
	{
		node = node->previous;

		return *this;
	}

	template<typename T, typename Allocator>
	Bool LinkedList<T, Allocator>::Iterator::operator!=(Iterator other) const
	{
		return node != other.node;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Iterator LinkedList<T, Allocator>::begin()
	{
		return head;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Iterator LinkedList<T, Allocator>::end()
	{
		return nullptr;
	}

	template<typename T, typename Allocator>
	const typename LinkedList<T, Allocator>::Iterator LinkedList<T, Allocator>::begin() const
	{
		return head;
	}

	template<typename T, typename Allocator>
	const typename LinkedList<T, Allocator>::Iterator LinkedList<T, Allocator>::end() const
	{
		return nullptr;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::CopyFrom(const LinkedList<T, Allocator>& other)
	{
		for (const Node& node : other)
		{
			Node* temporary		= Node::Create();
			temporary->value	= node.value;

			Add(temporary);
		}
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::SwapWith(LinkedList<T, Allocator>& other)
	{
		Swap( &head,		&other.head			);
		Swap( &tail,		&other.tail			);
		Swap( &nodeCount,	&other.nodeCount	);
	}

#pragma endregion
}