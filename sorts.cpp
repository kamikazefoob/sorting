//Todd Tirums
//CSCI 385
//Assignment 3
//Sorting


#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

//various sorts
//template:
//void name(vector<int>& list);
void bubbleSort(vector<int>& list);
void selectionSort(vector<int>& list);
void shellSort(vector<int>& list);
void mergeSort(vector<int>& list);
void quickSort(vector<int>& list);

//helper functions for above sorts
void mSort(vector<int>& list, vector<int>& temp, int left, int right, int& comparisons);
void merge(vector<int>& list, vector<int>& temp, int left, int mid, int right, int& comparisons);
void CopyArray(vector<int>& temp, vector<int>& list, int left, int right);
void qSort(vector<int>& list, int low, int high, int& comparisons, int& swaps);
int partition(vector<int>& list, int low, int high, int& comparisons, int& swaps);

//other functions
int GetInput();
bool TestSort(vector<int>& list, vector<int>& otherList);
void TimeToSort(vector<int>& list, vector<int>& otherList);

int main()
{
    //lists to be sorted, size of list
    vector<int> baseList;
    vector<int> sortList;
     
    int size;
    
    srand(time(NULL)); //seed the rng
    
    size = GetInput();
    
    //fill the lists
    generate_n(back_inserter(baseList), size, rand);
    sortList = baseList;
    
    cout << endl << endl;
    cout << "Random order: " << endl << endl;
    TimeToSort(baseList, sortList);
    
    baseList.clear();
    for(int i = size; i > 0; i--)
        baseList.push_back(i);
    sortList = baseList;
    
    cout << endl << endl << "Reverse sorted:" << endl << endl;
    TimeToSort(baseList, sortList);
    
    int mid = baseList.size()/2;
    int temp = baseList[mid+1];
    baseList[mid+1] = baseList[mid];
    baseList[mid] = temp;
    
    cout << endl << endl << "Nearly sorted:" << endl << endl;
    TimeToSort(baseList, sortList);
    
    
    return 0;
}

//**********************************************
//*************** BEGIN SORTS ******************
//**********************************************

void bubbleSort(vector<int>& list)
//pre: list has at least one item
//post: list is sorted
//sorts list using the bubblesort algorithm
{
    bool sorted;
    int swaps = 0;
    int comparisons = 0;
    
    for(int i = 0; i < list.size()-1; i++)
    {
        sorted = true;
        for(int j = 0; j < (list.size() - i - 1); j++)
        {
            comparisons++;
            if(list[j+1] < list[j])//if next element is smaller than current
            {   //swap
                int temp = list[j+1];
                list[j+1] = list[j];
                list[j] = temp;
                
                sorted = false;
                swaps++;
            }//end if
        }//end for
    }//end for
    
    cout << "Sort: Bubblesort" << endl;
    cout << "Size of list: " << list.size() << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    cout << "Number of swaps: " << swaps << endl;
        
}//end func


void selectionSort(vector<int>& list)
//pre: list has at least one item
//post: list is sorted
//list is sorted using selection sort algorithm
{
    int swaps = 0;
    int comparisons = 0;
    
    for(int i = 0; i < (list.size()-1); i++)
    {
        int min = i;
        for(int j = i+1; j < (list.size()); j++)
        {
            comparisons++;
            if(list[j] < list[min])//find smallest element
            {
                min = j;
            }//end if
        }//end for
        
        if(min != i)
        {//swap
            int temp = list[i];
            list[i] = list[min];
            list[min] = temp;
            swaps++;
        }//end if
    }//end for
    
    cout << "Sort: Selection Sort" << endl;
    cout << "Size of list: " << list.size() << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    cout << "Number of swaps: " << swaps << endl;
}//end func


void shellSort(vector<int>& list)
//pre: list has at least one item
//post: list is sorted
//sorts list using shellsort algorithm
{
    int comparisons = 0;
    int swaps = 0;
    int temp;
    int j;
    int gap;
    
    
     for(gap = list.size()/2; gap > 0; gap = gap/2)
     {
        for(int i = gap; i < list.size(); i++)
        {
            temp = list[i];
            comparisons++;
            for(j = 1; (j >= gap) && (list[j-gap] > temp); j = j-gap)
            {   //swap
                int temp2 = list[j];
                list[j] = list[j-gap];
                list[j-gap] = temp2;
                swaps++;
            }//end for
            list[j] = temp;
        }//end for
     }//end for
     
    
    cout << "Sort: Shellsort" << endl;
    cout << "Size of list: " << list.size() << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    cout << "Number of swaps: " << swaps << endl;
}


void mergeSort(vector<int>& list)
//pre: list has at least one item
//post: list is sorted
//list is sorted using the mergesort algorithm
{
    vector<int> temp;
    temp = list;
    int left = 0;
    int right = list.size()-1;
    int comparisons = 0;
    
    mSort(list, temp, left, right, comparisons);
    
    cout << "Sort: Mergesort" << endl;
    cout << "Size of list: " << list.size() << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    cout << "Mergesort does not swap." << endl;
}



