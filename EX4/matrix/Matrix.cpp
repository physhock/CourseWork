#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Programma prinimaet iz in.txt file s matricey
//Vvivodit v out.txt raws&coloumns s 1 AND 0
//Shkolnikov Fedor 13501/4


//Function kotoraya razbivaet nash file po strochkam
const char *readLine(FILE *file); 
//Functiont kotoraya razbivaet strochky po simvolam,v kashestve razdelitelya - " ".
int* parseLine(const char* lineData, int& lineSize);


int main()
{

	int SizeX = 0;
	int SizeY = 0;
 
	FILE* f= fopen("C:\\Users\\FedoR\\in.txt","rt");
	int counter = 0;
	while (!feof(f) && counter < 2 ) 
	{
		const char *line = readLine(f);
		if (counter == 0 )
		{
			SizeX = atoi(line);
			free((void*)line);
		}
		else if (counter == 1 )
		{
			SizeY = atoi(line);
			free((void*)line);
		} 		
		counter++;
	}
	
    



		FILE* fout=fopen("C:\\Users\\FedoR\\out.txt", "wt");
	if (fout==0)
	{
		printf("Error opening file data.txt\n");
		return -1;
	}

	




	int testCounter = 0;
	int* ptr= NULL;
	int** pMyArray = (int**)malloc(sizeof(ptr)*SizeX);

	for ( int i=0; i < SizeX; ++i )
	{
		pMyArray[i] = (int*)malloc (sizeof(int)*SizeY);

		for ( int j =0; j < SizeY; ++j)
		{

			pMyArray[i][j] = testCounter++;
		}
	}

	
	int row = 0;
	while ( !feof(f) )
	{
		const char* lineData = readLine(f); // lineData = 0 1 2 3 
		int lineSize = 0;
		int* lineValues= parseLine(lineData,lineSize);			

		for ( int i=0; i < lineSize; ++i )
			pMyArray[row][i] = lineValues[i];

		free (lineValues);
		row++;
	}



	for ( int i=0; i < SizeX; ++i ) //Stroki
	{		
		bool hasZero = false;
		bool hasOne  = false;

		for ( int j =0; j < SizeY ; ++j)
		{
			if ( pMyArray[i][j] == 0 )
				hasZero = true;       
			else 
				hasOne = true;

			if ( hasZero && hasOne )
			{
				fprintf (fout,"Rows with both values (0 and 1) = %d\n",i);
				break;
			}
		}
	}

	
	for ( int i=0; i < SizeX; ++i ) //Stolbcu
	{		
		bool hasZero = false;
		bool hasOne  = false;

		for ( int j =0; j < SizeY ; ++j)
		{
			if ( pMyArray[j][i] == 0 )
				hasZero = true;        
			else 
				hasOne = true;

			if ( hasZero && hasOne )
			{
				fprintf (fout,"Coloumns with both values (0 and 1) = %d\n",i);
				break;
			}
		}
	}

fclose(fout);
system("pause");
return 0;
}

const char *readLine(FILE *file) {

    if (file == NULL) {
        printf("File pointer is null");
        exit(1);
    }

    int maximumLineLength = 128;
    char *lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength);

    if (lineBuffer == NULL) {
        printf("Error allocating memory for line buffer");
        exit(1);
    }

    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF)) {        
        lineBuffer[count] = ch;
        count++;

        ch = getc(file);
    }

    lineBuffer[count] = '\0';    
    return lineBuffer;
}


int* parseLine(const char* lineData, int& lineSize)
{
	const int maxRowSize=128;
	int* lineValues =  (int*)malloc(maxRowSize*sizeof(int));
	lineSize=0;
	char *token= NULL;	
   
   token = strtok((char*)lineData, " ");
   
   while( token != NULL ) 
   {	  
	  lineValues[lineSize] = atoi(token); 
      token = strtok(NULL, " ");
	  lineSize++;
   }
   return lineValues;
}