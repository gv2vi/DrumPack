#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include  <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//VertexCover2Sat using Minisat
//??%Loading....

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
	{		fprintf(descFic, " %d ", x );
				
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
 
 
		/* this check is not strictly necessary, but if m is not close to n,
		   it makes the whole thing quite a bit faster */
		if (c[i]++ < m) continue;
 
		for (i = 0; c[i] >= m - i;) if (++i >= n) return;
		for (c[i]++; i; i--) c[i-1] = c[i] + 1;
	}
}

int main(int argc, char* argv[])
{
	int status; 
	pid_t fork_return; 

	fork_return = fork(); 

	if (fork_return == 0) /* child process */ 
	{ 
	    int k;
	    printf("Choose K : \n");
	    scanf("%d", &k);
	    ecrireGraph("Graphe.in", k) ;
    	    ecrireComb("Combinaison.in", nb_sommet(), k);
    	    exit(0); 
	} 
	else /* parent process */ 
	{ 
  	wait(&status); 
  	char command[50];
    	strcpy( command, "cat Graphe.in Combinaison.in > Final.in" );
    	system(command);
 	} 
}
