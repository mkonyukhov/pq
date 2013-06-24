#ifndef PQ_IMPL_HPP
#define PQ_IMPL_HPP

#include <iostream>
#include <vector>

template<class Type, class Compare>
priority_queue<Type, Compare>::priority_queue()
    : maxSize(16), actSize(0), lessThan(Compare())
    { heap = new Type[maxSize]; }

template<class Type, class Compare>
priority_queue<Type, Compare>::priority_queue(const priority_queue &r)
    : lessThan(Compare())
{
    heap = new Type [maxSize = r.maxSize];
    actSize = r.actSize;
    for(size_t i = 0; i <= actSize; i++) heap[i] = r.heap[i];
}

template<class Type, class Compare>
priority_queue<Type, Compare>::priority_queue(const std::vector<Type> &v,
    int num) : lessThan(Compare())
{
    num < 0 ? actSize = v.size() : actSize = num;
    num < 0 ? maxSize = 2 * v.size() + 1 : maxSize = 2 * num + 1; 
    
    heap = new Type[maxSize];
    
    for(size_t i = 0; i < actSize; ++i) {
        heap[i+1] = v[i];
    }
    
    buildHeap();
}

template<class Type, class Compare>
priority_queue<Type, Compare>::~priority_queue()
    { delete[] heap; }

template<class Type, class Compare>
int priority_queue<Type, Compare>::size() const
    { return actSize; }

template<class Type, class Compare>
int priority_queue<Type, Compare>::capacity() const
    { return maxSize; }

template<class Type, class Compare>
bool priority_queue<Type, Compare>::empty() const
    { return !(bool)actSize; }

template<class Type, class Compare>
void priority_queue<Type, Compare>::makeEmpty()
    { actSize = 0; }

template<class Type, class Compare>
void priority_queue<Type, Compare>::push(const Type &item)
{
    heap[0] = item;
    
    if(actSize + 1 == maxSize)
    {
        Type *tmp = new Type[maxSize *= 2];
        for(size_t i = 0; i <= actSize; ++i) tmp[i] = heap[i];
        delete[] heap;
        heap = tmp;
    }
    
    int hole = ++actSize;
    for(; lessThan(item, heap[hole / 2]); hole /= 2) heap[hole] = heap[hole / 2];
    heap[hole] = item;
}

template<class Type, class Compare>
void priority_queue<Type, Compare>::push(const std::vector<Type> &v, int num)
{
    int cur = actSize;
    num < 0 ? actSize += v.size() : actSize += num;
    if(actSize + 1 >= maxSize)
    {
        Type *tmp = new Type[maxSize += 2 * actSize];
        for(size_t i = 0; i <= actSize; ++i) tmp[i] = heap[i];
        delete[] heap;
        heap = tmp;
    }
    
    for(size_t i = cur; i < actSize; ++i) heap[i+1] = v[i];
    buildHeap();
}

template<class Type, class Compare>
void priority_queue<Type, Compare>::print() const
{
    std::cout << "_________________________\n";
    
    for(size_t i = 1; i <= actSize; i++) {
        std::cout << heap[i] << '\t';
        
        if (((i+1) & i) == 0) {
            std::cout << '\n';
        }
    }
    
    std::cout << "\n_________________________\n";
}

template<class Type, class Compare>
void priority_queue<Type, Compare>::swap(priority_queue &rhs)
{
    if (this == rhs) {
        return;
    }

    priority_queue t(rhs);
    rhs = *this;
    *this = t;
}

template<class Type, class Compare>
const Type& priority_queue<Type, Compare>::top() const
{ 
    if(empty()) {
        throw UnderflowException();
    }
    
    return heap[1];
}

