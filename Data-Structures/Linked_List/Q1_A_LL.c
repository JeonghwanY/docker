//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	// 뭘 먼저 구현해야해 오름차순이 되게 index의 위치를 구해야지
	int index=0;
	ListNode* cur;
	cur=ll->head;
	while (cur!=NULL){
		if (cur->item==item)
			return -1;
		if (cur -> item >item)
			break;
		cur = cur->next;
		index++;
	}
	if (insertNode(ll,index,item)==0)///////////이부분 그냥 이 함수만 리턴했었음.
		return index;
	else
		return -1;
	


}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}
//insertNode -> 인덱스에 값을 추가하는 것 파이썬에서는 .append() 
//c에서는 리스트노드, 값, 다음노드 주소가 필요함. 각각을 포인터로 가져온다.

int insertNode(LinkedList *ll, int index, int value){

	ListNode *newnode,*prev;
	if(ll==NULL||0>index||index>ll->size)//ll널을 확인하는게 연결리스트자체가 없으면 노드를 추가못하니까
		return -1;
	newnode=(ListNode *)malloc(sizeof(ListNode));
	if (newnode==NULL) return -1;////////////메모리 할당 실패대비라는데 좀 알아둬야할듯

	//ll->head=newnode;
	newnode->item=value;
	newnode->next=NULL;//왜 index가 아닌가? index는 아래에서 정해주려나?
	//index가 head일때 0일때
	if (index==0){
		newnode->next=ll->head;//////////이거 좀 중요하다 잘 알아두기
		ll->head=newnode;
	}else{//인덱스가 중앙이나 끝일때 어떻게 삽입을 할까
		prev=findNode(ll,index-1);//인덱스가 현재 넣으려고하는값의 바로 앞을 찾는 것
		if(prev==NULL) return -1;
		newnode->next=prev->next;///다음주소를 연결해주는거 뉴노드의 넥스트값은 2고
		prev->next=newnode;//뉴노드를 넥스트값으로 가지는 prev는 노드 1이다

	}
	ll->size++;

	
	return 0;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
