#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include "mesfonctions.h"
#include <unistd.h>
#include <pthread.h>








void definirPixel(SDL_Surface *surface, int x, int y, int red, int green, int blue)
{
	Uint32 pixel;
	pixel=SDL_MapRGB(surface->format, red,green, blue); // on défini la couleur du nouveau pixel

    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.

    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur

    de l'image : 8, 16, 24 ou 32 bits.*/

    int nbOctetsParPixel = surface->format->BytesPerPixel;

    /*Ici p est l'adresse du pixel que l'on veut modifier*/

    /*surface->pixels contient l'adresse du premier pixel de l'image*/

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;


    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/

    switch(nbOctetsParPixel)

    {

        case 1:

            *p = pixel;

            break;


        case 2:

            *(Uint16 *)p = pixel;

            break;


        case 3:

            /*Suivant l'architecture de la machine*/

            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)

            {

                p[0] = (pixel >> 16) & 0xff;

                p[1] = (pixel >> 8) & 0xff;

                p[2] = pixel & 0xff;

            }

            else

            {

                p[0] = pixel & 0xff;

                p[1] = (pixel >> 8) & 0xff;

                p[2] = (pixel >> 16) & 0xff;

            }

            break;


        case 4:

            *(Uint32 *)p = pixel;

            break;

    }

}

int calculDistanceEuclidienne(int nombreNeurones, int nombreDentrees,float *valEntrees,float *resultParNeurone, float **poidsNeurones)
{
	int i,j,nbNeuronesModifies,neuroMin;
	nbNeuronesModifies=0;
	neuroMin=0;
		for (i= 0; i < nombreNeurones; ++i)
		{
			resultParNeurone[i]=0;
			for(j=0;j<nombreDentrees;j++)
			{
				resultParNeurone[i]+=(float)pow((double)(poidsNeurones[i][j]-valEntrees[j]),2);
		//		printf("valEntrees=%lf\n",valEntrees[j] );
			}
			if (resultParNeurone[neuroMin]>resultParNeurone[i])
			{
				neuroMin=i;
			}
		}
		for (i= 0; i < nombreNeurones; ++i)
		{
			printf("resultParNeurone =%lf, resultParNeurone[neuroMin]* MULT_DIST_MIN=%lf\n",resultParNeurone[i],resultParNeurone[neuroMin]* MULT_DIST_MIN );
			if(resultParNeurone[i]<resultParNeurone[neuroMin]* MULT_DIST_MIN) //
			{
				nbNeuronesModifies++;
			}
		}
		return nbNeuronesModifies;
}


void classeResultDansGeneral(int nombreNeurones,float *resultParNeurone,int *classementGeneral)
{
		int max=0;
		int flagMax,i,j;
		for (i=nombreNeurones-1; i>=0 ; --i) 
		{
			
				for (j = 0; j < nombreNeurones; ++j)
				{
					if (max<resultParNeurone[j])
					{
						max=resultParNeurone[j];
						flagMax=j;
					}
				}

				classementGeneral[i]=flagMax;
				resultParNeurone[flagMax]=0;
				flagMax=0;
				max=0;
		}

		for ( i = 0; i < nombreNeurones; ++i)
		{
		//	printf("%d=%d\n",i,classementGeneral[i] );
		}

}



