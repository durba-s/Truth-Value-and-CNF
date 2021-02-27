/* Logic Homework 3, Part 1 */
/* Team Number: 15 */
#include <stdio.h>
#include <string.h>
#include<math.h>
#define MAX 100 // macro indicating the maximum size of stack


/***************************************************************/
/********************stack operations***************************/

// Inserting data onto top of stack. Takes as arguments the data to be pushed, the array used for implementing the stack and an integer pointer referencing the index of the top of that stack.
void push(char data, char stack[], int *top)  
{ 
   if(*top != MAX-1) // if stack is not full
   {  *top = *top + 1;   
      stack[*top] = data;
        
   } 	
   else 
   {
      printf("Could not insert data, Stack is full.\n");
   }
}

// Removing element from top of stack. Takes as arguments the array used for implementing the stack and an integer pointer referencing the index of the top of that stack. Returns the popped character.
char pop(char stack[], int *top) 
{
   char data;	
   if(*top != -1) //checking whether stack contains some elements
   {
      data = stack[*top];
      *top = *top - 1;
	    
      return data;
   } 
   else 
   {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}
 //NOTE:
// A pointer to the variable top is passed instead of passing the top variable itself. This is done to ensure top is passed as reference and any modifications to the top variable 
// would be reflected in the calling function


/***************************************************************/
/********************* implementation **************************/

// function to implement the solution for Part 1. Takes as arguments the number of atoms, the character array to store the completely parenthesized input formula and the array to store the valuation of the atoms
// returns the final result of evaluating the formula (either T or F)
char eval_formula(int n, char formula[], char operand_val[])    
{
   char operand_stack[MAX];  // character array to implement operand stack
   char operator_stack[MAX]; // character array to implement operator stack
   int operand_top = -1; // integer pointing to the top of the operand stack
   int operator_top = -1; // integer pointing to the top of the operand stack
    // Complete the implementation function to calculate the final valuation of the formula
   int i=0; //counter variable
   while(1){
   	if(formula[i]=='('){  //'(' is pushed into operator stack   		 		  		
   		push(formula[i],operator_stack,&operator_top);
		    		
   	}
   	else if(formula[i]=='^'||formula[i]=='>'||formula[i]=='V'||formula[i]=='~'){ //operators are pushed to operator stack
	   	   
   		push(formula[i],operator_stack,&operator_top);
   		
   	}
   	else if(formula[i]>='1'&&formula[i]<='9'){   //the truth values of the operands are substituted in the formula and pushed to operand stack
   		int j=(int)formula[i];
   	
   		push(operand_val[j-49],operand_stack,&operand_top); //ASCI value of '1'=49 and the truth value of the number i is in the a[i-1]th element of operand value array like 1 is the 0th element,2 is the 1st ....
   		
	   }
   	else if(formula[i]==')'){   //the process implemented when  ')'occurs in the formula
	    char check=operator_stack[operator_top];   //'check' is the topmost character of the operator stack
	    if(check=='V'||check=='^'||check=='>'){    //checks if the operator is binary ,if yes then pop out 2 atoms from the operand stack
	    	char op1=pop(operand_stack,&operand_top);     //operand 1 is retrieved
	
	    	char op2=pop(operand_stack,&operand_top);     //operand 2 is retrieved
	    
	    	char op=pop(operator_stack,&operator_top);    //the operator is retrieved
	    	
	    	int x1=(op1=='T')?1:0;              //converting the truth value of operand1 i.e T and F to 1 and 0
	    	int x2=(op2=='T')?1:0;				//converting the truth value of operand2 i.e T and F to 1 and 0
	    	int res;
	    	switch(op){
	    		case 'V':res=x1|x2;                 //if the operator retrieved is '^' or operation is performed on the operands
	    		break;
	    		case '^':res=x1&x2;                 //if the operator retrieved is 'V' and operation is performed on the operands
	    		break;
	    		case '>':res=x1|(!x2);              //if the operator retrieved is'>',implication operation of x2>x1 since in the original formula if it were a>b while popping we would get in the order ba
	    		break;	    		
			}
			char result=(res==1)?'T':'F';           //the integer result converted back to T/F
			push(result,operand_stack,&operand_top);    //result pushed to the operand stack
			pop(operator_stack,&operator_top);       //the '(' preceeding the operators i.e the '(' corresponding to ')' is popped out
		}
		else if(check=='~'){                 //checks if the unary operator negation is present
			char op1=pop(operand_stack,&operand_top);	  //operand retrieved  	
	    	char op=pop(operator_stack,&operator_top);    //negation operator retrieved
	    	char result=(op1=='T')?'F':'T';	         //negation performed	    	
			
			push(result,operand_stack,&operand_top); //result pushed to operand stack
			pop(operator_stack,&operator_top);    //the '(' preceeding the operators i.e the '(' corresponding to ')' is popped out
		}	
 
   	}
   	else if(operator_top = -1){
   		return pop(operand_stack,&operand_top);   //when operator stack has no element left return the element of the operand stack
	   }
   	
   	i++;                  //counter incremented
   }
  
}
/***************************************************************/
/***********************main function***************************/

int main()
{
	
   int n; // number of operands
  
   char formula[MAX]; // character array to store the input formula
   
   char operand_val[10]; // array to store the valuation of operands (either T or F)  
   
     // Complete the main function to get the inputs and call the implementation function      
    scanf("%d",&n);   //gets the numeber of operands
    getchar();
     
	scanf("%s", &formula);  //get the formula
	getchar();
	
	scanf("%s", &operand_val);   //get valuations of the atoms
    getchar();
	printf("%c",eval_formula(n,formula,operand_val));  //prints the valuation of the formula
 
   return 0;
   
}