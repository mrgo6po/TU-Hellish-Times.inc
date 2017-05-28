#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dictionary{
	char word[20];
	char transWord[20];
	char typeOfWord[20];
	char exampLine[81];
	float date;
	float rating;
	struct Dictionary *next;
};


struct Node* readFile(FILE *fp){
	struct Dictionary dic;
	struct Node *head=NULL;
	struct Node *current=NULL;

	while(1){
		if(fread(&tv, sizeof(struct Dictionary), 1, fp)<=0){
			break;
		}
		if(head==NULL){
			head = (struct Node*)malloc(sizeof(struct Node));
			current = head;
		}else{
			current->next = (struct Node*)malloc(sizeof(struct Node));
			current = current->next;
		}
		current[0].dic = dic;
		current->next=NULL;
	}
	return head;
}

int printAll(struct Node *node){
	int i=1;

	if(node == NULL){
		printf("No words added.\n");
		return -1;
	}

	while(node!=NULL){
		printf("%d:\n", i);
		printf("\n\tWords:\t\t%lld", node[0].dic.word);
		printf("\n\tTranslation:\t\t%s", node[0].dic.transWord);
		printf("\n\tWord class:\t%s", node[0].typeOfWord);
		printf("\n\tExample translation: \t\t%lf", node[0].dic.exampLine);
		printf("\n\tDate added:\t\t%d\n", node[0].dic.date);
		printf("\n\tTranslation rating:\t\t%d\n", node[0].dic.rating);
		node = node->next;
		i++;
	}
	return 0;
}

struct Node* addWord(struct Node *head){
	struct Node *node = NULL;
	int word_status=0;
	char word[20];

	if(head == NULL){
		head = (struct Node*)malloc(sizeof(struct Node));
		head->next = NULL;
		node = head;
	}else{
		node = head;
		while(node->next!=NULL){
			node = node->next;
		}
		node->next = (struct Node*)malloc(sizeof(struct Node));
		node = node->next;
		node->next = NULL;
	}

	while(1){
		printf("\n\tEnter a new word: ");
		scanf("%lld", &word);
		word_status = notAdded(head, word);
		if(word_status==0){
			printf("\tThis word has already been added.\n");
		}else{
			node[0].dic.word = word;
			break;
		}
	}

	printf("\n\tEnter a translation: ");
	scanf("%s", node[0].dic.transWord);

	printf("\n\tEnter the class of the word(noun, verb, adjective): ");
	scanf("%s", node[0].dic.typeOfWord);

	printf("\n\tEnter an example translation: ");
	scanf("%lf", &node[0].dic.exampLine);

	printf("\n\tEnter the date of adding(DD/MM/YY): ");
	scanf("%d", &node[0].dic.date);

	printf("\n\tEnter a rating of the translation(0 to 10): ");
	scanf("%d", &node[0].dic.rating);

	return head;
}

void saveToFile(struct Node *head, FILE* fp){
	struct Node *node = head;
	while(node!=NULL){
		fwrite(&node[0].dic, sizeof(struct Dictionary), 1, fp);
		node = node->next;
}