void sauvegardeDansTab(int nbNeuronesModifies, int nombreDentrees,int numeroMaladie,int *classementGeneral,float **poidsNeurones,float ***saveMaladiesNeuronesPoids)
{
	int saveData,i,j;
	printf("Voulez-vous sauvegarder les neurones ?\n");
	do
	{
	printf("1 : Oui\n");
	printf("0 : Non\n");
	scanf("%d",&saveData);
	CLEAR_STDIN;
	}while(saveData!=1 && saveData!=0);

	if(saveData==1)
	{
		saveMaladiesNeuronesPoids[numeroMaladie]=malloc((nbNeuronesModifies+1)*sizeof(float*));
		for (int i = 0; i < nbNeuronesModifies+1; ++i)
		{
			saveMaladiesNeuronesPoids[numeroMaladie][i]=malloc(nombreDentrees*sizeof(float));
		}
		saveMaladiesNeuronesPoids[numeroMaladie][0][0]=nbNeuronesModifies;
		for (i = 1; i < nbNeuronesModifies+1; ++i)
		{
			for (j = 0; j < nombreDentrees; ++j)
			{
				saveMaladiesNeuronesPoids[numeroMaladie][i][j]=poidsNeurones[classementGeneral[i-1]][j]; // car les maladies vont de 1 à 5 
				printf("neurone %d, valSauvegardé %f\n",i,saveMaladiesNeuronesPoids[numeroMaladie][i][j] );
			}
		}
		
	}

}









void sauvegardeDansFichier(int nombreDentrees,float ***saveMaladiesNeuronesPoids)
{
	int i,j,saveData;
	short nbMal=(short)NB_MALADIES;
	float nbNeuronesModifies;

	

	do
	{
	printf("Voulez-vous sauvegarder vos données ?\n");
	printf("1 Oui\n");
	printf("0 Non\n");
	scanf("%d",&saveData);
	CLEAR_STDIN;
	}while(saveData!=1 && saveData!=0);
	if (saveData==1)
	{

			FILE* fichier = NULL;


		    fichier = fopen(NOM_FICHIER, "r+");

		    if (fichier != NULL)
		    {
		    	
		   		fwrite(&nbMal,sizeof(short),1,fichier);
		   		fwrite(&nombreDentrees,sizeof(int),1,fichier);
		       	for (i = 0; i < NB_MALADIES; ++i)
		       	{  				
   					nbNeuronesModifies=saveMaladiesNeuronesPoids[i][0][0];
		     		for (j = 0; j<nbNeuronesModifies; ++j)
		       		{
			       		
			       			fwrite(saveMaladiesNeuronesPoids[i][j],nombreDentrees*sizeof(float),1,fichier);	
			       		
			       	}
		       	}
		        fclose(fichier); // On ferme le fichier qui a été ouvert

		    }
		    else
		    {
		    	printf("ERROR FICHIER NON OUVRABLE, VERIFIER SON EXISTENCE\n");
		    }
	}

}

