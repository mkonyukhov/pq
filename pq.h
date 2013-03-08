#ifndef PQ_H
#define PQ_H

#include <iostream>
#include <vector>

using namespace std;

class UnderflowException{};

template <class Type, class Compare>
class myPQueue
{
public:
	myPQueue();
	myPQueue(const myPQueue &r);
	myPQueue(const vector<Type> &v, int num = -1);
	~myPQueue();

	class iterator;
    friend class iterator;
    class reverse_iterator;
    friend class reverse_iterator;

	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

	int size() const;
	int capacity() const;
	bool empty() const;
	void makeEmpty();
	void push(const Type &item);
	void push(const vector<Type> &v, int num = -1);
	void print () const;
	void swap(myPQueue &r);
	const Type& top() const;
	void pop();
	void pop(Type &item);
	void pop(iterator &begin, iterator &end);

	myPQueue& operator=(const myPQueue<Type, Compare> &r);	
	bool operator==(const myPQueue<Type, Compare> &r);
	bool operator!=(const myPQueue<Type, Compare> &r);
	bool operator<(const myPQueue<Type, Compare> &r);
	bool operator>(const myPQueue<Type, Compare> &r);

	class iterator
	{
	public:
		iterator(myPQueue<Type, Compare> *a = 0, bool end = false);
       	Type& operator*();
       	iterator operator++();
       	iterator operator++(int);
       	iterator operator--();
       	iterator operator--(int);
       	bool operator ==(const iterator &r);
       	bool operator !=(const iterator &r);
    protected:
       	int pos;
       	myPQueue<Type, Compare> *ptr;
	};
	
	class reverse_iterator: public iterator
	{
	public:
		reverse_iterator(myPQueue<Type, Compare> *a = 0, bool end = false);
		reverse_iterator(const reverse_iterator &r);
		reverse_iterator operator++();
      	reverse_iterator operator++(int);
       	reverse_iterator operator--();
       	reverse_iterator operator--(int);
	};
	
	class const_iterator : public iterator
	{
	public:
		const_iterator (myPQueue<Type, Compare> *a = 0, bool end = false);
		const_iterator (const iterator &r);
		const Type& operator*() const;
	};
	
	class const_reverse_iterator : public reverse_iterator
	{
	public:
		const_reverse_iterator (myPQueue<Type, Compare> *a = 0, bool end = false);
		const_reverse_iterator (const reverse_iterator &r);
		const Type& operator* () const;
	};

private:
	void percolateDown(int hole);
	void buildHeap();
	int maxSize, actSize;
	Type *heap;
	Compare lessThan;
};

template<class Type, class Compare>
inline myPQueue<Type, Compare>::myPQueue()
	: maxSize(16), actSize(0), lessThan(Compare())
	{ heap = new Type[maxSize]; }

template<class Type, class Compare>
inline myPQueue<Type, Compare>::myPQueue(const myPQueue &r)
	: lessThan(Compare())
{
	heap = new Type [maxSize = r.maxSize];
	actSize = r.actSize;
	for(int i = 0; i <= actSize; i++) heap[i] = r.heap[i];
}

template<class Type, class Compare>
inline myPQueue<Type, Compare>::myPQueue(const vector<Type> &v, int num)
	: lessThan(Compare())
{
	num < 0 ? actSize = v.size() : actSize = num;
	num < 0 ? maxSize = 2 * v.size() + 1 : maxSize = 2 * num + 1; 
	heap = new Type[maxSize];
	for(int i = 0; i < actSize; ++i) heap[i+1] = v[i];
	buildHeap();
}

template<class Type, class Compare>
inline myPQueue<Type, Compare>::~myPQueue()
	{ delete[] heap; }

template<class Type, class Compare>
inline int myPQueue<Type, Compare>::size() const
	{ return actSize; }

template<class Type, class Compare>
inline int myPQueue<Type, Compare>::capacity() const
	{ return maxSize; }

