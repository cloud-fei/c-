#include<iostream>
#include<thread>

using namespace std;

void printHello(){
    cout << "hello from thread!" << endl;
}

int main(){
    std::thread t(printHello);

    t.join();

    cout << "hello from main thread!" << endl; 
    return 0;
   
}



// g++ 编译时报错：
// /tmp/cc9Pijnr.o: In function `std::thread::thread<void (&)(), , void>(void (&)())':
// multi_thread.cpp:(.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_[_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_]+0x21): undefined reference to `pthread_create'
// collect2: error: ld returned 1 exit status

// 原因：lpthread 不是linux下默认多线程的库，在编译的时候加上链接参数 -lpthread 就可以了