int loadDepuisFichier(float ****saveMaladiesNeuronesPoids)
{
	int i,j,loadData,nombreDentrees;
	short nbMal;
	float nbNeuronesModifies;
	


   
	

	do
	{
	printf("Voulez-vous charger les données depuis le fichier ?\n");
	printf("1 Oui\n");
	printf("0 Non\n");
	scanf("%d",&loadData);
	CLEAR_STDIN;
	}while(loadData!=1 && loadData!=0);
	if (loadData==1)
	{

			FILE* fichier = NULL;


		    fichier = fopen(NOM_FICHIER, "r+");
		   
		    if (fichier != NULL)
		    {
		   		fread(&nbMal,sizeof(short),1,fichier);
		   		*saveMaladiesNeuronesPoids=malloc(nbMal*sizeof(float**));
		   		fread(&nombreDentrees,sizeof(int),1,fichier);
				
		       	for (i = 0; i < NB_MALADIES; ++i)
		       	{
		       	
		       		fread(&nbNeuronesModifies,sizeof(float),1,fichier);
		       		fseek(fichier, (-1)*sizeof(float), SEEK_CUR); // on se redécale vers la gauche pour faire tout le tab en 1 coup
		       		printf("nbNeuronesModifies=%lf\n",nbNeuronesModifies);
		       		(*saveMaladiesNeuronesPoids)[i]=malloc(((int)nbNeuronesModifies+1)*sizeof(float*));
		       		
		       		

		     		for (j = 0; j <(int)(nbNeuronesModifies); ++j)
		       		{
			       			(*saveMaladiesNeuronesPoids)[i][j]=malloc(nombreDentrees*sizeof(float));

			       			fread((*saveMaladiesNeuronesPoids)[i][j],nombreDentrees*sizeof(float),1,fichier);	
			      	
			       	}

		       	}
		        fclose(fichier); // On ferme le fichier qui a été ouvert



/*
float nbN;
save=malloc(NB_MALADIES*sizeof(float*));
for (i = 0; i < NB_MALADIES; ++i)
{
	save[i]=malloc(((int)saveMaladiesNeuronesPoids[i][0][0])*sizeof(float*));
	
}	

for (i = 0; i < NB_MALADIES; ++i)
{
	for (j = 0; j < (int)saveMaladiesNeuronesPoids[i][0][0] ; ++j)
	{
		save[i][j]=malloc(nombreDentrees*sizeof(float));
		
	}
}


//save[0][0][0]=1;


for (i = 0; i < NB_MALADIES; ++i)
{

	nbN=saveMaladiesNeuronesPoids[i][0][0];
	printf("maladie nb %d, nbN=%d/%lf\n",i,j,nbN );
	for (j =1; j < (int)saveMaladiesNeuronesPoids[i][0][0] ; ++j)
	{
		for (k = 0; k < nombreDentrees; ++k)
		{
			printf("je suis là \n");
			save[i][j][k]=saveMaladiesNeuronesPoids[i][j][k];
		}
			printf("nbN numéro : %d\n",j );
	}
	printf("maladie numéro : %d\n",i );
}
*/
			

printf("nombreDentrees=%d\n",nombreDentrees );
		    if(nombreDentrees!=0)

		        return nombreDentrees;
		    }
		    else
		    {
		    	printf("ERROR FICHIER NON OUVRABLE, VERIFIER SON EXISTENCE\n");
		    	return -1;
		    }
	}

	return -1;

}


/*
void* retunSave()
{
	return save;
}*/




/*

void amelioreGagnantEtVoisin(float** poidsNeurones, int nombreNeurones, int nombreDentrees, float* valEntrees ,int neuroneGagnant)
{
	int i,j,max,flagMax;
	float* resultParNeurone; //prend le résultat et le numéro du neurone dans le poidsNeurones
	resultParNeurone=malloc(nombreNeurones*sizeof(float)); 

	float* resultParNeuroneBis; //prend le résultat et le numéro du neurone dans le poidsNeurones
	resultParNeuroneBis=malloc(nombreNeurones*sizeof(float)); 

	int* classementVoisins;
	classementVoisins=malloc(nombreNeurones*sizeof(int)); 



	for (i= 0; i < nombreNeurones; ++i)
	{
		resultParNeurone[i]=0;
		for(j=0;j<nombreDentrees;j++)
		{
			resultParNeurone[i]+=(float)pow((double)(poidsNeurones[i][j]-poidsNeurones[neuroneGagnant][j]),2);

		}
		printf("neurone %d, resultParNeurone=%f \n",i,resultParNeurone[i]);
	}

for (i = 0; i < nombreNeurones; ++i)
{
	resultParNeuroneBis[i]=resultParNeurone[i];

}


max=0;
for (i=nombreNeurones-1; i>=0 ; --i) 
{
	
		for (j = 0; j < nombreNeurones; ++j)
		{

			if (max<resultParNeuroneBis[j])
			{
				max=resultParNeuroneBis[j];
				flagMax=j;
			}
		}

		classementVoisins[i]=flagMax;

		resultParNeuroneBis[flagMax]=0;
		flagMax=0;
		max=0;
		
}

free(resultParNeuroneBis);

// resultParNeurone[classementVoisins[0]] permet d'avoir la distance euclidienne (calculée précédement) du neurone le plus proche de la cible (ici le gagnant)
// fonctionHj(resultParNeurone[classementVoisins[0]]) permet d'avoir la modulation de la vitesse d'apprentissage correspondante

for (i = 0; i < nombreDentrees; ++i)
{

for (j = 0; j < nombreNeurones; ++j)
	{
			poidsNeurones[classementVoisins[j]][i]=poidsNeurones[classementVoisins[j]][i] + (VITESSE_APPRENTISSAGE *fonctionHj(resultParNeurone[classementVoisins[j]])*(valEntrees[i]-poidsNeurones[classementVoisins[j]][i]));
		printf("resultParNeurone[classementVoisins[j]] %f\n", resultParNeurone[classementVoisins[j]]);
	}

}

}


	


float fonctionHj(float distanceEuclidienne)
{
	
	float resultat=(float)exp(-((pow((double)distanceEuclidienne,2))/(2*pow((double)SIGMA,2))));
	printf("distanceEuclidienne=%f, hj()=%f\n",distanceEuclidienne,resultat );
	return resultat;
}

*/



