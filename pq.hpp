#ifndef PQ_HPP
#define PQ_HPP

#include <iostream>
#include <vector>

class UnderflowException {};

template <class Type, class Compare>
class priority_queue
{
public:
	priority_queue();
	priority_queue(const priority_queue &r);
	priority_queue(const std::vector<Type> &v, int num = -1);
	~priority_queue();

	class iterator;
	friend class iterator;
	class reverse_iterator;
	friend class reverse_iterator;

	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

	int size() const;
	size_t capacity() const;
	bool empty() const;
	void makeEmpty();
	void push(const Type &item);
	void push(const std::vector<Type> &v, int num = -1);
	void print () const;
	void swap(priority_queue &r);
	const Type& top() const;
	void pop();
	void pop(Type &item);
	void pop(iterator &begin, iterator &end);

	priority_queue& operator=(const priority_queue<Type, Compare> &r);	
	bool operator==(const priority_queue<Type, Compare> &r);
	bool operator!=(const priority_queue<Type, Compare> &r);
	bool operator<(const priority_queue<Type, Compare> &r);
	bool operator>(const priority_queue<Type, Compare> &r);

	class iterator
	{
	public:
		iterator(priority_queue<Type, Compare> *a = 0, bool end = false);
	       	Type& operator*();
       		iterator operator++();
       		iterator operator++(int);
       		iterator operator--();
       		iterator operator--(int);
       		bool operator ==(const iterator &r);
		bool operator !=(const iterator &r);
	protected:
		int pos;
		priority_queue<Type, Compare> *ptr;
	};
	
	class reverse_iterator: public iterator
	{
	public:
		reverse_iterator(priority_queue<Type, Compare> *a = 0, bool end = false);
		reverse_iterator(const reverse_iterator &r);
		reverse_iterator operator++();
      	reverse_iterator operator++(int);
       	reverse_iterator operator--();
       	reverse_iterator operator--(int);
	};
	
	class const_iterator : public iterator
	{
	public:
		const_iterator (priority_queue<Type, Compare> *a = 0, bool end = false);
		const_iterator (const iterator &r);
		const Type& operator*() const;
	};
	
	class const_reverse_iterator : public reverse_iterator
	{
	public:
		const_reverse_iterator (priority_queue<Type, Compare> *a = 0, bool end = false);
		const_reverse_iterator (const reverse_iterator &r);
		const Type& operator* () const;
	};

private:
	void percolateDown(size_t hole);
	void buildHeap();
	size_t maxSize, actSize;
	Type *heap;
	Compare lessThan;
};

#include "pq_impl.hpp"

#endif /* PQ_HPP */
