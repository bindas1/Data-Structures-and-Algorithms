#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;
template<typename IteratorType>
 void seSort(IteratorType first, IteratorType last)
 {
    for(IteratorType it = first; it != last; ++it)
    {
        auto j = it-1;
        auto key = *(it);
        while(j >= first && *j > key )
        {
          std::iter_swap(j+1,j);
          j--;
        }
    std::iter_swap(j+1, &key);
    }
 }

template<typename iteratorType>
iteratorType myPartition( iteratorType first, iteratorType last )
{
    auto p = first;
    auto current = next(first);
    while (current != last)
    {
        if (*current < *first)
            swap(*++p, *current);
        ++current;
    }

    swap(*first, *p);

    return p;

}

template<typename iteratorType>
void myQuickSort(iteratorType first, iteratorType last)
{
    if(distance(first, last) >= 2){
        auto p = myPartition(first, last);
        myQuickSort(first,p);
        myQuickSort(p+1,last);
    }
}

int main()
{
    vector<string> quick, se, defSort;
    string str;
    fstream inputFile, outputFile;
    inputFile.open( "Pan.txt" );
    outputFile.open( "out.txt" );

    int el = 0;

    if(inputFile.is_open() && outputFile.is_open()){
        while(inputFile>>str and el < 1000){
            defSort.push_back(str);
            quick.push_back(str);
            se.push_back(str);
            el++;
        }



    auto t1 = std::chrono::high_resolution_clock::now();
    seSort(se.begin(), se.end());
    auto t2 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

    outputFile<<"SELECTION SORT:\n";
    for(auto i:se){

        outputFile<<i<<"\n";
    }
    outputFile<<"SeTIME: "<<dt.count()<<"\n";

    t1 = std::chrono::high_resolution_clock::now();
    myQuickSort(quick.begin(), quick.end());
    t2 = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

    outputFile<<"QUICKSORT:\n";
    for(auto i:quick){

        outputFile<<i<<"\n";
    }
    outputFile<<"QuTIME: "<<dt.count()<<"\n";

    t1 = std::chrono::high_resolution_clock::now();
    sort(defSort.begin(), defSort.end());
    t2 = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

    outputFile<<"DEFAULT SORT:\n";
    for(auto i:defSort){

        outputFile<<i<<"\n";
    }
    outputFile<<"DeTIME: "<<dt.count()<<"\n";

    return 0;
    }
}
