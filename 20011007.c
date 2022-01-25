#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

char hardship,name[20];
int nums[8][8],area[8][8],counter[32],memoryRow[16],memoryColumn[16],memoryValue[16];
int tmp,i,j,k=0,row,column,value,row1,column1,row2,column2,matchedRow,matchedColumn,matched;
int kLength=4,oLength=6,zLength=8,length,kMemoryLength=2,oMemoryLength=6,zMemoryLength=16,memoryLength,sleepLength,kSleepLength=3,oSleepLength=4,zSleepLength=5;
int playersGuesses=0,computersGuesses=0,computerScore=0,playerScore=0;
char cls[3] = "cls";

void gameStart(int length,int sleepLength);
void playersFirstCard(int length);
void playersSecondCard(int length);
void computersFirstCard(int length,int memoryLength);
void computersSecondCard(int length,int memoryLength);
void addToMemory(int memoryLength,int row,int column,int value);
int findFromMemory(int memoryLength,int row,int column,int value);
void game(int length,int memoryLength,int sleepLength);
void gameEnd(int length);
void red();
void white();
void turquoise();
void green();
void blue();

int main(int argc, char *argv[]) {

	green();
	srand(time(NULL));
	printf("Isminizi yaziniz: ");
	gets(name);
	system(cls);
	printf("Hosgeldin %s! Lutfen oynamak istedigin zorluk derecesini sec. Kolay -> k, Orta -> o, Zor -> z\n",name);
	scanf("%c",&hardship);
	
	while((hardship!='k')&&(hardship!='o')&&(hardship!='z')){
		system(cls);
		red();
		printf("Lutfen gecerli bir zorluk seviyesi gir!!! Kolay -> k, Orta -> o, Zor -> z\n");
		white();
		scanf("%c",&hardship);
	}
	system(cls);
	
	for(i = 0;i< 32;i++){
		counter[i] = 0;
	}
	
	if(hardship == 'k'){

		gameStart(kLength,kSleepLength);
		game(kLength,kMemoryLength,kSleepLength);
		gameEnd(kLength);
		
	}else if(hardship == 'o'){
		
		gameStart(oLength,oSleepLength);
		game(oLength,oMemoryLength,oSleepLength);
		gameEnd(oLength);
		
	}else if(hardship == 'z'){
		
		gameStart(zLength,zSleepLength);
		game(zLength,zMemoryLength,zSleepLength);
		gameEnd(zLength);
		
	}
	
	return 0;
}

void game(int length,int memoryLength,int sleepLength){
	while((playerScore<(length*length/4+1)) && (computerScore<(length*length/4+1))){
		
		playersFirstCard(length);
		playersSecondCard(length);	
		playersGuesses++;
		addToMemory(memoryLength,row1,column1,nums[row1][column1]);
		addToMemory(memoryLength,row2,column2,nums[row2][column2]);
							
		while((nums[row1][column1] == nums[row2][column2]) && (playerScore<(length*length/4+1))){
			area[row1][column1]='-';
			area[row2][column2]='-';
			playerScore++;
			green();
			printf("Dogru bildin.\n");
			white();
			if((playerScore == (length*length/4))&&(computerScore==(length*length/4))){
					break;
			}
			if(playerScore<(length*length/4+1)){
					playersFirstCard(length);
					playersSecondCard(length);	
					addToMemory(memoryLength,row1,column1,nums[row1][column1]);
					addToMemory(memoryLength,row2,column2,nums[row2][column2]);
					playersGuesses++;
			}
		}
		sleep(sleepLength);
		system(cls);
		
		if(playerScore<(length*length/4+1)){

			computersFirstCard(length,memoryLength);
			computersSecondCard(length,memoryLength);
			computersGuesses++;
			addToMemory(memoryLength,row1,column1,nums[row1][column1]);
			addToMemory(memoryLength,row2,column2,nums[row2][column2]);

			
			while((nums[row1][column1] == nums[row2][column2]) && (computerScore<(length*length/4+1))){
				area[row1][column1]='-';
				area[row2][column2]='-';
				computerScore++;
				green();
				printf("Bilgisayar dogru bildi.\n");
				white();
				sleep(sleepLength);
				if((playerScore == (length*length/4))&&(computerScore==(length*length/4))){
					break;
				}
				if(computerScore<(length*length/4+1)){
					computersFirstCard(length,memoryLength);
					computersSecondCard(length,memoryLength);	
					addToMemory(memoryLength,row1,column1,nums[row1][column1]);
					addToMemory(memoryLength,row2,column2,nums[row2][column2]);
					computersGuesses++;
				}
			}
			sleep(sleepLength);
			system(cls);
		}
		
		if((playerScore == (length*length/4))&&(computerScore==(length*length/4))){
			break;
		}
	}	
}

void addToMemory(int memoryLength,int row,int column,int value){
	memoryRow[k] = row;
	memoryColumn[k] = column;
	memoryValue[k] = value;
	k++;
	if(k==memoryLength){
		k=0;
	}
}

