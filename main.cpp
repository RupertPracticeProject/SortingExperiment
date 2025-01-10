#include <chrono>
#include <iostream>
#include <vector>
#define SHOW_ARRAY 1
#define NO_ARRAY 0
using namespace std;
using namespace std::chrono;


void initVector(vector<int> & array, int size = 10)
{

    if(array.size() == 0)
    {
        for(int i = 1; i < size; ++i)          
        {
            for(int j = 1; j < size; ++j)
            {
                array.push_back(i*j%(28));
            }
        }
    }
    else
    {
        for(int i = 1; i < size; ++i)          
        {
            for(int j = 1; j < size; ++j)
            {
                array[(i-1)*(size-1)+j-1] = i*j%(28);
            }
        }
    }
}


class NumberSorter
{
    public:
        static void Print(vector<int> a)
        {
            for(int num:a) cout << num << " " ;
            cout << endl;
        }
        static void Swap(int * a, int * b)
        {
            int temp = *a;
            *a = *b;
            *b = temp;
        }
        static void BubbleSort(vector<int> & a, bool RightOrder(int a, int b))
        {
            int length = a.size();
            for(int i = 0; i < length-1; ++i)
            {
                bool isSwap = false;
                for(int j = 0; j < length-1-i; ++j)
                {
                    if(!RightOrder(a[j], a[j+1]))
                    {
                        Swap(&a[j], &a[j+1]);
                        isSwap = true;
                    }
                }
                if(!isSwap)
                {
                    break;
                }
            }
        }

        static void Merge(vector<int> & a, int start, int middle, int end, bool RightOrder(int a, int b))
        {
            int length = a.size();
            int temp[length], leftIndex = start, rightIndex = middle+1;
            for(int i = start; i <= end; ++i) temp[i] = a[i];
            for(int i = start; i <= end; ++i)
            {
                if(leftIndex > middle)
                {
                    a[i] = temp[rightIndex];
                    rightIndex ++;
                    continue;
                }
                if(rightIndex > end)
                {
                    a[i] = temp[leftIndex];
                    leftIndex ++;
                    continue;
                }
                if(RightOrder(temp[leftIndex], temp[rightIndex]))
                {
                    a[i] = temp[leftIndex];
                    leftIndex ++;
                }
                else
                {
                    a[i] = temp[rightIndex];
                    rightIndex ++;
                }
            }
            
        }
        static void MergeRecursively(vector<int> & a, int start, int middle, int end, bool RightOrder(int a, int b))
        {
            if(start != middle) MergeRecursively(a, start, (start+middle)/2, middle, RightOrder);
            if(middle+1 != end) MergeRecursively(a, middle+1, (middle+1+end)/2, end, RightOrder);
            Merge(a, start, middle, end, RightOrder);
        }
        static void MergeSort(vector<int> & a, bool RightOrder(int a, int b))
        {
            int length = a.size();
            MergeRecursively(a, 0, (length-1)/2, length-1, RightOrder);
        }

        static void SortAndCalculateTime(void Sort(vector<int> & a, bool RightOrder(int a, int b)), vector<int> & array, bool RightOrder(int a, int b), int arrayFlag)
        {
            if(arrayFlag == WITH_ARRAY) Print(array);

            auto start = high_resolution_clock::now();
            Sort(
                array,
                RightOrder
            );
            auto end = high_resolution_clock::now();
            auto totalTimeInNanoSeconds = duration_cast<nanoseconds>(end-start).count();
            if(arrayFlag == WITH_ARRAY) Print(array);
            cout << "It's cost " << totalTimeInNanoSeconds << " nano seconds to sort the array. " << "\n\n\n\n";
        }
};



int main()
{

    

    vector<int> array;

    initVector(array, 100);
    

    NumberSorter::SortAndCalculateTime(
        NumberSorter::BubbleSort,
        array,
        [](int a, int b)
        {
            return a < b;
        },
        NO_ARRAY
    );


    initVector(array, 100);

    NumberSorter::SortAndCalculateTime(
        NumberSorter::MergeSort,
        array,
        [](int a, int b)
        {
            return a < b;
        },
        NO_ARRAY
    );
    

    return 0;
}