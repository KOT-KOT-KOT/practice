#include "stdafx.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <string.h> 
#include <malloc.h> 
#include <clocale> 
#include <windows.h> 


using namespace std; 
using namespace System; 
using namespace System::IO; 
 
#define ENTER 13 
#define ESC 27 
#define UP 72 
#define DOWN 80 
#define HOME 71
#define END 79

 



struct z { 
 char name[30]; 
 char region[20]; 
 float prise; 
 int am; 
 int wm; 
 int dm; 
 int lm; 
 };

struct sp {
	char nteam[30];
	int all;
	struct sp* sled;
	struct sp* pred;	
};

int menu(int); 
void max_prise(struct z*,int); 
void kolvo(struct z*,int);
void alfalist(struct z*,int, struct sp**);
void vstavka(struct z*,char*,int, struct sp**);
void listing(struct z*,int);
void diagram(struct z*,int,struct sp**);
void poisk(struct z*,int);

int main(array<System::String ^> ^args) 
{

char dan[6][55]={ 
  "Какая команда команда имеет больше всего призовых?    ", 
  "Сколько команд в регионе <Введите регион>?            ", 
  "Алфавитный список всех команд                         ", 
  "Диаграмма: процент сыгранных матчей                   ", 
  "Есть ли одинаковые призовые у команд из разных регион?",
  "Выход                                                 " 
  }; 
char BlankLine[ ]="                                                        "; 
int NT; 


 int i,n; 
 FILE *in; 
 struct z *team; 
 setlocale(LC_CTYPE,"Russian"); 
 Console::CursorVisible::set(false); 
 Console::BufferHeight=Console::WindowHeight; 
 Console::BufferWidth=Console::WindowWidth; 
 if((in=fopen("table.dat","r"))==NULL) 
{ 
printf("\nФайл table  не открыт !"); 
_getch(); exit(1); 
} 
 fscanf(in,"%d",&NT); 
team=(struct z*)malloc(NT*sizeof(struct z)); 
 
for(i=0;i<NT;i++) 
 fscanf(in,"%s%s%f%d%d%d%d",team[i].name, 
 team[i].region, &team[i].prise, &team[i].am, &team[i].wm, 
 &team[i].dm, &team[i].lm); 
 
for(i=0;i<NT;i++) 
 printf("\n%-20s %-10s %-10.2f %-5d %-5d %-5d %-5d", 
 team[i].name, 
 team[i].region, team[i].prise,team[i].am, team[i].wm, 
 team[i].dm, team[i].lm); 
_getch(); 
    while(1) 
  { 
  Console::ForegroundColor=ConsoleColor::White; 
  Console::BackgroundColor=ConsoleColor::Black; 
 
  Console::Clear(); 
 
  Console::ForegroundColor=ConsoleColor::Red; 
  Console::BackgroundColor=ConsoleColor::White; 
  Console::CursorLeft=10; 
  Console::CursorTop=4; 
  printf(BlankLine); 
  for(i=0;i<6;i++) 
  { 
  Console::CursorLeft=10; 
  Console::CursorTop=i+5; 
  printf(" %s ",dan[i]); 
  } 
  Console::CursorLeft=10; 
  Console::CursorTop=11; 
  printf(BlankLine); 
  n = menu(6); 

  struct sp* spisok = 0;
  switch(n) { 
    case 1:max_prise(team, NT); break; 
    case 2:kolvo(team, NT); break; 
    case 3:alfalist(team, NT, &spisok) ; break; 
    case 4:diagram(team, NT, &spisok); break;
	case 5:poisk(team, NT); break;
    case 6: exit(0); 
    } 
  } 
  return 0; 
   
} 
int menu(int n) 
{
	char dan[6][55]={ 
  "Какая команда команда имеет больше всего призовых?    ", 
  "Сколько команд в регионе <Введите регион>?            ", 
  "Алфавитный список всех команд                         ", 
  "Диаграмма: процент сыгранных матчей                   ", 
  "Есть ли одинаковые призовые у команд из разных регион?",
  "Выход                                                 " 
  }; 
char BlankLine[ ]="                                                        ";
int y1=0,y2=n-1; 
char c=1; 
while (c!=ESC) 
{ 
  switch(c) { 
   case DOWN: y2=y1; y1++; break; 
   case UP: y2=y1; y1--; break; 
   case ENTER: return y1+1; 
   case HOME: y2 = y1; y1 = 0; break;
   case END: y2 = y1; y1 = n-1;break;
   } 
  if(y1>n-1){y2=n-1;y1=0;} 
  if(y1<0) {y2=0;y1=n-1;} 
  Console::ForegroundColor=ConsoleColor::Black
	  ; 
  Console::BackgroundColor=ConsoleColor::Red; 
  Console::CursorLeft=11; 
  Console::CursorTop=y1+5; 
  printf("%s",dan[y1]); 
  Console::ForegroundColor=ConsoleColor::Red; 
  Console::BackgroundColor=ConsoleColor::White; 
  Console::CursorLeft=11; 
  Console::CursorTop=y2+5; 
  printf("%s",dan[y2]); 
  c=getch(); 
  }  
exit(0); 
} 
void max_prise(struct z* team, int NT) 
{ 
int i=0; struct z best; 
strcpy(best.name,team[0].name); 
best.prise=team[0].prise; 
for(i=1;i<NT;i++) 
if (team[i].prise>best.prise) 
{ 
strcpy(best.name,team[i].name); 
best.prise=team[i].prise; 
} 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Red; 
Console::CursorLeft=10; 
Console::CursorTop=15; 
printf("Наибольшие призовые %2.2f млн долларов",best.prise); 
Console::CursorLeft=10; 
Console::CursorTop=16; 
printf("имеет команда %s",best.name); 
getch(); 
} 


