/* Logic Homework 3, Part 2 */
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
/********************* implementation **************************    
                    (1Vnot1)*/
 
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
   while(1){              //loop to evaluate expression
   	if(formula[i]=='('){  //'(' is pushed into operator stack   		 		  		
   		push(formula[i],operator_stack,&operator_top); //push bracket into operator stack
		    		
   	}
   	else if(formula[i]=='^'||formula[i]=='>'||formula[i]=='V'||formula[i]=='~'){ //operators are pushed to operator stack
	   	   
   		push(formula[i],operator_stack,&operator_top);//push operator into operator stack
   		
   	}
   	else if(formula[i]>='1'&&formula[i]<='9'){   //the truth values of the operands are substituted in the formula and pushed to operand stack
   		int j=(int)formula[i];
   	
   		push(operand_val[j-49],operand_stack,&operand_top); //ASCI value of '1'=49
   		
	   }
   	else if(formula[i]==')'){   //the process implemented when  ')'occurs in the formula
	    char check=operator_stack[operator_top];
	    if(check=='V'||check=='^'||check=='>'){    //checks if the operator is binary
	    	char op1=pop(operand_stack,&operand_top);     //operand 1 is popped
	
	    	char op2=pop(operand_stack,&operand_top);     //operand 2 is popped
	    
	    	char op=pop(operator_stack,&operator_top);    //the operator is popped
	    	
	    	int x1=(op1=='T')?1:0;              //converting T and F to 1 and 0
	    	int x2=(op2=='T')?1:0;				//converting T and F to 1 and 0
	    	int res;
	    	switch(op){
	    		case 'V':res=x1|x2;                 //or operation
	    		break;
	    		case '^':res=x1&x2;                 //and operation
	    		break;
	    		case '>':res=x1|(!x2);              //implication operation of x2>x1
	    		break;	    		
			}
			char result=(res==1)?'T':'F';           //result converted back to T/F
			push(result,operand_stack,&operand_top);    //result pushed to stack
			pop(operator_stack,&operator_top);       //the '(' preceeding the operators i.e the '(' corresponding to ')' is popped out
		}
		else if(check=='~'){                 //checks if the unary operator negation is present
			char op1=pop(operand_stack,&operand_top);	  //operand popped   	
	    	char op=pop(operator_stack,&operator_top);    //negation operator popped
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
   	
    scanf("%d",&n);   
   // getchar();
   char operand_val[n]; // array to store the valuation of operands (either T or F)    
   
   // Complete the main function to get the inputs and call the implementation function
 
	scanf("%s", &formula);
//	getchar();
	//scanf("%[^\n]", &operand_val);
    //getchar();  
	
    int p = (int) pow(2, n);
    char TruthTable[p]; //an array which stores all the possible valuations of the given formula
    char ValComb[p][n]; //array storing all possible combinations of valuations of the atoms
    
		for (int i = 0; i < p; i++) {        //storing all possible valuations of atoms in the ValComb array
			for (int k = 0; k < n; k++) {
				int v = i & 1 << n - 1 - k;
				char c=(v == 0 ?'F' :'T');
				ValComb[i][k]=c;
			}
			
		}
	int isSat=0;
	int isVal=1;
	for (int i = 0; i < p; i++) {
			for (int k = 0; k < n; k++)
            {
                operand_val[k]=ValComb[i][k];
			
            }
            TruthTable[i]=eval_formula(n,formula,operand_val);
				   //storing the valuations of the formula for all combinations of valuations of atomes
			}
//	printf("\nTruth Table\n");
 /* for(int i=0;i<p;i++){           //optional : prints the truth table
		for(int k=0;k<n;k++)
			printf("%c ",ValComb[i][k]);
		printf("%c\n",TruthTable[i]);
		
	} */    
	
		for(int i=0;i<p;i++){      //check satisfiability of expression
			if(TruthTable[i]=='T'){
				isSat=1;
				break;
			}
		}
		for(int i=0;i<p;i++){
			if(TruthTable[i]=='F'){       //check validity of expression
				isVal=0;
				break;
			}
				
		}
 
		if(isSat==1)
			printf("Formula is satisfiable.\n");
		else if(isSat==0)	
			printf("Formula is not satisfiable.\n");
		if(isVal==1){		
			printf("Formula is valid.\n");
			printf("T\n"); //Print T for top or Tautology(which is always true)
		}
		else if(isVal==0){
		
			printf("Formula is not valid.\n");
			
		int count=0;
		printf("(");
		for(int i=0;i<p;i++){	     //prints cnf					
			if(TruthTable[i]=='F'){    //find all rows of truth table which valuate to F
			if(count==0)
				printf("(");
			else
				printf("^(");   //conjunction between each term
			count++;
			for(int j=0;j<n;j++){
			if(ValComb[i][j]=='T'){
				if(j!=(n-1))
					printf("(~%d)V",j+1);   //negation in case an atom evaluates to true in that line of truth table 
				else
					printf("(~%d)",j+1);
			}
			if(ValComb[i][j]=='F'){
				if(j!=(n-1))
					printf("%dV",j+1);//disjunction between atoms
				else
					printf("%d",j+1);
			}	
			}
			printf(")");
		}			
		}
		printf(")");
	}
			printf("\n");	
 
   return 0;
   
}