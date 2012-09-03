#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define TABLESIZE 53

struct linknode
{
	char fileName[SIZE];
	struct linknode *next;
	struct linknode *prev;
};

void initializeHashTable(struct linknode **hashTable)
{
	int i;
	for(i=0;i<TABLESIZE;i++)
		hashTable[i] = NULL;
}

int calcHash(char alpha)
{
	int asciiVal, hash;
	asciiVal = alpha;
	int a = 'a';
	int z = 'z';
	int A = 'A';
	int Z = 'Z';
	if(asciiVal >= a && asciiVal <= z)
		hash = asciiVal - a + 1;
	else if(asciiVal >= A && asciiVal <= Z)
		hash = 26 + asciiVal - A + 1;
	else
		hash = 0;
	return (hash);
}

struct linknode* insertNode(struct linknode *hashNode, char name[])
{
	int i;
	struct linknode *tmp;
	tmp = (struct linknode *) malloc(sizeof(struct linknode));
	for(i=0; i < sizeof(name); i++)
		tmp -> fileName[i] = name[i];
	if(hashNode != NULL)
		hashNode -> prev = tmp;
	tmp -> next = hashNode;
	tmp -> prev = NULL;
	hashNode = tmp;
	return hashNode;
}

struct linknode* deleteNode(struct linknode *hashNode, char name[])
{
	//yet to be coded
}

struct linknode* searchNode(struct linknode *hashNode, char name[])
{
	struct linknode *item, *tmp;
	short int flag = 0;
	tmp = hashNode;
	item = NULL;
	if (tmp == NULL)
		item = NULL;
	else
	{
		while(tmp != NULL && flag == 0)
		{
			if (strcmp(name, tmp->fileName) == 0)
				item = tmp;
			tmp = tmp->next;
		}
	}
	return(item);
}

void showList(struct linknode *hashNode)
{
	struct linknode *tmp;
	tmp = hashNode;
	if (tmp == NULL)
		printf("Empty hashNode.");
	else
		while(tmp != NULL)
		{
			printf(" %s ", tmp->fileName);
			tmp = tmp->next;
		}
}

void insertFile(char name[], struct linknode **hashTable)
{
	int hash;
	char init;
	init = name[0];
	hash = calcHash(init);
	hashTable[hash] = insertNode(hashTable[hash], name);
}

void deleteFile(char name[], struct linknode **hashTable)
{
	int hash;
	char init;
	init = name[0];
	hash = calcHash(init);
	hashTable[hash] = deleteNode(hashTable[hash], name);
}

void searchFile(char name[], struct linknode **hashTable)
{
	int hash;
	char init;
	struct linknode *temp;
	init = name[0];
	hash = calcHash(init);
	temp = searchNode(hashTable[hash], name);
	if (temp == NULL)
		printf("\nFile not found!\n");
	else
	{
		printf("\nFile found: %s", temp -> fileName);
		printf("\nFile found at table entry %d\n", hash);
	}
}

void displayTable(struct linknode **hashTable)
{
	int i;
	for(i=0; i < TABLESIZE; i++)
	{
		printf("%d: ", i);
		showList(hashTable[i]);
		printf("\n");
	}
}

int main()
{
	int choice;
	char ans = 'y';
	char fname[SIZE];
	struct linknode *hashTable[TABLESIZE];
	initializeHashTable(hashTable);
	
	while(ans == 'y')
	{
		printf("1. Create file\n");
		printf("2. Delete File\n");
		printf("3. Search File\n");
		printf("4. Display Table\n");
		printf("5. Exit\n");
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				printf("Enter file name: ");
				scanf("%s", fname);
				insertFile(fname, hashTable);
				break;

			case 2:
				printf("Enter file name: ");
				scanf("%s", fname);
				deleteFile(fname, hashTable);
				break;

			case 3:
				printf("Enter file name: ");
				scanf("%s", fname);
				searchFile(fname, hashTable);
				break;

			case 4:
				displayTable(hashTable);
				break;

			case 5:
				exit(0);
		}
	}
	return (0);
}