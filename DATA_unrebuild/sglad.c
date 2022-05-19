#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NMAX 1000000

struct stack {
  double elem[NMAX];
  int top;
};

void init(struct stack *stk) {
  stk->top = 0;
}

void push(struct stack *stk, double f) {
  if(stk->top < NMAX) {
    stk->elem[stk->top] = f;
    stk->top++;
  } else
    printf("Стек полон, количество элементов: %d !\n", stk->top);
}

double pop(struct stack *stk) {
  double elem;
  if((stk->top) > 0)
  {
    stk->top--;
    elem = stk->elem[stk->top];
    return elem;
  }
  else
  {
    printf("Стек пуст!\n");
    return 0;
  }
}

double stkTop(struct stack *stk) {
  if((stk->top) > 0) {
    return stk->elem[stk->top-1];
  } else {
    printf("Стек пуст!\n");
    return 0;
  }
}

int getcount(struct stack *stk) {
  return stk->top;
}

int isempty(struct stack *stk) {
  if(stk->top == 0)    return 1;
  else return 0;
}

void stkPrint(struct stack *stk) {
  int i;
  i=stk->top; // i - количество элементов в стеке
  if(isempty(stk) == 1) return; // стек пуст
  do {
    i--;
    printf("%f\n", stk->elem[i]);
  }while(i>0);
}

double R(double t, double p0, double p1, double p2, double p3){
	return (-t*(1-t)*(1-t)*p0+(2-5*t*t+3*t*t*t)*p1+t*(1+4*t-3*t*t)*p2-t*t*(1-t)*p3)/2;
}

void Swap(char* a, char* b)
{
   char tmp = *a;
   *a = *b;
   *b = tmp;
}

char* reverse(char* str)
{
   char* begin = str;
   char* end = str;
 
   for (; *end; ++end) { ; }
 
   for (--end; begin < end; ++begin, --end)
   {
      Swap(begin, end);
   }
 
   return str;
}

char* IntToAnsi(int dig, char str[], size_t len)
{
   int i = 0;
 
   while (dig && (i < len - 1))
   {
      str[i++] = (dig % 10) + '0';
      dig /= 10;
   }
 
   if ((i == 0) && (i < len))
   {
      str[i++] = '0';
   }
 
   str[i] = '\0';
 
   reverse(str);
 
   return str;
}

char* DoubleToAnsi(double dig, size_t acc, char str[], size_t len)
{
   int hi = (int) dig;
   int lo = (dig - hi) * pow(10, acc);
   char* pstr = str;
 
   IntToAnsi(hi, pstr, len);
 
   if (lo)
   {
      for (; *pstr; ++pstr) { ; }
 
      *pstr++ = '.';
      IntToAnsi(lo, pstr, len - (pstr - str));
   }
 
 
   return str;
}

