#ifndef Vector
#define Vector
#include <iostream>
#include <fstream>
#include <exception>
using std::ostream;
using std::istream;
using std::exception;

template<typename T>
class vector
{
    public:
    vector():size(0),capacity(5),array(new T[capacity]) {}
    vector(const vector& rhs):size(rhs.size),capacity(rhs.capacity+5),array(new T[rhs.capacity+5])
    {
        for(int i=0;i<rhs.Size();i++)
        {
            array[i]=rhs.array[i];
        }
    }
    vector(int elements,int value=0):size(elements),capacity(elements+5),array(new T[capacity])
    {
        for(int i=0;i<size;i++)
        {
            array[i]=value;
        }
    }
    void push_back(const T value);
    void pop_back();
    bool empty() const;
    int Size() const;
    int Capacity() const;
    T& operator[](int index);
    //vector<T>& operator=(const vector<T>& rhs);
    T& front();
    T& back();
    void clear();
    private:
    int size;
    int capacity;
    T* array;
};

template<typename T>
bool vector<T>::empty() const
{   
    return size==0;
}

template<typename T>
int vector<T>::Size()  const
{
    return size;
}

template<typename T>
int vector<T>::Capacity()  const
{
    return capacity;
}

template<typename T>
void vector<T>::push_back(T value)
{
    if(size<capacity)
    {
        array[size++]=value;
    }
    else 
    {
        capacity*=2;
        T* temp=new T[capacity];
        for(int i=0;i<size;i++)
        {
            temp[i]=array[i];
        }
        temp[size++]=value;
        //delete[] array;
        array=temp;
    }
}

template<typename T>
void vector<T>::pop_back()
{
    if(size==0)
    {
        throw exception("the vector is already empty\n");
    }
    size--;
}

template<typename T>
T& vector<T>::front()
{
    return array[0];
}

template<typename T>
T& vector<T>::back()
{
    return array[size-1];
}

template<typename T>
T& vector<T>::operator[](int index)
{
    return array[index];
}

template<typename T>
void vector<T>::clear()
{
    size=0;
}

    
#endif