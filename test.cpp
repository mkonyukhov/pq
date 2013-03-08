#include <cstring>
#include <iostream>
#include "pq.h"
#include <queue>

using namespace std;

int
main (int argc, char const *argv[])
{
  if (!strcmp (argv[1], "my"))
    {
      myPQueue < double, greater < double >>q;
      for (int i = 0; i < 100000; ++i)
	q.push (i / 2);
      for (int i = 0; i < 100000; ++i)
	q.pop ();
    }
  else
    {
      priority_queue < double, vector < double >, greater < double >>q;
      for (int i = 0; i < 100000; ++i)
	q.push (i / 2);
      for (int i = 0; i < 100000; ++i)
	q.pop ();
    }
  return 0;
}
