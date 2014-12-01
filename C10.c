#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include  <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//C10 VertexCover Test
//1%Loading...N2T.....

int fact(int nb)
{
 if ( nb == 0 ) 
        return 1;
   else return(nb * fact(nb - 1));
}

int nb_sommet(){
return 10;}

int est_adjacent(int u, int v){
 if(0< u && 0<v && u<11 && v<11){
  return (((10+u-v)%10==1)||((10+v-u)%10==1));
 }	
 else return 0;
}



int comb_cal(int n)
{
	return fact(nb_sommet()) / ( ( fact(n) ) * ( fact(nb_sommet() - n) )  );
}



void 
ouvrirFichier (char *nom, FILE **desc, char *mode)
{
  *desc = fopen (nom, mode);
  if (*desc == NULL)
    {
      fprintf (stderr, 
	       "\"%s\": nom de fichier incorrect", 
	       nom);
      if (mode [0] == 'w')
	fprintf (stderr, " ou ouverture en ecriture impossible.");
      exit (EXIT_FAILURE);
    }
}


void 
ecrireEnTete (FILE *descFic, char *mode, int k)
{
  fprintf (descFic, "%s", mode);
  fprintf (descFic, "%d %d \n", nb_sommet(), nb_sommet()+comb_cal(k));
}


void 
ecrireGraph (char *nom, int k)
{
  FILE *descFic = NULL;
 
  ouvrirFichier (nom, &descFic, "w");
  ecrireEnTete (descFic, "p cnf ", k);
  

for(int x=1; x<=nb_sommet(); x++)
	{		
			fprintf(descFic, " %d ", x );
			for(int y=0; y<=nb_sommet(); y++)
			{
				if( (est_adjacent(x,y)==1) )
				{
					fprintf(descFic, " %d ", y);
				}
						
			}
			
			fprintf(descFic, " 0\n");
	       }

  fclose (descFic);
}




void ecrireComb(char* nom, int m, int n)
{
	
	FILE *descFic = NULL;
	ouvrirFichier (nom, &descFic, "w");
	int i;
	unsigned char c[100];
	
	for (i = 0; i < n; i++) c[i] = n - i;
 
	while (1) {
		for (i = n; i--;)
			{
				fprintf(descFic, "-%d", c[i]);
				if(i |= i)
				   fprintf(descFic, " ");
				else
		 		   fprintf(descFic, " 0\n");
			}
 
 		if (c[i]++ < m) continue;
 
		for (i = 0; c[i] >= m - i;) if (++i >= n) return;
		for (c[i]++; i; i--) c[i-1] = c[i] + 1;
	}
}

void contenu(int k)
{
    ecrireGraph("Graph.in", k) ;
    sleep(10);
    ecrireComb("Comb.in", nb_sommet(), k);  
    sleep(10);
}


void concat()
{
	char command[50];
    	strcpy( command, "cat Graph.in Comb.in > Res1.in" );
    	system(command);
}


void my_main(int k)
{
	int status; 
	pid_t fork_return; 

	fork_return = fork(); 

	if (fork_return == 0) /* child process */ 
	{ 
	    contenu(k);
    	    exit(0); 
	} 
	else /* parent process */ 
	{ 
  	wait(&status); 
  	concat();
  
	} 
}

int test()
{
	int status; 
	pid_t fork_return; 

	fork_return = fork(); 

	if (fork_return == 0) /* child process */ 
	{ 
    	char command[50];
    	strcpy( command, "minisat Res1.in res.out" );
    	system(command);
    
    	exit(0); 
	} 
	else /* parent process */ 
	{ 
   	wait(&status); 
  	int i;
	FILE *fp;
    	int c;
	fp = fopen("res.out", "r"); // error check this!
	// this while-statement assigns into c, and then checks against EOF:
	while((c = fgetc(fp)) != EOF) {
        if (c == 'U') 
	   return 0;
           //printf("FALSE");
           else
	   return 1;
	   //printf("TRUE");
        
    	}

        fclose(fp);
	//return i;
    } 
}


void test_K(int k)
{
int status; 
	pid_t fork_return; 

	fork_return = fork(); 

	if (fork_return == 0) /* child process */ 
	{ 
    	my_main(k);
    	exit(0); 
	} 
	else /* parent process */ 
	{ 
   	wait(&status); 
   	int i=test() ;
	if(i==0)
		printf("False\n");
	else
		printf("Good\n");

	}

    
}

int main(int argc, char* argv[])
{	
	int a;
	printf("Choisir 1 ou 2 pour demarrer\n");
	printf("1 pour Tester avec un K \n");
	printf("OU \n");
	printf("2 pour Chercher le K minimum\n");
	printf("Votre choix : \n");	
	scanf("%d", &a);
	if(a == 1)
	{	
		printf("Votre choix soit %d  \n", a);	
		int k;
		printf("Entrez 1 K pour Tester\n");
		scanf("%d", &k);
		test_K(k);	
	}
	else if (a ==2)
	{	
		printf("Votre choix soit %d  \n", a);
		int status; 
		pid_t fork_return; 

		fork_return = fork(); 

		if (fork_return == 0) /* child process */ 
		   { 
	    		printf("K=1...Loading...");
		   } 
		else /* parent process */ 
		   { 
  			wait(&status); 
  			for(int i=1; i<=nb_sommet()+1; i++)
			   {
				if(i != nb_sommet()+1)
				   {
					printf("K=%d...Loading....\n", i);
					test_K(i);
				
				   }
				else
				printf("THE END\n");
		   	   }
		    }
	} 
	else
	{	printf("Pas command \n");	
	 	return 0;
	} 
}
