#include <bits/stdc++.h>
using namespace std;

template<class T>
class Heap{
protected:
    T *elements;
    int capacity;
    int count;
    
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete []elements;
    }
    void push(T item);
    int getItem(T item);
    void remove(T item);
    void clear();
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]";
    }
    static void heapSort(T* start, T* end){
        //TODO
        int count = end - start;
        int position = count / 2;
        while (position >= 0){
            Sorting<T>::reheapDown(start, count, position);
            position -= 1;
        }
        int last = count - 1;
        while (last > 0){
            swap(start[0], start[last]);
            last -= 1;
            Sorting<T>::reheapDown(start, last+1, 0);
        }
        Sorting<T>::printArray(start,end);
    }
private:
    void ensureCapacity(int minCapacity); 
    void reheapUp(int position);
    void reheapDown(int index)
    {
        int leftChild = index * 2 + 1;
        int rightChild = index * 2 + 2;
        int largeChild;
        if (leftChild <= this->count-1){
            if (rightChild <= this->count-1 && this->elements[rightChild] > this->elements[leftChild] )
                largeChild = rightChild;
            else 
                largeChild = leftChild;
            
            if (this->elements[largeChild] > this->elements[index]){
                swap(this->elements[largeChild], this->elements[index]);
                reheapDown(largeChild);
            }
        }
    }
};

template<class T>
void Heap<T>::push(T item){
    if (this->count >= this->capacity){
        ensureCapacity(this->count+1);
        this->capacity *= 2;
    }
    this->count++;
    this->elements[this->count - 1] = item;
    reheapUp(this->count - 1);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    T *ptr = this->elements;
    this->elements = new T[minCapacity*2];
    for (int i = 0; i < minCapacity - 1; i++)
        this->elements[i] = ptr[i];
    delete[] ptr;
}

template<class T>
void Heap<T>::reheapUp(int position){
    if  (position > 0 && position < this->count){
        int parent = (position-1)/2;
        if (this->elements[position] > this->elements[parent]){
            swap(this->elements[position], this->elements[parent]);
            reheapUp( parent);
        }
    }
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < this->count; i++){
        if (this->elements[i] == item)
            return i;
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    if (this->count >= 0){
        int idx = getItem(item);
        if (idx != -1){
            this->elements[idx] = this->elements[this->count - 1];
            this->count -= 1;
            reheapDown(idx);
        }
    }
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    this->count = 0;
    delete[] this->elements;
}

template<class T>
int Heap<T>::size(){
    return this->count;
}

template<class T>
bool Heap<T>::isEmpty(){
    return this->count==0;
}

template<class T>
T Heap<T>::peek(){
    return this->elements[0];
}

template<class T>
bool Heap<T>::contains(T item){
    for (int i = 0; i < this->count ; i++)
        if (this->elements[i] == item)
            return true;
    return false;
}

template<class T>
bool Heap<T>::pop(){
    if (this->count > 0){

        this->elements[0] = this->elements[this->count - 1];
        this->count -= 1;
        reheapDown(0);

        return true;
    }
    return false;
}

int main(){
Heap<int> maxHeap;
int arr[] = {42,35,30,15,20,21,18,3,7,14};
for (int i = 0; i < 10; i++)
    maxHeap.push(arr[i]);
maxHeap.remove(42);
maxHeap.remove(35);
maxHeap.remove(30);
maxHeap.printHeap();
    return 0;
}

int minWaitingTime1(int n, int arrvalTime[], int completeTime[],int time) {
    // YOUR CODE HERE
    int min=completeTime[0];
    int result=0;
    for(int i=1;i<n;i++){
        if(arrvalTime[i]<=time && completeTime[i]<min){
            min=completeTime[i];
            result=i;
        }  
    }
    return result;  
} 
int minWaitingTime(int n, int arrvalTime[], int completeTime[]) {
    // YOUR CODE HERE
    int time=0;
    int count=n;
    int results=0;
    while(count>1){
        int a=minWaitingTime1(count,arrvalTime,completeTime,time);
        count--;
        results+=(time-arrvalTime[a])+completeTime[a];
        time+=completeTime[a];
        for(int i=0;i<count;i++ ){
            if(i>=a){
                completeTime[i]=completeTime[i+1];
                arrvalTime[i]=arrvalTime[i+1];
            }
        }   
    }
    results+=(time-arrvalTime[0])+completeTime[0];
    return results;   
}