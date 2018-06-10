	#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 int j=0;
// Stack t�r�ndeki struct�m�z
struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};
//De�i�ken t�r�ndeki struct�m�z
struct Variable{
	int* deger;
	char* harf;
};
 
// Stack ��lemleri
struct Stack* createStack( unsigned capacity )
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
 
    if (!stack) 
        return NULL;
 
    stack->top = -1;
    stack->capacity = capacity;
 
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
 
    if (!stack->array)
        return NULL;
    return stack;
}
int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}
char peek(struct Stack* stack)
{
    return stack->array[stack->top];
}
char pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}
void push(struct Stack* stack, char op)
{
    stack->array[++stack->top] = op;
}
 
 
// Karakterin i�lem olup olmad��n� kontrol eden fonksiyon
int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
 
// ��lemlerin �ncelik s�ras�n� kontrol eden fonsiyon
int Prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
 
    case '^':
        return 3;
    }
    return -1;
}

 
// �nfix ifadeyi postfix ifadeye �eviren fonksiyon 
int infixToPostfix(char* exp)
{
    int i, k;
 	Variable v;
 	//Direk atama durumu
 	if(exp[5]==';')
 	v.deger[j]=exp[4] - '0';
 	v.harf[j]=exp[0];
	
 	j++;
    // Stack olu�turuyoruz
    struct Stack* stack = createStack(strlen(exp));
    if(!stack) // See if stack was created successfully 
        return -1 ;
        
//4den ba�l�yor ��nk� exp[0] atanacak de�i�ken oluyor(E�itli�in sol taraf�n�n adresi
    for (i = 4, k = -1; exp[i]; i++)
    {
    	if(exp[i]!=' '){
        // Okunan karakter i�lemse ��kt�ya yaz�yor
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
         
        // Okuann karakter '(' ise stack'e push ediyor
        else if (exp[i] == '(')
            push(stack, exp[i]);
         
        // Okunan karakter ')' ise '(' karakteri g�rene kadar stacke psuh ediyor
        else if (exp[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // ge�ersiz girdi            
            else
                pop(stack);
        }
        else // Rastlan�lmayan operat�r
        {
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
 
}
    }
 
    // B�t�n operat�rleri stack bo�alana kadar �ekiyoruz
    while (!isEmpty(stack))
        exp[++k] = pop(stack );
 
    exp[++k] = '\0';
    printf( "\n%s", exp );
}
 
// Dosyalar� filedan okudu�umuz ve infixtopostfix fonksiyonunu �a��rd���m�z main fonksiyonu
int main()
{
	int i=0,j,row=0,col=0;
	char data;
	char *line;
	FILE *fp;
line=(char*)malloc(sizeof char(30));
fp=fopen("input.txt","r");
      while ( fgets (line,30, fp ) != NULL ) /* sat�r oku */
      {
do{
			printf("%c",line[i]);
			i++;
}while(line[i]!=';');
printf(";");
infixToPostfix(line);
i=0;
printf("\n");
}
    return 0;
}
