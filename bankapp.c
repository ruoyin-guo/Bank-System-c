/*
 * Program to implement a simple bank application
 **********************************************************
 *Author                Dept,               Date                Notes
 ***************************************************************************
 *Ruoyin Guo           COmp Sci.           Mar 12 2020     Initioal version
 *Ruoyin Guo           Comp Sci.           Mar 13 2020     Debuggeing
 *
 *
 *
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void add(FILE*, char*,char*);
void deposit(FILE*, char*, char*, char*);
void withdrawl(FILE*, char*, char*, char*);
//float countBalance(FILE*);


int main(int argc, char *argv[]){

	//check the inpur is valid
	if (argc < 2){
		fprintf(stderr, "Error, incorrect usage!\n");
		fprintf(stderr, "-a ACCTNUM NAME\n");
		fprintf(stderr, "-d ACCTNUM DATE AMOUNT\n");
		fprintf(stderr, "-w ACCTNUM DATE AMOUNT\n");
		exit(1);
	}

	int a = strcmp(argv[1],"-a");
	int b = strcmp(argv[1],"-d");
	int c = strcmp(argv[1],"-w");

	//if argv[1] is -a
	if(a == 0 && argc != 4){
		fprintf(stderr, "Error, incorrect usage!\n");
		fprintf(stderr, "-a ACCTNUM NAME\n");
		exit(1);
	}

	// if argv[1] is -d
	if(b == 0 && argc != 5){
                fprintf(stderr, "Error, incorrect usage!\n");
                fprintf(stderr, "-d ACCTNUM DATE AMOUNT\n");
                exit(1);
	}
	
	//if argv[1] is -w
	if(c == 0 && argc != 5){
                fprintf(stderr, "Error, incorrect usage!\n");
                fprintf(stderr, "-w ACCTNUM DATE AMOUNT\n");
                exit(1);
	}

	FILE *s= fopen("bankdata.csv","r+a");
	if (s==NULL){
		fprintf(stderr,"Error, unable to locate the data file bankdata.csv\n");
		exit(100);
	}


	//add account
	//FILE *data = fopen("bankdata.csv","at");
	//
	if(a == 0){ //if it is -a
	add(s,argv[2],argv[3]);
	}

	if(b==0){  //if it is -d
	deposit(s,argv[2],argv[3],argv[4]);
	}

	if(c==0) {
		//float total_balance = countBalance(s);
		withdrawl(s,argv[2],argv[3],argv[4]);
	}
	fclose(s);


}

// function to pass the accountnum, name 
// return the error code
void add(FILE*source, char*ACCTNUM, char*NAME)
{
	//check if account number already exist
	char array[1000];   //arr to store source
	char new[50];  //arr to store new accout info

	fgets(array,999,source);
	while(!feof(source))
	{
		if(strstr(array,ACCTNUM)!=NULL)
		{	// if there is substring
			 fprintf(stderr, "Error, acount number %s already exists\n",ACCTNUM);
		exit(50);
		}
		fgets(array,999,source);
	}
	
		//fgets(array,999,source

	// if it is a new account num, append it to file
	strcpy(new,"AC");
	strcat(new,",");
	strcat(new,ACCTNUM);
	strcat(new, ",");
	strcat(new,NAME);
	strcat(new, "\n");

	fputs(new,source);
	
} 

void deposit(FILE*source, char*ACCTNUM, char*DATE, char*AMOUNT)
{
        //check if account exist
        char array[1000];   //arr to store source
        char new[100];  //arr to store new accout info

	int count=0;
        fgets(array,999,source);
        while(!feof(source))
        {
                if(strstr(array,ACCTNUM)!=NULL)//account does not exist
                {       // if there is substring
                        count=1;
			
                }
		fgets(array,999,source);
	}
	if(count==0){
		
		fprintf(stderr,"Error, account number %s does not exitsts\n", ACCTNUM);
		exit(50);
	}

        

        // if account num exitst, append trasaction to file
        strcpy(new,"TX");
        strcat(new,",");
        strcat(new,ACCTNUM);
        strcat(new, ",");
	strcat(new, DATE);
	strcat(new,",");
	strcat(new,AMOUNT);
	strcat(new, "\n");

        fputs(new,source);
	
}

void withdrawl(FILE*source, char*ACCTNUM, char*DATE, char*AMOUNT)
{
	char array[1000];   //arr to store each line of source
        char new[100];  //arr to store new accout info
	float balance=0;
        int count=0;
	
	char *token;

	//first go through the file to check whether the account exitst
        fgets(array,999,source);
        while(!feof(source))
        {
		
                if(strstr(array,ACCTNUM)!=NULL)//account exist
                {       
                        count=1;

                }
	

                fgets(array,999,source);
        }



	//if account does not exits	
        if(count==0){

                fprintf(stderr,"Error, account number %s does not exitsts\n", ACCTNUM);
                exit(50);
        }

	// second time go throught the file, need to chang the pointer
	rewind(source);

	char line[100];
	fgets(line,99,source);
	while(!feof(source))
	{
		char*token = strtok(line, ",");  //token at AC/TX
		if(strcmp(token,"TX")==0){  //if AC, read next line
			
			token = strtok(NULL,","); //token at acctnum
			if(strcmp(token,ACCTNUM)==0){  //acctnum has to be matched
				token = strtok(NULL,","); //date
				token = strtok(NULL,","); //money
				float f =atof(token);
				balance += f;
			}
		}
			fgets(line,99,source);
	}
	float withdrawl = atof(AMOUNT);
	if(withdrawl > balance){
		fprintf(stderr,"Error,account number %s has only %.2f\n",ACCTNUM,balance);
		exit(60);
	}
	

        // if account num exitst, append trasaction to file
        strcpy(new,"TX");
        strcat(new,",");
        strcat(new,ACCTNUM);
        strcat(new, ",");
        strcat(new, DATE);
        strcat(new,",");
	strcat(new,"-");
        strcat(new,AMOUNT);
        strcat(new, "\n");

        fputs(new,source);
}

