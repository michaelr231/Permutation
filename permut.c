#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_S 80 /** MAX WORD SIZE **/

/** This program called permut.c
 is about taking a word from a user that
 he wants to find in the text , and output
 all permuts for this word.
**/
void swap(char *, char *);
int permut(char *, int , int,char *,int );
int main(int argc,char *argv[])
{
	char buff[SIZE_S];
	char str[SIZE_S];
	FILE *file;
	char *string;
	int bufflen;	
	int count=0;
	int k=0,n;
	int is_per=0;
 	/** if there is 2 or less arguments in the command line return error**/	
       if (argc < 3)
	{
		fprintf(stderr,"error: There is few argumets from expected\n");
		exit(0);
    	}
	/** if there is 3 or more arguments in the command line return error**/	
	if (argc > 3)
	{
		fprintf(stderr,"error: There is too many arguments from expected\n");
		exit(0);
	}

	/** if there is 3 argumets enterd in the command line the program good to go. **/	
  	if (argc == 3)
	{
		string=argv[2];
		strcpy(str,string);
		n = strlen(str);
		/** if there is any problem with the file or doesnt exist return error **/
		if(!(file=fopen(argv[1],"r")))
		{
			fprintf(stderr,"error: Cannot open this file\n");
			exit(0);
		}

		while(!feof(file))
		{
			fscanf(file,"%s",buff);
			bufflen=strlen(buff); /** the word we just take from the text **/

				/** if there is no anything in the text file , returns error **/
				if(bufflen==0)
				{
					fprintf(stderr,"error: The file is empty\n");
					exit(0);
				}
				/** if the length of the string we just scanned is less then the string that 
				the used enter , we no check it becuse it not same size and letters. **/
				if(bufflen >= n)
				{
					if(!feof(file))/** if we already in the EOF **/
					count=permut(str, 0, n-1,buff,k);
				}
				/** it means if there is any permut we count is_per +1 **/
				if(count==1)
				is_per++;
		}	
		/** if is_per=0 like it intallized so there is no permut matchs **/
		if(is_per==0)
		fprintf(stdout,"error: There is no permute for this word\n");
	fclose(file);
	}
return 0;
}
/** This swap function is swap between
 the characters **/
void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/** This function check if there is any permut for the string
that the user enter and find in the text file , if there is a match
this function prints the output like wroten in the text file **/ 
int permut(char *a, int start, int end,char *buff ,int k)
{
	
	int q=0,p=strlen(a);
 	int i,result,g;
        const char* from = buff;
	char *to = (char*) malloc(p);/** given a size of string that user enter in the command **/
	g=strlen(buff);
	/** if we find a match permut **/
	if((strcmp(buff,a)==0))	
	k=1;
			
	/** while the original string from the user is < or = to the buffer string 
	from the text file and checks in a string "p" size in the row
	same a the length of the user enterd string. 
	for example : user= abc text: qweabcd
	first checks qwe
	then 	wea
	then	eab
	then 	abc... **/
	while(p<=g)
	{
		/** copy to new string "to" from index p and index q **/
        	strncpy(to, from+q, p-q);
		/** if we checked all the characters **/
		if (start == end)
		{
			p++;/** index+1 **/
			q++;/** index+1 **/
			result=strcmp(a,to);
			/** if the string is equals to the "to" string  we print 
			the output exaclty like in the text file **/
		        if(result==0)
			{
				printf("%s\n",a);
				k=1;	
			}
		}
		else
		{
			/** for loop checks and take char by char and swaps
			 with swap function and enter again to permute function **/
			for (i = start; i <= end; i++)
			{
				swap((a+start), (a+i));
				k=permut(a, start+1, end,to,k);
				swap((a+start), (a+i)); 
			}
			q++;
			p++;	
		}
	}
free(to);/** free malloc **/
return k;/** return to the count in the main **/
}


