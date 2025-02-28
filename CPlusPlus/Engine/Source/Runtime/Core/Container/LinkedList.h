#pragma once

#include "../Allocator/DefaultAllocator.h"



namespace Engine
{
	template<typename T, typename Allocator = DefaultAllocator<T>>
	class LinkedList
	{
	public:
		struct Node
		{
			Node* previous;
			Node* next;

			T storage;


			Void LinkBefore(Node* node);
			Void LinkAfter(Node* node);
			Void Unlink();


			static Node* Create();
			static Void Delete(Node* node);
		private:
			using NodeAllocator = typename Allocator::template Rebind<Node>::Other;
		};


		LinkedList();
		LinkedList(const LinkedList<T, Allocator>& other);
		LinkedList(LinkedList<T, Allocator>&& other);
		~LinkedList();


		Void Add(Node* node);
		Void InsertAt(SizeType index, Node* node);
		Void RemoveAt(SizeType index, Bool releaseOwnedResource = true);

		Void Clear();


		Node* GetHead() const;
		Node* GetTail() const;
		SizeType GetNodeCount() const;


		LinkedList<T, Allocator>& operator=(const LinkedList<T, Allocator>& other);
		LinkedList<T, Allocator>& operator=(LinkedList<T, Allocator>&& other);

		Node* operator[](SizeType index);
		const Node* operator[](SizeType index) const;
	public:
		class Iterator
		{
		public:
			Iterator(Node* node);


			LinkedList<T, Allocator>::Node& operator*();
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
		Node* head;
		Node* tail;

		SizeType nodeCount;
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
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::Node::Create()
	{
		Node* ret		= NodeAllocator().Allocate(1);
		ret->previous	= nullptr;
		ret->next		= nullptr;

		return ret;
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
	LinkedList<T, Allocator>::LinkedList(const LinkedList<T, Allocator>& other)
	{
		CopyFrom(other);
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::LinkedList(LinkedList<T, Allocator>&& other)
	{
		head = nullptr;
		tail = nullptr;

		SwapWith(other);
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
		{
			head = removed->next;
		}
		else if ( index == nodeCount - 1 )
		{
			tail = removed->previous;
		}

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
	LinkedList<T, Allocator>& LinkedList<T, Allocator>::operator=(const LinkedList<T, Allocator>& other)
	{
		Clear();
		CopyFrom(other);

		return *this;
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>& LinkedList<T, Allocator>::operator=(LinkedList<T, Allocator>&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::operator[](SizeType index)
	{
		ASSERT( index < nodeCount, "Index output of range" );


		if ( index + 1 < nodeCount - index )
		{
			Node* ret = head;

			SizeType begin	= 1;
			SizeType end	= index + 1;
			for (SizeType iteration = 1; iteration < end; iteration++)
				ret = ret->next;

			return ret;
		}
		else
		{
			Node* ret = tail;

			Int32 begin	= nodeCount - 1 - 1;
			Int32 end	= index - 1;
			for (Int32 iteration = begin; iteration > end; iteration--)
				ret = ret->previous;

			return ret;
		}
	}

	template<typename T, typename Allocator>
	const typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::operator[](SizeType index) const
	{
		ASSERT( index < nodeCount, "Index output of range" );


		if ( index + 1 < nodeCount - index )
		{
			Node* ret = head;

			SizeType begin	= 1;
			SizeType end	= index + 1;
			for (SizeType iteration = 1; iteration < end; iteration++)
				ret = ret->next;

			return ret;
		}
		else
		{
			Node* ret = tail;

			Int32 begin	= nodeCount - 1 - 1;
			Int32 end	= index - 1;
			for (Int32 iteration = begin; iteration > end; iteration--)
				ret = ret->previous;

			return ret;
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
			temporary->storage	= node.storage;

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