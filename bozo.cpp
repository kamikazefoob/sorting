//Bozo sort
//
//Bozo sort takes two random items in the list, and swaps them.
//It continues doing this with "new" random elements for each iteration until sorted.
//"New" means that random elements are chosed each iteration, with no guarantee of non-repetition
//
//Written by Todd Tirums

#include <algorithm>
//for adjacent_find, generate_n
#include <vector>
//self-explanatory
#include <iostream>
//self-explanatory
#include <ctime>
//for time
#include <string>
//for atoi
#include <cstring>
//for strcmp

using namespace std;

void Usage();
void Bozo(vector<int>& list);
bool IsInOrder(const vector<int>& x);

int main(int argc, char* argv[])
{
	vector<int> list;
	//list of items to be sorted
	int parseArgs = 1;
	//number of arguments parsed, start at 1 to ignore argv[0]
	bool verbose = false;
	//flag for output
	bool usage = false;
	//flag for usage, if this is set, nothing else is done.
	bool size = false;
	//flag for setting size of list
	bool def = false;
	//default settings
	int num = 5;
	//size of list
	unsigned long long counter = 0;
	//number of permutations

    
    //Parse command line arguments
    for(parseArgs = 1; parseArgs < argc; parseArgs++)
	{
		if(tolower(*argv[parseArgs]) == 'v' || !strcmp(argv[parseArgs], "--verbose"))
		{//verbose
			verbose = true;
		}//end verbose
		else if(tolower(*argv[parseArgs]) == 'u' || !strcmp(argv[parseArgs], "--usage"))
		{//usage
			usage = true;
		}//end usage
		else if(tolower(*argv[parseArgs]) == 's' || !strcmp(argv[parseArgs], "--size"))
		{//size
			size = true;
            
			if((parseArgs+1) < argc)
			{
				parseArgs++;
				num = atoi(argv[parseArgs]);
			}
			else
			{
				cerr << "Insufficient arguments\n";
				return -1;
			}
		}//end size
        else if(tolower(*argv[parseArgs]) == 'q')
        {//sizeVerbose
            size = true;
            verbose = true;
            
            if((parseArgs+1) < argc)
            {
                parseArgs++;
                num = atoi(argv[parseArgs]);
            }
            else
            {
                cerr << "Insufficient arguments\n";
                return -1;
            }
        }//end sizeVerbose
		else if(tolower(*argv[parseArgs]) == 'd' || !strcmp(argv[parseArgs], "default"))
		{//size
			def = true;
			parseArgs++;
		}//end default
		else
		{//invalid argument
			cerr << "Invalid arguments" << endl << endl;
			Usage();
			return -1;
		}//end invalid arguments
	}

	if(usage)
	{//if usage is set, nothing else is done, so we return 0
		verbose = false;
		Usage();
		return 0;
	}

	srand(time(NULL));
    //seed rng

	// Initiate the vector with num random numbers
	generate_n(back_inserter(list), num, rand);

	while(!IsInOrder(list))
	{//perform until sorted
		if(verbose)
		{
			copy(list.begin(), list.end(), ostream_iterator<int>(cout, " "));
			cout << "\n\n";
		}

		Bozo(list);
		counter++;
	}

	cout << "Sorting took " << counter << " attempts." << endl;

	return 0;
}

void Usage()
//pre: none
//post: usage instructions are sent to cout
{
	cout << "Bozo usage:" << endl << endl;
	cout << "u or --usage will display this message" << endl << endl;
    cout << "v or --verbose will output the contents of the list during sorting" << endl;
	cout << "s or --size, followed by an integer, will set the size of the list as specified" << endl;
    cout << "q will set both verbose and set the size as specified" << endl;

	cout << endl << endl;

	return;
}

void Bozo(vector<int> &list)
//pre: list has at least two items
//post: two different items in list have swapped locations with each other
//swap two random items, do not swap an item with itself
{
    int swap;
	//temporary location to hold item to swap
	int i = 0;
	//index into the list
	int j = 0;
	//second index into the list

	srand(time(NULL));
	//seed random

	while(i == j)
	{//continue until unequal
		i = rand() % list.size();
		j = rand() % list.size();
	}

	//perform swap
	swap = list[i];
	list[i] = list[j];
	list[j] = swap;

	return;
}

bool IsInOrder(const vector<int>& x)
//checks if the list is sorted
//pre: x is not empty
//post: returns true if x is sorted, false otherwise
{
    return adjacent_find(x.begin(), x.end(), greater<int>()) == x.end();
}