int findFromMemory(int memoryLength,int row,int column,int value){
	for(i=0;i<memoryLength;i++){
		if(memoryValue[i] == value){
			if((memoryRow[i]!=row) || (memoryColumn[i]!=column)){
				matchedRow = memoryRow[i];
				matchedColumn = memoryColumn[i];
				return 1;
			}
		}
	}
	return 0;
}

void gameStart(int length,int sleepLength){
	green();
	printf("Oyun basliyor!\n");
	white();
	for(i = 0;i<length;i++){
		for(j = 0; j<length;j++){
			
			tmp = rand() % (length*length/2);
			while(counter[tmp] >= 2){
				tmp = rand() % (length*length/2);
			}
			nums[i][j] = tmp;
			counter[tmp] += 1;
			area[i][j] = '*';

		}	
	}
	sleep(2);
	system(cls);
	printf("---------------------------------------------------------------\n        ");
	for(i=0;i<length;i++){
		turquoise();
		printf("%d\t",i+1);
	}
	printf("\n   ");
	for(i=0;i<length;i++){
		printf("--------");
	}
	printf("\n");
	for(i = 0;i<length;i++){
		turquoise();
		printf("%d |   ",i+1);
		white();
		for(j = 0; j<length;j++){
			printf("\t%d",nums[i][j]);
		}	
		printf("\n");
	}
	printf("---------------------------------------------------------------\n");
	green();
	printf("Kartlar %d saniye icinde kapaniyor...\n",sleepLength);
	sleep(sleepLength);
	system(cls);
}


void playersFirstCard(int length){
	green();
	printf("Senin siran %s!\n",name);
	white();
	printf("---------------------------------------------------------------\n        ");
	for(i=0;i<length;i++){
		turquoise();
		printf("%d\t",i+1);
	}
	printf("\n   ");
	for(i=0;i<length;i++){
		printf("--------");
	}
	printf("\n");
	for(i = 0;i<length;i++){
		turquoise();
		printf("%d |   ",i+1);
		white();
		for(j = 0; j<length;j++){
			if(area[i][j] == '-'){
				red();
			}
			printf("\t%c",area[i][j]);
			white();
		}	
		printf("\n");
	}
	printf("---------------------------------------------------------------\n");
	green();
	printf("Acmak istedigin 1. kartin satirini gir.\n");
	scanf("%d",&row1);
	row1=row1-1;
	
	if((row1<0)||(row1>=length)){
		system(cls);
		red();
		printf("Lutfen gecerli bir satir degeri gir!\n");
		playersFirstCard(length);
		return;
	}
	green();
	printf("Acmak istedigin 1. kartin sutununu gir.\n");
	scanf("%d",&column1);
	column1=column1-1;
	
	if((column1<0)||(column1>=length)){
		system(cls);
		red();
		printf("Lutfen gecerli bir sutun degeri gir!\n");
		playersFirstCard(length);
		return;
	}
	
	if(area[row1][column1] == '-'){
		system(cls);
		red();
		printf("Bu kart zaten dogru eslesti lutfen farkli bir kart sec!\n");
		playersFirstCard(length);
		return;
	}
	system(cls);
}

void playersSecondCard(int length){
	white();
	printf("---------------------------------------------------------------\n        ");
	for(i=0;i<length;i++){
		turquoise();
		printf("%d\t",i+1);
	}
	printf("\n   ");
	for(i=0;i<length;i++){
		printf("--------");
	}
	printf("\n");		
	for(i = 0;i<length;i++){
		turquoise();
		printf("%d |   ",i+1);
		white();		
		for(j = 0; j<length;j++){
			if((i == row1) && (j == column1)){
				blue();
				printf("\t%d",nums[i][j]);
				white();
			}else{
				if(area[i][j] == '-'){
					red();
				}				
				printf("\t%c",area[i][j]);
				white();
			}
		}	
		printf("\n");
	}
	printf("---------------------------------------------------------------\n");	
	green();
	printf("Acmak istedigin 2. kartin satirini gir.\n");
	scanf("%d",&row2);
	row2=row2-1;
	
	if((row2<0)||(row2>=length)){
		system(cls);
		red();
		printf("Lutfen gecerli bir satir degeri gir!\n");
		playersSecondCard(length);
	}
	green();
	printf("Acmak istedigin 2. kartin sutununu gir.\n");
	scanf("%d",&column2);
	column2=column2-1;
	
	if((column2<0)||(column2>=length)){
		system(cls);
		red();
		printf("Lutfen gecerli bir sutun degeri gir!\n");
		playersSecondCard(length);
		return;
	}	
	
	if(area[row2][column2] == '-'){
		system(cls);
		red();
		printf("Bu kart zaten dogru eslesti lutfen farkli bir kart sec!\n");
		playersSecondCard(length);
		return;
	}	
	
	if((row1==row2)&&(column1==column2)){
		system(cls);
		red();
		printf("Bu kart zaten acik. Lutfen farkli bir kart sec!\n");
		playersSecondCard(length);
		return;
	}
	white();
	system(cls);
	printf("---------------------------------------------------------------\n        ");
	for(i=0;i<length;i++){
		turquoise();
		printf("%d\t",i+1);
	}
	printf("\n   ");
	for(i=0;i<length;i++){
		printf("--------");
	}
	printf("\n");					
	for(i = 0;i<length;i++){
		turquoise();
		printf("%d |   ",i+1);
		white();		
		for(j = 0; j<length;j++){
			if((i == row1) && (j == column1)){
				blue();
				printf("\t%d",nums[i][j]);
				white();
			}else if((i == row2) && (j == column2)){
				blue();
				printf("\t%d",nums[i][j]);
				white();
			}else{
				if(area[i][j] == '-'){
					red();
				}				
				printf("\t%c",area[i][j]);
				white();
			}
		}	
		printf("\n");
	}
	printf("---------------------------------------------------------------\n");
}	

