
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char data;
    int freq;
    struct Node *left, *right;
};

struct Node* createNode(char data, int freq)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void printCodes(struct Node* root, int code[], int top)
{
    if (root->left)
    {
        code[top] = 0;
        printCodes(root->left, code, top + 1);
    }

    if (root->right)
    {
        code[top] = 1;
        printCodes(root->right, code, top + 1);
    }

    if (!root->left && !root->right)
    {
        printf("%c: ", root->data);

        for (int i = 0; i < top; i++)
            printf("%d", code[i]);

        printf("\n");
    }
}

int main()
{
    int n, i, j;
    char ch[50];
    int freq[50];

    struct Node* nodes[100];

    printf("Enter number of characters: ");
    scanf("%d", &n);

    printf("Enter characters and their frequencies:\n");

    for (i = 0; i < n; i++)
    {
        scanf(" %c %d", &ch[i], &freq[i]);
        nodes[i] = createNode(ch[i], freq[i]);
    }

    int size = n;

    while (size > 1)
    {
        int min1 = -1, min2 = -1;

        for (i = 0; i < size; i++)
        {
            if (min1 == -1 || nodes[i]->freq < nodes[min1]->freq)
            {
                min2 = min1;
                min1 = i;
            }
            else if (min2 == -1 ||
                     nodes[i]->freq < nodes[min2]->freq)
            {
                min2 = i;
            }
        }

        struct Node* left = nodes[min1];
        struct Node* right = nodes[min2];

        struct Node* parent =
            createNode('$', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        if (min1 > min2)
        {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        nodes[min1] = parent;

        for (i = min2; i < size - 1; i++)
            nodes[i] = nodes[i + 1];

        size--;
    }

    int code[100];

    printf("\nHuffman Codes:\n");
    printCodes(nodes[0], code, 0);

    return 0;
}