void kolvo(struct z *team, int NT)
{
int i,k=0;
char reg[20];
Console::CursorLeft=10; 
 Console::CursorTop=17;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Red;
 Console::WriteLine(L"Введите регион:"); 
SetConsoleCP(1251); 
 Console::CursorLeft=10; 
 Console::CursorTop=18; 
 gets(reg); 
SetConsoleCP(866); 
for(i=0;i<NT;i++)
	if (strcmp(team[i].region,reg)==0)
										k++;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Red;
Console::CursorLeft=30; 
Console::CursorTop=17; 
printf("Команд из региона: %s", reg);
Console::CursorLeft=30; 
Console::CursorTop=18; 
printf("Всего : %d",k);
getch();
}

void vstavka(struct z* team,char* nteam, int NT, struct sp**spisok) 
{ 
int i; 
struct sp *nov,*nt,*z=0; 
for(nt=*spisok; nt!=0 && strcmp(nt->nteam,nteam)<0; z=nt, nt=nt->sled); 
if(nt && strcmp(nt->nteam,nteam)==0) return; 
nov=(struct sp *) malloc(sizeof(struct sp)); 
strcpy(nov->nteam,nteam); 
nov->sled=nt;
nov->pred=z;
nov->all=0; 
for(i=0;i<NT;i++) 
if(strcmp(team[i].name,nteam)==0) 
nov->all+=team[i].am; 
if(!z) *spisok=nov; 
else z->sled=nov; 
 if(nt) nt->pred=nov;
  nov->sled = nt;
return; 
} 


void alfalist(struct z* team, int NT, struct sp**spisok) 
{ 
int i, n=0; 
struct sp* nt; 
struct sp* z;
Console::ForegroundColor=ConsoleColor::Red; 
Console::BackgroundColor=ConsoleColor::White; 
Console::Clear(); 
if(!*spisok) 
for(i=0;i<NT;i++) 
vstavka(team,team[i].name, NT, spisok); 
Console::Clear(); 
printf("\n\t\t Алфавитный список команд и обратный"); 
printf("\n =======================================================================\n"); 
for(nt=*spisok; nt!=0; nt=nt->sled) 
printf("\n %-30s %ld",nt->nteam,nt->all); 
 for (nt = *spisok, z=0; nt != 0; z=nt, nt = nt->sled);
    for(nt=z; nt!=0; nt=nt->pred)
    {  
    Console::CursorLeft=48;
    Console::CursorTop=4+n;
        printf(" %-30s %ld", nt->nteam, nt->all);
    n+=1;
    }
    getch();
}



void diagram(struct z *team, int NT, struct sp**spisok)
{
struct sp *nt;
int len,i,NColor;
long sum = 0 ;
char str1[20];
char str2[20];
System::ConsoleColor Color;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::White;
Console::Clear();
for(i=0;i<NT;i++) sum = sum+team[i].am ;
if(!*spisok)
	for(i=0;i<NT;i++)
		vstavka(team,team[i].name, NT, spisok);
Color=ConsoleColor::Black; NColor=0;
for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
	sprintf(str1,"%s",nt->nteam);
	sprintf(str2,"%3.1f%%",(nt->all*100./sum));
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor= ConsoleColor::White;
	Console::CursorLeft=5; Console::CursorTop=i+1;
	printf(str1);
	Console::CursorLeft=20;
	printf("%s",str2);
	Console::BackgroundColor=++Color; NColor++;
	Console::CursorLeft=30;
	for(len=0; len<nt->all*100/sum; len++) printf(" ");
	if(NColor==14)
		{ Color=ConsoleColor::Black; NColor=0; }
	}
getch();
return ;
}

void poisk(struct z *team, int NT) {
    int i, j, flag = 0;
    for (i = 0; i < NT; i++) {
        for (j = i + 1; i < j; j++) { 
            if (team[i].region != team[j].region) {
                if (team[i].prise == team[j].prise) {
                    Console::ForegroundColor = ConsoleColor::White;
                    Console::BackgroundColor = ConsoleColor::Red;
                    Console::CursorLeft = 10;
                    Console::CursorTop = 15;
                    printf("Существует 2 команды из разных регионов с одинаковыми призовыми");
                    Console::CursorLeft = 10;
                    Console::CursorTop = 16;
                    printf("%s %10.3f и %s %10.3f", team[i].name, team[i].prise, team[j].name, team[j].prise);
                    getch();
                    flag = 1; 
                }
            }
        }
    }
    if (flag == 0) {
        Console::ForegroundColor = ConsoleColor::White;
        Console::BackgroundColor = ConsoleColor::Red;
        Console::CursorLeft = 10;
        Console::CursorTop = 15;
        printf("В файле table.dat не найдено разных команд с одинаковыми призовыми");
        getch();
    }
}
