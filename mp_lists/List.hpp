/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if(head_ == NULL) return;

  ListNode* temp = head_;
  ListNode* temp1;

  while(temp->next != NULL){
    temp1 = temp->next;
    delete temp;
    temp = temp1;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  newNode -> next = head_;
  newNode -> prev = NULL;

  if(head_ != NULL){
    head_->prev = newNode;
  }
  if(tail_ == NULL){
    tail_ = newNode;
  }

  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);

  if(head_ == NULL){
    head_ = newNode;
  }

  newNode -> next = NULL;
  newNode -> prev = tail_;

  if(tail_ != NULL){
    tail_->next = newNode;
  }

  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1

  if(start==NULL){
    return NULL;
  }

  if(splitPoint < 1){
    return start;
  }

  if(length_ < splitPoint){
    return NULL;
  }

  ListNode * curr = start;
  for (int i = 0; i < splitPoint-1 && curr != NULL; i++) {
    if(curr->next != NULL) curr = curr->next;
  }

  if(curr != NULL){
      curr = curr->next;
      curr->prev->next = NULL;
      tail_ = curr->prev;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the one three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if(length_ < 3){
    return;
  }

  ListNode* one = head_;
  ListNode* two = head_->next;
  ListNode* three = two->next;

  one->next = three->next;
  three->next->prev = one;
  three->next = one;
  one->prev = three;
  head_ = two;
  two->prev = NULL;

  for(int i = 1; i < (length_/3); i++){

    one = one->next;
    two = one->next;
    three = two->next;

    one->prev->next = two;
    two->prev = one->prev;

    if(three->next != NULL){
      one->next = three->next;
      three->next->prev = one;
      std::cout<<"Three next is NULL";
    }else one->next = NULL;

    one->prev = three;
    three->next = one;

    if(three->next == NULL) return;
  }

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the one node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(startPoint == endPoint){
    return;
  }
  if(startPoint == NULL || endPoint == NULL){
    return;
  }

  ListNode *start = startPoint;
  ListNode *end = endPoint->next;
  ListNode *startp = startPoint;

  while (start != end){
        startp = start->prev;
        start->prev = start->next;
        start->next = startp;
        start = start->prev;
    }

    startp = endPoint->prev;
    ListNode * temp = startPoint->next;
    if(temp!=NULL){
      endPoint->prev = startPoint->next;
      startPoint->next->next = endPoint;
    }

    else{
      endPoint->prev = NULL;
    }

    if(startp!=NULL){
      startPoint->next = startp;
      startp->prev = startPoint;
    }

    else{
      startPoint->next = nullptr;
    }

    start = startPoint;
    startPoint = endPoint;
    endPoint = start;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2


  if(n <= 1){
    return;
  }

  if(length_<=1){
    return;
  }

  if(n>=length_){
    reverse();
  }

  int i = n;
  ListNode * curr1 = head_;
  ListNode * curr2 = head_;
  ListNode * curr3 = NULL;

  while(curr1 != NULL){
       if (i==0){
           if(curr2 == head_)
               head_ = curr3;
            reverse(curr2,curr3);
            i = n;
            curr2 = curr1;
            curr3 = curr1;
       }
       if (curr1->next == NULL){
            reverse(curr2,curr1);
       }
       curr3= curr1;
       curr1 = curr1->next;
       i--;

}
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param one The starting node of the one sequence.
 * @param two The starting node of the two sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * one, ListNode* two) {
  /// @todo Graded in MP3.2

  ListNode * curr = NULL;
   ListNode * temp1 = one;
   ListNode * temp2 = one;
   ListNode * temp3 = two;

   if(one->data < two->data){
         temp1 = temp2;
         temp2 = temp2->next;
   }

   else{
         temp1 = temp3;
         temp3 = temp3->next;
   }

   curr = temp1;

   while(temp3 != NULL && temp2 != NULL){
       if(temp2 == NULL && temp3== NULL){
         break;
       }else if(temp2 == NULL ||(temp3->data < temp2->data && temp3 != NULL) ){
         curr->next = temp3;
         curr->next->prev = curr;
         temp3 = temp3->next;
         curr = curr->next;
       }
       else{
         curr->next = temp2;
         curr->next->prev = curr;
         temp2 = temp2->next;
         curr = curr->next;
       }
   }


   if(temp2 == NULL)
   {
     curr->next = temp3;
     temp3->prev = curr;
   }

   if(temp3 == NULL){
     curr->next = temp2;
     temp2->prev = curr;
   }
   return temp1;

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.

  return NULL;
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1){
    return start;
  }
  int size = chainLength/2;
  ListNode *temp;
  temp = split(start, size);
  ListNode *begin = mergesort(start, size);
  ListNode *end = mergesort(temp, chainLength-size);

  return merge(begin, end);
}
