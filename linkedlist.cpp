
#include <iostream>
#define use_CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

#define MAX_NODE 100
using namespace std;
struct Node{
	int data;
	Node* prev;
	Node* next;
};

struct NodeHeap{
	int use;
	Node node;
};

NodeHeap heap[MAX_NODE];
	
void initHeap(void){
	for (int i = 0; i < MAX_NODE; i++)
		heap[i].use = 0;
}

void initNode(Node* node){
	node->data = 0;
	node->prev = node;
	node->next = node;
}

Node* getNode(){
	for (int i = 0; i < MAX_NODE; i++){
		if (!heap[i].use){
			heap[i].use = 1;
			initNode( &(heap[i].node) );
			return &(heap[i].node);
		}
	}
	return NULL;
}

void destroyNode(Node* node){
	NodeHeap* heap_node = (NodeHeap*)((int*)node - 1);
	heap_node->use = 0;
}

Node* appendListNode(Node* list, int data)
{
	Node* node = getNode();
	node->data = data;
	if (list == NULL)
	{
		return node;
	}
	else
	{
		Node* last = list->prev;
		last->next = node;
		list->prev = node;
		node->prev = last;
		node->next = list;
		return list;
	}
}

Node* removeListNode(Node* list, Node* node)
{
	if (list == list->next)
	{
		destroyNode(node);
		return NULL;
	}
	else
	{
		Node* prev = node->prev;
		Node* next = node->next;
		prev->next = next;
		next->prev = prev;
		destroyNode(node);
		return (list == node) ? next : list;
	}
}

int main(int argc, char* argv[])
{

	int N;
	
	Node* list = NULL;
	Node* node = NULL;

	initHeap();

	//scanf("%d", &N);
	cout << "input number of Node:";
	cin >> N;
	
	for (int i = 0; i < N; i++)
		list = appendListNode(list, i+1);
	

	node = list;
	while (list != list->next)	{
		Node* nextNode = node->next;
		list = removeListNode(list, node);
		node = nextNode->next->next;
	}

	printf("#ANS= %d\n", list->data);
	
	return 0;
}
