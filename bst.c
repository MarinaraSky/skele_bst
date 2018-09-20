#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF	128

typedef struct Node
{
	struct Node *leftNode;
	struct Node *rightNode;

	int value;
	unsigned index;
} Node;

Node *getNums(FILE *source);
Node *newNode(int numToSort);
Node *insertNode(Node *input, int num);
void printTree(Node *tree);

static int curDepth = 0;
static int maxDepth = 0;

int main(int argc, char *argv[])
{
	FILE *source;
	if(argc > 1)
	{
		source = fopen(argv[1], "r");	
		if(source == NULL)
		{
			printf("Cannont Find File %s\n", argv[1]);
		}
	}
	Node *tree = getNums(source);
	printTree(tree);
	printf("Depth: %d\n", maxDepth);
}

Node *getNums(FILE *source)
{
	int number;
	char numToConvert[BUFF];
	int *nums;
	int buffSize = BUFF;
	int isFirst = 0;
	Node *tree = NULL;
	while(fgets(numToConvert, buffSize, source) != NULL)
	{
		number = atoi(numToConvert);
		if(isFirst == 0)
		{
			tree = insertNode(tree, number);		
			isFirst++;
		}
		else
		{
			insertNode(tree, number);			
		}
	}
	fclose(source);
	return tree;
}

static int inc = 0;

Node *newNode(int numToSort)
{
	Node *new = malloc(sizeof(Node));	
	if(new == NULL)
	{
		printf("Error\n");
	}
	new->value = numToSort;
	new->index = inc++;
	new->leftNode = new->rightNode = NULL;
	printf("new Node\n");
	return new;
}

Node *insertNode(Node *tree, int num)
{
	if(tree == NULL)
	{
		return newNode(num);	
	}	
	if(tree->value < num)
	{
		printf("right\n");
		curDepth++;
		if(tree->rightNode != NULL && tree->rightNode->rightNode != NULL && tree->rightNode->leftNode == NULL)
		{
			printf("test1\n");
			tree->rightNode->leftNode = tree;
			tree->rightNode = NULL;
		}
		tree->rightNode = insertNode(tree->rightNode, num);
	}
	else
	{
		printf("left\n");
		curDepth++;
		if(tree->leftNode != NULL && tree->leftNode->leftNode != NULL && tree->leftNode->rightNode == NULL)
		{
			printf("test2\n");
			tree->leftNode->rightNode = tree;
			tree->leftNode = NULL;
		}
		tree->leftNode = insertNode(tree->leftNode, num);
	}
	if(curDepth > maxDepth)
	{
		maxDepth = curDepth;
	}	
	curDepth = 0;
	return tree;	
}

void printTree(Node *tree)
{
	if(tree != NULL)
	{
		printTree(tree->leftNode);
		printf("%d\n", tree->value);
		printTree(tree->rightNode);	
	}	
	free(tree);
}
