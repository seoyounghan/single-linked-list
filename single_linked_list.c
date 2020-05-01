/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>//입출력 전처리기 파일 
#include<stdlib.h>//문자열 전처리기 파일

 /* 필요한 헤더파일 추가 */

typedef struct Node {//노드의 키값과 링크를 저장
	int key;
	struct Node* link;
} listNode;

typedef struct Head {//첫번째 노드를 포인팅 해줄 구조체
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);//구조체 동적 할당
int freeList(headNode* h);//구조체 동적 할당 해제

int insertFirst(headNode* h, int key);//첫번째 노드 추가
int insertNode(headNode* h, int key);//노드 삽입
int insertLast(headNode* h, int key);//마지막 노드 삽입

int deleteFirst(headNode* h);//첫번째 노드 지움
int deleteNode(headNode* h, int key);//노드를 키값 입력을 통해 지움
int deleteLast(headNode* h);//마지막 노드를 지움
int invertList(headNode* h);//리스트를 뒤집는다

void printList(headNode* h);//리스트를 프린팅 해준다.

int main()
{
	char command;//사용자에게 메뉴를 입력받을 변수
	int key;//키값을 입력받을 변수
	headNode* headnode = NULL;//headnode 값 선언

	do {
		printf("-------------[한서영]  [2019038038]------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}//switch문을 통해서 입력받고 메뉴 선택 가능

	} while (command != 'q' && command != 'Q');//끝날때 까지

	return 1;
}

headNode* initialize(headNode* h) {//구조체 동적 할당 초기화

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {//list 해제
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//p에 할당

	listNode* prev = NULL;//널 값으로 바꾸어줌
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}//구조체 안에 있는 값들 해제
	free(h);//h해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {//해더 노드 생성

	listNode* node = (listNode*)malloc(sizeof(listNode));//동적 할당
	node->key = key;//key값 노드에 할당

	node->link = h->first;
	h->first = node;//노드의 링크를 변경해 주어 헤더자리에 오게 한다.

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* temp = (listNode*)malloc(sizeof(listNode));//임시 저장 구조체
	listNode *prenode = (listNode*)malloc(sizeof(listNode));//노드의 전 단계 구조체를담음
	listNode *node = (listNode*)malloc(sizeof(listNode));//임시 저장 구조체

	temp->key = key;//temp에 키 값을 담음

	if ((h->first) ==NULL)
	{
		insertFirst(h, key);
		h->first->link = NULL;

		return 0;
	}//만약 비어있는 구조체인 경우 헤더값을 추가한 뒤에 널 값을 이어줌
	else
	{
		node = (h->first->link);
		prenode = (h->first);
	}//만약 비어있지 않다면 노드와 프리 노드에 각각 값을 할당한다.

	if ((prenode->key) > key)//만약 키값이 첫번째 노드 값보다 작으면 헤더 삽입을 통해 insert
	{
		insertFirst(h, key);
		return 0;
	}
	if (node == NULL)//만약 node 값이 아무것도 없다면 마지막 값에 넣어줌
	{
		insertLast(h, key);
		return 0;
	}

	while ((node) != NULL)//노드값이 널이 아닌 경우 반복
	{

		if ((node->key) >= (key))//만약 키가 더 작으면 삽입을 해준다. 
		{//prenode의 링크를 temp에 연결 후 temp의 링크를 node에 연결
			(temp->link) = (prenode->link);
			(prenode->link) = temp;

			return 0;
		}
		if ((node->link) == NULL)//만약 다음 값이 없다면 반복문 나감
			break;
		prenode = node;
		node = (node->link);//노드와 프리노드 값 다음 값으로 

	}
	if ((node->link) == NULL)
		insertLast(h, key);//만약 다음 값이 없다면 마지막에 노드 추가

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//리스트 마지막에 값 추가

	listNode* temp = (listNode*)malloc(sizeof(listNode));
	listNode *node = (listNode*)malloc(sizeof(listNode));//임시로 값을 받아올 리스트 생성

	node = (h->first);
	(temp->key) = key;//임시 리스트에 값 저장


	while (1) {//헤더 리스트를 받아왔으므로 마지막 부분까지 받아준 후 node와 link연결
		if ((node->link) == NULL)
		{
			(node->link) = temp;
			(temp->link) = NULL;
			break;
		}
		node = (node->link);
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp = (listNode*)malloc(sizeof(listNode));

	if (h == NULL)//값이 들어있지 않으면 삭제 할 수 없음
	{
		printf("값이 들어있지 않은 리스트\n");
	}

	temp = h->first->link;//임시 값 저장

	h->first->link = NULL;
	h->first = temp;//헤더를 바꿔 주어서 저장

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* prenode = (listNode*)malloc(sizeof(listNode));
	listNode *node = (listNode*)malloc(sizeof(listNode));//값을 임시로 저장

	if (h == NULL)//비어있는지 검사
	{
		printf("값이 들어있지 않은 리스트\n");
	}
	
	prenode = h->first;
	node = h->first->link;//노드에 값을 저장해준다

	if ((h->first->key) == key)//만약 키 값이 같으면 첫번째 노드를 삭제한다.
	{
		deleteFirst(h);
		return 0;
	}
	while (node!=NULL)//첫번째 이후 값 부터는 키 값 검사후 노드를 다음 노드로 바꾸어줌
	{
		if ((node->key) == key)
		{
			(prenode->link) = (node->link);//키 값이 같으면 링크 값 바꾸어줌
			return 0;
		}
		prenode = node;
		node = (node->link);

		if ((node->link) == NULL)
			break;
	}
	if (node->link == NULL)//마지막 값 일 경우
		deleteLast(h);

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {//마지막 노드 삭제
	listNode* prenode = (listNode*)malloc(sizeof(listNode));
	listNode *node = (listNode*)malloc(sizeof(listNode));//임시 저장 구조체

	if (h == NULL)//값이 들어있는지 검사
	{
		printf("값이 들어있지 않은 리스트\n");
	}

	prenode = h->first;
	node = h->first->link;//임시 노드에 값 할당

	if (prenode->link == NULL)
		freeList(h);//만약 값이 하나만 들어있다면 할당 해제를 해줌

	while (1)
	{
		if (node->link == NULL)
		{
			prenode->link = NULL;
			return 0;
		}
		prenode = node;
		node = node->link;
	}//마지막 값까지 간 다음에 프리노드의 링크를 끊어 주어서 삭제
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	listNode* copy = (listNode*)malloc(sizeof(listNode));//임시 저장 구조체

	if (h == NULL)//값이 있는지 검사
	{
		printf("값이 들어있지 않은 리스트\n");
	}

	copy = (h->first);//임시로값을 저장

	insertFirst(temp, copy->key);//첫번째 값 넣은 후
	temp->first->link = NULL;//마지막 으로 갈 것이므로 널값을 이어줌

	copy = (copy->link);//다음 값으로 넘김

	while ((copy) != NULL)//copy의 키 값을 순서대로 temp에 앞으로 집어 넣는 형식으로 해줌
	{
		insertFirst(temp, copy->key);
		copy = (copy->link);

	}

	h->first->key = temp->first->key;
	h->first->link = temp->first->link;//copy값을 h에 복사

	return 0;
}


void printList(headNode* h) {//리스트 프린팅
	int i = 0;//카운팅해줄 변수
	listNode* p;//노드 값 임시 저장

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}//리스트가 비어있는 경우

	p = h->first;//첫번째 값 포인팅

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}//리스트 출력

	printf("  items = %d\n", i);
}