void computersFirstCard(int length,int memoryLength){
	
	matched = 0;
	for(i=0;i<memoryLength;i++){
		for(j=0;j<memoryLength;j++){
			if((memoryValue[i])==(memoryValue[j])){
				if((memoryRow[i]!=memoryRow[j])||(memoryColumn[i]!=memoryColumn[j])){
					if(area[memoryRow[i]][memoryColumn[i]] != '-'){
						row1 = memoryRow[i];
						row2 = memoryRow[j];
						column1 = memoryColumn[i];
						column2 = memoryColumn[j];
						matched = 1;
						break;
					}
				}
			}
		}
		if(matched == 1){
			break;
		}
	}
	
	if(matched == 0){
		row1 = rand() % length;
		column1 = rand() % length;
	}
	
	if(area[row1][column1] == '-'){
		system(cls);
		computersFirstCard(length,memoryLength);
		return;
	}
	green();
	printf("Bilgisayarin 1. hamlesi!\n");
	sleep(1);
	system(cls);
	white();
	printf("---------------------------------------------------------------\n        ");
	for(i=0;i<length;i++){
		turquoise();
		printf("%d\t",i+1);
	}
	printf("\n   ");
	for(i=0;i<length;i++){
		printf("--------");
	}
	printf("\n");		
	for(i = 0;i<length;i++){
		turquoise();
		printf("%d |   ",i+1);
		white();		
		for(j = 0; j<length;j++){
			if((i == (row1)) && (j == (column1))){
				blue();
				printf("\t%d",nums[i][j]);
				white();
			}else{
				if(area[i][j] == '-'){
					red();
				}				
				printf("\t%c",area[i][j]);
				white();
			}
		}	
		printf("\n");
	}
	printf("---------------------------------------------------------------\n");
	sleep(2);
	system(cls);	
}
	
void computersSecondCard(int length,int memoryLength){
	system(cls);
	
	if(matched == 0){
		if((findFromMemory(memoryLength,row1,column1,nums[row1][column1]))==1){
			row2 = matchedRow;
			column2 = matchedColumn;
		}else{
			row2 = rand() % length;
			column2 = rand() % length;
			for(i=0;i<memoryLength;i++){
				if(memoryValue[i] == nums[row2][column2]){
					if((memoryRow[i]==row2)&&(memoryColumn[i]==column2)){
						system(cls);
						computersSecondCard(length,memoryLength);
						return;
					}
				}
			}
		}
	}
	
	if(area[row2][column2] == '-'){
		system(cls);
		computersSecondCard(length,kMemoryLength);
		return;
	}
	
	if((row1==row2)&&(column1==column2)){
		system(cls);
		computersSecondCard(length,kMemoryLength);
		return;
	}
	green();
	printf("Bilgisayarin 2. hamlesi!\n");
	sleep(1);
	system(cls);
	white();
	printf("---------------------------------------------------------------\n        ");
	for(i=0;i<length;i++){
		turquoise();
		printf("%d\t",i+1);
	}
	printf("\n   ");
	for(i=0;i<length;i++){
		printf("--------");
	}
	printf("\n");
	for(i = 0;i<length;i++){
		turquoise();
		printf("%d |   ",i+1);
		white();		
		for(j = 0; j<length;j++){
			if((i == (row1)) && (j == (column1))){
				blue();
				printf("\t%d",nums[i][j]);
				white();
			}else if((i == (row2)) && (j == (column2))){
				blue();
				printf("\t%d",nums[i][j]);
				white();
			}else{
				if(area[i][j] == '-'){
					red();
				}				
				printf("\t%c",area[i][j]);
				white();
			}
		}	
		printf("\n");
	}
	printf("---------------------------------------------------------------\n");
		
}	

void gameEnd(int length){
	green();
	if(playerScore == (length*length/4+1)){
		printf("Tebrikler %s! %d tahminle oyunu kazandin. Puanin: %d. Bilgisayarin puani: %d.",name,playersGuesses,playerScore,computerScore);
	}else if(computerScore==(length*length/4+1)){
		printf("Bilgisayar %d tahminle oyunu kazandi. Bilgisayarin puani: %d. Puanin: %d.",computersGuesses,computerScore,playerScore);
	}else{
		printf("Oyun berabere bitti. Puanin: %d. Bilgisayarin puani: %d.",playerScore,computerScore);
	}
	white();
	sleep(5);
}

void red(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
}

void white(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void blue(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
}

void green(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}

void turquoise(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
}


