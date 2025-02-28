#pragma once

#include "../CoreMinimal.h"

#include "../Iterator/Adapter.h"



namespace Engine::Template
{
	// Represents a doubly linked list
	template<typename A>
	class LinkedList
	{
	public:
		struct Node
		{
			using ElementType = typename A::ElementType;


			Node*		previous;
			Node*		next;
			ElementType	element;


			Void LinkBefore(Node* node);
			Void LinkAfter(Node* node);
			Void Unlink();

			static Node* Create();
			static Void Delete(Node* node);
		private:
			using NodeAllocatorType = typename A::template Rebind<Node>::Other;
		};


		using ThisType = LinkedList<A>;


		LinkedList();
		LinkedList(ThisType&& other);
		LinkedList(const ThisType& other);
		ThisType& operator=(ThisType&& other);
		ThisType& operator=(const ThisType& other);
		~LinkedList();


		Void Add(Node* node);
		Void InsertAt(SizeType index, Node* node);
		Void RemoveAt(SizeType index, Bool isNeedToDeleteNode = true);

		Void Clear();


		Node* GetHead();
		Node* GetTail();
		const Node* GetHead() const;
		const Node* GetTail() const;
		SizeType GetNodeCount() const;


		Node* operator[](SizeType index);
		const Node* operator[](SizeType index) const;
	public:
		template<typename NodeType>
		class IteratorBase
		{
		public:
			using ElementType	= typename NodeType::ElementType;
			using DistanceType	= Int32;


			IteratorBase(NodeType* node = nullptr) : node(node) {}


			ElementType& Dereference() const { return node->element; }
			Void Increment() { node = node->next; }
			Void Decrement() { node = node->previous; }
			Bool Equal(const IteratorBase<NodeType>& iterator) const { return node == iterator.node; }
		private:
			NodeType* node;
		};


		using Iterator		= Engine::Iterator::BidirectionalIteratorAdapter<IteratorBase<Node>>;
		using ConstIterator	= Engine::Iterator::BidirectionalIteratorAdapter<IteratorBase<const Node>>;


		Iterator begin();
		Iterator end();

		ConstIterator begin() const;
		ConstIterator end() const;
	private:
		Void SwapWith(ThisType&& other);
		Void CopyFrom(const ThisType& other);
	private:
		Node*		head;
		Node*		tail;
		SizeType	nodeCount;
	};

	
#pragma region Details

	template<typename A>
	Void LinkedList<A>::Node::LinkBefore(Node* node)
	{
		this->previous = node->previous;
		Node* previous = node->previous;
		if (previous)
			previous->next = this;

		this->next		= node;
		node->previous	= this;
	}

	template<typename A>
	Void LinkedList<A>::Node::LinkAfter(Node* node)
	{
		this->next = node->next;
		Node* next = node->next;
		if (next)
			next->previous = this;

		this->previous	= node;
		node->next		= this;
	}

	template<typename A>
	Void LinkedList<A>::Node::Unlink()
	{
		if (previous)
			previous->next = next;

		if (next)
			next->previous = previous;

		next = previous = nullptr;
	}

	template<typename A>
	typename LinkedList<A>::Node* LinkedList<A>::Node::Create()
	{
		Node* result		= NodeAllocatorType().Allocate(1);
		result->previous	= nullptr;
		result->next		= nullptr;

		return result;
	}

	template<typename A>
	Void LinkedList<A>::Node::Delete(Node* node)
	{
		NodeAllocatorType().Deallocate(node, 1);
	}

	template<typename A>
	LinkedList<A>::LinkedList()
		: head(nullptr), tail(nullptr), nodeCount(0)
	{

	}

	template<typename A>
	LinkedList<A>::LinkedList(ThisType&& other)
	{
		tail = head = nullptr;

		SwapWith(other);
	}

	template<typename A>
	LinkedList<A>::LinkedList(const ThisType& other)
	{
		CopyFrom(other);
	}

	template<typename A>
	typename LinkedList<A>::ThisType& LinkedList<A>::operator=(ThisType&& other)
	{
		SwapWith(other);

		return *this;
	}

