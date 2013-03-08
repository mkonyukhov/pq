#include <iostream>

using namespace std;

class UnderflowException
{
};

template < class Object > class myPQueue
{
public:
  myPQueue ();
  myPQueue (const myPQueue & r);
  ~myPQueue ();

  int size () const;
  int capacity () const;
  bool empty () const;
  void makeEmpty ();
  void push (const Object & item);
  void print () const;
  void swap (myPQueue & r);
  void percolateDown (int hole);
  const Object & top () const;
  void pop (int &Object);
private:
  int maxSize, actSize;
  Object *heap;
};

template < class Object > myPQueue < Object >::myPQueue ():maxSize (16),
actSize (0)
{
  heap = new Object[maxSize];
}

template < class Object > myPQueue < Object >::myPQueue (const myPQueue & r)
{
  heap = new Object[maxSize = r.maxSize];
  for (int i = 0; i < actSize; i++)
    heap[i] = r.heap[i];
}

template < class Object > myPQueue < Object >::~myPQueue ()
{
  delete[]heap;
}

template < class Object > int myPQueue < Object >::size () const const
{
  return actSize;
}

template < class Object > int myPQueue < Object >::capacity () const const
{
  return maxSize;
}

template < class Object > bool myPQueue < Object >::empty () constconst
{
  return !(bool) actSize;
}

template < class Object > void myPQueue < Object >::makeEmpty ()
{
  actSize = 0;
}

template < class Object > void myPQueue < Object >::push (const int &item)
{
  heap[0] = item;

  if (actSize + 1 == maxSize)
    {
      Object *tmp = new Object[maxSize *= 2];
      for (int i = 0; i <= actSize; ++i)
	tmp[i] = heap[i];
      delete[]heap;
      heap = tmp;
    }

  int hole = ++actSize;
  for (; item < heap[hole / 2]; hole /= 2)
    heap[hole] = heap[hole / 2];
  heap[hole] = item;
}

template < class Object > void myPQueue < Object >::print () const const
{
  for (int i = 1; i <= actSize; i++)
    {
      cout << heap[i] << '\t';
      if (((i + 1) & i) == 0)
	cout << '\n';
    }
  cout << '\n';
}

template < class Object > void myPQueue < Object >::swap (myPQueue & r)
{
  myPQueue t (r);
  r = *this;
  *this = t;
}

template < class Object > const Object & myPQueue < Object >::top () const const
{
  if (empty ())
    throw UnderflowException ();
  return heap[1];
}

template < class Object > void myPQueue < Object >::percolateDown (int hole)
{
  int child;
  Object tmp = heap[hole];

  for (; hole * 2 <= actSize; hole = child)
    {
      child = hole * 2;
      if (child != actSize && heap[child + 1] < heap[child])
	child++;
      if (heap[child] < tmp)
	heap[hole] = heap[child];
      else
	break;
    }
  heap[hole] = tmp;
}

template < class Object > void myPQueue < Object >::pop (Object & item)
{
  item = top ();
  heap[1] = heap[actSize--];
  percolateDown (1);
}
