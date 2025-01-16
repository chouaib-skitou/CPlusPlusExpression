#include <iostream>
#include <utility>

/*
Le SystÃ¨me international d'unitÃ©s (abrÃ©gÃ© en SI), inspirÃ© du 
systÃ¨me mÃ©trique, est le systÃ¨me d'unitÃ©s le plus largement 
employÃ© au monde.

Le SystÃ¨me international comporte sept unitÃ©s de base, 
destinÃ©es Ã  mesurer des grandeurs physiques indÃ©pendantes
 et possÃ©dant chacune un symbole :

  + La masse, mesurÃ©e en kilogramme (kg).
  + Le temps, mesurÃ© en second (s).
  + La longueur, mesurÃ© en mÃ¨tre (m).
  + La tempÃ©rature, mesurÃ©e en kelvin (K).
  + L'intensitÃ© Ã©lectrique, mesurÃ©e en ampÃ¨re (A).
  + La quantitÃ© de matiÃ¨re, mesurÃ©e en mole   (mol).
  + L'intensitÃ© lumineuse, mesurÃ©e en candela  (cd). 

A partir de ces unitÃ©s de bases, il est possible de construire 
des unitÃ©s dÃ©rivÃ©es. Par exemple : 

  + La frequence, exprimÃ©e en s^-1
  + La vitesse, exprimÃ©e en m.s^-1
  + L'energie, exprimÃ©e en kg.m^2.s^âˆ’2 

On remarque que ses unitÃ©s dÃ©rivÃ©es sont toutes des produits de 
puissance d'unitÃ© de base.

On se propose d'implÃ©menter un systeme permettant de calculer des
grandeurs avec des unitÃ©s en utilisant le type des objets unitÃ©s
pour empecher des erreurs comme kg + m.
*/

/*
  ETAPE 1 - STRUCTURE UNIT

  Ecrivez une structure unit qui prend en parametre template un type T
  et 7 entiers, chacune reprÃ©sentant une unitÃ© de base. Vous les
  ordonnerez de faÃ§on Ã  suivre l'ordre de la liste donnÃ©e plus haut.

  Cette structure contient une valeur de type T.
*/

/*
  ETAPE 2 - UNITES ET UNITES DERIVEES
  En utilisant le modele ci dessous, dÃ©finissez des types
  representant les grandeurs demandÃ©es.

  Indice : https://fr.wikipedia.org/wiki/Syst%C3%A8me_international_d%27unit%C3%A9s#Unit%C3%A9s_d%C3%A9riv%C3%A9es
*/

// Masse : kg
template<typename T>
using mass = unit<T,1,0,0,0,0,0,0>;

// Longeur : m
template<typename T>
using length = unit<T,0,0,1,0,0,0,0>;

// Vitesse m.s-1
template<typename T>
using speed = ;

// Force exprimÃ©e en Newton
template<typename T>
using newton = ;

// conductance Ã©lectrique
template<typename T>
using siemens = ;

/*
  ETAPE 3 - OPERATIONS

  Ecrivez les operateurs +,-,* et / entre deux unitÃ©s 
  du mÃªme type mais avec des unitÃ©s cohÃ©rentes.

  On peut multipliez ou divisÃ© du temps par une masse mais
  on ne peut pas ajouter des Kelvin Ã  des metres.
*/


/*
  ETAPE 4 - SIMPLIFICATION
  A partir de C++20, n'importequelle structure constexpr peut servir
  de parametres template.

  DÃ©finissez une structure spec contenant un tableau de 7 entiers et les opÃ©rations et
  constrcuteurs que vous jugerez nÃ©cessaire et implÃ©mentez dans un deuxieme fichier la
  totalitÃ© des opÃ©rations et types prÃ©cÃ©dent en partant du principe que unit devient

  template<typename T, spec D> struct unit;
*/

int main()
{
  // POUR CHAQUE ETAPE, ECRIVEZ LES TESTS QUE VOUS JUGEREZ SUFFISANT
}