int main(int argc, char **argv)
{
	FILE * f;
	char name[30];
	char sep[10] = ",";
	char str[300];
	char *istr;
	int i, j, l, m, col, period, all_col, error, zero_val;
	int sglad_col[10];
	struct stack *stk[10];
	double val, first, second;
	
	for(i = 0; i < 10; i++){
		stk[i] = (struct stack*)malloc(sizeof(struct stack));
		init(stk[i]);
	}
	
	printf("Enter file name(format \"Data.csv\", but no more 30 simbols): ");
	scanf("%s", name);
	
	f = fopen(name, "r");
	
	printf("Enter number columes: ");
	scanf("%d", &all_col);
	
	printf("Enter number columes, that we want to sglad(max 10): ");
	scanf("%d", &col);
	
	for(i = 0; i < col; i++){
		printf("Enter number's colume %d: ", i + 1);
		scanf("%d", &sglad_col[i]);
	}
	
	printf("Enter period number: ");
	scanf("%d", &period);
	
	fscanf(f, "%s", str);
	
	j = 0;
	
	while(j > -1){
	//for(i = 0; i < 100; i++){
		error = fscanf(f, "%s", str);
		
		if(error == -1){
			break;
		}
		
		if(j == 0){
			m = 0;
			istr = strtok (str,sep);
			
			for(l = 1; l < all_col + 1; l++){
				istr = strtok (NULL,sep);
				
				if(l == sglad_col[m]){
					val = atof(istr);
					push(stk[m],val);
					m++;
				}
			}
		}
		
		j++;
		
		if(j == period){
			j = 0;
		}
	}
	
	fclose(f);
	
	//printf("1 det\n");
	//stkPrint(stk[0]);
	
	//printf("2 det\n");
	//stkPrint(stk[1]);
	
	//printf("3 det\n");
	//stkPrint(stk[2]);
	
//---------------Удаление нулей-------------
	
	printf("Delete zero.\n");
	
	//del_zero(stk[0]);
	//del_zero(stk[1]);
	//del_zero(stk[2]);
	
	struct stack *prom_stk;
	prom_stk = (struct stack*)malloc(sizeof(struct stack));
	init(prom_stk);
	
	for(m = 0; m < col; m++){
		first = pop(stk[m]);
		//printf("%f\n", first);
		zero_val = 0;
		l = getcount(stk[m]);
		//printf("%d\n", l);
		for(i = 0; i < l; i++){
			second = pop(stk[m]);
			//printf("%f\n", second);
			if(second == 0){
				zero_val++;
			}
			else{
				push(prom_stk, first);
				//printf("%f\n", first);
				if(zero_val != 0){
					for(j = 0; j < zero_val; j++){
						val = (first - second) * (j+1) / (zero_val + 1) + second;
						//printf("%f\n", val);
						push(prom_stk, val);
					}
				}
				
				first = second;
				zero_val = 0;
			}
		}
		
		if(zero_val != 0){
			for(i = 0; i < zero_val + 1; i++){
				push(prom_stk,first);
			}
		}
		
		//stkPrint(prom_stk);
		
		
		l = getcount(prom_stk);
		
		for(i = 0; i < l; i++){
			val = pop(prom_stk);
			push(stk[m], val);
		}
		
		//stkPrint(stk[m]);
	}
	
//---------Добавление точек------------------

	/*printf("Create new point.\n");
	
	double t, p0, p1, p2, p3;
	
	struct stack *prom_stk_dop;
	prom_stk_dop = (struct stack*)malloc(sizeof(struct stack));
	init(prom_stk_dop);
	
	for(i = 0; i < col; i++){
		
		p0 = pop(stk[i]);
		p1 = pop(stk[i]);
		p2 = pop(stk[i]);
		p3 = pop(stk[i]);
		
		for(t = 0; t < 0.66; t += 0.33 / period){
			val = R(t, p0, p1, p2, p3);
			push(prom_stk, val);
		}
		
		l = getcount(stk[i]);
		for(j = 0; j < l; j++){
			p0 = p1;
			p1 = p2;
			p2 = p3;
			p3 = pop(stk[i]);
			
			for(t = 0.33; t < 0.66; t += 0.33 / period){
				val = R(t, p0, p1, p2, p3);
				push(prom_stk, val);
			}
		}
		
		for(t = 0.66; t <= 1; t += 0.33 / period){
			val = R(t, p0, p1, p2, p3);
			push(prom_stk, val);
		}
		
		l = getcount(prom_stk);
		
		for(j = 0; j < l; j++){
			val = pop(prom_stk);
			push(prom_stk_dop, val);
		}
		
		for(j = 0; j < l; j++){
			val = pop(prom_stk_dop);
			push(stk[i], val);
		}
	}*/
	
	//stkPrint(stk[0]);
	
//-------Создание нового CSV файла------------

	printf("Create new csv.\n");
	
	FILE * out;
	char new_name[34];
	char pref[4] = "NEW_";
	char out_str[300];
	char value[20];
	char *avalue;
	
	strcpy(new_name, pref);
	strcat(new_name, name);
	
	out = fopen(new_name, "w");
	
	f = fopen(name, "r");
	 
	fscanf(f, "%s", str);
	fprintf(out, "%s\n", str);
	
	j = 0;
	
	while(j > -1){
	//for(i = 0; i < 10; i++){
		error = fscanf(f, "%s", str);
		
		if(error == -1){
			break;
		}
		m = 0;
		
		istr = strtok (str,sep);
		if(0 == sglad_col[m] - 1){
			val = pop(stk[m]);
			avalue = DoubleToAnsi(val, 4, value, sizeof(str));
			strcpy(out_str,avalue);
			if(l != all_col - 1){
				strcat(out_str,sep);
			}
			m++;
		}
		else{
			strcpy(out_str,istr);
			if(l != all_col - 1){
				strcat(out_str,sep);
			}
		}
		
		for(l = 1; l < all_col; l++){
			istr = strtok (NULL,sep);
			
			if(l == sglad_col[m] - 1){
				val = pop(stk[m]);
				//printf("%f ", val);
				avalue = DoubleToAnsi(val, 4, value, sizeof(str));
				//printf("%s\n", avalue);
				strcat(out_str,avalue);
				if(l != all_col - 1){
					strcat(out_str,sep);
				}
				m++;
			}
			else{
				strcat(out_str,istr);
				if(l != all_col - 1){
					strcat(out_str,sep);
				}
			}
			//printf("%s\n", out_str);
		}
		
		fprintf(out, "%s\n", out_str);
	}
	
	fclose(f);
	fclose(out);
	
	return 0;
}

