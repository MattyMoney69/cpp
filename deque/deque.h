#ifndef DEQUE_H
#define	DEQUE_H

#define MAX_ARRAY_SIZE 1000
#define MAX_NODES_SIZE 5050

template <typename T>
class Deque {
public:
  Deque();
  T& operator[] (int index)const;
  T& operator[] (int index);
  void pop_back();
  void push_back(const T &value);
  void pop_front();
  void push_front(const T &value);
  void newNode(bool isTop);
private:
  T** nodes;
  T* top;
  T* bottom;
  int topArrI;
  int bottomArrI;
  int topI;
  int bottomI;
}; // class Deque 

#include "deque.cpp"

#endif	// DEQUE_H

