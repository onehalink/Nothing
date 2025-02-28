#pragma once

#include "../Template.h"

#include "../Allocator/DefaultAllocator.h"

#include "../Mathematics/NumericCalculation.h"



namespace Engine
{
	template<typename T, typename Allocator>
	class LinkedList
	{
	public:
		struct Node
		{
			Node*	next;
			T		element;
		

			static Node* Create();
			static Void Destroy(Node* node);
		private:
			using NodeAllocator = typename Allocator::template Rebind<Node>::Other;
		};


		LinkedList();
		LinkedList(const LinkedList<T, Allocator>& other);
		LinkedList(LinkedList<T, Allocator>&& other);
		~LinkedList();


		Void Add(Node* node);
		Void InsertAt(SizeType index, Node* node);
		Void RemoveAt(SizeType index);

		Void Clear();


		Node* GetHead() const;
		SizeType GetCount() const;


		LinkedList<T, Allocator>& operator=(const LinkedList<T, Allocator>& other);
		LinkedList<T, Allocator>& operator=(LinkedList<T, Allocator>&& other);

		Node* operator[](SizeType index);
		const Node* operator[](SizeType index) const;
	public:
		class Iterator
		{
		public:
			Iterator(Node* node);


			Node& operator*();
			Node* operator->();

			Iterator& operator++();
			Iterator operator++(Int32);

			Bool operator==(Iterator other) const;
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
	private:
		Node*		head;
		SizeType	count;
	};


#pragma region Details

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::Node::Create()
	{
		Node* ret = NodeAllocator().Allocate(1);
		ret->next = nullptr;

		return ret;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Node::Destroy(Node* node)
	{
		NodeAllocator().Deallocate(node, 1);
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::LinkedList()
		: head(nullptr), count(0)
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
		head	= other.head;
		count	= other.count;

		other.head = nullptr;
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>::~LinkedList()
	{
		Node* node = head;
		while (node)
		{
			Node* next = node->next;

			Node::Destroy(node);
			node = next;
		}
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Add(Node* node)
	{
		if ( count == 0 )
			head = node;
		else
			( *this )[ count - 1 ]->next = node;

		count++;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::InsertAt(SizeType index, Node* node)
	{
		if ( index == 0 )
		{
			node->next	= head;
			head		= node;
		}
		else
		{
			Node* previous = ( *this )[ index - 1 ];

			node->next		= previous->next;
			previous->next	= node;
		}

		count++;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::RemoveAt(SizeType index)
	{
		Node* removed;
		if ( index == 0 )
		{
			removed	= head;
			head	= removed->next;
		}
		else
		{
			Node* previous = ( *this )[ index - 1 ];

			removed			= previous->next;
			previous->next	= removed->next;
		}

		Node::Destroy(removed);
		count--;
	}

	template<typename T, typename Allocator>
	Void LinkedList<T, Allocator>::Clear()
	{
		this->~LinkedList();

		head	= nullptr;
		count	= 0;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::GetHead() const
	{
		return head;
	}

	template<typename T, typename Allocator>
	SizeType LinkedList<T, Allocator>::GetCount() const
	{
		return count;
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>& LinkedList<T, Allocator>::operator=(const LinkedList<T, Allocator>& other)
	{
		this->~LinkedList();
		CopyFrom(other);

		return *this;
	}

	template<typename T, typename Allocator>
	LinkedList<T, Allocator>& LinkedList<T, Allocator>::operator=(LinkedList<T, Allocator>&& other)
	{
		Swap( &head,	&other.head		);
		Swap( &count,	&other.count	);

		return *this;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::operator[](SizeType index)
	{
		Node* ret = head;
		for (SizeType iteration = 1; iteration <= index; iteration++)
			ret = ret->next;

		return ret;
	}

	template<typename T, typename Allocator>
	const typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::operator[](SizeType index) const
	{
		Node* ret = head;
		for (SizeType iteration = 1; iteration <= index; iteration++)
			ret = ret->next;

		return ret;
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
		count = 0;

		for (Node& node : other)
		{
			Node* temporary		= Node::Create();
			temporary->element	= node.element;

			Add(temporary);
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
	typename LinkedList<T, Allocator>::Node* LinkedList<T, Allocator>::Iterator::operator->()
	{
		return node;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Iterator& LinkedList<T, Allocator>::Iterator::operator++()
	{
		node = node->next;

		return *this;
	}

	template<typename T, typename Allocator>
	typename LinkedList<T, Allocator>::Iterator LinkedList<T, Allocator>::Iterator::operator++(Int32)
	{
		Iterator ret = *this;

		++( *this );

		return ret;
	}

	template<typename T, typename Allocator>
	Bool LinkedList<T, Allocator>::Iterator::operator==(Iterator other) const
	{
		return node == other.node;
	}

	template<typename T, typename Allocator>
	Bool LinkedList<T, Allocator>::Iterator::operator!=(Iterator other) const
	{
		return !operator==(other);
	}

#pragma endregion
}