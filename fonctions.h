#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__

typedef struct etudiant{
	char nom[256];
	int* tab_voeux; 
	int* tab_classement;
	int* tab_visites;
	int affecte;
	struct etudiant* suivant;
						
}etudiant;

typedef struct liste_etudiants{
	etudiant* tete;
	int nb_etudiants;
}liste_etudiants;

typedef struct filiere{
	char nom[256];
	int nb_places_dispo;
	liste_etudiants* L_etudiants;
	int identifiant;
	struct filiere* suivant;
}filiere;

typedef struct liste_filieres{
	filiere* tete;
	int nb_filieres;
}liste_filieres;

etudiant* copie_etudiant(etudiant* e, liste_filieres* L_f);
etudiant* recherche_etudiant(liste_etudiants* L_e, etudiant* e);
void affectation_candidats_concours(liste_etudiants* Liste_etudiants, liste_filieres* Liste_filieres);
void inserer(liste_etudiants* L, etudiant* e);
void supprimer(filiere* f, etudiant* e);
filiere* recherche_filiere_id(liste_filieres* L_f ,int id);
etudiant* recherche_etudiant_non_affecte(liste_etudiants* L_e);
filiere* recherche_filiere_non_visitee(etudiant* e, liste_filieres* L_f);
int place_disponible_filiere(filiere* f);
etudiant* meuilleur_resultats(etudiant* e, filiere* f);
etudiant* init_etudiant(liste_filieres* L_f);
void affiche_filieres(liste_filieres* L_f);
void inserer_filiere(liste_filieres* L_f, filiere* f);
filiere* init_filiere();
liste_etudiants* init_liste_etudiants();
liste_filieres* init_liste_filieres();
void affiche_affectations(liste_filieres* L_f);
void affiche_etud(etudiant* e);
void detruire_liste_etudiants(liste_etudiants* );
void detruire_liste_filieres(liste_filieres* );

#endif