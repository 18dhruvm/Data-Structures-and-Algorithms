#include <bits/stdc++.h>
using namespace std;

class Node 
{
public:
	int data;
	Node* next;
};
void Split(Node* source,Node** frontRef, Node** backRef)
{
	Node* fast;
	Node* slow;
	slow = source;
	fast = source->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}
Node* SortedMerge(Node* a, Node* b)
{
	Node* result = NULL;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (a->data <= b->data) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else {
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return (result);
}
void MergeSort(Node** headRef)
{
	Node* head = *headRef;
	Node* a;
	Node* b;

	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	Split(head, &a, &b);

	MergeSort(&a);
	MergeSort(&b);

	*headRef = SortedMerge(a, b);
}

void print(Node* node)
{
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
}

void push(Node** head_ref, int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

int main()
{
	Node* res = NULL;
	Node* a = NULL;

	cout << "Enter no of elements to be sorted: ";
	int no=0;
	cin >> no;
	
	for (int i=0;i<no;i++)
	{
	    int element;
	    cout << "Enter element: ";
	    cin >> element;
	    push(&a, element);
	}

	cout << "\nUnSorted Linked List is: \n";
	print(a);
	MergeSort(&a);

	cout << "\nSorted Linked List is: \n";
	print(a);

	return 0;
}

