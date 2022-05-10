//040190018
//Esad Ömer Kurt

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

//Student data will be stored as a linked list consisting of following 2 types of structs

//Struct to hold the School Number
//First node of a students data will be stored as this type
struct StNo{
	int data;
	struct Node* next;	
};

//Struct to hold the Name&Surname
//Rest of the nodes will be stored in this type
struct Node {
    char data;
    struct Node* next;
};

//Student lists will be stored in sorted stacks 
//Following struct will store pointers to the first node of the student data
struct stack {
	struct StNo* data;
	struct stack* next;	
};

//Function prototypes
int menu (void);
struct StNo* enter (void);
void push (struct stack** head_ref, struct StNo* data_head);				
struct StNo* pop (struct stack** head_ref);
void printS (struct StNo* head);
int read (struct StNo** head, int type);
void sort (struct stack** head, int type);
void printList (struct stack** head);
void pushSort (struct stack** Stacks[3]);
int rmvStudent (struct stack** Stacks[3]);
void clearList (struct Node* list);
 

int main(){
	
	int choice; //User input from the menu
	
	//Three stacks will be sorted in three different ways requested by the assignment
	struct stack* stack0 = NULL;
	struct stack* stack1 = NULL;
	struct stack* stack2 = NULL; 
	
	//Pointers to those three stacks will be stored in an array 
	//This way they all can be referenced to a function together
	struct stack** Stacks[3];
	
	Stacks[0] = &stack0;	//This stack will be ID sorted
	Stacks[1] = &stack1;	//This stack will be year sorted
	Stacks[2] = &stack2;	//This stack will be faculty code sorted


	//Main loop that processes the system
	while(1){
	
	//User is asked for an input through menu() function
	choice = menu();	
	
		switch (choice){	//Switch case for the input
		
		//Almost all cases are reduced down to a complete function
		//"getchar()" is used for interface arrangements
		
			case 1:	//Student entry
				pushSort (Stacks);
				break;
				
			case 2:	//ID sorted listing
				printList(Stacks[0]);
				getchar();
				getchar();
				break;
				
			case 3:	//Year sorted listing
				printList(Stacks[1]);
				getchar();
				getchar();
				break;
				
			case 4:	//Faculty sorted listing
				printList(Stacks[2]);
				getchar();
				getchar();
				break;
				
			case 5:	//Student removal
			
				//A message is printed depending on the result of the removal
				if(rmvStudent(Stacks) == 0) printf("\n\tStudent not found"); 
				else printf("\n\tStudent removed succesfully");
				getchar();
				getchar();
				break;
				
			case 6:	//Exit
				return 0;
				
			default: //Default case for inputs with no action determined
			system("cls");
			printf("\n\n      Error\n\n      Press any button");
			getchar();
			getchar();
					//Just continues to the next loop
		}		
	}
}

//////////////
//MENU funtion
int menu(void){	

	//Clears the screen and displays the menu
	system("cls");
	printf("\n\n\t1-Enter Student\n");
	printf("\t2-Display school numbers sorted by ID\n");
	printf("\t3-Display school numbers sorted by year\n");
	printf("\t4-Display school numbers sorted by faculty\n");
	printf("\t5-Delete Student\n");
	printf("\t6-Exit\n\n\n Choice: ");
	
	auto int a;
	
	//Scans and returns the user input
	scanf("%d",&a);
	return a;	
}

////////////////////////
//Student Entry Function
struct StNo* enter(void){
	
	//Char array is used to store the student name before
	//inserting into the list
	char name[30];
	//Student no
	int no;
	
	
	printf("\n\n Enter School ID:  ");
	scanf("%d",&no);
	
	//Checking if input has right amount of digits to be school number
	int digit = floor(log10 (no)) + 1;
	
	if(digit < 7 || digit > 9){
		//If it cannot be a school number
		//Process is terminated and error message is displayed
		system("cls");
		printf("\n\n\tERROR\n\tWrong entry of School Number"); 
		getchar();	
		getchar();	
		return NULL;
		
	} 
	

