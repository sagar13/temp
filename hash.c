#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define SIZE 10
#define TABLESIZE 53

struct linknode
{
	char fileName[SIZE];
	struct linknode *next;
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
	tmp -> next = hashNode;
	hashNode = tmp;
	return hashNode;
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
		printf("2. Display Table\n");
		printf("3. Exit\n");
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
			displayTable(hashTable);
			break;

			case 3:
			exit(0);
		}
	}
	return (0);
}