template<class Type, class Compare>
inline bool myPQueue<Type, Compare>::empty() const
	{ return !(bool)actSize; }

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::makeEmpty()
	{ actSize = 0; }

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::push(const Type &item)
{
	heap[0] = item;
	
	if(actSize + 1 == maxSize)
	{
		Type *tmp = new Type[maxSize *= 2];
		for(int i = 0; i <= actSize; ++i) tmp[i] = heap[i];
		delete[] heap;
		heap = tmp;
	}
	
	int hole = ++actSize;
	for(; lessThan(item, heap[hole / 2]); hole /= 2) heap[hole] = heap[hole / 2];
	heap[hole] = item;
}

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::push(const vector<Type> &v, int num)
{
	int cur = actSize;
	num < 0 ? actSize += v.size() : actSize += num;
	if(actSize + 1 >= maxSize)
	{
		Type *tmp = new Type[maxSize += 2 * actSize];
		for(int i = 0; i <= actSize; ++i) tmp[i] = heap[i];
		delete[] heap;
		heap = tmp;
	}
	
	for(int i = cur; i < actSize; ++i) heap[i+1] = v[i];
	buildHeap();
}

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::print() const
{
	cout << "_________________________\n";
	for(int i = 1; i <= actSize; i++) {
		cout << heap[i] << '\t';
		if (((i+1) & i) == 0) cout << '\n';
	}
	cout << "\n_________________________\n";
}

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::swap(myPQueue &r)
{
	myPQueue t(r);
	r = *this;
	*this = t;
}

template<class Type, class Compare>
inline const Type& myPQueue<Type, Compare>::top() const
{ 
	if(empty()) throw UnderflowException();
	return heap[1];
}

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::percolateDown(int hole)
{
	int child;
	Type tmp = heap[hole];
	
	for (; hole * 2 <= actSize; hole = child)
	{
		child = hole * 2;
		if(child != actSize && lessThan(heap[child+1], heap[child])) child++;
		if(lessThan(heap[child], tmp)) heap[hole] = heap[child];
		else break;
	}
	heap[hole] = tmp;
}

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::pop()
{
	if(empty()) throw UnderflowException();
	heap[1] = heap[actSize--];
	percolateDown(1);
}

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::pop(Type &item)
{
	if(empty()) throw UnderflowException();
	item = top();
	heap[1] = heap [actSize--];
	percolateDown(1);		
}

template<class Type, class Compare>
inline bool myPQueue<Type, Compare>::operator==(const myPQueue<Type, Compare> &r)
{
	if(actSize != r.actSize) return false;
	for(int i = 0; i <= actSize; ++i)
		if(heap[i] != r.heap[i])
			return false;
	return true;		
}

template<class Type, class Compare>
inline bool myPQueue<Type, Compare>::operator!=(const myPQueue<Type, Compare> &r)
{
	if(actSize != r.actSize) return true;
	for(int i = 0; i <= actSize; ++i)
		if(heap[i] != r.heap[i])
			return true;
	return false;		
}

template<class Type, class Compare>
inline bool myPQueue<Type, Compare>::operator<(const myPQueue<Type, Compare> &r)
{
	if(*this == r) return false;
	if(size() < r.size()) return true;
	if(size() > r.size()) return false;
	
	for(int i = 1; i <=actSize; ++i) if(heap[i] < r.heap[i]) return true;
	return false;
}

template<class Type, class Compare>
inline bool myPQueue<Type, Compare>::operator>(const myPQueue<Type, Compare> &r)
{
	if(*this == r) return false;
	if(size() > r.size()) return true;
	if(size() < r.size()) return false;
	
	for(int i = 1; i <=actSize; ++i) if(heap[i] > r.heap[i]) return true;
	return false;
}

template<class Type, class Compare>
inline myPQueue<Type, Compare> &myPQueue<Type, Compare>::operator=(const myPQueue &r)
{
    if (this != &r)
    {
        delete[] heap;
        heap = new Type [maxSize = r.maxSize];
        actSize = r.actSize;
		for(int i = 0; i <= actSize; i++) heap[i] = r.heap[i];
    }
    return *this;
}

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::buildHeap()
	{ for(int i = actSize / 2; i > 0; --i) percolateDown(i); }
	
template<class Type, class Compare>	
inline myPQueue<Type, Compare>::iterator::iterator(myPQueue<Type, Compare> *p, bool end)
{
	ptr = p;
    end ? pos = p->actSize + 1 : pos = 1;
}

template<class Type, class Compare>
inline Type& myPQueue<Type, Compare>::iterator::operator*()
{
	return ptr->heap[pos];
}

template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::iterator myPQueue<Type, Compare>::iterator::operator++()
{
	pos++;
	return *this;
}
	
template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::iterator myPQueue<Type, Compare>::iterator::operator--()
{
	pos--;
	return *this;
}

template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::iterator myPQueue<Type, Compare>::iterator::operator++(int)
{
	myPQueue<Type, Compare>::iterator t = *this;
	pos++;
	return t;
}

template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::iterator myPQueue<Type, Compare>::iterator::operator--(int)
{
	myPQueue<Type, Compare>::iterator t = *this;
	pos--;
	return t;
}

