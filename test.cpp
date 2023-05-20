#include<iostream>
#include"Vector.h"
#include<vector>
#include <chrono>
using namespace Sake::stl;
using namespace std;

int main(){
    Vector<int>v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    Vector<int>v2(std::move(v1));
    v2.show();
    if(v1 != v2){
        cout << "v1 == v2" << endl;
    }
    else{
        cout << "v1 != v2" << endl;
    }

    //测试性能
    const int N = 1000000;
    {
        Vector<int>myVector;
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < N; ++i){
            myVector.push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto durations = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << "myVector耗时:  " << durations << "ms" << endl;
    }
    {
        vector<int>stdVetor;
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < N; ++i){
            stdVetor.push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto durations = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout << "stdVetor耗时:  " << durations << "ms" << endl;
    }

    return 0;
}