template<class Type, class Compare>
void priority_queue<Type, Compare>::percolateDown(size_t hole)
{
    size_t child;
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
void priority_queue<Type, Compare>::pop()
{
    if(empty()) throw UnderflowException();
    heap[1] = heap[actSize--];
    percolateDown(1);
}

template<class Type, class Compare>
void priority_queue<Type, Compare>::pop(Type &item)
{
    if(empty()) {
        throw UnderflowException();
    }

    item = top();
    
    heap[1] = heap[actSize--];
    
    percolateDown(1);        
}

template<class Type, class Compare>
bool priority_queue<Type, Compare>::operator==(const priority_queue<Type, Compare> &r)
{
    if(actSize != r.actSize) return false;
    for(size_t i = 1; i <= actSize; ++i)
        if(heap[i] != r.heap[i])
            return false;
    return true;        
}

template<class Type, class Compare>
bool priority_queue<Type, Compare>::operator!=(const priority_queue<Type, Compare> &r)
{
    if (actSize != r.actSize) {
        return true;
    }
    
    for(size_t i = 1; i <= actSize; ++i) {
        if(heap[i] != r.heap[i]) {
            return true;
        }
    }
    
    return false;        
}

template<class Type, class Compare>
bool priority_queue<Type, Compare>::operator<(const priority_queue<Type, Compare> &r)
{
    if(*this == r) return false;
    if(size() < r.size()) return true;
    if(size() > r.size()) return false;
    
    for(size_t i = 1; i <=actSize; ++i) if(heap[i] < r.heap[i]) return true;
    return false;
}

template<class Type, class Compare>
bool priority_queue<Type, Compare>::operator>(const priority_queue<Type, Compare> &r)
{
    if(*this == r) return false;
    if(size() > r.size()) return true;
    if(size() < r.size()) return false;
    
    for(size_t i = 1; i <=actSize; ++i) if(heap[i] > r.heap[i]) return true;
    return false;
}

template<class Type, class Compare>
priority_queue<Type, Compare> &priority_queue<Type, Compare>::operator=(const priority_queue &r)
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
void priority_queue<Type, Compare>::buildHeap()
    { for(int i = actSize / 2; i > 0; --i) percolateDown(i); }
    
template<class Type, class Compare>    
 priority_queue<Type, Compare>::iterator::iterator(priority_queue<Type, Compare> *p, bool end)
{
    ptr = p;
    end ? pos = p->actSize + 1 : pos = 1;
}

template<class Type, class Compare>
Type& priority_queue<Type, Compare>::iterator::operator*()
{
    return ptr->heap[pos];
}

template<class Type, class Compare>
typename priority_queue<Type, Compare>::iterator priority_queue<Type, Compare>::iterator::operator++()
{
    pos++;
    return *this;
}
    
template<class Type, class Compare>
typename priority_queue<Type, Compare>::iterator priority_queue<Type, Compare>::iterator::operator--()
{
    pos--;
    return *this;
}

template<class Type, class Compare>
typename priority_queue<Type, Compare>::iterator priority_queue<Type, Compare>::iterator::operator++(int)
{
    priority_queue<Type, Compare>::iterator t = *this;
    pos++;
    return t;
}

template<class Type, class Compare>
typename priority_queue<Type, Compare>::iterator priority_queue<Type, Compare>::iterator::operator--(int)
{
    priority_queue<Type, Compare>::iterator t = *this;
    pos--;
    return t;
}

template<class Type, class Compare>    
priority_queue<Type, Compare>::reverse_iterator::reverse_iterator(priority_queue<Type, Compare> *p, bool end)
{
    priority_queue<Type, Compare>::iterator::ptr = p;
    end ? priority_queue<Type, Compare>::iterator::pos = p->actSize
        : priority_queue<Type, Compare>::iterator::pos = 0;
}

template<class Type, class Compare>    
priority_queue<Type, Compare>::reverse_iterator::reverse_iterator
    (const priority_queue<Type, Compare>::reverse_iterator &r)
{
    typedef priority_queue<Type, Compare>::iterator iter;
    iter::ptr = r.iter::ptr;
    iter::pos = r.iter::pos;
}


template<class Type, class Compare>
typename priority_queue<Type, Compare>::reverse_iterator priority_queue<Type, Compare>::reverse_iterator::operator++()
{
    priority_queue<Type, Compare>::iterator::pos--;
    return *this;
}
    
template<class Type, class Compare>
typename priority_queue<Type, Compare>::reverse_iterator priority_queue<Type, Compare>::reverse_iterator::operator--()
{
    priority_queue<Type, Compare>::iterator::pos++;
    return *this;
}

template<class Type, class Compare>
typename priority_queue<Type, Compare>::reverse_iterator priority_queue<Type, Compare>::reverse_iterator::operator--(int)
{
    priority_queue<Type, Compare>::reverse_iterator t = *this;
    priority_queue<Type, Compare>::iterator::pos++;
    return t;
}

template<class Type, class Compare>
typename priority_queue<Type, Compare>::reverse_iterator priority_queue<Type, Compare>::reverse_iterator::operator++(int)
{
    priority_queue<Type, Compare>::reverse_iterator t = *this;
    priority_queue<Type, Compare>::iterator::pos--;
    return t;
}

template<class Type, class Compare>    
priority_queue<Type, Compare>::const_iterator::const_iterator(priority_queue<Type, Compare> *p, bool end)
    : priority_queue<Type, Compare>::iterator(p, end) {}

template<class Type, class Compare>    
priority_queue<Type, Compare>::const_iterator::const_iterator(const iterator &r)
    : priority_queue<Type, Compare>::iterator(r) {}

template<class Type, class Compare>
const Type& priority_queue<Type, Compare>::const_iterator::operator*() const
{
    return priority_queue<Type, Compare>::iterator::ptr->heap[priority_queue<Type, Compare>::iterator::pos];
}

template<class Type, class Compare>
priority_queue<Type, Compare>::const_reverse_iterator::const_reverse_iterator(priority_queue<Type, Compare> *a, bool end)
    : priority_queue<Type, Compare>::reverse_iterator(a, end) {}

template<class Type, class Compare>    
priority_queue<Type, Compare>::const_reverse_iterator::const_reverse_iterator(const reverse_iterator &r)
    : priority_queue<Type, Compare>::reverse_iterator(r) {}

template<class Type, class Compare>
const Type& priority_queue<Type, Compare>::const_reverse_iterator::operator*() const
{ return priority_queue<Type, Compare>::iterator::ptr->heap[priority_queue<Type, Compare>::iterator::pos]; }

template<class Type, class Compare>
void priority_queue<Type, Compare>::pop(iterator &begin, iterator &end)
{
    while(begin != end--)  {
        *end = heap[actSize--];
    }
    
    buildHeap();
}

template <class Type, class Compare>
typename priority_queue<Type, Compare>::iterator priority_queue<Type, Compare>::begin()
    { return iterator(this, false); }

template <class Type, class Compare>
typename priority_queue<Type, Compare>::iterator priority_queue<Type, Compare>::end()
    { return iterator(this, true); }
    
template <class Type, class Compare>
inline typename priority_queue<Type, Compare>::reverse_iterator
    priority_queue<Type, Compare>::rbegin()
{
    return reverse_iterator(this, true);
}

template <class Type, class Compare>
typename priority_queue<Type, Compare>::reverse_iterator priority_queue<Type, Compare>::rend()
    { return reverse_iterator(this, false); }

template <class Type, class Compare>
bool priority_queue<Type, Compare>::iterator::operator==(const priority_queue<Type, Compare>::iterator &r)
{
    return ((ptr == r.ptr) && (pos == r.pos));
}

template <class Type, class Compare>
bool priority_queue<Type, Compare>::iterator::operator!=(const priority_queue<Type, Compare>::iterator &r)
{
    return ((ptr != r.ptr) || (pos != r.pos));
}

#endif /* PQ_IMPL_HPP */
