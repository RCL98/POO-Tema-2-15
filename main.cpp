#include <iostream>
#include <fstream>
#include "Lista.h"
#include "Nr_natural.h"
#include "Nr_intreg.h"
using namespace std;

template <class T>
void Swap(T &a,T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int Partition(T v[], int start, int stop)
{
    T pivot = v[stop];
    int piv_poz = start,i;
    for( i = start; i <=stop-1 ; i++)
    {
        if(v[i]< pivot)
        {
            Swap(v[piv_poz],v[i]);
            piv_poz++;
        }
    }
    Swap(v[piv_poz],v[i]);
    return piv_poz;
}

template <class T>
void Quicksort(T v[],int st,int dr)
{
    if(st < dr)
    {
        int p = Partition(v,st,dr);
        Quicksort(v,st,p-1);
        Quicksort(v,p+1,dr);
    }
}

int main()
{
    ifstream f("numere.in");
    ofstream g("numere.out");
    nr_natural v[10];
    int n,i;
    f>>n;
    for(i=0;i<n;i++)
    {
         f>>v[i];
    }
    for(i=0;i<n;i++)
        g<<v[i]<<" ";
    g<<endl;
    Quicksort(v,0,n-1);
    for(i=0;i<n;i++)
        g<<v[i]<<" ";
    return 0;
}
