#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
struct COFFEE {
    string articul;
    int count = 0;
    float price = 0;
    COFFEE* next = NULL;
};
 
struct BOUUGHTTHINGS {
    string name;
    float price = 0;
    BOUUGHTTHINGS* next = NULL;
};
 
COFFEE* prependNode(COFFEE* head, string articul, int count, float price)
{
    COFFEE* newNode = new COFFEE;
    newNode->articul = articul;
    newNode->count = count;
    newNode->price = price;
    newNode->next = head;
    head = newNode;
    return head;
}
 
void displayList(COFFEE* head)
{
    COFFEE* list = head;
    int count = 0;
    while (list != NULL)
    {
        cout << count++ << ". ";
        cout << list->articul << " ";
        cout << list->count << " ";
        cout << list->price << " ";
        list = list->next;
        cout << endl;
    }
}
 
void removeSpecialNode(COFFEE* head, string wantedArtucule)
{
    if (head->next == NULL)
    {
        return;
    }
    COFFEE* prev = head;
    COFFEE* tempt = head->next;
    if (tempt->articul == wantedArtucule)
    {
        tempt = head->next;
        prev->next = tempt->next;
        delete tempt;
    }
    else
    {
        removeSpecialNode(head->next, wantedArtucule);
    }
}
 
float findMaxPrize(COFFEE* head)
{
    COFFEE* list = head;
    float maxPrice = list->price;
    while (list != NULL)
    {
        if (maxPrice < list->price)
        {
            maxPrice = list->price;
        }
        list = list->next;
    }
    return maxPrice;
}
 
float findMinPrize(COFFEE* head)
{
    COFFEE* list = head;
    float minPrice = list->price;
    while (list != NULL)
    {
        if (minPrice > list->price)
        {
            minPrice = list->price;
        }
        list = list->next;
    }
    return minPrice;
}
 
void search(COFFEE* head)
{
    cout << "1. name" << endl;
    cout << "2. count" << endl;
    cout << "3. price" << endl;
 
    int option;
    cin >> option;
 
    COFFEE* list = head;
    string name;
    int count;
    float price;
    switch (option)
    {
    case 1:
        cin >> name;
        while (list != NULL)
        {
            if (name == list->articul)
            {
                cout << "found";
                return;
            }
            list = list->next;
        }
        cout << "not found";
        break;
    case 2:
        cin >> count;
        while (list != NULL)
        {
            if (count == list->count)
            {
                cout << "found";
                return;
            }
            list = list->next;
        }
        cout << "not found";
        break;
    case 3:
        cin >> price;
        while (list != NULL)
        {
            if (price == list->price)
            {
                cout << "found";
                return;
            }
            list = list->next;
        }
        cout << "not found";
        break;
    }
 
}
 
bool mainMenu(COFFEE* head)
{
    cout << "1. Buy" << endl;
    cout << "2. Pay" << endl;
    cout << "3. Find the cheapest product" << endl;
    cout << "4. Find the most expensive product" << endl;
    cout << "5. Search" << endl;
    cout << "6. Show menu" << endl;
    cout << "0. Exit" << endl;
 
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
 
        return true;
        break;
    case 2:
 
        return true;
        break;
    case 3:
        cout << findMinPrize(head) << endl;
        return true;
        break;
    case 4:
        cout << findMaxPrize(head) << endl;
        return true;
        break;
    case 5:
        search(head);
        cout << endl;
        return true;
        break;
    case 6:
        displayList(head);
        return true;
        break;
    case 0:
 
        return false;
        break;
    }
 
}
 
 
int main()
{
    COFFEE* head = NULL;
    BOUUGHTTHINGS* head2 = NULL;
    string articuls;
    int num;
    float price1;
    int addCount;
 
    cout << "enter number: ";
    cin >> addCount;
 
    for (int i = 0; i < addCount; i++)
    {
        cin >> articuls;
        cin >> num;
        cin >> price1;
        head = prependNode(head, articuls, num, price1);
    }
 
    /*bool exit = false;
    do {
        exit = mainMenu(head);
    } while (exit);*/
 
 
 
 
    displayList(head);
    cout << "Choose index: ";
    int option;
    cin >> option;
 
    COFFEE* list = head;
    for (int i = 0; i < option; i++)
    {
        list = list->next;
    }
    if (list->count == 1)
    {
        removeSpecialNode(head, list->articul);
    }
    else
    {
        list->count--;
    }
    displayList(head);

    }

