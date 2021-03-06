/*

Data Structure Project using Linkedlist.
Empoyee manager app

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node{
  char name[10] ;
  int age;
  struct Node *next;
}Node;

typedef struct{
  struct Node *head;
  struct Node *tail;
  int numberOfNode;
} List;

// function prototypes

void menu();
void initList(List *);
Node *createNewNode(char [],int);
int isListEmpty(List *);

void insertAtHead(List *, char [],int);
void insertNodeAtHead(List *, Node *);

void insertAtTail(List *, char [],int);
void insertNodeAtTail(List *, Node *);

void printListDetail(List *);
void deleteAtHead(List *);
void deleteAtTail(List *);

void inputDataFromFile(List *, char *);
void outputToFile(List *);

Node *find(List *, char [], int, Node **);
void insertTarget(List *,char [], int , char [], int);
void deleteTarget(List *,char [], int);

void menu() {

  printf("Welcome to Employee Manager App Using Linkedlist\n");
  printf("Please chose options as follow\n");
  printf("Enter 1: Insert At Head\n");
  printf("Enter 2: Insert At Tail\n");
  printf("Enter 3: Delete At Head\n");
  printf("Enter 4: Delete At Tail\n");
  printf("Enter 5: Open input file and write data to the Linked list\n");
  printf("Enter 6: Output to File \n");
  printf("Enter 7: Print list detail \n");
  printf("Enter 8: Find specific node in the linked list\n");
  printf("Enter 9: Insert specific node\n");
  printf("Enter 10: Delete specific node\n");


  printf("Enter 0: Exit \n");

}

void initList(List * listPointer) {
  listPointer->head = NULL;
  listPointer->tail = NULL;
  listPointer->numberOfNode = 0;
}

Node *createNewNode(char name[],int age){
  /*
  creat a new node with the assign data: name and age to insert to the linkedList
  */

    Node *newNode = (Node *)malloc(sizeof(Node));
  // check if new node created or not
  if (newNode == NULL){
    printf("There is a error, CAN'T create new node\n");
    return newNode;
  } else {
    printf("Node created successfully\n");
    strcpy(newNode->name, name); // in C can't assign string value to array directly
                                 // have to use strcpy
    newNode->age = age;
    newNode->next = NULL;   // pointer to the second node
  }
  return newNode;
}

int isListEmpty(List *listPointer){
  if (listPointer->numberOfNode == 0){
    return 1;
  } else {
    return 0;
  }
}

void insertAtHead(List * listPointer, char name[],int age){

   Node *newNode = createNewNode(name,age);
   insertNodeAtHead(listPointer,newNode);
  // increase the number of node in the list
  listPointer->numberOfNode++;
}

void insertNodeAtHead(List *listPointer, Node *newNode){
  /*
  start insert new node to linkedList
  */
  if (isListEmpty(listPointer) == 1){
    printf("List is Empty, head and tail poiter point to same data\n");
    listPointer->head = newNode;
    listPointer->tail = newNode;
  } else {
    printf("List is Not Empty\n");
    newNode->next = listPointer->head;
    listPointer->head = newNode;
  }
}

void insertAtTail(List *listPointer, char name[],int age){

  Node *newNode = createNewNode(name,age);
  insertNodeAtTail(listPointer,newNode);
  // increase the number of node in the list
  listPointer->numberOfNode++;
}

void insertNodeAtTail(List *listPointer, Node *newNode){
  // start check to delete Node
  if (isListEmpty(listPointer) == 1){
    printf("List is Empty, head and tail poiter point to same data\n");
    listPointer->head = newNode;
    listPointer->tail = newNode;
  } else {
    printf("List is Not Empty\n");
    listPointer->tail->next = newNode;
    listPointer->tail = newNode;
  }
}

