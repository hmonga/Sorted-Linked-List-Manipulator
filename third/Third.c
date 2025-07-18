#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
  int data;
  struct Node *next;
};

// make the node
struct Node *createNode(int value)
{
  struct Node *newNode = malloc(sizeof(struct Node));
  newNode->data = value;
  newNode->next = NULL;
  return newNode;
}

// insert at the beginning
void insertAtHead(struct Node **head, int value)
{
  struct Node *newNode = createNode(value);
  newNode->next = *head;
  *head = newNode;
}

// insert in sorted order
void insert(struct Node **head, int value)
{
  if (*head == NULL || (*head)->data > value)
  {
    insertAtHead(head, value);
    return;
  }

  struct Node *current = *head;
  while (current->next != NULL && current->next->data < value)
  {
    current = current->next;
  }

  struct Node *newNode = createNode(value);
  newNode->next = current->next;
  current->next = newNode;
}

void deleteNode(struct Node **head, int value)
{
  struct Node *temp = *head, *prev = NULL;
  if (temp != NULL && temp->data == value)
  {
    *head = temp->next;
    free(temp);
    return;
  }
  while (temp != NULL && temp->data != value)
  {
    prev = temp;
    temp = temp->next;
  }
  if (temp == NULL)
    return;
  prev->next = temp->next;
  free(temp);
}

// print Linked List
void print_LL(struct Node *head)
{
  if (head == NULL)
  {
    printf("EMPTY\n");
    return;
  }

  struct Node *current = head;
  while (current != NULL)
  {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

// read file
void read_file(const char *filename, struct Node **head)
{
  FILE *file = fopen(filename, "r");

  if (!file)
  {
    perror("Error opening file\n");
    exit(EXIT_FAILURE);
  }

  char instruction[10];
  int value;

  while (fscanf(file, "%s %d", instruction, &value) == 2)
  {
    if (strcmp(instruction, "INSERT") == 0)
    {
      insert(head, value);
    }
    else if (strcmp(instruction, "DELETE") == 0)
    {
      deleteNode(head, value);
    }
    print_LL(*head);
  }
  fclose(file);
}

// free list
void free_LL(struct Node *head)
{
  struct Node *current = head;
  while (current != NULL)
  {
    struct Node *temp = current;
    current = current->next;
    free(temp);
  }
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "./third {text file}\n");
    exit(1);
  }

  struct Node *head = NULL; 
  read_file(argv[1], &head);
  free_LL(head);

  return EXIT_SUCCESS;
}
//