	getchar();
	printf("\n Enter Name and Surname: ");
	
	//gets() is used to deal with spaces easily
	gets(name);	
	
	//A linked list is created
	struct StNo* head = (struct StNo*)(malloc(sizeof(struct StNo)));
	
	//First node holds the School number 
	head->data = no;		

	//Next nodes will hold chars, so they are different thpe of node structs
	head->next = (struct Node*)(malloc(sizeof(struct Node)));
	
	//"temp" is used to avoid messing with "head" pointer
	struct Node* temp = head->next;
	
	int i = 0;
	while (1){
		
		//Student name is inserted into nodes one by one from the name array		
		temp->data = name[i++];
		
		if (name[i]=='\0'){
			temp->next = NULL;
			break;
		}
		
		temp->next = (struct Node*)(malloc(sizeof(struct Node)));
		
		//"temp" is set to point at the next node every loop
		temp = temp->next;
	}
	
	printf("\n\n\tSuccess");
	getchar();
	
	return head;	//Return the head pointer for the completed list for student 
	
}


////////////////////////
//Push funtion for stack

void push(struct stack** head_ref, struct StNo* data_head){
	
	//Standart push algorithm
	//Takes a pointer to a student list as data and inserts it on top of the given stack
	
	struct stack* temp = (struct stack*)malloc(sizeof(struct stack));
	
	temp->data = data_head;
	temp->next = (*head_ref);
	(*head_ref) = temp;
		
}

///////////////////////	
//Pop funtion for stack	
	
struct StNo* pop(struct stack** head_ref){
	
	//Standart pop algorithm
	//Extracts the top component of the stack
	
	//temp is the pointer to the node extracted
	//temp2 is the data of the node extracted
	
	struct stack* temp = (*head_ref);
	(*head_ref) = temp->next;
	struct StNo* temp2 = temp->data;
	
	//temp is cleared from memory and temp2 is returned
	free(temp);
	return 	temp2;
	
}


////////////////////////////////////////
//Print function for single student list

void printS(struct StNo* head){	
	
	printf("\nStudent ID: %09d  Student Name&Surname: ", head->data);
	
	
	struct Node* temp = head->next;
	
	while(1){
		
			printf("%c",temp->data);
			
		if (temp->next == NULL)return;		
		
		temp = temp->next;
	}
	printf("\n\n");
}

/////////////////////////////////////////////////////////////////
//Peek function that reads the data of the top element of a stack

int read(struct StNo** head, int type){
	
	//This function returns different parts of the data depending on an additional argument
	
	switch (type){
		
		case 0:
			return(*head)->data;							//Returns whole School Number
			break;
			
		case 1:
			return((*head)->data)%10000;					//Returns only the ID
			break;
			
		case 2:
			return ((((*head)->data)%1000000)/10000);		//Returns only the Year
			break;
			
		case 3:
			return ((*head)->data)/1000000;					//Retuýrns only the Faculty Code
			break;	
				
	}
}

///////////////
//Sort function

void sort(struct stack** head, int type){
	
	//I have used "using a temporary stack to sort" method
	
	//It pops a node from the main stack and holds it
	//Checks the temp stack if there are any nodes that has higher values than held node
	//Pops the nodes with higher values from the temp stack and pushes them into main stack
	//After none left with higher value, pushes held node into the temp stack
	
	//This process is repeated untill main stack is empty
	//At this point temp stack has the nodes sorted in descending order
	//All the elements are popped and pushed into the main stack again
	//Now main stack has the nodes sorted in ascending order, whis was the goal 
	
	
	struct StNo* held; 			//Current investigated node
	struct stack* temp = NULL; 	//empty temporary stack
	
	//Sorting type is determined by "type" value which alters the read() function's output
	
	//Loop that pops nodes from main stack until it is empty
	while((*head) != NULL){
		
		//A node is popped and held
		held = pop(head);	
		
		//All the nodes with higher values are popped from temp stack
		while(temp != NULL){
			
			if(read(&held, type) < read(&(temp->data), type)){
			push(head,pop(&temp));
					
			}else break;	
					
			
		}	
		//Held stack is inserted into temp stack	
		push(&temp, held);			
	}	
	
	//All the nodes are inserted back to main stack
	while(temp != NULL){
		push(head,pop(&temp));
	}
}

