#include <iostream>
#include <string>
using namespace std;
 
struct COFFEE
{
    string name = "";
    int count = 0;
    float price = 0;
    COFFEE* next = NULL;
};
 

COFFEE* prependNode(COFFEE* head )
{
    COFFEE* newNode = new COFFEE;
    
    cin >> newNode->name;
    cin >> newNode->count;
    cin >> newNode->price;
 
    newNode->next = head;
    head = newNode;
 
    return head;
}
 

void displayNodes(COFFEE* head)
{
    COFFEE* list = head;
    
    while (list != NULL)
    {
        cout << list->name << " " << list->count << " " << list->price << endl;
        list = list->next;
    }
}
 
void calculatePrice(COFFEE* head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        cout << head->name;
        cout << " "<<(head->count)*(head->price) << endl;
        calculatePrice(head->next);
    }
}

float totalPrice(COFFEE* head, float S)
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        S = (head->count) * (head->price);
        return S + totalPrice(head->next, S);
    }
}
 
int main()
{
    COFFEE* head = NULL;
    
    for (size_t i = 0; i < 3; i++)
    {
        head = prependNode(head);
    }
    cout << endl;
 
    displayNodes(head);
    cout << endl;
 
    calculatePrice(head);
    cout << endl;
 
    cout << "Total price: " << totalPrice(head, 0);
    cout << endl;
}
