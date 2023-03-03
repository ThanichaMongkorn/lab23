#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

int main(int argc,char* argv[]){
    float sum=0;
    float number;
    if(argc==1){
        cout <<"Please input numbers to find average.";
    }else{
        cout <<"---------------------------------\n";
            for(int i=1;i<argc;i++){
            char* text =argv[i];
            number=atof(text);
            sum = number+sum;
        }
        cout <<"Average of "<<argc-1<<" numbers = "<<sum/(argc-1)<<"\n";
        cout <<"---------------------------------\n";
        
        
    }
    return 0;
}
