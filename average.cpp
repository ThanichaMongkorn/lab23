#include<iostream>
using namespace std;

int main(int argc,char* argv[]){
    int sum=0;
    for(int i=0;i<argc;i++){
        char* text =argv[i];
        sum=text+sum;
    }
    cout <<sum/argc;

    return 0;
}