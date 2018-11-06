#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fonctions.h"

void affiche_affectations(liste_filieres* L_f){
	filiere* f=L_f->tete;
	int i,j;
	printf("\n\n\nAffichage des affectations finales :\n");
	for(i=0;i<L_f->nb_filieres;i++){
		printf("	-%s : \n",f->nom);
		etudiant* e=f->L_etudiants->tete;
		if(e!=NULL){
			for(j=0;j<f->nb_places_dispo;j++){
				if(e==NULL) return;	
				printf("		-%s\n",e->nom);
				e=e->suivant;
			}
		}
		else printf("		-(vide)\n");
		f=f->suivant;
	}
}

liste_filieres* init_liste_filieres(){
	liste_filieres* L_f=malloc(sizeof(liste_filieres));
	L_f->nb_filieres=0;
	L_f->tete=NULL;
	return L_f;
}

liste_etudiants* init_liste_etudiants(){
	liste_etudiants* L_e=malloc(sizeof(liste_etudiants));
	L_e->nb_etudiants=0;
	L_e->tete=NULL;
	return L_e;
}

filiere* init_filiere(){
	filiere* f=(filiere*)malloc(sizeof(filiere));
	printf("\nSaisir le nom de la filière : ");
	scanf("%255s",f->nom);
	printf("\nSaisir le nombre de place(s) disponible(s) : ");
	scanf("%d",&f->nb_places_dispo);
	f->L_etudiants=(liste_etudiants*)malloc(sizeof(liste_etudiants));
	f->suivant=NULL;
	return f;
}

void inserer_filiere(liste_filieres* L_f, filiere* f){
	f->identifiant=L_f->nb_filieres;
	L_f->nb_filieres++;
	if(L_f->tete==NULL) {
		L_f->tete=f;
		return;
	}
	filiere* index = L_f->tete;
	while(index->suivant != NULL){
		index = index->suivant;
	}
	index->suivant=f;
}

void affiche_filieres(liste_filieres* L_f){
	filiere* f=L_f->tete;
	printf("Liste des filières :\n");
	while(f->suivant!=NULL){
		printf("	*%s -> id(%d)\n",f->nom, f->identifiant);
		f=f->suivant;
	}
	printf("	*%s -> id(%d)\n",f->nom, f->identifiant);
}

etudiant* copie_etudiant(etudiant* e_p, liste_filieres* L_f){
	etudiant* e=(etudiant*)malloc(sizeof(etudiant));
	int nb_f=L_f->nb_filieres;
	strcpy(e->nom,e_p->nom);
	e->tab_voeux=(int*)malloc(sizeof(int)*nb_f);
	e->tab_classement=(int*)malloc(sizeof(int)*nb_f);
	e->tab_visites=(int*)malloc(sizeof(int)*nb_f);
	e->affecte=e_p->affecte;
	e->suivant=NULL;
	int i;
	for (i=0;i<nb_f;i++){
		e->tab_voeux[i]=e_p->tab_voeux[i];
	}
	for (i=0;i<nb_f;i++){
		e->tab_classement[i]=e_p->tab_classement[i];
	}
	for (i=0;i<nb_f;i++){
		e->tab_visites[i]=e_p->tab_visites[i];
	}
	return e;
}

etudiant* init_etudiant(liste_filieres* L_f){
	etudiant* e=(etudiant*)malloc(sizeof(etudiant));
	int nb_f=L_f->nb_filieres;
	printf("\nSaisir le nom de l'étudiant(e) : ");
	scanf("%255s",e->nom);
	e->tab_voeux=(int*)malloc(sizeof(int)*nb_f);
	e->tab_classement=(int*)malloc(sizeof(int)*nb_f);
	e->tab_visites=(int*)malloc(sizeof(int)*nb_f);
	e->affecte=0;
	e->suivant=NULL;
	int i;
	for (i=0;i<nb_f;i++){
		int v;
		affiche_filieres(L_f);
		printf("Saisir l'identifiant du voeu %d pour l'etudiant(e) %s : ",i+1,e->nom);
		scanf("%d",&v);
		e->tab_voeux[i]=v;
	}
	for (i=0;i<nb_f;i++){
		int c;
		affiche_filieres(L_f);
		printf("Saisir le classement de l'étudiant(e) %s dans la filière d'identifiant %d : ",e->nom,i);
		scanf("%d",&c);
		e->tab_classement[i]=c;
	}
	for (i=0;i<nb_f;i++){
		e->tab_visites[i]=0;
	}
	return e;
}

void affiche_etud(etudiant* e){
	int i;
	int taille = sizeof(e->tab_voeux)/sizeof(int);
	printf("\n	*Affichage de %s :\n",e->nom );
	printf("		*Affecté(e) : %s \n",e->affecte?"oui":"non" );
	for(i=0;i<=taille;i++){
		printf("		*Voeu %d : id(%d) , classé(e) : %d\n",i+1,e->tab_voeux[i], e->tab_classement[e->tab_voeux[i]]);
	}
}

etudiant* recherche_etudiant(liste_etudiants* L_e, etudiant* e){
	int i=0;
	etudiant* index=L_e->tete;
	for (i = 0; i < L_e->nb_etudiants; ++i)
	{
		if(strcmp(index->nom,e->nom)==0){
			return index;
		}
		index=index->suivant;
	}
	return NULL;
}