void printListDetail(List * listPointer){

  Node * current = listPointer->head;

  if (isListEmpty(listPointer) == 1){
    printf("LIST IS EMPTY\n");
  } else {
    printf("*************************************************************\n\n");

    printf("HEAD ADDRESS %p\n",listPointer->head);
    printf("\n");
    while(current != NULL){
      printf("[%s - %d | Node address  %p - Node's pointer next address %p ] ",current->name,current->age, current, current->next);
      printf("\n");
      current = current->next; // move to the next pointer
    }

    printf("\nTAIL ADDRESS %p\n",listPointer->tail);
    printf("\n");

    printf("Number of Node: %d\n\n",listPointer->numberOfNode);

    printf("*************************************************************\n");

  }
}

void deleteAtHead(List * listPointer) {

	// check if the list is empty or not
	if (isListEmpty(listPointer) == 1) {

		printf("List is empty, please input data first");
	}
	else if (listPointer->numberOfNode == 1) {
    // the list has only 1 node

		listPointer->head = listPointer->tail = NULL;

	}
	else {
    printf("Data to be deleted\n");
    printf("Name: %s\n", listPointer->head->name);
    printf("Age: %d\n", listPointer->head->age);
		listPointer->head = listPointer->head->next;
    printf("Success fully deleted data \n");
	}

  listPointer->numberOfNode--;

}
void deleteAtTail(List * listPointer) {

	// check if the list is empty or not
	if (isListEmpty(listPointer) == 1) {
		printf("List is empty, please input data first");
	}
	else if (listPointer->numberOfNode == 1) {
    // the list has only 1 node
		listPointer->head = listPointer->tail = NULL;
	}
	else {
    // creat a new pointer type node to track the previous node of tail node
    Node *current = listPointer->head ;

    printf("Tail's data  to be deleted\n");
    printf("Name: %s\n", listPointer->tail->name);
    printf("Age: %d\n", listPointer->tail->age);

    // loop until find the previous of tail node
    while(current->next != listPointer->tail){
      //jump to the next node, until found the node previous to the tail then exit
      current = current->next;
    }
    // found the previous node,set the tail to previous node, and the tail pointer to null
    listPointer->tail = current;
    listPointer->tail->next = NULL;
    free(current);
	}

  listPointer->numberOfNode--;

}

void inputDataFromFile(List *listPointer, char *fileName){

  FILE *ifp;
  char *mode = "r";
  char username[12]; // 11 chatacters + 1 "/0" character
  int age;

  ifp = fopen(fileName, mode);

  if ( ifp == NULL) {
    fprintf(stderr, "Can't open input file %s\n",fileName );
    exit(1);
  }

  while (!feof(ifp)){

    if((fscanf(ifp,"%s %d",username, &age))!=2)
    /*
    Since our format is "%s %d", we expect it to read in 2 values
    Now, if we get 2 values, the loop continues. If we don't get 2 values,
    either because we are at the end of the file or some other problem occurred
    (e.g., it sees a letter when it is trying to read in a number with %d), then the loop will end.
      */
    break;
    insertAtTail(listPointer,username, age);
  }

    fclose(ifp);
}

void outputToFile(List *listPointer){

  FILE  *ofp;

  char outputFilename[] = "outList2.txt";

  ofp = fopen(outputFilename, "w");

  if (ofp == NULL){
    fprintf(stderr, "Can't write data to output file \n" );
    exit(1);
  }

  Node * current = listPointer->head;
  if (listPointer->numberOfNode == 0){

    printf("LIST IS EMPTY\n");
  } else {

    while(current != NULL){
      fprintf(ofp,"%s %d\n",current->name,current->age);
      current = current->next; // move to the next pointer
    }

  }
    free(current);
    fclose(ofp);
}

Node *find(List *listPointer, char findName[], int findAge, Node **previousPtr){

Node *current = listPointer->head;
*previousPtr = NULL;

while (current != NULL){

  if ((strcmp(current->name, findName) == 0) && (current->age == findAge)) {
    break;
  }

  *previousPtr = current;
  current = current->next;
}
  return current;
}