template<class Type, class Compare>	
inline myPQueue<Type, Compare>::reverse_iterator::reverse_iterator(myPQueue<Type, Compare> *p, bool end)
{
	myPQueue<Type, Compare>::iterator::ptr = p;
    end ? myPQueue<Type, Compare>::iterator::pos = p->actSize
    	: myPQueue<Type, Compare>::iterator::pos = 0;
}

template<class Type, class Compare>	
inline myPQueue<Type, Compare>::reverse_iterator::reverse_iterator
	(const myPQueue<Type, Compare>::reverse_iterator &r)
{
	myPQueue<Type, Compare>::iterator::ptr = r.myPQueue<Type, Compare>::iterator::ptr;
	myPQueue<Type, Compare>::iterator::pos = r.myPQueue<Type, Compare>::iterator::pos;
}


template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::reverse_iterator myPQueue<Type, Compare>::reverse_iterator::operator++()
{
	myPQueue<Type, Compare>::iterator::pos--;
	return *this;
}
	
template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::reverse_iterator myPQueue<Type, Compare>::reverse_iterator::operator--()
{
	myPQueue<Type, Compare>::iterator::pos++;
	return *this;
}

template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::reverse_iterator myPQueue<Type, Compare>::reverse_iterator::operator--(int)
{
	myPQueue<Type, Compare>::reverse_iterator t = *this;
	myPQueue<Type, Compare>::iterator::pos++;
	return t;
}

template<class Type, class Compare>
inline typename myPQueue<Type, Compare>::reverse_iterator myPQueue<Type, Compare>::reverse_iterator::operator++(int)
{
	myPQueue<Type, Compare>::reverse_iterator t = *this;
	myPQueue<Type, Compare>::iterator::pos--;
	return t;
}

template<class Type, class Compare>	
inline myPQueue<Type, Compare>::const_iterator::const_iterator(myPQueue<Type, Compare> *p, bool end)
	: myPQueue<Type, Compare>::iterator(p, end) {}

template<class Type, class Compare>	
inline myPQueue<Type, Compare>::const_iterator::const_iterator(const iterator &r)
	: myPQueue<Type, Compare>::iterator(r) {}

template<class Type, class Compare>
inline const Type& myPQueue<Type, Compare>::const_iterator::operator*() const
{
	return myPQueue<Type, Compare>::iterator::ptr->heap[myPQueue<Type, Compare>::iterator::pos];
}

template<class Type, class Compare>
inline myPQueue<Type, Compare>::const_reverse_iterator::const_reverse_iterator(myPQueue<Type, Compare> *a, bool end)
	: myPQueue<Type, Compare>::reverse_iterator(a, end) {}

template<class Type, class Compare>	
inline myPQueue<Type, Compare>::const_reverse_iterator::const_reverse_iterator(const reverse_iterator &r)
	: myPQueue<Type, Compare>::reverse_iterator(r) {}

template<class Type, class Compare>
inline const Type& myPQueue<Type, Compare>::const_reverse_iterator::operator*() const
{ return myPQueue<Type, Compare>::iterator::ptr->heap[myPQueue<Type, Compare>::iterator::pos]; }

template<class Type, class Compare>
inline void myPQueue<Type, Compare>::pop(iterator &begin, iterator &end)
{
	while(begin != end) 
	{
		end--;
		*end = heap[actSize--];
	}
	buildHeap();
}

template <class Type, class Compare>
typename myPQueue<Type, Compare>::iterator myPQueue<Type, Compare>::begin()
	{ return iterator(this, false); }

template <class Type, class Compare>
typename myPQueue<Type, Compare>::iterator myPQueue<Type, Compare>::end()
	{ return iterator(this, true); }
	
template <class Type, class Compare>
typename myPQueue<Type, Compare>::reverse_iterator myPQueue<Type, Compare>::rbegin()
	{ return reverse_iterator(this, true); }

template <class Type, class Compare>
typename myPQueue<Type, Compare>::reverse_iterator myPQueue<Type, Compare>::rend()
	{ return reverse_iterator(this, false); }

template <class Type, class Compare>
bool myPQueue<Type, Compare>::iterator::operator==(const myPQueue<Type, Compare>::iterator &r)
{
    return ((ptr == r.ptr) && (pos == r.pos));
}

template <class Type, class Compare>
bool myPQueue<Type, Compare>::iterator::operator!=(const myPQueue<Type, Compare>::iterator &r)
{
    return ((ptr != r.ptr) || (pos != r.pos));
}

#endif /* PQ_H */