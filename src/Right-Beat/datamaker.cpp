#include <iostream>   
#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
#include <ctime>  
#include <fstream>  
#include <algorithm>  
#include <windows.h>  
using namespace std;  
//ofstream cout("data.in");  
int main()  
{  
    srand(time(0));  
//  srand( (unsigned)time( NULL ) );  
    //freopen("input.txt","w",stdout);   
    int a,b;  
    a=rand()%100+1,b=rand()%100+1;  
    printf("%d %d\n",a,b);   
    return 0;  
} 
