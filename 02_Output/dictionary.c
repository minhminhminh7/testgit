#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>




#define HASH_SIZE 63
#define MAX_LINE 2048
#define FINENAME_SIZE 1024

typedef struct 
{
	unsigned char value[1024]; //English word
	//unsigned char offset[1024];
	unsigned long offset;
	struct Word *next; //next pointer
}Word;


void init(Word *hashdict[]); //set Null
Word *creat_word(const char *w);//creat Node
int hash_word(unsigned char *w);//creat hash_value
void addWord(Word **hashdict[], Word x);//add word into node
void display(Word *hashdict[]);
//Word *search_word(Word **hashdict, char *w);

void init(Word *hashdict[]) //set NULL 
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		hashdict[i] = NULL;
	}
}



Word *creat_word(const char *w, unsigned long off)//creat node
{
	Word *newNode = malloc(sizeof(Word));
	//newNode->value = w;
	if (newNode == NULL)
	{
		printf("error");
	}

		strcpy(newNode->value, w);
		newNode->offset = off;
	newNode->next = NULL;	
	return newNode;

}

int hash_word(unsigned char *w)//set hash value through first letter
{
	unsigned int hash_value = w[0] % 63;
	return hash_value;
}

void addWord(Word **hashdict, Word *x)//add word at the end of node
{

	int hash_value = hash_word(x->value);
	//printf("gia tri hash: %d\n", hash_value);
	Word *tmp = hashdict[hash_value];
	Word *p = creat_word(x->value, x->offset);

	if (tmp == NULL)
	{
		hashdict[hash_value] = p;
		printf("Hash:%d  gia tri p %s offset %d\n", hash_value, p->value, p->offset);
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		    tmp->next = p;
			printf("Hash:%d  gia tri p %s  offset %d\n", hash_value, p->value, p->offset);
	}
	
	//printf("gia tri p %s", p);
}


//void search_word(Word **hashdict, char *w)
Word *search_word(Word **hashdict, char *w)
{
	int hash = hash_word(w);
	Word *p = hashdict[hash];
	while (p != NULL)
	{
		//printf("hash: %d gia tri p: %s gia tri w: %s  ", hash, p->value, w);
		if (strncmp(p->value, w, strlen(p->value) - 1) == 0)
		//if (strcmp(p->value, w) == 0)
		{
			return p->offset;	

			//printf("Founf %s %d\n", p->value, p->offset);
		}
		p = p->next;
	}
	return NULL;
	//return 0;
}

void display(Word *hashdict[])
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if (hashdict[i] == NULL)
		{
			printf("\t%i\t---\n", i);
		}
		else
		{
			//printf("\t%i\t%s\n", i, p->value);
			Word *p = hashdict[i];
			printf("\t%i\t%s\t\t\t%d ", i, p->value, p->offset);
			while (p != NULL)
			{		
				//p = p->next;
				printf("%s\t%d ", p->value, p->offset);
				p = p->next;
			}
		}
	}

}

int get_meaning(unsigned char *buf, struct Word* wobject, FILE *dict_file)
{

}

int main()
{
	FILE *f;
	f = fopen("dictionary.txt", "r");

	if (f == NULL)
	{
		printf("Error file ");
		exit(1);
	}

	struct Word* hashdict[HASH_SIZE];
	char filename[FINENAME_SIZE];
	Word *buffer = malloc(sizeof(Word));
	
	Word *wo = filename + 1;
	Word *wobject = NULL;
	if (buffer == NULL)
	{
		printf("Error in allocating memory!!!\n");
		return -1;
	}
	init(hashdict);	
	//display(hashdict);
	//fseek(f, 0, SEEK_END);
	//Word *i = malloc(sizeof(Word));
	unsigned long positions[10];
	int i = 0;
	positions[i++] = ftell(f);
	Word *buf[64];
	while (fgets(filename, sizeof(filename), f))
	{
		//printf("%s\n ", filename);	
		int length = ftell(f); 
		int length1 = ftell(f);
		Word *wo;
		wo = (Word*) malloc(sizeof(Word));
		if (filename[0] == '#')
		{
			//puts(wo);
			strcpy(wo->value, filename + 1);
			//printf("Hash number: %d\n", hash_word(wo->value));
			printf("length word %d\n", length);
			printf("len filename: %d\n", strlen(filename));
			wo->offset = length;
			buf[i] = wo->offset;
			i++;			
			printf("length word %d\n", wo->offset);
			addWord(hashdict, wo);
		}
		else 
		{	
			int length1 = ftell(f);
			//strcpy(wo->offset, filename);
			strcpy(buffer, filename);
			printf("buffer: %s\n", buffer);
			printf("length meaning %d\n", length1);
			//addWord(hashdict, wo->offset);			
			printf("len filename: %d\n", strlen(filename));
	        
		}
		//printf("length word %d\n", wo->offset);
	}
	
	//fseek(f, 6, SEEK_SET);
	//char ch = fgetc(f);
	//printf("Char: %c\n", ch);
	/*for (i = 1; i < 64; i++)
	{
		printf("Gia tri buf:%d\n ", buf[i]);
	}*/

	display(hashdict);
	char str[50];
	printf("Enter word: ");
	gets(str);
	//search_word(hashdict, str);
	Word *tmp = search_word(hashdict, str);
	if (tmp == NULL)
	{
		printf("NOT FOUND\n");
	}
	else
	{

		printf("Found %d\n", search_word(hashdict, str));
	}
	
		fseek(f, search_word(hashdict, str), SEEK_SET);
		while (fgets(filename, sizeof(filename), f))
		{
			if (filename[0] == '#')
			{
				break;
			}
			printf("%s\n", filename);
		}
	
	fclose(f);
	system("pause");

}