void amelioreGagnantEtVoisin(float** poidsNeurones, int nombreNeurones, int nombreDentrees, float* valEntrees ,int neuroneGagnant, float apprentissage)
{
	int i,j,max,flagMax;
	float oldVal;
	float* resultParNeurone; //prend le résultat et le numéro du neurone dans le poidsNeurones
	resultParNeurone=malloc(nombreNeurones*sizeof(float)); 

	float* resultParNeuroneBis; //prend le résultat et le numéro du neurone dans le poidsNeurones
	resultParNeuroneBis=malloc(nombreNeurones*sizeof(float)); 

	int* classementVoisins;
	classementVoisins=malloc(nombreNeurones*sizeof(int)); 




	for (i= 0; i < nombreNeurones; ++i)
	{
		resultParNeurone[i]=0;
		for(j=0;j<nombreDentrees;j++)
		{
			resultParNeurone[i]+=(float)pow((double)(poidsNeurones[i][j]-poidsNeurones[neuroneGagnant][j]),2);

		}
	//	printf("resultParNeurone %f \n", resultParNeurone[i]);
	}

	for (i = 0; i < nombreNeurones; ++i)
	{
		resultParNeuroneBis[i]=resultParNeurone[i];

	}


	max=0;
	for (i=nombreNeurones-1; i>=0 ; --i) 
	{
		
			for (j = 0; j < nombreNeurones; ++j)
			{

				if (max<resultParNeuroneBis[j])
				{
					max=resultParNeuroneBis[j];
					flagMax=j;
				}
			}

			classementVoisins[i]=flagMax;

			resultParNeuroneBis[flagMax]=0;
			flagMax=0;
			max=0;
			
	}

	free(resultParNeuroneBis);

	// resultParNeurone[classementVoisins[0]] permet d'avoir la distance euclidienne (calculée précédement) du neurone le plus proche de la cible (ici le gagnant)
	// fonctionHj(resultParNeurone[classementVoisins[0]]) permet d'avoir la modulation de la vitesse d'apprentissage correspondante

	for (i = 0; i < nombreNeurones; ++i)
	{

		for (j = 0; j < nombreDentrees; ++j)
		{
			oldVal=poidsNeurones[classementVoisins[i]][j] + (apprentissage*fonctionHj(resultParNeurone[classementVoisins[i]])*(valEntrees[j]-poidsNeurones[classementVoisins[i]][j]));
			
				poidsNeurones[classementVoisins[i]][j]=oldVal;
				
			//	printf("classement ordre décroissant %lf \n" ,poidsNeurones[classementVoisins[i]][j] );
		}

		//	printf("resultParNeurone[classementVoisins[i]] %f\n", resultParNeurone[classementVoisins[i]]);

	}
}


	


float fonctionHj(float distanceEuclidienne)
{
	float resultat=(float)exp(-((pow((double)distanceEuclidienne,2))/(2*pow((double)SIGMA,2))));
//	printf("distanceEuclidienne=%f, hj()=%f\n",distanceEuclidienne,resultat );

	return resultat;
}



