#include<stdio.h>
#include<conio.h>
#include<string.h>

int IC,C;
char IR[4],R[4];
int SI;
char M[100][4];
char buffer[41];
int i=0,loc;
int t=0,a=0;
int j;
FILE *fp,*fp1;

void EXECUTEUSERPROGRAM();
void LOAD();
void MOS();
void START();
void READ();
void WRITE();
void TERMINATE();
void init();

void EXECUTEUSERPROGRAM()
{

    for(i=0;i<4;i++)
    {
        IR[i]=M[IC][i];
    }

    loc = ((int)IR[2] -48)*10 + ((int)IR[3] -48);
    IC++;
	printf("\n\n%d\n\n",loc);
    if(IR[0] == 'G' && IR[1] =='D')
    {
        SI = 1;
        printf("\nIN GD\n");
        MOS();
    }

    else if(IR[0] == 'P' && IR[1] =='D')
    {
        SI = 2;
        printf("\nIN PD\n");
        int i;
        for(i=loc;i<loc+10;i++)
        {
            printf("M[%d] : ",i);
            for(j=0;j<4;j++)
            {


                printf("%c",M[i][j]);
            }
            printf("\n");
        }
	MOS();

    }

    else if(IR[0] == 'H')
    {
        SI = 3;
        printf("Program TERMINATEd");
        MOS();
    }

    else if(IR[0]=='L' && IR[1]=='R')
    {
        printf("\nIn LR\n");
        for(i=0;i<4;i++)
        {
            R[i]=M[loc][i];
            printf("%c",R[i]);
        }
        EXECUTEUSERPROGRAM();
    }

    else if(IR[0]=='S' && IR[1]=='R')
    {
    printf("\nIN SR\n" );
    printf("\nmemory stored with data-->>");
    for(i=0;i<4;i++)
    {
        M[loc][i]=R[i];
        printf("%c",M[loc][i]);
    }
    EXECUTEUSERPROGRAM();
    }

    else if(IR[0]=='C' && IR[1]=='R')
    {
        for(i=0;i<4;i++)
        {
            if(R[i]==M[loc][i])
              {  printf("\nStrings Match\n");
		C=1;
}
            else
            {
                C=0;
                printf("\nStrings Don't Match\n");
		break;
            }
        }

            EXECUTEUSERPROGRAM();
    }

    else if(IR[0]=='B' && IR[1]=='T')
    {
        if(C==1)
        {
            IC=loc;
            printf("\nValue of IC ->>%d", IC);
        }

    EXECUTEUSERPROGRAM();
    }

}

void init()
{
    int i, j;
    for(i=0;i<100;i++)
    {
        for(j=0;j<4;j++)
        {
            M[i][j]='$';
        }
    }

    for(i=0;i<4;i++)
    {
        IR[i]=R[i]='$';
    }

    for(i=0;i<4;i++)
    {
        IR[i]=R[i]='$';
    }
}

void READ()
{
    int i, j, k;

    if(fgets(buffer,41,fp)!=NULL)
    {

        k=0;
        for(i=loc;i<loc+10;i++)
        {
            printf("M[%d] : ",i);
            for(j=0;j<4 && buffer[k]!='\0';j++)
            {
                M[i][j]=buffer[k];
                k++;

                printf("%c",M[i][j]);
            }
            printf("\n");
        }

    }
    EXECUTEUSERPROGRAM();
}
deletebuffer()

{
int asd;
for(asd=0;asd<41;asd++)
{
	buffer[asd]=NULL;
}
}
void WRITE()
{
    int i, j, k;
    IR[3] = '0';

    k=0;


	printf("\n");
	deletebuffer();
    for(i=loc; i<loc+10; i++)
    {
	for(j=0; j<4 && M[i][j]!='$'; j++)
        {
		if(M[i][j]=='\n')
		{
			buffer[k]=' ';
		}
		else
		buffer[k] = M[i][j];
		printf("%c",buffer[k]);
		k++;
        }
    }
	buffer[k]='\n';
	printf("\nlets see the whole string\n");
	int as;
	for(as=0;as<41;as++)
	{
		printf("%c",buffer[as]);
	}

        fputs(buffer,fp1);

    EXECUTEUSERPROGRAM();
}

void TERMINATE()
{
    memset(buffer,0,41);
    buffer[0]='\n';
    buffer[1]='\n';
    fputs(buffer,fp1);
}

void MOS()
{
        switch(SI)
        {
            case 1:
                READ();
                break;

            case 2:
                WRITE();
                break;

            case 3:
                TERMINATE();
                break;

            default:
                SI = 0;
        }
}



void START()
{

    IC = 0;
    EXECUTEUSERPROGRAM();
}

void LOAD()
{
    int t=0;
    int i,j,k;
    while(getc(fp)!=EOF)
    {
        fseek(fp,-1,SEEK_CUR);
        memset(buffer,0,42);
	fgets(buffer,42,fp);


        printf("\nBuffer contents\n");
        for(i=0;i<41;i++)
	{
	printf("%c",buffer[i]);
        }
	printf("\n");

        if(buffer[0] == '$' && buffer[1] == 'A' && buffer[2] =='M' && buffer[3] == 'J')
        {
                printf("\nProcess STARTed\n");
               t=0;
                init();
        }
        else if(buffer[0] == '$' && buffer[1] == 'D' && buffer[2] =='T' && buffer[3] == 'A')
        {
            START();
        }

        else if(buffer[0] == '$' && buffer[1] == 'E' && buffer[2] =='N' && buffer[3] == 'D')
            continue;

else
	{
        int k,i;
		for(k=t;k<t+10;k++)
		{
			printf("M[%d]:",k);
			for(i=0;i<4;i++)
			{
				M[k][i]=buffer[a];
				a++;
				printf("%c",M[k][i]);
			}
			printf("\n");


		}
		t=t+10;
		a=0;
	}
    }
    fclose(fp);
    fclose(fp1);
}


int main()
{
  fp=fopen("input.txt","r");
  fp1=fopen("output.txt","w");

    LOAD();

    return 0;
}
