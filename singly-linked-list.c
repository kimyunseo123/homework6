#include<stdio.h>
#include<stdlib.h>

// 필요한 헤더파일 추가
typedef struct Node { // (typedef를 사용하여) listNode 구조체 생성
	int key;
	struct Node* link;
} listNode;

typedef struct Head { // (typedef를 사용하여) headNode 구조체 생성
	struct Node* first;
}headNode;


// 함수 리스트
headNode* initialize(headNode* h);

int freeList(headNode* h); // 메모리 해제

int insertFirst(headNode* h, int key); // list 처음에 key에 대한 노드 추가
int insertNode(headNode* h, int key); // list 검색 후, 노드 삽입
int insertLast(headNode* h, int key); // list에 key에 대한 노드 추가

int deleteFirst(headNode* h);  // list의 첫번째 노드 삭제
int deleteNode(headNode* h, int key); // list에 key에 대한 노드 삭제
int deleteLast(headNode* h); // list의 마지막 노드 삭제

int invertList(headNode* h); // list의 link를 역순으로 재배치
void printList(headNode* h); // list 출력

int main()
{
	char command; // 변수 command
	int key; // 변수 key
	headNode* headnode=NULL;

	do{
        printf("[----- [Kim Yun Seo]  [2020021016] -----]\n");

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
		scanf(" %c", &command); // command 값 받기

		switch(command) {
		case 'z': case 'Z': // command 값이 z 또는  일 경우
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': // command 값이 p 또는 P 일 경우
			printList(headnode);
			break;
		case 'i': case 'I': // command 값이 i 또는 I 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // command 값이 d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // command 값이 n 또는 N 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertLast(headnode, key);
			break;
		case 'e': case 'E':// command 값이 e 또는 E 일 경우
			deleteLast(headnode);
			break;
		case 'f': case 'F': // command 값이 f 또는 F 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // command 값이 t 또는 T 일 경우
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // command 값이 r 또는 R 일 경우
			invertList(headnode);
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행
	return 1;
}

headNode* initialize(headNode* h) {

	// headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(h != NULL) // headNode가 NULL이 아님
		freeList(h); // 메모리 해제
 
	// headNode에 대한 메모리를 할당하여 리턴
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // temp에 'headNode' type으로 주소 받기
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	// h와 연결된 listNode 메모리 해제
	// headNode도 해제되어야 함
	listNode* p = h->first;
	listNode* prev = NULL;

	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev); // listNode 메모리 해제
	}
	free(h); // headNode 메모리 해제
	return 0;
}

// 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 'listNode' type으로 주소 받기
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	// key를 기준으로 삽입할 위치를 찾는다 
	while(n != NULL) {
		if(n->key >= key) {
			
			if(n == h->first) { // 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 
				h->first = node;
				node->link = n;
			} else { // 중간이거나 마지막인 경우 
				node->link = n;
				trail->link = node;
			}
			return 0;
		}
		trail = n;
		n = n->link;
	}
	trail->link = node; // 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입
	return 0; 
}

// list에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 'listNode' type으로 주소 받기
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) // first가 NULL일 경우
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) { // link가 NULL이 아닐 경우
		n = n->link;
	}
	n->link = node;
	return 0;
}

// list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 'listNode' type으로 주소 받기
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

// list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // first가 NULL일 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	// key를 기준으로 삽입할 위치를 찾는다 
	while(n != NULL) {
		if(n->key == key) {
		
			if(n == h->first) { // 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 
				h->first = n->link;
			} else { // 중간인 경우거나 마지막인 경우 
				trail->link = n->link;
			}
			free(n); // 노드 삭제
			return 0;
		}
		trail = n;
		n = n->link;
	}
	// 위치를 찾지 못 한경우 
	printf("cannot find the node for key = %d\n", key); // 위치를 찾지 못했다고 경고
	return 0;

}

// list의 마지막 노드 삭제
int deleteLast(headNode* h) {

	if (h->first == NULL) // first가 NULL일 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	// 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 
	if(n->link == NULL) { // link가 NULL일 경우
		h->first = NULL;
		free(n); // 노드 삭제
		return 0;
	}
	// 마지막 노드까지 이동 
	while(n->link != NULL) { // link가 NULL이 아닐 경우
		trail = n;
		n = n->link;
	}
	trail->link = NULL; // n이 삭제되므로, 이전 노드의 링크 NULL 처리 
	free(n); // 노드 삭제

	return 0;
}

 // list의 첫번째 노드 삭제
int deleteFirst(headNode* h) {

	if (h->first == NULL) // first가 NULL일 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;
	h->first = n->link;
	free(n); // 노드 삭제
	return 0;
}

 // 리스트의 링크를 역순으로 재 배치
int invertList(headNode* h) {


	if(h->first == NULL) { // first가 NULL일 경우
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){ // first가 NULL이 아닐 경우
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}
	h->first = middle;
	return 0;
}

void printList(headNode* h) { // list 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // headNode가 NULL일 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // listNode가 NULL이 아닐 경우
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
