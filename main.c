#include<stdio.h>
#include<string.h>
#include "fonctions.h"

int main(){
	int nb_filieres;
	int nb_etudiants;
	liste_filieres* L_filieres=init_liste_filieres();
	liste_etudiants* L_etudiants=init_liste_etudiants();
	printf("Saisir le nombre de filières : ");
	scanf("%d",&nb_filieres);
	int i;
	filiere* f;
	etudiant* e;
	for(i=0;i<nb_filieres;i++){
		printf("\nFilière %i \n",i+1);
		f=init_filiere();
		inserer_filiere(L_filieres,f);
		f=NULL;
	}
	printf("Saisir le nombre d'étudiant(e)s : ");
	scanf("%d",&nb_etudiants);
	for(i=0;i<nb_etudiants;i++){
		printf("\nEtudiant(e) %i \n",i+1);
		e=init_etudiant(L_filieres);
		affiche_etud(e);
		printf("\n\n\n");
		inserer(L_etudiants,e);
		e=NULL;
	}
	affectation_candidats_concours(L_etudiants,L_filieres);
	//detruire_liste_etudiants(L_etudiants);
	//detruire_liste_filieres(L_filieres);
	return 0;
}