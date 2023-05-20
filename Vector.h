#pragma once
#include<iostream>
#include<stdexcept>
namespace Sake{
namespace stl{

template<class T>
class Vector{
public:
    Vector();
    ~Vector();
    Vector(int size);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);
    void push_back(const T& value);
    void pop_back();
    int size() const;
    int capacity() const;
    void show() const;  //自定义方法
    void reserve(int size);
    void resize(int size);
    T& at(int index) const;
    T& operator [](int index) const;
    bool empty() const;
    void clear();
    T& front() const;
    T& back() const;
    void swap(Vector<T>& other);
    T* data() const;
    bool operator==(const Vector<T>& other) const;
    bool operator != (const Vector<T>& other) const;
    Vector<T>& operator =(Vector<T>& other);
    Vector<T>& operator =(Vector<T>&& other);


    class Iterator{
    public:
        Iterator():m_pointer(nullptr){}
        Iterator(T* pointer):m_pointer(pointer){}
        ~Iterator(){}
        bool operator == (const Iterator& other){
            return m_pointer == other.m_pointer;
        }
        
        bool operator != (const Iterator& other){
            return m_pointer != other.m_pointer;
        }
        
        Iterator operator = (const Iterator& other){
            m_pointer = other.m_pointer;
            return *this;
        }

        Iterator operator ++ (){
            m_pointer+=1;
            return *this;
        }

        Iterator operator ++(int){
            Iterator it = *this;
            ++(*this);
            return it;
        }

        Iterator operator+(int i){
            Iterator it =*this;
            it.m_pointer += i;
            return it;
        }

        Iterator operator-(int i){
            Iterator it =*this;
            it.m_pointer -= i;
            return it;
        }

        Iterator& operator+=(int i){
            m_pointer+=i;
            return *this;
        }

        Iterator& operator-=(int i){
            m_pointer-=i;
            return *this;
        }

        int operator-(const Iterator& other){
            return m_pointer - other.m_pointer;
        }

        T& operator *(){
            return *m_pointer;
        }