void affectation_candidats_concours(liste_etudiants* Liste_etudiants, liste_filieres* Liste_filieres){
	etudiant* un_etudiant = recherche_etudiant_non_affecte(Liste_etudiants);
	while ( un_etudiant != NULL ){
		//On utilise des copies d'étudiants afin de ne pas mélanger les étudiants stockés dans
		//une filière et les étudiants stockés dans la liste d'étudiants originale 'Liste_etudiants'
		etudiant* e_cp=copie_etudiant(un_etudiant, Liste_filieres);
		filiere* une_filiere = recherche_filiere_non_visitee(e_cp,Liste_filieres);
		un_etudiant->tab_visites[une_filiere->identifiant]=1;
		e_cp->tab_visites[une_filiere->identifiant]=1;
		printf("\n		--L'étudiant(e) %s se présente à %s\n",e_cp->nom,une_filiere->nom );
		if (place_disponible_filiere(une_filiere)){
        	un_etudiant->affecte = 1;
        	e_cp->affecte = 1;
        	printf("\n		--L'étudiant(e) %s est accepté(e) à %s\n",e_cp->nom,une_filiere->nom );
        	inserer(une_filiere->L_etudiants,e_cp);
        	}
    	else{ 
			etudiant* tmp_etudiant = meuilleur_resultats(e_cp,une_filiere);
			if (tmp_etudiant != NULL){
				printf("\n		--L'étudiant(e) %s a de meuilleur résultats que %s, %s devient sans filière\n",e_cp->nom,tmp_etudiant->nom,tmp_etudiant->nom );
				printf("\n		--L'étudiant(e) %s est accepté(e) à %s\n",e_cp->nom,une_filiere->nom );
				
				etudiant* trouve_e=recherche_etudiant(Liste_etudiants,tmp_etudiant);
				
				trouve_e->affecte = 0;
				tmp_etudiant->affecte = 0;
				
				un_etudiant->affecte = 1;
				e_cp->affecte = 1;
				
				inserer(une_filiere->L_etudiants,e_cp);
        		supprimer(une_filiere,tmp_etudiant);
        	}
        	else printf("\n		--L'étudiant(e) %s est refusé(e), il(elle) passe à son prochain voeu\n",e_cp->nom);
        }
        un_etudiant = recherche_etudiant_non_affecte(Liste_etudiants);
	}
	affiche_affectations(Liste_filieres);
}

void inserer(liste_etudiants* L, etudiant* e){
	L->nb_etudiants++;
	if(L->tete==NULL) {
		L->tete=e;
		L->tete->suivant=NULL;
		return;
	}
	e->suivant=L->tete;
	L->tete=e;
}

void supprimer(filiere* f, etudiant* e){
	f->L_etudiants->nb_etudiants--;
	etudiant* index = f->L_etudiants->tete;
	etudiant* pred=f->L_etudiants->tete;
	etudiant* supp=NULL;
	if(strcmp(f->L_etudiants->tete->nom, e->nom)==0){
		if (f->L_etudiants->tete->suivant==NULL) {
		 	f->L_etudiants->tete=NULL;
			return;
		}
		else {
			f->L_etudiants->tete=f->L_etudiants->tete->suivant;
			return;
		}
	}
	int i=0;
	while(i<f->nb_places_dispo){
		if(index==e){
			supp=index;
			pred->suivant=supp->suivant;
			supp->suivant=NULL;
			supp=NULL;
			e->suivant=NULL;
			e=NULL;
		}
		pred = index;
		index = index->suivant;
		i++;
	}
}



filiere* recherche_filiere_id(liste_filieres* L_f ,int id){
	filiere* f = L_f->tete;
	while (f != NULL){
		if ( f->identifiant == id)
			return f;
		else
			f = f->suivant;
	}
	return NULL;
}



etudiant* recherche_etudiant_non_affecte(liste_etudiants* L_e){
	etudiant* e = L_e->tete;
	int i=0;
	while(i<L_e->nb_etudiants){
		if (e->affecte){
			e = e->suivant;}
		else{
			printf("\n	-L'étudiant(e) %s est libre\n",e->nom);
			return e;
		}
		i++;
	}
	return NULL;
}




filiere* recherche_filiere_non_visitee(etudiant* e, liste_filieres* L_f){
	int i = 0;
	int voeu = e->tab_voeux[i];
	while (e->tab_visites[voeu]){
		i = i + 1;
		voeu = e->tab_voeux[i];
	}
	return recherche_filiere_id( L_f , voeu);
}



int place_disponible_filiere(filiere* f){
	return ( f->nb_places_dispo >  f->L_etudiants->nb_etudiants  ) ;
}



etudiant* meuilleur_resultats(etudiant* e, filiere* f){
	int id = f->identifiant,i=0;
	etudiant* index = f->L_etudiants->tete;
	etudiant* e_dernier = f->L_etudiants->tete;
	while (i<f->nb_places_dispo) {
		if (index->tab_classement[id] > e_dernier->tab_classement[id]) 
			e_dernier = index;
		index = index->suivant;
		i++;
		}
	if (e_dernier->tab_classement[id] >  e->tab_classement[id]) 
		return e_dernier;
	return NULL;
}


/**************************************************
void detruire_liste_etudiants(liste_etudiants* L_e){
	etudiant* e=L_e->tete;
	if(e!=NULL){
		while(e->suivant!=NULL){
			e=e->suivant;
		}
		free(e->tab_voeux);
		free(e->tab_classement);
		free(e->tab_visites);
		free(e);
		e=NULL;
		detruire_liste_etudiants(L_e);
	}
	else{
		free(L_e);
	}
}

void detruire_liste_filieres(liste_filieres* L_f){
	filiere* f=L_f->tete;
	if(f!=NULL){
		while(f->suivant!=NULL){
			f=f->suivant;
		}
		detruire_liste_etudiants(f->L_etudiants);
		free(f);
		f=NULL;
		detruire_liste_filieres(L_f);
	}
	else{
		free(L_f);
	}
}
********************************************************/
