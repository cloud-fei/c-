#include<iostream>
#include<unistd.h>
using namespace std;
int main(){
    pid_t pid = fork();

    if(pid == -1){
        cout << "Failed to creat child process" << endl;
    }else if(pid == 0){
        cout << "Success to creat child process" << endl;
    }else{
        cout << "Child process pid:" << pid << endl;
    }

    return 0;
}