//////////////////////////////////////////////////////////
//Print function to print the whole stack of student lists

void printList(struct stack** head){
	
	//Checked if the stack has any data at all
	if((*head) == NULL){
		printf("List is empty. Press any key");
		return;
	}
	
	//Stack elements are ran through printS() one by one 
	struct stack* temp = (*head);	
	while(1){
		
		printS(temp->data);
		
		//Checking if the end is reached
		if(temp->next != NULL){
			temp = temp->next;
		}else return;
		
	}		
	
}



//////////////////////////////////////////////////////////////////
//A function to push a new student into all 3 stacks and sort them

void pushSort (struct stack** Stacks[3]){
	
	struct StNo* temp = enter();
	
	//temp == NULL means student entry was failed
	if(temp == NULL) return;
	
	
	push(Stacks[0], temp);
	sort(Stacks[0], 1);
	
	push(Stacks[1], temp);
	sort(Stacks[1], 2);
	
	push(Stacks[2], temp);
	sort(Stacks[2], 3);


}

//////////////////
//Removal function

int rmvStudent (struct stack** Stacks[3]){
	
	//key is the Student Number to be deleted
	int key;
	//state is the removal state 0: Not complete 1: Removal complete
	int state = 0;
	
	//Temp structs to look through the stacks
	struct StNo* held = NULL; 
	struct stack* temp = NULL;
		
		//Checking if there are any student in the storage at all
		if((*Stacks[0]) == NULL){
		printf("\nNo data available");
		return 1;
			
	}
		
		
	//Input is requested
	printf("\nPlease enter the School Number to be deleted:\n");
	scanf("%d",&key);
	
	//key is searched through all the stack
	while((*Stacks[0]) != NULL){
		
		//Nodes are popped and checked if their data is the key
			
		held = pop(Stacks[0]);	//pop
		if(held->data == key){	//check
		
			//If right node is found "state" is changed to 1 
			state = 1;
			
			//and no further pop() was performed
			break;
			
		}
		push(&temp, held);
	}
	
	//All the popped nodes in the temp stack is pushed back into the main stack
	while(temp != NULL){
		push(Stacks[0], pop(&temp));	
	}	
	
	//key node should be found in 3 stacks seperately
	//but if it can be found, looking through one stack should be 
	//enough to know if it is there since they have the same data set
		
	
	//So if it was not found in first stack
	//Process is terminated
	if (state == 0) return 0;
	
	
	//Other 2 stacks go through the same process
	while((*Stacks[1]) != NULL){
			
		held = pop(Stacks[1]);
		
		if(held->data == key){
			break;
		}
		push(&temp, held);
	}
	
	while(temp != NULL){
		push(Stacks[1], pop(&temp));
	}
	
	
	
	while((*Stacks[2]) != NULL){
			
		held = pop(Stacks[2]);
		
		if(held->data == key){
			break;
		}
		push(&temp, held);
	}
	
	while(temp != NULL){
		push(Stacks[2], pop(&temp));
	}
	
	
	//"held" is the pointer to the student number node
	
	//All nodes other than student number are cleared with clearList function
	clearList(held->next);
	//After that student number node is cleared too
	free(held);
	
	return 1;
}
	
///////////////////////////////////////////////
//Recursive destroy function for a student list

void clearList (struct Node* list){
	
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//This only destroys starting 
	//from the "char" nodes of a student list
	
	if (list->next != NULL) clearList(list->next);
	free(list);
	
}