void quickSort(vector<int>& list)
//pre: list has at least one item
//post: list is sorted
//list is sorted using quicksort algorithm
{
    int comparisons = 0;
    int swaps = 0;
    
    qSort(list, 0, list.size()-1, comparisons, swaps);
    
    cout << "Sort: Quicksort" << endl;
    cout << "Size of list: " << list.size() << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    cout << "Number of swaps: " << swaps << endl;
}

void bozo(vector<int>& list)
//pre: list has at least one item
//post: list is sorted if size <= 5
//list is sorted using bozo sort
{
    if(list.size() > 5)
    {
        cout << "Bozo sort will not work well with more than 5 items." << endl;
        return;
    }//end if

}//end bozo


//**********************************************
//************** BEGIN HELPERS *****************
//**********************************************


void mSort(vector<int>& list, vector<int>& temp, int left, int right, int& comparisons)
//pre: list/temp have at least one item, left/right !=0, called from mergeSort
//post: list is sorted
//sorts list using mergesort algorithm
{
    int mid;

    if(right > left)//more than one element
    {
        mid = (left + right) / 2;
        mSort(list, temp, left, mid, comparisons); //left half
        mSort(list, temp, mid+1, right, comparisons);//right half
        merge(list, temp, left, mid, right, comparisons);//bring it all together
    }//end if
}//end func

void merge(vector<int>& list, vector<int>& temp, int left, int mid, int right, int& comparisons)
//pre: list/temp not empty, left,mid,right !=0, called from mSort
//post: merges items from temp back into list
//helper function for mergesort
//NOTE: had assistance from Eric Anthony for this function
{
    int l = left;
    int i = left;
    int j = mid+1;
    int k = 0;
    
    while(l <= mid && j <= right)
    {
        if(list[l] <= list[j])
        {
            comparisons++;
            temp[i] = list[l];
            l++;
        }//end if
        else
        {
            temp[i] = list[j];
            j++;
        }//end else
        i++;
    }//end while
        
    if(l > mid)
    {
        for(k = j; k <= right; k++)
        {
            temp[i] = list[k];
            i++;
        }//end for
    }//end if
    else
    {
        for(k = l; k <= mid; k++)
        {
            temp[i] = list[k];
            i++;
        }//end for
    }//end else
        
    for(k = left; k <= right; k++)
    {
        list[k] = temp[k];
    }//end for
}//end func

void qSort(vector<int>& list, int low, int high, int& comparisons, int& swaps)
//pre: list has at least one item, low/high != 0, called from quickSort
//post: list is sorted
//sorts list using quicksort algorithm
{
    int mid;
    
    if(low < high)
    {
        mid = partition(list, low, high, comparisons, swaps);//find pivot
        qSort(list, low, mid-1, comparisons, swaps);//left half
        qSort(list, mid+1, high, comparisons, swaps);//right half
    }//end if
}//end func

int partition(vector<int>& list, int low, int high, int& comparisons, int& swaps)
//pre: list has at least one item, low/high != 0
//post: returns new pivot
{
    int pivot = list[low];
    
    do {
        while(low < high && list[high] >= pivot)
        {
            comparisons++;
            high = high - 1;
        }//end while
        
        if(low < high)
        {
            list[low] = list[high];
            while((low < high) && (list[low] <= pivot))
            {
                comparisons++;
                low++;
            }//end while
            if(low < high)
            {
                swaps++;
                list[high] = list[low];
            }//end if
        }//end if
    } while (low < high);//end do-while
    
    swaps++;
    list[low] = pivot; //moves pivot to its appropriate spot
    
    return low; //marks position
}

//**********************************************
//*************** BEGIN OTHER ******************
//**********************************************

int GetInput()
//pre: none
//post: size is returned to caller
//gets desired size from user
//does not account for bad input
{
    int size;
    
    cout << "Please enter the size of the array: " << endl;
    cin >> size;
    
    return size;
}

bool TestSort(vector<int>& list, vector<int>& otherList)
//pre: both lists have at least one item
//post: returns true if lists are equal, false otherwise
//outputs a message indicating whether the two lists are equal, and returns a boolean stating as such
{
    bool sorted = false;
    
    if(list == otherList)
    {
        sorted = true;
    
        cout << "Our sort produced an equivalent result to the built in sort!" << endl;
    }
    else
        cout << "Our sort did NOT produce the same result as the built in sort. Please try again." << endl;
    
    
    cout << endl << endl << endl;
    
    return sorted;
}

void TimeToSort(vector<int>& list, vector<int>& otherList)
//pre: list and otherlist have items
//post: calls each sort and tests if their results are equivalent to c++'s built in sort
//can add other sorts if needed
{
    vector<int> temp = otherList;
    
    //use the built in sort to sort the second list
    sort(otherList.begin(), otherList.end());
    
    cout << endl;
    
    bubbleSort(list);
    TestSort(list, otherList);
    list = temp; //reset the list
    
    selectionSort(list);
    TestSort(list, otherList);
    list = temp; //reset the list
    
    shellSort(list);
    TestSort(list, otherList);
    list = temp; //reset the list
    
    mergeSort(list);
    TestSort(list, otherList);
    list = temp; //reset the list
    
    quickSort(list);
    TestSort(list, otherList);
    list = temp; //reset the list
    
}
