#include <dirent.h> 

#define REPART_NEURONES 10
#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#define SIGMA 15 //2
#define VITESSE_APPRENTISSAGE 0.8 //0.8
#define NOM_FICHIER "sauvegardePoids.bin"
#define NB_MALADIES 5
#define PARAM_EN_X 0
#define PARAM_EN_Y 1


#define MULT_DIST_MIN 10+30 //1.5+2 // dans calculDistanceEuclidienne, on renvoi le nombre de neurones modifies
//ce chiffre permet de multiplier la premiere valeure renvoyée (et d'ajouter 2 (si jamais distmin= 0))
//  nbNeuronesModifie est utilisé pour savoir le nombre de neurones sauvegardés dans le tab


#define COEFF_MULT_AFFICH 99
//1 neurone





void definirPixel(SDL_Surface *surface, int x, int y, int red, int green, int blue);
float fonctionHj(float distanceEuclidienne);
void amelioreGagnantEtVoisin(float** poidsNeurones, int nombreNeurones, int nombreDentrees, float* valEntrees ,int neuroneGagnant, float apprentissage);
int calculDistanceEuclidienne(int nombreNeurones, int nombreDentrees,float *valEntrees,float *resultParNeurone, float **poidsNeurones);
void classeResultDansGeneral(int nombreNeurones,float *resultParNeurone,int *classementGeneral);
void sauvegardeDansTab(int nbNeuronesModifie, int nombreDentrees,int numeroMaladie,int *classementGeneral,float **poidsNeurones,float ***saveMaladiesNeuronesPoids);
void sauvegardeDansFichier(int nombreDentrees,float ***saveMaladiesNeuronesPoids);
int loadDepuisFichier(float ****saveMaladiesNeuronesPoids);



void* retunSave();
