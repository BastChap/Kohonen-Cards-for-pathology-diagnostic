#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "mesfonctions.h"
#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <time.h>
#include <sys/stat.h>
#include <string.h>		// pour les strcpy et strcat
#include <unistd.h>		// pour le execl
#include <sys/types.h>  // pour le wait
#include <sys/wait.h>	// pour le wait








int main(int argc, char *argv[])

{

	    SDL_Surface *ecran = NULL, *imageDeFond = NULL;
	    SDL_Rect positionFond;
	    positionFond.x = 0;
	    positionFond.y = 0;
	   
	    SDL_Init(SDL_INIT_VIDEO);


		int nombreDentrees=4;		// les entrées Fievre, diahree, Sueurs, Toux




printf("**************************************************************************************************************************************************************************************\n");
printf("LOGICIEL DE DETECTION DE MALADIES\n");
printf("Detecte Grippe, Rhume, Gastro, Hypoglycémie, Aucune Maladie\n");
printf("Les paramètres utilisés sont des floattants\n");
printf("FIEVRE : Température en °C Valeur min=36°C, Valeur max=41°C\n");
printf("VOMISSEMENTS : Valeur min : 0-1 = Aucune envie, valeur max : 9-10 = J'ai des vomissements à fortes répétitions, avec 3 = Nausées/Légères envies de vomir\n");
printf("SUEURS : Valeur min : 0-1 = Pas de sueurs,frissons... Valeur max : 9-10 = Fortes sueurs, frissons important et fréquents\n");
printf("TOUX : Valeur min : 0-1 = Forte toux Sèche, 5=pas de toux, Valeur max : 9-10 = Forte toux Grasse\n");
printf("**************************************************************************************************************************************************************************************\n");



/* // permet de généraliser les entrée 1
		do{
		printf("combien d'entrees ? (minimum 2)\n");
		retour=scanf("%d",&nombreDentrees);
		CLEAR_STDIN;
		}while(nombreDentrees<2);
*/



		float *valEntrees;
		int retour;
		float constApprentissage;
		int nbNeuronesModifie=0;
		valEntrees=malloc(nombreDentrees*sizeof(float));


		int nombreNeurones;		//les neurones
		printf("combien de neurones voulez-vous ?\n");
		retour=scanf("%d",&nombreNeurones);
		CLEAR_STDIN;
		
		float val;
		
		int firstLap=0;
		int x=0;
		int y=0;
		int i;
		int j;
		int k;
		int m;
		int tempsMax,temps;
		float nbN;
		int select=0; // permet de varier entre afficher tous les neurones ou que ceux plus proche
		int choix=1;
		int numeroMaladie;
		int rMaladie=0;
		int gMaladie=0;
		int bMaladie=0;
		int choose;
		int varLoad;
		int flagChangeMaladie=1;
		int valImod;
		char nomMaladie[50];


		float** poidsNeurones;

		//initialisation du tab
		poidsNeurones=malloc((nombreNeurones)*sizeof(float*));
		for (i=0; i<nombreNeurones; i++)
		{
			poidsNeurones[i]=malloc(nombreDentrees*sizeof(float));
		}


		float* resultParNeurone; //prend le résultat et le numéro du neurone dans le poidsNeurones
		resultParNeurone=malloc(nombreNeurones*sizeof(float)); 

		int* classementGeneral;
		classementGeneral=malloc(nombreNeurones*sizeof(int)); 
		

		float *** saveMaladiesNeuronesPoids;
		saveMaladiesNeuronesPoids=malloc(NB_MALADIES*sizeof(float*)); //NB_MALADIES est le nombre de maladies, après c'est le nombre de neurones dans la zone puis nombre d'entrees
		for (i=0; i<NB_MALADIES; i++)
		{
			
			saveMaladiesNeuronesPoids[i]=malloc(nombreNeurones*sizeof(float*));
			for (j = 0; j < nombreNeurones; ++j)
			{
							saveMaladiesNeuronesPoids[i][j]=malloc(nombreDentrees*sizeof(float));
			}

		}
		


		for (i=0; i<NB_MALADIES; i++)
		{
			for (j = 0; j < nombreNeurones; ++j)
			{
				for (k = 0; k < nombreDentrees; ++k)
				{
					saveMaladiesNeuronesPoids[i][j][k]=0;

				}
			
			}	

		}

		




		varLoad=loadDepuisFichier(&saveMaladiesNeuronesPoids);

		

		if (varLoad!=-1)
		{
			nombreDentrees=(int)varLoad;
			flagChangeMaladie=0;
	
			for (i = 0; i < NB_MALADIES; ++i)
			{
							nbN=saveMaladiesNeuronesPoids[i][0][0];
				
			}
			for (i = 0; i <nombreNeurones; ++i)
			{
				classementGeneral[i]=i;
			}
		
		}	
		


tempsMax=50;
temps=0;

while(choix != 0)
	{

		if(choix==1)
		{

			if (firstLap!=0)
			{
				sauvegardeDansTab(nbNeuronesModifie,nombreDentrees,numeroMaladie,classementGeneral,poidsNeurones,saveMaladiesNeuronesPoids);
			
			}
			else
			{
				firstLap=1;
			}
			


			do
			{
				

			printf("Quelle est la maladie ? (1-5)\n");
			if(saveMaladiesNeuronesPoids[0][0][0!=0]){printf("Initialized");}
			printf("1 : Grippe\n");
			if(saveMaladiesNeuronesPoids[1][0][0!=0]){printf("Initialized");}
			printf("2 : Rhume\n");
			if(saveMaladiesNeuronesPoids[2][0][0!=0]){printf("Initialized");}
			printf("3 : Gastro\n");
			if(saveMaladiesNeuronesPoids[3][0][0!=0]){printf("Initialized");}
			printf("4 : Hypoglycémie\n");
			if(saveMaladiesNeuronesPoids[4][0][0!=0]){printf("Initialized");}
			printf("5 : Rien, vous n'avez absolument rien\n");
			printf("6 : Ne rien faire\n");
		//	printf("7 : Tester une maladie inconnue\n");
			

			retour=scanf("%d",&numeroMaladie);
			CLEAR_STDIN;
				

			}while(numeroMaladie!=1 && numeroMaladie!=2 && numeroMaladie!=3 && numeroMaladie!=4 && numeroMaladie!=5 && numeroMaladie!=6);
			numeroMaladie--;
			if (numeroMaladie!=5)
			{
			temps=0;
			switch(numeroMaladie) // du binaire avec les 255, on peut faire jusqu'à 8 couleurs, noir inclus
			{
				case 0:
				strcpy(nomMaladie,"Grippe");
				rMaladie=255;
				gMaladie=0;
				bMaladie=0;
				break;

				case 1:
				strcpy(nomMaladie,"Rhume");
				rMaladie=0;
				gMaladie=255;
				bMaladie=0;
				break;

				case 2:
				strcpy(nomMaladie,"Gastro");
				rMaladie=255;
				gMaladie=255;
				bMaladie=0;
				break;

				case 3:
				strcpy(nomMaladie,"Hypoglycémie");
				rMaladie=0;
				gMaladie=0;
				bMaladie=255;
				break;

				case 4:
				strcpy(nomMaladie,"Aucune maladie");
				rMaladie=255;
				gMaladie=0;
				bMaladie=255;
				break;

				default:
				printf("erreur, faut choisir entre les maladies, sinon c'est Rien (5)\n");
				numeroMaladie=NB_MALADIES-1;
				rMaladie=255;
				gMaladie=0;
				bMaladie=255;


			}
		
			do 
			{
			printf("Comment voulez-vous définir les poids de vos neurones ?\n" );
			printf("0 : Utiliser les derniers chargés (uniquement ceux retenu)\n");
			printf("1 : Aleatoirement\n");
			retour=scanf("%d",&choose);
			CLEAR_STDIN;

			}while(choose!=0 && choose!=1);






			if(choose==0)
			{
				nbN=saveMaladiesNeuronesPoids[numeroMaladie][0][0];
				printf("choose 0 nbN=%lf\n",nbN );
				for ( i = 1; i < nombreNeurones; ++i) // i%(int)nbN va superposer les pixels
				{
					
					valImod=(i-1)%((int)saveMaladiesNeuronesPoids[numeroMaladie][0][0]-1);
					for ( j = 0; j < nombreDentrees; ++j)
					{

						poidsNeurones[i-1][j]=saveMaladiesNeuronesPoids[numeroMaladie][1+valImod][j];
					}
				}
					

			}

			else
			{
				// initialisation des poids aléatoirement

				for ( i = 0; i < nombreNeurones; ++i)
				{
					for ( j = 0; j < nombreDentrees; ++j)
					{
						poidsNeurones[i][j]=((float)rand()/(float)(RAND_MAX)) *REPART_NEURONES;

						//printf("poidsNeurones[i][j]%lf\n",poidsNeurones[i][j] );
					}
				}
				choix=2; // car après avoir changé la maladie faut forcément changer les entrées
			}
			

		}
	}


	

		
		if (choix==2)
		{
				
		////////////////////////////////DEFINITION DES ENTREES
		



		printf("Maladie actuellement traitée : %s \n",nomMaladie);
		printf("FIEVRE : Température en °C Valeur min=36°C, Valeur max=41°C\n");
		retour=scanf("%f",&val);
		valEntrees[0]= REPART_NEURONES*(val-36.0)/(41.0-36);
		printf("VOMISSEMENTS : Valeur min : 0-1 = Aucune envie, valeur max : 9-10 = J'ai des vomissements à fortes répétitions, avec 3 = Nausées/Légères envies de vomir\n");
		retour=scanf("%f",&val);
		valEntrees[1]= REPART_NEURONES*val/10.0;
		printf("SUEURS : Valeur min : 0-1 = Pas de sueurs,frissons... Valeur max : 9-10 = Fortes sueurs, frissons important et fréquents\n");
		retour=scanf("%f",&val);
		valEntrees[2]= REPART_NEURONES*val/10.0;
		printf("TOUX : Valeur min : 0-1 = Forte toux Sèche, 5=pas de toux, Valeur max : 9-10 = Forte toux Grasse\n");
		retour=scanf("%f",&val);
		valEntrees[3]= REPART_NEURONES*val/10.0;

			// Si on veut généraliser
		/*
			for ( i = 0; i < nombreDentrees; ++i)
			{
				printf("choisir la valeur des entrées");
				retour=scanf("%f",&valEntrees[i]);
				CLEAR_STDIN;
			}
		*/
		}

		
		if (choix!=5 && choix!=4 && choix!=6 && choix!=7 && numeroMaladie!=5)
		{
		



		///////////////////////////////////CHANGEMENT DES POIDS//////////////////////////


	///////////////////////////////////// CALCUL DES SORTIES -> CLASSEMENT DES NEURONES ////////////////

		nbNeuronesModifie=calculDistanceEuclidienne(nombreNeurones,nombreDentrees,valEntrees,resultParNeurone, poidsNeurones);
		printf("nbNeuronesModifie ^^= %d\n",nbNeuronesModifie );


		classeResultDansGeneral(nombreNeurones,resultParNeurone,classementGeneral);



	////////////////////////////// AFFICHAGE GRAPHIQUE////////////////////////////////////////




	    Uint32 rmask, gmask, bmask, amask;
	 	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
		#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
		#endif



		imageDeFond=SDL_CreateRGBSurface(0,REPART_NEURONES*COEFF_MULT_AFFICH,REPART_NEURONES*COEFF_MULT_AFFICH,32,rmask,gmask,bmask,amask);
		SDL_SaveBMP(imageDeFond,"posi.bmp");

	
		
		x=(int)(valEntrees[PARAM_EN_X]*COEFF_MULT_AFFICH);
	  	y=(int)(valEntrees[PARAM_EN_Y]*COEFF_MULT_AFFICH);
	  	if(x>=imageDeFond->h-1)
	  	{
	  		x=imageDeFond->h-2;
	  	} 
	  	if(y>=imageDeFond->w-1)
	  	{
	  		y=imageDeFond->w-2;
	  	} 
	  	
	  	if(x<1)
	  	{
	  		x=1;
	  	} 
	  	if(y<1)
	  	{
	  		y=1;
	  	} 
	  	

	  	for ( i = -1; i < 2; ++i)
	  	{
	  		for (j = -1; j < 2; ++j)
	  		{
				definirPixel(imageDeFond,x+i, y+j, 255,255,255);
			}
		}


/*

		printf("Entrer 3 pour afficher seulement les neurones les plus proches \n");
		retour=scanf("%d",&select);
*/ select=1;
		if(select==3)
		{

			for (i = 0; i < nbNeuronesModifie; ++i)
			{
				

				x=(int)(poidsNeurones[classementGeneral[i]][PARAM_EN_X] *COEFF_MULT_AFFICH);
			  	y=(int)(poidsNeurones[classementGeneral[i]][PARAM_EN_Y] *COEFF_MULT_AFFICH);
			 	if(x>=imageDeFond->h-2)
			  	{
			  		x=imageDeFond->h-2;
			  	} 
			  	if(y>=imageDeFond->w-2)
			  	{
			  		y=imageDeFond->w-2;
			  	} 
			  	
			  	if(x<1)
			  	{
			  		x=1;
			  	} 
			  	if(y<1)
			  	{
			  		y=1;
			  	} 
			  	

			  	for ( j = -1; j < 2; ++j)
			  	{
			  		for (k = -1; k < 2; ++k)
			  		{
						definirPixel(imageDeFond,x+j, y+k, rMaladie,gMaladie,bMaladie);
					}
				}

			}
		}
		else
		{
			select=3; // faut refaire le classement ...
			for (i = 0; i < nombreNeurones; ++i)
			{
				x=(int)(poidsNeurones[i][PARAM_EN_X]*COEFF_MULT_AFFICH);
			  	y=(int)(poidsNeurones[i][PARAM_EN_Y]*COEFF_MULT_AFFICH);
			 	if(x>=imageDeFond->h-2)
			  	{
			  		x=imageDeFond->h-2;
			  	} 
			  	if(y>=imageDeFond->w-2)
			  	{
			  		y=imageDeFond->w-2;
			  	} 
			  	
			  	if(x<1)
			  	{
			  		x=1;
			  	} 
			  	if(y<1)
			  	{
			  		y=1;
			  	} 
			  	

			  	for ( j = -1; j < 2; ++j)
			  	{
			  		for (k = -1; k < 2; ++k)
			  		{
						definirPixel(imageDeFond,x+j, y+k, rMaladie,gMaladie,bMaladie);
					}
				}

			}
		}


		SDL_SaveBMP(imageDeFond,"posi2.bmp");



		if (flagChangeMaladie!=0)
		{
			

		
			if(temps<tempsMax)
			{
				constApprentissage=VITESSE_APPRENTISSAGE*(1-(temps/tempsMax));
				temps++;
			}

			amelioreGagnantEtVoisin(poidsNeurones, nombreNeurones, nombreDentrees, valEntrees ,classementGeneral[0], constApprentissage);

		}
		else
		{
			flagChangeMaladie=1;


		}




	  



		  /* Chargement d'une image Bitmap dans une surface */


	    /* On blitte par-dessus l'écran */



		ecran = SDL_SetVideoMode(imageDeFond->h,imageDeFond->w, 24, SDL_HWSURFACE);

		    
		SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

		SDL_Flip(ecran);

	  	}



	  	if (choix == 4)
	  	{
	  		varLoad=loadDepuisFichier(&saveMaladiesNeuronesPoids);
			if (varLoad!=-1)
			{
				nombreDentrees=varLoad;
			}	  		
	  	}





	  	if (choix==5 || choix==7) //si choix = 7 on veut l'ensemble des maladies et on projete l'entrée dessus pour voir ou il tombe
	  	{
 	


	    Uint32 rmask, gmask, bmask, amask;
	 	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
		#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
		#endif



		imageDeFond=SDL_CreateRGBSurface(0,REPART_NEURONES*COEFF_MULT_AFFICH,REPART_NEURONES*COEFF_MULT_AFFICH,32,rmask,gmask,bmask,amask);
		SDL_SaveBMP(imageDeFond,"posi.bmp");



		for (m = 0; m < NB_MALADIES; ++m)
		{
			if(saveMaladiesNeuronesPoids[m][0][0]!=0)
			{

					switch(m+1) // du binaire avec les 255, on peut faire jusqu'à 8 couleurs, noir inclus
				{
					case 1:
					rMaladie=255;
					gMaladie=0;
					bMaladie=0;
					break;

					case 2:
					rMaladie=0;
					gMaladie=255;
					bMaladie=0;
					break;

					case 3:
					rMaladie=255;
					gMaladie=255;
					bMaladie=0;
					break;

					case 4:
					rMaladie=0;
					gMaladie=0;
					bMaladie=255;
					break;

					case 5:
					rMaladie=255;
					gMaladie=0;
					bMaladie=255;
					break;

				}
				


				nbN=saveMaladiesNeuronesPoids[m][0][0];

			  	for (i = 1; i < (int) nbN ; ++i)
				{
					x=(int)(saveMaladiesNeuronesPoids[m][i][PARAM_EN_X]*COEFF_MULT_AFFICH);
				  	y=(int)(saveMaladiesNeuronesPoids[m][i][PARAM_EN_Y]*COEFF_MULT_AFFICH);
				 	if(x>=imageDeFond->h-2)
				  	{
				  		x=imageDeFond->h-2;
				  	} 
				  	if(y>=imageDeFond->w-2)
				  	{
				  		y=imageDeFond->w-2;
				  	} 
				  	
				  	if(x<1)
				  	{
				  		x=1;
				  	} 
				  	if(y<1)
				  	{
				  		y=1;
				  	} 
				  	

				  	for ( j = -1; j < 2; ++j)
				  	{
				  		for (k = -1; k < 2; ++k)
				  		{
				  			
				  	//		printf("x=%d\n", x);
				  	//		printf("y=%d\n", y);

							definirPixel(imageDeFond,x+j, y+k, rMaladie,gMaladie,bMaladie);
						}
					}

				}
			}
		}


		printf("Le rouge correspond à la Grippe\n");
		printf("Le vert correspond à la Rhume\n");
		printf("Le jaune correspond à la Gastro\n");
		printf("Le bleu correspond à la Hypoglycémie\n");
		printf("Le rose correspond à la une Bonne Santée\n");



		if (choix ==5)
		{



		
		SDL_SaveBMP(imageDeFond,"posi2.bmp");



		ecran = SDL_SetVideoMode(imageDeFond->h,imageDeFond->w, 24, SDL_HWSURFACE);

		    
		SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

		SDL_Flip(ecran);

	  	}

	}

		if (choix == 6)
	  	{
	  		
		sauvegardeDansTab(nbNeuronesModifie,nombreDentrees,numeroMaladie,classementGeneral,poidsNeurones,saveMaladiesNeuronesPoids);

		sauvegardeDansFichier(nombreDentrees,saveMaladiesNeuronesPoids);
		
	  	}



	  	if (choix == 7)
	  	{


	  			printf("FIEVRE : Température en °C Valeur min=36°C, Valeur max=41°C\n");
				retour=scanf("%f",&val);
				CLEAR_STDIN;
				if (val>=36 && val<=41)
				{
					valEntrees[0]= (float)REPART_NEURONES*(val-36.0)/(41.0-36.0);
				}
				else
				{
					printf("ERREUR ligne 738\n");
					valEntrees[0]=0;
				}
				printf("Valeur=%lf\n",valEntrees[0] );
				printf("VOMISSEMENTS : Valeur min : 0-1 = Aucune envie, valeur max : 9-10 = J'ai des vomissements à fortes répétitions, avec 3 = Nausées/Légères envies de vomir\n");
				retour=scanf("%f",&val);
				CLEAR_STDIN;
				valEntrees[1]= (float)REPART_NEURONES*val/10.0;
				printf("Valeur=%lf\n",valEntrees[1] );
				printf("SUEURS : Valeur min : 0-1 = Pas de sueurs,frissons... Valeur max : 9-10 = Fortes sueurs, frissons important et fréquents\n");
				retour=scanf("%f",&val);
				CLEAR_STDIN;
				printf("Valeur=%lf\n",valEntrees[1] );
				valEntrees[2]= (float)REPART_NEURONES*val/10.0;
				printf("TOUX : Valeur min : 0-1 = Forte toux Sèche, 5=pas de toux, Valeur max : 9-10 = Forte toux Grasse\n");
				retour=scanf("%f",&val);
				CLEAR_STDIN;
				valEntrees[3]= (float)REPART_NEURONES*val/10.0;
				printf("Valeur=%lf\n",valEntrees[1] );
		  		
		  		/*for ( i = 0; i < nombreDentrees; ++i)
				{
					printf("choisir la valeur des entrées");
					retour=scanf("%f",&valEntrees[i]);
					CLEAR_STDIN;
				}*/


				printf("x=%f,y=%f\n",valEntrees[PARAM_EN_X],valEntrees[PARAM_EN_Y] );
				x=(int)((int)(valEntrees[PARAM_EN_X])*COEFF_MULT_AFFICH);
				y=(int)((int)(valEntrees[PARAM_EN_Y])*COEFF_MULT_AFFICH);

				if (x<=2)
				{
					x=2;
				}
				if (y<=2)
				{
					y=2;
				}
				if (x>imageDeFond->w-2)
				{
					x=imageDeFond->w-3;
				}
				if (y>imageDeFond->h-2)
				{
					y=imageDeFond->h-3;
				}
	
	  		  	printf("x=%d,y=%d\n",x,y );

	  		  	for ( j = -2; j < 3; ++j)
			  	{
			  		for (k = -2; k < 3; ++k)
			  		{
			  		printf("x=%d,y=%d\n",x,y );

			  			
			  			definirPixel(imageDeFond,x+j, y+k, 255,255,255);
					}
				}


				SDL_SaveBMP(imageDeFond,"posi2.bmp");
				ecran = SDL_SetVideoMode(imageDeFond->h,imageDeFond->w, 24, SDL_HWSURFACE);

				    
				SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

				SDL_Flip(ecran);
	  	}



		do
		{
		printf("Maladie actuellement traitée : %s \n",nomMaladie);
		printf("0 : sortir du programme\n");
		printf("1 : passer à une autre maladie\n");
		printf("2 : passer à une autre entrée\n");
		printf("3 : refaire une itération avec les mêmes entrées\n");
		printf("4 : charger les données depuis le fichier\n");
		printf("5 : afficher la carte préremplie\n");
		printf("6 : sauvegarder dans le fichier\n");
		printf("7 : recherche d'une maladie (utilisation de la carte)\n");

		retour=scanf("%d",&choix);

		CLEAR_STDIN;
		}while(choix!=0 && choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5 && choix!=6 && choix!=7);
		
		

	}


		sauvegardeDansTab(nbNeuronesModifie,nombreDentrees,numeroMaladie,classementGeneral,poidsNeurones,saveMaladiesNeuronesPoids);

		sauvegardeDansFichier(nombreDentrees,saveMaladiesNeuronesPoids);
		

	    SDL_FreeSurface(imageDeFond); /* On libère la surface */


	    SDL_Quit();


	    return EXIT_SUCCESS;

}


