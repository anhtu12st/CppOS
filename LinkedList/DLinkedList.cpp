#include <bits/stdc++.h>
using namespace std;

template <class T>
class DLinkedList
{
public:
    class Node; // Forward declaration
    class Iterator;

protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList() : head(NULL), tail(NULL), count(0){};
    ~DLinkedList(){};
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    bool empty();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    T removeAt(int index);
    bool removeItem(const T &item);
    void clear();
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;
        Iterator begin()
        {
            return Iterator(this, true);
        }
        Iterator end()
        {
            return Iterator(this, false);
        }

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();

        // Prefix ++ overload
        Iterator &operator++();

        // Postfix ++ overload
        Iterator operator++(int);
    };
    string toString()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }
        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        return ss.str();
    }
};

template <class T>
void DLinkedList<T>::add(const T &e)
{
    /* Insert an element into the end of the list. */
    Node *pNode = new Node(e);
    if (this->count == 0)
    {
        this->head = this->tail = pNode;
        //pNode->next = this->tail;
        //pNode->previous = this->head;
    }
    else
    {
        Node *tmp = this->tail;
        this->tail = pNode;
        pNode->next = NULL;
        pNode->previous = tmp;
        tmp->next = pNode;
    }
    this->count += 1;
}

template <class T>
void DLinkedList<T>::add(int index, const T &e)
{
    /* Insert an element into the list at given index. */
    if (index < 0 || index > this->count)
    {
        throw std::out_of_range("Index_is_out_of_range");
    }
    Node *pNode = new Node(e);
    if (index == 0)
    {
        if (this->count == 0)
        {
            add(e);
            return;
        }
        Node *tmp = this->head;
        this->head = pNode;
        pNode->previous = NULL;
        pNode->next = tmp;
        tmp->previous = pNode;
    }
    else if (index == this->count)
    {
        add(e);
        return;
    }
    else
    {
        Node *tmp = this->head;
        while (index--)
        {
            tmp = tmp->next;
        }
        tmp->previous->next = pNode;
        pNode->next = tmp;
        pNode->previous = tmp->previous;
        tmp->previous = pNode;
    }
    this->count += 1;
}

template <class T>
int DLinkedList<T>::size()
{
    /* Return the length (size) of list */
    return this->count;
}

template <class T>
T DLinkedList<T>::get(int index)
{
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this->count)
    {
        throw std::out_of_range("Index_is_out_of_range");
    }
    Node *pNode = this->head;
    while (index--)
    {
        pNode = pNode->next;
    }
    return pNode->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T &e)
{
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this->count)
    {
        throw std::out_of_range("Index_is_out_of_range");
    }
    Node *pNode = this->head;
    while (index--)
    {
        pNode = pNode->next;
    }
    pNode->data = e;
}

template <class T>
bool DLinkedList<T>::empty()
{
    /* Check if the list is empty or not. */
    return !this->count;
}

template <class T>
int DLinkedList<T>::indexOf(const T &item)
{
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node *pNode = this->head;
    int index = 0;
    while (pNode != NULL)
    {
        if (pNode->data == item)
        {
            return index;
        }
        pNode = pNode->next;
        index++;
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::contains(const T &item)
{
    /* Check if item appears in the list */
    Node *pNode = this->head;
    while (pNode != NULL)
    {
        if (pNode->data == item)
        {
            return true;
        }
        pNode = pNode->next;
    }
    return false;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index < 0 || index >= this->count)
    {
        throw std::out_of_range("Index_is_out_of_range");
    }
    Node *p = this->head;
    if (this->count == 1)
    {
        this->head = NULL;
        this->tail = NULL;
        this->count--;
        T x = p->data;
        delete p;
        return x;
    }
    if (index == 0)
    {
        this->head = p->next;
        p->next->previous = NULL;
        T x = p->data;
        delete p;
        this->count--;
        return x;
    }
    if (index == this->count - 1)
    {
        p = this->tail;
        Node *tmp = p->previous;
        this->tail = tmp;
        tmp->next = NULL;
        T x = p->data;
        delete p;
        this->count--;
        return x;
    }
    for (int i = 1; i < index; i++)
    {
        p = p->next;
    }
    Node *tmp = p->next;
    T x = tmp->data;
    p->next = tmp->next;
    tmp->next->previous = p;
    delete tmp;
    this->count--;
    return x;
}

template <class T>
bool DLinkedList<T>::removeItem(const T &item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int x = 0;
    Node *p = this->head;
    while (p != NULL && p->data != item)
    {
        p = p->next;
        x++;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {
        removeAt(x);
        return true;
    }
}

template <class T>
void DLinkedList<T>::clear()
{
    /* Remove all elements in list */
    Node *p = this->head;
    Node *px = this->head;
    while (this->count--)
    {
        px = p;
        p = p->next;
        delete px;
    }
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}

/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin)
{
    this->pList = pList;
    if (begin)
    {
        if (pList != NULL)
        {
            this->current = pList->head;
            this->index = 0;
        }
        else
        {
            this->current = NULL;
            this->index = -1;
        }
    }
    else
    {
        this->current = NULL;
        if (pList != NULL)
        {
            this->index = pList->size();
        }
        else
        {
            this->index = 0;
        }
    }
}

template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator)
{
    this->index = iterator.index;
    this->current = iterator.current;
    this->pList = iterator.pList;
    return *this;
}

template <class T>
void DLinkedList<T>::Iterator::set(const T &e)
{
    if (this->current == NULL)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    this->current->data = e;
}

template <class T>
T &DLinkedList<T>::Iterator::operator*()
{
    if (this->current == NULL)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    return this->current->data;
}

template <class T>
void DLinkedList<T>::Iterator::remove()
{
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if (this->current == NULL)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    T p = this->current->data;
    if (this->index == 0)
    {
        this->current = NULL;
        this->index = -1;
    }
    else
    {
        this->index -= 1;
        this->current = this->current->previous;
    }
    this->pList->removeItem(p);
}

template <class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator)
{
    return !(this->current == iterator.current && this->pList == iterator.pList && this->index == iterator.index);
}

template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator++()
{
    if (this->current == NULL && this->index != -1)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    if (this->index == -1)
    {
        this->index += 1;
        this->current = this->pList->head;
        return *this;
    }
    this->index++;
    this->current = this->current->next;
    return *this;
}

template <class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    if (this->index >= this->pList->size())
    {
        throw std::out_of_range("Segmentation fault!");
    }
    DLinkedList<T>::Iterator p = *this;
    ++*this;
    return p;
}

int main()
{
    return 0;
}