RAW Paste Data
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct COFFEE {
	string articul;
	int count = 0;
	float price = 0;
	COFFEE* next = NULL;
};

struct BOUUGHTTHINGS {
	string name;
	float price = 0;
	BOUUGHTTHINGS* next = NULL;
};

COFFEE* prependNode(COFFEE* head, string articul, int count, float price)
{
	COFFEE* newNode = new COFFEE;
	newNode->articul = articul;
	newNode->count = count;
	newNode->price = price;
	newNode->next = head;
	head = newNode;
	return head;
}

void displayList(COFFEE* head)
{
	COFFEE* list = head;
	int count = 0;
	while (list != NULL)
	{
		cout << count++ << ". ";
		cout << list->articul << " ";
		cout << list->count << " ";
		cout << list->price << " ";
		list = list->next;
		cout << endl;
	}
}

void removeSpecialNode(COFFEE* head, string wantedArtucule)
{
	if (head->next == NULL)
	{
		return;
	}
	COFFEE* prev = head;
	COFFEE* tempt = head->next;
	if (tempt->articul == wantedArtucule)
	{
		tempt = head->next;
		prev->next = tempt->next;
		delete tempt;
	}
	else
	{
		removeSpecialNode(head->next, wantedArtucule);
	}
}

float findMaxPrize(COFFEE* head)
{
	COFFEE* list = head;
	float maxPrice = list->price;
	while (list != NULL)
	{
		if (maxPrice < list->price)
		{
			maxPrice = list->price;
		}
		list = list->next;
	}
	return maxPrice;
}

float findMinPrize(COFFEE* head)
{
	COFFEE* list = head;
	float minPrice = list->price;
	while (list != NULL)
	{
		if (minPrice > list->price)
		{
			minPrice = list->price;
		}
		list = list->next;
	}
	return minPrice;
}

void search(COFFEE* head)
{
	cout << "1. name" << endl;
	cout << "2. count" << endl;
	cout << "3. price" << endl;

	int option;
	cin >> option;

	COFFEE* list = head;
	string name;
	int count;
	float price;
	switch (option)
	{
	case 1:
		cin >> name;
		while (list != NULL)
		{
			if (name == list->articul)
			{
				cout << "found";
				return;
			}
			list = list->next;
		}
		cout << "not found";
		break;
	case 2:
		cin >> count;
		while (list != NULL)
		{
			if (count == list->count)
			{
				cout << "found";
				return;
			}
			list = list->next;
		}
		cout << "not found";
		break;
	case 3:
		cin >> price;
		while (list != NULL)
		{
			if (price == list->price)
			{
				cout << "found";
				return;
			}
			list = list->next;
		}
		cout << "not found";
		break;
	}

}

bool mainMenu(COFFEE* head)
{
	cout << "1. Buy" << endl;
	cout << "2. Pay" << endl;
	cout << "3. Find the cheapest product" << endl;
	cout << "4. Find the most expensive product" << endl;
	cout << "5. Search" << endl;
	cout << "6. Show menu" << endl;
	cout << "0. Exit" << endl;

	int option;
	cin >> option;
	switch (option)
	{
	case 1:

		return true;
		break;
	case 2:

		return true;
		break;
	case 3:
		cout << findMinPrize(head) << endl;
		return true;
		break;
	case 4:
		cout << findMaxPrize(head) << endl;
		return true;
		break;
	case 5:
		search(head);
		cout << endl;
		return true;
		break;
	case 6:
		displayList(head);
		return true;
		break;
	case 0:

		return false;
		break;
	}

}


int main()
{
	COFFEE* head = NULL;
	BOUUGHTTHINGS* head2 = NULL;
	string articuls;
	int num;
	float price1;
	int addCount;

	cout << "enter number: ";
	cin >> addCount;

	for (int i = 0; i < addCount; i++)
	{
		cin >> articuls;
		cin >> num;
		cin >> price1;
		head = prependNode(head, articuls, num, price1);
	}

	/*bool exit = false;
	do {
		exit = mainMenu(head);
	} while (exit);*/




	displayList(head);
	cout << "Choose index: ";
	int option;
	cin >> option;

	COFFEE* list = head;
	for (int i = 0; i < option; i++)
	{
		list = list->next;
	}
	if (list->count == 1)
	{
		removeSpecialNode(head, list->articul);
	}
	else
	{
		list->count--;
	}
	displayList(head);
}