        T* operator ->(){
            return m_pointer;
        }
    private:
        T* m_pointer;
    };
    Iterator begin();
    Iterator end();
    Iterator find(const T& value);
    Iterator insert(const T& value);
    Iterator insert(Iterator it,const T& value);
    Iterator insert(Iterator it,int n,const T& value);
    Iterator erase(Iterator it);
    Iterator erase(Iterator first,Iterator last);


private:
    T* m_data;
    int m_size;
    int m_capacity;
};

template<class T>
Vector<T>::Vector():m_data(nullptr),m_size(0),m_capacity(0){

}

template<class T>
Vector<T>::Vector(int size){
    m_capacity = size;
    m_size = size;
    m_data = new int[size];
}

template<class T>
Vector<T>::Vector(const Vector<T>& other){
    while (other.m_size > m_capacity)
    {
        if(m_capacity == 0){
            m_capacity = 1;
        }else{
            m_capacity *= 2;
        }
    }
    m_data = new int[m_capacity];
    for (int i = 0; i < other.size(); i++)
    {
        m_data[i] = other.m_data[i];
    }
    m_size = other.m_size;    
}

//移动构造函数
template<class T>
Vector<T>::Vector(Vector<T>&& other)
    :m_data(other.m_data),m_size(other.m_size),m_capacity(other.m_capacity){
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
}

template<class T>
Vector<T>::~Vector(){
    if(m_data != nullptr){
        delete [] m_data;
        m_data = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
}

template<class T>
void Vector<T>::push_back(const T& value){
    if(m_size < m_capacity){
        m_data[m_size] = value;
        m_size++;
        return;
    }
    if(m_capacity == 0){
        m_capacity = 1;
    }
    else{
        m_capacity *= 2;
    }
    T* data = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
        data[i] = m_data[i];
    }
    if(m_data != nullptr){
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_data[m_size] =value;
    m_size++;
    return;
}

template<class T>
void Vector<T>::pop_back(){
    if(m_size > 0){
        m_size--;
    }
}

template<class T>
int Vector<T>::size() const{
    return m_size;
}

template<class T>
int Vector<T>::capacity() const{
    return m_capacity;
}

template<class T>
void Vector<T>::show() const{
    std::cout<<"m_size: "<< m_size <<"   m_capacity: "<<m_capacity<<std::endl;
    for (int i = 0; i < m_size; i++)
    {
        std::cout<<m_data[i]<<",";        
    }
    std::cout<<std::endl;
}

template<class T>
void Vector<T>::reserve(int size){
    if(size < m_capacity){
        return;
    }
    while (size > m_capacity)
    {
        if(m_capacity == 0){
            m_capacity = 1;
        }else{
            m_capacity *= 2;
        }
    }
    T* data = new T[m_capacity];
    for(int i=0;i<m_size;++i){
      data[i] = m_data[i];
    }
    if(m_data != nullptr){
        delete[] m_data;
        m_data = nullptr;
    }
    m_data = data;
}

template<class T>
void Vector<T>::resize(int size){
    if(size <= m_size){
        m_size = size;
        return;
    }
    if(size <= m_capacity){
        for (int i = m_size; i < size; i++)
        {
            m_data[i] = T();
        }
        m_size = size;
        return;
    }

    while (m_capacity < size)
    {
        if(m_capacity == 0){
            m_capacity =1;
        }else{
            m_capacity *=2;
        }
    }
    T* data = new T[size];
    for(int i = 0; i < m_size; i++){
        data[i] = m_data[i];
    }
    for(int i=m_size;i<size;i++){
        data[i] = T();
    }
    if(m_data != nullptr){
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_size = size;
}

template<class T>
T& Vector<T>::at(int index) const{
    if(index < 0 || index >= m_size)
        throw std::logic_error("out of range");
    return m_data[index];
}

template<class T>
T& Vector<T>::operator [](int index) const{
    return at(index);
}

template<class T>
bool Vector<T>::empty() const{
    return m_size == 0;
}

template<class T>
void Vector<T>::clear(){
    m_size = 0;
}

template<class T>
T& Vector<T>::front() const{
    if(m_size < 0 ){
         throw std::logic_error("vector is empty()");
    }
    return m_data[0];
}

template<class T>
T& Vector<T>::back() const{
    if(m_size < 0 ){
        throw std::logic_error("vector is empty()");
    }
    return m_data[m_size-1];
}

template<class T>
void Vector<T>::swap(Vector<T>& other){
    T* data = other.m_data;
    int size = other.m_size;
    int capacity = other.m_capacity;

    other.m_data = m_data;
    other.m_capacity = m_capacity;
    other.m_size = m_size;

    m_data = data;
    m_size = size;
    m_capacity = capacity;
}

template<class T>
T* Vector<T>::data() const{
    return m_data;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const{
    if(this->size() != other.size()){
        return false;
    }
    for(int i = 0; i < other.size(); ++i){
        if(this->m_data[i] != other.m_data[i]){
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator != (const Vector<T>& other) const{
    return !(*this == other);
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>& other){
    if(m_capacity < other.m_size){
        if(m_data != nullptr){
            delete[] m_data;
            m_data = nullptr;   
            m_capacity = 0;
            m_size = 0;
        }
        while (other.m_size > m_capacity)
        {
           if(m_capacity == 0 )
                m_capacity = 1;
           else
                m_capacity *= 2;
        }
        m_data = new T[m_capacity];
    }
    for (int i = 0; i < other.size(); i++)
    {
        m_data[i] = other.m_data[i];
    }
    m_size = other.m_size;
    return *this;
}

//C++11 移动语义优化
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other){
    if(&other != this){
        if(m_data != nullptr){
            delete[] m_data;
        }
        m_data = other.m_data;
        m_capacity = other.m_capacity;
        m_size = other.m_size;

        other.m_data = nullptr;
        other.m_capacity = 0;
        other.m_size = 0;
    }
    return *this;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::begin(){
    Vector<T>::Iterator it(m_data);
    return it;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::end(){
    Vector<T>::Iterator it(m_data+m_size);
    return it;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::find(const T& value){
    for(Vector<int>::Iterator it = begin(); it != end();it++){
        if((*it) == value){
            return it;
        }
    }
    return end();
}

template<class T>
typename Vector<T>::Iterator Vector<T>::insert(Iterator it,const T& value){
    return insert(it,1,value);
}

template<class T>
typename Vector<T>::Iterator Vector<T>::insert(Iterator it,int n,const T& value){
    int size = it - begin();
    if (m_size + n <= m_capacity)
    {
        //这里可以做一些内存移动优化
        for(int i = m_size; i > size; i--){
            m_data[i+n-1] = m_data[i-1];
        }
        for(int i = 0; i < n; ++i){
            m_data[size+i] = value;
        }
        m_size +=n;
        return Vector<T>::Iterator(m_data + size);
    }
    while (m_size + n > m_capacity)
    {
        if(m_capacity == 0){
            m_capacity = 1;
        }
        else{
            m_capacity *=2;
        }
    }
    T* data = new T[m_capacity];
    for(int i=0; i<size;i++){
        data[i] = m_data[i];
    }
    
    for(int i=0; i < n;i++){
        data[size + i] =value;
    }

    for (int i = size; i < m_size; i++)
    {
        data[i + n] = m_data[i];
    }
    
    if(m_data != nullptr){
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_size +=n;
    return Vector<T>::Iterator(m_data + size);
}

template<class T>
typename Vector<T>::Iterator  Vector<T>::erase(Iterator it){
    if(end()-it == 1){
        m_size -=1;
        return end();
    }
    int size = it-begin();
    for (int i = size ; i < m_size; i++)
    {
        m_data[i] = m_data[i+1];
    }
    m_size -=1;
    return it;
}

template<class T>
typename Vector<T>::Iterator  Vector<T>::erase(Iterator first,Iterator last){
    int f = first-begin();
    int l = last-begin();
    int n = last-first;
    for (int i = f; i < m_size-l; i++)
    {
       m_data[f++] = m_data[l++];
    }
    m_size -=n;
    return first;   
}


}
}
