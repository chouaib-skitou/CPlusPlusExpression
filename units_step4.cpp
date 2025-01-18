#include <iostream>
#include <cassert>

/*
  ETAPE 4 - SIMPLIFICATION
  À partir de C++20, n'importe quelle structure constexpr peut servir
  de paramètre template.

  On définit donc une structure `spec` contenant un tableau de 7 entiers 
  et les opérations et constructeurs nécessaires. 

  Puis on modifie `unit` en :
     template<typename T, spec D> struct unit;
*/

//
// --------------------- Implémentation Étape 4 ---------------------
//

/**
 * @brief `spec` stocke les exposants des 7 unités de base :
 *        [ kg, s, m, K, A, mol, cd ]
 */
struct spec
{
    int dims[7] = {}; // 7 entiers

    // Constructeur par défaut : tout à zéro
    constexpr spec() = default;

    // Constructeur qui initialise explicitement les 7 exposants
    constexpr spec(int kg, int s, int m, int kelvin, int a, int mol, int cd)
      : dims{kg, s, m, kelvin, a, mol, cd} {}

    // Opérateur == pour comparer deux specs
    friend constexpr bool operator==(spec const& lhs, spec const& rhs)
    {
        for (int i = 0; i < 7; ++i)
        {
            if (lhs.dims[i] != rhs.dims[i]) return false;
        }
        return true;
    }

    // Opérateur !=
    friend constexpr bool operator!=(spec const& lhs, spec const& rhs)
    {
        return !(lhs == rhs);
    }

    // Opérateur + : addition des exposants
    friend constexpr spec operator+(spec const& lhs, spec const& rhs)
    {
        spec r;
        for(int i = 0; i < 7; ++i)
        {
            r.dims[i] = lhs.dims[i] + rhs.dims[i];
        }
        return r;
    }

    // Opérateur - : soustraction des exposants
    friend constexpr spec operator-(spec const& lhs, spec const& rhs)
    {
        spec r;
        for(int i = 0; i < 7; ++i)
        {
            r.dims[i] = lhs.dims[i] - rhs.dims[i];
        }
        return r;
    }
};

/**
 * @brief Nouvelle version de `unit` :
 *        `template<typename T, spec D> struct unit`
 *
 * @tparam T : type sous-jacent (double, float, int, ...)
 * @tparam D : un `spec` décrivant les 7 exposants
 */
template<typename T, spec D>
struct unit
{
    T value;
};

// --------------------- Opérateurs arithmétiques ---------------------

// + (dimensions identiques)
template<typename T, spec D1, spec D2>
auto operator+(unit<T, D1> lhs, unit<T, D2> rhs)
{
    static_assert(D1 == D2, 
                  "Dimensions must match for addition.");
    return unit<T, D1>{ lhs.value + rhs.value };
}

// - (dimensions identiques)
template<typename T, spec D1, spec D2>
auto operator-(unit<T, D1> lhs, unit<T, D2> rhs)
{
    static_assert(D1 == D2, 
                  "Dimensions must match for subtraction.");
    return unit<T, D1>{ lhs.value - rhs.value };
}

// * (on additionne les exposants)
template<typename T, spec D1, spec D2>
auto operator*(unit<T, D1> lhs, unit<T, D2> rhs)
{
    constexpr spec R = D1 + D2;
    return unit<T, R>{ lhs.value * rhs.value };
}

// / (on soustrait les exposants)
template<typename T, spec D1, spec D2>
auto operator/(unit<T, D1> lhs, unit<T, D2> rhs)
{
    constexpr spec R = D1 - D2;
    return unit<T, R>{ lhs.value / rhs.value };
}

// --------------------- Quelques "spec" pré-définis ---------------------
// Ordre : kg, s, m, K, A, mol, cd

constexpr spec mass_spec    ( 1,  0,  0,  0, 0, 0, 0 ); // kg
constexpr spec length_spec  ( 0,  0,  1,  0, 0, 0, 0 ); // m
constexpr spec speed_spec   ( 0, -1,  1,  0, 0, 0, 0 ); // m.s^-1
constexpr spec newton_spec  ( 1, -2,  1,  0, 0, 0, 0 ); // kg.m.s^-2
constexpr spec siemens_spec (-1, 3, -2, 0, 2, 0, 0 );   // kg^-1.m^-2.s^3.A^2

// --------------------- Alias pour simplifier l'usage ---------------------
template<typename T> using mass   = unit<T, mass_spec>;
template<typename T> using length = unit<T, length_spec>;
template<typename T> using speed  = unit<T, speed_spec>;
template<typename T> using newton = unit<T, newton_spec>;
template<typename T> using siemens= unit<T, siemens_spec>;

// ----------------------------------------------------------------------
//                           MAIN DE TEST
// ----------------------------------------------------------------------
int main()
{
    // --- Test ETAPE 4 : Tout est désormais basé sur spec + unit<T, D> ---

    // Masse
    mass<double> m1{5.0}, m2{3.0};
    auto m3 = m1 + m2;  // addition => ok, même dimension
    std::cout << "m3.value = " << m3.value << " (kg)\n";

    // Vitesse
    speed<double> v1{10.0}, v2{2.0};
    auto v3 = v1 + v2;
    std::cout << "v3.value = " << v3.value << " (m.s^-1)\n";

    // Force (Newton)
    newton<double> f1{100.0}, f2{50.0};
    auto f3 = f1 + f2;
    std::cout << "f3.value = " << f3.value << " (Newtons)\n";

    // Conductance (Siemens)
    siemens<double> c1{0.5}, c2{0.2};
    auto c3 = c1 + c2;
    std::cout << "c3.value = " << c3.value << " (Siemens)\n";

    // Multiplication : mass * speed => (kg=1, s=-1, m=1)
    auto mass_times_speed = m1 * v1;
    std::cout << "m1 * v1 => " << mass_times_speed.value
              << " => dimension(kg=1, s=-1, m=1)\n";

    // Subtraction : (speed)
    auto v4 = v1 - v2;
    std::cout << "v4.value = " << v4.value << " (m.s^-1)\n";

    // newton * length => Joule (kg.m^2.s^-2)
    auto energy = f1 * length<double>{2.0};
    std::cout << "energy.value = " << energy.value
              << " => dimension(kg=1, s=-2, m=2)\n";

    // speed / length => (m.s^-1) / m => s^-1 => fréquence
    auto freq = v1 / length<double>{2.0};
    std::cout << "freq.value = " << freq.value
              << " => dimension(kg=0, s=-1, m=0)\n";

    // Vérification "simple" via assert
    assert(m3.value == 8.0);        // 5 + 3
    assert(v3.value == 12.0);       // 10 + 2
    assert(f3.value == 150.0);      // 100 + 50
    assert(c3.value == 0.7);        // 0.5 + 0.2
    assert((m1 * v1).value == 50.0);// 5 * 10
    assert(v4.value == 8.0);        // 10 - 2
    assert(energy.value == 200.0);  // 100 * 2
    assert(freq.value == 5.0);      // 10 / 2

    // Si on décommente la ligne suivante, on aura une erreur de compilation
    // car les dimensions diffèrent (mass + speed) :
    // auto invalid = m1 + v1; // Erreur => dimensions mismatch

    std::cout << "\n\033[1;32mAll tests (Step 4) passed successfully!\033[0m\n";
    return 0;
}
