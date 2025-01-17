#include <iostream>
#include <utility>
#include <cassert>
#include <concepts>

/*
Le SystÃ¨me international d'unitÃ©s (abrÃ©gÃ© en SI), inspirÃ© du 
systÃ¨me mÃ©trique, est le systÃ¨me d'unitÃ©s le plus largement 
employÃ© au monde.

Le SystÃ¨me international comporte sept unitÃ©s de base, 
destinÃ©es Ã  mesurer des grandeurs physiques indÃ©pendantes
 et possÃ©dant chacune un symbole :

  + La masse, mesurÃ©e en kilogramme (kg).
  + Le temps, mesurÃ© en second (s).
  + La longueur, mesurÃ©e en mÃ¨tre (m).
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

// ETAPE 1: Ajout de la structure unit (T, kg, s, m, K, A, mol, cd)
template<typename T, int KG, int S, int M, int KELVIN, int A, int MOL, int CD>
struct unit
{
  T value;
};

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
using speed = unit<T,0,-1,1,0,0,0,0>;

// Force exprimÃ©e en Newton => kg.m.s^-2
template<typename T>
using newton = unit<T,1,-2,1,0,0,0,0>;

// conductance Ã©lectrique => siemens
// kg^-1.m^-2.s^3.A^2
template<typename T>
using siemens = unit<T,-1,3,-2,0,2,0,0>;

/*
  ETAPE 3 - OPERATIONS

  Ecrivez les operateurs +,-,* et / entre deux unitÃ©s 
  du mÃªme type mais avec des unitÃ©s cohÃ©rentes.

  On peut multipliez ou divisÃ© du temps par une masse mais
  on ne peut pas ajouter des Kelvin Ã  des metres.
*/

// Addition (+)
template<typename T,
         int kg1, int s1, int m1, int K1, int A1, int mol1, int cd1,
         int kg2, int s2, int m2, int K2, int A2, int mol2, int cd2>
auto operator+(unit<T, kg1, s1, m1, K1, A1, mol1, cd1> lhs,
               unit<T, kg2, s2, m2, K2, A2, mol2, cd2> rhs)
{
  static_assert(kg1 == kg2 && s1 == s2 && m1 == m2 && K1 == K2 && A1 == A2 && mol1 == mol2 && cd1 == cd2,
                "Dimensions must match for addition");
  return unit<T, kg1, s1, m1, K1, A1, mol1, cd1>{ lhs.value + rhs.value };
}

// Subtraction (-)
template<typename T,
         int kg1, int s1, int m1, int K1, int A1, int mol1, int cd1,
         int kg2, int s2, int m2, int K2, int A2, int mol2, int cd2>
auto operator-(unit<T, kg1, s1, m1, K1, A1, mol1, cd1> lhs,
               unit<T, kg2, s2, m2, K2, A2, mol2, cd2> rhs)
{
  static_assert(kg1 == kg2 && s1 == s2 && m1 == m2 && K1 == K2 && A1 == A2 && mol1 == mol2 && cd1 == cd2,
                "Dimensions must match for subtraction");
  return unit<T, kg1, s1, m1, K1, A1, mol1, cd1>{ lhs.value - rhs.value };
}

// Multiplication (*)
template<typename T,
         int kg1, int s1, int m1, int K1, int A1, int mol1, int cd1,
         int kg2, int s2, int m2, int K2, int A2, int mol2, int cd2>
auto operator*(unit<T, kg1, s1, m1, K1, A1, mol1, cd1> lhs,
               unit<T, kg2, s2, m2, K2, A2, mol2, cd2> rhs)
{
  return unit<T,
              kg1 + kg2,
              s1 + s2,
              m1 + m2,
              K1 + K2,
              A1 + A2,
              mol1 + mol2,
              cd1 + cd2>{ lhs.value * rhs.value };
}

// Division (/)
template<typename T,
         int kg1, int s1, int m1, int K1, int A1, int mol1, int cd1,
         int kg2, int s2, int m2, int K2, int A2, int mol2, int cd2>
auto operator/(unit<T, kg1, s1, m1, K1, A1, mol1, cd1> lhs,
               unit<T, kg2, s2, m2, K2, A2, mol2, cd2> rhs)
{
  return unit<T,
              kg1 - kg2,
              s1 - s2,
              m1 - m2,
              K1 - K2,
              A1 - A2,
              mol1 - mol2,
              cd1 - cd2>{ lhs.value / rhs.value };
}


int main()
{
  // POUR CHAQUE ETAPE, ECRIVEZ LES TESTS QUE VOUS JUGEREZ SUFFISANT

  // Quick test with mass
  mass<double> m1{ 5.0 }, m2{ 3.0 };
  auto m3 = m1 + m2; // OK: same dimension
  std::cout << "m3.value = " << m3.value << " (kg)\n";

  // Quick test with speed
  speed<double> v1{10.0}, v2{2.0};
  auto v3 = v1 + v2;
  std::cout << "v3.value = " << v3.value << " (m.s^-1)\n";

  // Quick test with newton
  newton<double> f1{100.0}, f2{50.0};
  auto f3 = f1 + f2;
  std::cout << "f3.value = " << f3.value << " (Newtons)\n";

  // Quick test with siemens
  siemens<double> c1{ 0.5 }, c2{ 0.2 };
  auto c3 = c1 + c2;
  std::cout << "c3.value = " << c3.value << " (Siemens)\n";

  // Speed * mass => dimension(kg=1, s=-1, m=1)
  auto mass_times_speed = m1 * v1;
  std::cout << "m1 * v1 => " << mass_times_speed.value << " => dimension(kg=1, s=-1, m=1)\n";

  // ------------------------------------------------------------------
  //                Additional tests
  // ------------------------------------------------------------------
  {
    // Testing subtraction of speed
    auto v4 = v1 - v2;
    std::cout << "v4.value = " << v4.value << " (m.s^-1, after subtracting speeds)\n";

    // Testing multiplication of newton by length => newton * meter => (kg=1, s=-2, m=1) * (kg=0, s=0, m=1)
    // => exponents: (1+0, -2+0, 1+1) => (kg=1, s=-2, m=2)
    // => This is basically an energy dimension (Joule = N·m).
    auto energy = f1 * length<double>{ 2.0 };
    std::cout << "energy.value = " << energy.value << " => dimension(kg=1, s=-2, m=2)\n";

    // Testing division: speed / length => dimension => (kg=0, s=-1, m=1) / (kg=0, s=0, m=1)
    // => exponents: (0-0, -1-0, 1-1) => (0, -1, 0)
    // => This is 1/s dimension (i.e. frequency).
    auto freq = v1 / length<double>{ 2.0 };
    std::cout << "freq.value = " << freq.value << " => dimension(kg=0, s=-1, m=0)\n";

    // Quick asserts for validation
    assert(m3.value == 8.0);
    assert(v3.value == 12.0);
    assert(f3.value == 150.0);
    assert(c3.value == 0.7);
    assert((m1 * v1).value == 50.0);
    assert(v4.value == 8.0);        // 10 - 2
    assert(energy.value == 200.0);  // 100 * 2
    assert(freq.value == 5.0);      // 10 / 2
  }

  // Uncommenting the following line should fail at compile time (dimension mismatch):
  // auto invalid = m1 + v1; // dimension mismatch => mass + speed

  std::cout << "\033[1;32mAll additional tests passed!\033[0m\n";

  return 0;
}
