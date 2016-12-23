
template <typename T>
Deque<T>::Deque()
{
  topI = bottomI = MAX_NODES_SIZE / 2;
  nodes = new T*[MAX_NODES_SIZE];
  newNode(1);
  newNode(0);
} // deque()

template <typename T>
T& Deque<T>::operator[] (int index)const
{
  int emptyInTop = topArrI + 1;
  int actualIndex = index + emptyInTop;
  int nodeI = actualIndex / MAX_ARRAY_SIZE;
  int arrI = actualIndex % MAX_ARRAY_SIZE;
  return nodes[topI + nodeI][arrI];
} // operator[] read

template <typename T>
T& Deque<T>::operator[] (int index)
{
  int emptyInTop = topArrI + 1;
  int actualIndex = index + emptyInTop;
  int nodeI = actualIndex / MAX_ARRAY_SIZE;
  int arrI = actualIndex % MAX_ARRAY_SIZE;
  return nodes[topI + nodeI][arrI];
} // operator[] write

template <typename T>
void Deque<T>::pop_back()
{
  if (bottomArrI == 0)
  {
    delete bottom;
    bottom = nodes[--bottomI - 1];
    bottomArrI = MAX_ARRAY_SIZE;
  } // end if
  
  bottom[--bottomArrI] = 0;
}  // pop_back()

template <typename T>
void Deque<T>::push_back(const T &value)
{
  if (bottomArrI == MAX_ARRAY_SIZE)
    newNode(0);
  bottom[bottomArrI++] = value;
} // push_back()

template <typename T>
void Deque<T>::pop_front()
{
  if (topArrI == MAX_ARRAY_SIZE - 1)
  {
    delete top;
    top = nodes[++topI];
    topArrI = -1;
  } // end if

  top[++topArrI] = 0;
} // pop_front()

template <typename T>
void Deque<T>::push_front(const T &value)
{
  if (topArrI < 0)
    newNode(1);
  top[topArrI--] = value;
} // push_front()

template <typename T>
void Deque<T>::newNode(bool isTop)
{
  T* array = new T[MAX_ARRAY_SIZE];
  if (isTop)
  {
    nodes[--topI] = array;
    top = array;
    topArrI = MAX_ARRAY_SIZE - 1;
  } // end if
  else
  {
    nodes[bottomI++] = array;
    bottom = array;
    bottomArrI = 0;
  } // end else
  
} // newNode





