	template<typename A>
	typename LinkedList<A>::ThisType& LinkedList<A>::operator=(const ThisType& other)
	{
		this->~LinkedList();
		CopyFrom(other);

		return *this;
	}

	template<typename A>
	LinkedList<A>::~LinkedList()
	{
		Clear();
	}

	template<typename A>
	Void LinkedList<A>::Add(Node* node)
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

		++nodeCount;
	}

	template<typename A>
	Void LinkedList<A>::InsertAt(SizeType index, Node* node)
	{
		ASSERT( index < nodeCount, "Index out of range" );

		if ( index == 0 )
		{
			node->LinkBefore(head);

			head = node;
		}
		else
		{
			node->LinkBefore( ( *this )[index] );
		}

		++nodeCount;
	}

	template<typename A>
	Void LinkedList<A>::RemoveAt(SizeType index, Bool isNeedToDeleteNode)
	{
		ASSERT( index < nodeCount, "Index out of range" );

		Node* removed = ( *this )[index];

		if ( index == 0 )
			head = removed->next;
		else if ( index == nodeCount - 1 )
			tail = removed->previous;

		removed->Unlink();
		--nodeCount;

		if (isNeedToDeleteNode)
			Node::Delete(removed);
	}

	template<typename A>
	Void LinkedList<A>::Clear()
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

	template<typename A>
	typename LinkedList<A>::Node* LinkedList<A>::GetHead()
	{
		return head;
	}

	template<typename A>
	typename LinkedList<A>::Node* LinkedList<A>::GetTail()
	{
		return tail;
	}

	template<typename A>
	const typename LinkedList<A>::Node* LinkedList<A>::GetHead() const
	{
		return const_cast<ThisType*>(this)->GetHead();
	}

	template<typename A>
	const typename LinkedList<A>::Node* LinkedList<A>::GetTail() const
	{
		return const_cast<ThisType*>(this)->GetTail();
	}

	template<typename A>
	SizeType LinkedList<A>::GetNodeCount() const
	{
		return nodeCount;
	}

	template<typename A>
	typename LinkedList<A>::Node* LinkedList<A>::operator[](SizeType index)
	{
		ASSERT( index < nodeCount, "Index out of range" );

		if ( index + 1 <= nodeCount / 2 )
		{
			Node* result = head;
			for (SizeType iteration = 1; iteration <= index; ++iteration)
				result = result->next;

			return result;
		}
		else
		{
			Node* result = tail;
			for (Int32 iteration = nodeCount - 2; iteration >= index; --iteration)
				result = result->previous;

			return result;
		}
	}

	template<typename A>
	const typename LinkedList<A>::Node* LinkedList<A>::operator[](SizeType index) const
	{
		return const_cast<ThisType*>(this)->operator[](index);
	}

	template<typename A>
	typename LinkedList<A>::Iterator LinkedList<A>::begin()
	{
		return { InPlace(), head };
	}

	template<typename A>
	typename LinkedList<A>::Iterator LinkedList<A>::end()
	{
		return { InPlace(), nullptr };
	}

	template<typename A>
	typename LinkedList<A>::ConstIterator LinkedList<A>::begin() const
	{
		return { InPlace(), head };
	}

	template<typename A>
	typename LinkedList<A>::ConstIterator LinkedList<A>::end() const
	{
		return { InPlace(), nullptr };
	}

	template<typename A>
	Void LinkedList<A>::SwapWith(ThisType&& other)
	{
		Swap( &head,		&other.head			);
		Swap( &tail,		&other.tail			);
		Swap( &nodeCount,	&other.nodeCount	);
	}

	template<typename A>
	Void LinkedList<A>::CopyFrom(const ThisType& other)
	{
		nodeCount = 0;

		for (const typename Node::ElementType& element : other)
		{
			Node* temporary		= Node::Create();
			temporary->element	= element;

			Add(temporary);
		}
	}

#pragma endregion
}


namespace Engine
{
	template<typename T>
	using LinkedList = Template::LinkedList<DefaultAllocator<T>>;
}