void insertTarget(List *listPointer,char findName[], int findAge, char insertName[], int insertAge){

  Node *newNode = createNewNode(insertName,insertAge);

  Node *current = NULL, *prev = NULL;
  current = find(listPointer, findName, findAge, &prev);

  if (current == NULL){
    printf("\nNOT FOUND DATA \n");
  } else {
    if (current == listPointer->head){
      insertAtHead(listPointer,insertName,insertAge);
      printf("Target node insert: name %s age %d \n", newNode->name, newNode->age);
    } else if ( current == listPointer->tail){
      insertAtTail(listPointer,insertName,insertAge);
      printf("Target node insert: name %s age %d \n", newNode->name, newNode->age);
    } else {
      prev->next = newNode;
      newNode->next = current;
    }
      listPointer->numberOfNode++;
      printf("Target node inserted: name %s age %d \n", newNode->name, newNode->age);
  }
}

void deleteTarget(List *listPointer,char findName[], int findAge){
  Node *current = NULL, *prev = NULL;
  current = find(listPointer, findName, findAge, &prev);

  if (current == NULL){
    printf("\nNOT FOUND DATA \n");
  } else {
      if (current == listPointer->head){
        deleteAtHead(listPointer);
        printf("Target node deleted: name %s age %d \n", current->name, current->age);
      } else if ( current == listPointer->tail){
        deleteAtTail(listPointer);
        printf("Target node deleted: name %s age %d \n", current->name, current->age);
      } else {
        prev->next = current->next;
      }
      listPointer->numberOfNode--;
      printf("Target node deleted: name %s age %d \n", current->name, current->age);
  }

}



int main() {

  char name[10];
  char insertName[10];
  int age,insertAge, quit = 0, userChoice;
  List employeeList;
  Node *currentNode = NULL, *previousNode = NULL;

  while(quit != 1){
    menu();
    printf("Please enter your choice\n");
    scanf("%d",&userChoice);

    switch (userChoice) {

      case 1:
      printf("Insert at head\n");
      printf(" Please enter your name\n");
      scanf("%s",name);
      printf("Please enter your age\n");
      scanf("%d",&age);
      insertAtHead(&employeeList,name,age );
      break;

      case 2:
      printf("Insert at tail\n");
      printf(" Please enter your name\n");
      scanf("%s",name);
      printf("Please enter your age\n");
      scanf("%d",&age);
      insertAtTail(&employeeList,name,age );
      break;

      case 3:
      printf("Delete at Head operation\n");
      deleteAtHead(&employeeList);
      break;

      case 4:
      printf("Delete at Tail operation\n");
      deleteAtTail(&employeeList);
      break;

      case 5:
      inputDataFromFile(&employeeList,"employee.txt");
      break;
      case 6:
      outputToFile(&employeeList);
      break;

      case 7:
      printListDetail(&employeeList);
      break;

      case 8:
      printf("please enter name you want to find\n");
      scanf("%s",name);
      printf("please enter age you want to find\n");
      scanf("%d",&age);

      currentNode = find(&employeeList,name,age,&previousNode);

      if (currentNode == NULL){
        printf("\nNOT FOUND DATA\n");
      } else {
        printf("Found data, address of the target node %p previous node %p \n", currentNode, previousNode);
      }
      break;

      case 9:
      printf("please enter name you want to find\n");
      scanf("%s",name);
      printf("please enter age you want to find\n");
      scanf("%d",&age);

      printf("please enter name you want to insert\n");
      scanf("%s",insertName);
      printf("please enter age you want to insert\n");
      scanf("%d",&insertAge);

      insertTarget(&employeeList,name,age, insertName, insertAge);
      break;

      case 10:
      printf("please enter name you want to delete\n");
      scanf("%s",name);
      printf("please enter age you want to delete\n");
      scanf("%d",&age);
      deleteTarget(&employeeList,name,age);
      break;

      case 0:
      quit = 1;
      break;

      default:
      printf("Please enter a valid choice\n");

    }
    printListDetail(&employeeList);

  }

  return 0;
}
