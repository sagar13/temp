#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define TABLESIZE 27

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
		hash = asciiVal - A + 1;
	else
		hash = 0;
	return (hash);
}

int getSize(struct linknode *hashNode)
{
	int count = 0;
	struct linknode *tmp;
	tmp = hashNode;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return count;
}

struct linknode* insertNode(struct linknode *hashNode, char name[])
{
	int i;
	struct linknode *tmp;
	tmp = (struct linknode *) malloc(sizeof(struct linknode));
	for(i=0; i < strlen(name); i++)
		tmp -> fileName[i] = name[i];
	tmp -> next = hashNode;
	hashNode = tmp;
	return hashNode;
}

struct linknode* deleteNode(struct linknode *hashNode, char name[])
{
	int i;
	struct linknode *tmp, *pre;
	tmp = hashNode;
	short int flag = 0;
	pre = NULL;
	if(tmp == NULL)
		return NULL;
	else if(strcmp(name, tmp->fileName) == 0)
	{
		hashNode = tmp->next;
		free(tmp);
		return hashNode;
	}
	else
	{
		while(tmp != NULL && flag == 0)
		{
			if (strcmp(name, tmp->fileName) == 0)
			{
				pre->next = tmp->next;
				free(tmp);
				flag = 1;
			}
			pre = tmp;
			tmp = tmp->next;
		}

		return hashNode;
	}
}

struct linknode** searchNode(struct linknode *hashNode, char name[])
{
	struct linknode **item, *tmp;
	int i, x=0, count=0;
	tmp = hashNode;
	char namestr[strlen(name)];
	while(tmp != NULL)
	{
		for(i=0; name[i] != '\0'; i++)
			namestr[i] = tmp->fileName[i];
		namestr[i] = '\0';
		if(strcmp(name, namestr) == 0)
			count++;
		tmp = tmp->next;
	}

	item = (struct linknode **) malloc(sizeof(struct linknode) * (count+1));		//dereference item first before dereferencing *item in the next line
	*item = (struct linknode *) malloc(sizeof(struct linknode) * (count+1));
	tmp = hashNode;

	while(tmp != NULL)
	{
		for(i=0; name[i] != '\0'; i++)
			namestr[i] = tmp->fileName[i];
		namestr[i] = '\0';
		if(strcmp(name, namestr) == 0)
			item[x++] = tmp;
		tmp = tmp->next;
	}
	item[x] = NULL;
	return (item);
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
	int hash, size, i=0, flag = 0;
	char init;
	struct linknode **temp;
	
	init = name[0];
	hash = calcHash(init);

	temp = searchNode(hashTable[hash], name);
	while(temp[i] != NULL)
	{
		printf("\nFile found: %s\n", temp[i] -> fileName);
		i++;
		flag = 1;
	}
	if (flag == 0)
		printf("\nFile not found!\n");
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

void writeToDisk(struct linknode **hashTable)
{
	FILE *writefiles;
	int i, count = 0;
	struct linknode *temp;
	char *file;
	writefiles = fopen("./hashtable.bin", "wb");
	if(!writefiles)
	{
		printf("Error: Unable to open file..");
	}

	fseek(writefiles, sizeof(int), SEEK_CUR);

	for(i=0; i < TABLESIZE; i++)
	{
		temp = hashTable[i];
		while(temp != NULL)
		{
			file = temp->fileName;
			fwrite(file, SIZE, 1, writefiles);
			temp = temp->next;
			count++;
		}
	}

	rewind(writefiles);
	fwrite(&count, sizeof(int), 1, writefiles);

	fclose(writefiles);
}

void readFromDisk(struct linknode **hashTable)
{
	FILE *readfiles;
	int i = 0, count = 0;
	struct linknode *temp;
	char file[SIZE];
	readfiles = fopen("./hashtable.bin", "rb");
	if(!readfiles)
	{
		printf("Error: Unable to open file..");
	}
	fread(&count, sizeof(int), 1, readfiles);
		while(i != count)
		{
			fread(file, SIZE, 1, readfiles);
			insertFile(file, hashTable);
			i++;
		}
	fclose(readfiles);
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
		printf("\n1. Create file\n");
		printf("2. Delete File\n");
		printf("3. Search File\n");
		printf("4. Display Table\n");
		printf("5. Exit\n");
		printf("6. Write to disk\n");
		printf("7. Read from disk\n");
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

			case 6:
				writeToDisk(hashTable);
				break;

			case 7:
				readFromDisk(hashTable);
				break;
		}
	}
	return (0);
}