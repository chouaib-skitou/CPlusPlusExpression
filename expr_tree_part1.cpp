#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <concepts> // If needed for std::convertible_to<bool>

//--------------------------------------------------------------------------------------
/*
  Le but de ce TP est de mettre en place un petit systÃ¨me d'EXPRESSION TEMPLATES
  Les EXPRESSION TEMPLATES sont une technique d'optimisation de calcul numÃ©rique qui
  utilisent la mÃ©ta-programmation pour construire une reprÃ©sentation lÃ©gÃ©re d'une formule
  arbitraire sous la forme d'un ARBRE DE SYNTAXE ABSTRAITE.

  Une fois construit Ã  la compilation, cet arbre devient exploitable Ã  la compilation 
  ou Ã  l'exÃ©cution pour effectuer des calculs de divers types. 

  RÃ©pondez au questions dans l'ordre en complÃ©tant le code.
*/
//---------------------------------------------------------------------------------------
namespace et
{
  // Q1 - DÃ©finissez un concept expr qui est valide si un type T fournit un membre T::is_expr()
  template<typename T>
  concept expr = requires()
  {
    /* ???? */
    { T::is_expr } -> std::convertible_to<bool>;
  };

  //---------------------------------------------------------------------------------------
  /*
    Le premier Ã©lÃ©ment fondamental d'un systeme d'EXPRESSION TEMPLATE est la classe de 
    terminal. Un TERMINAL reprÃ©sente une feuille de l'ARBRE DE SYNTAXE. Dans notre cas,
    nos terminaux sont numÃ©rotÃ© statiquement pour reprÃ©sent diffÃ©rentes variables.

    Q2. ComplÃ©tez l'implÃ©mentation de la structure template terminal ci dessous en suivant les demandes
  */
  //---------------------------------------------------------------------------------------
  template<int ID>
  struct terminal 
  {
    // Faite en sorte que terminal vÃ©rifie le concept expr
    /* ???? */ 
    static constexpr bool is_expr = true;

    std::ostream& print(std::ostream& os) const
    {
      // Pour terminal<I>, affiche "arg<I>" et renvoit os.
      /* ???? */ 
      return os << "arg<" << ID << ">";
    }

    template<typename... Args>
    constexpr auto operator()(Args&&... args) const
    {
      // Construit un tuple de tout les args et renvoit le ID-eme via std::get
      /* ???? */
      auto t = std::forward_as_tuple(args...);
      return std::get<ID>(t);
    }
  };

  // Generateur de variable numÃ©rotÃ©e
  template<int ID>
  inline constexpr auto arg = terminal<ID>{};

  // Variables _0, _1 et _2 sont prÃ©dÃ©finies
  inline constexpr auto _0  = arg<0>;
  inline constexpr auto _1  = arg<1>;
  inline constexpr auto _2  = arg<2>;

  //---------------------------------------------------------------------------------------
  /*
    Le deuxieme Ã©lÃ©ment  d'un systeme d'EXPRESSION TEMPLATE est la classe de noeud. 
    Un NODE reprÃ©sente un opÃ©rateur ou une fonction dans l'ARBRE DE SYNTAXE. 

    Il est dÃ©fini par le type de l'OPERATION effectuÃ©e au passage du noeud et d'une
    liste variadique de ses sous-nodes.

    Q3 ComplÃ©tez l'implÃ©mentation de la structure template node ci dessous en suivant les demandes
  */
  //---------------------------------------------------------------------------------------
  template<typename Op, typename... Children>
  struct node
  {
    // Faite en sorte que node vÃ©rifie le concept expr
    /* ???? */ 
    static constexpr bool is_expr = true;

    // Construisez un node Ã  partir d'une instance de Op et d'une liste variadique de Children
    // Ce constructeur sera constexpr
    /* ???? */ 
    constexpr node(Op op_, Children... c)
      : op(op_), children(c...)
    {}

    // L'operateur() de node permet d'Ã©valuer le sous arbre courant de maniÃ¨re 
    // rÃ©cursive. Les paramÃ¨tres args... reprÃ©sentent dans l'ordre les valeurs des
    // variables contenus dans le sous arbre.
    // Par exemple, le node {op_add, terminal<1>, terminal<0>} appelant operator()(4, 9)
    // doit renvoyer op_add(9, 4);
    template<typename... Args>
    constexpr auto operator()(Args&&... args) const
    {
      /* ???? */ 
      return std::apply(
        [&](auto const&... child)
        {
          // Evaluate each child with (args...) -> child(args...)
          // Then feed them into op(...)
          return op(child(args...)...);
        },
        children
      );
    }

    // Affiche un node en demandant Ã  Op d'afficher les sous arbres
    std::ostream& print(std::ostream& os) const
    {
      /*
        The key fix:
        - Instead of returning op.print(...) directly from the lambda,
          we do the printing inside the lambda (which returns void),
          then we return `os` after std::apply is done.
      */
      std::apply(
        [&](auto const&... child)
        {
          // print sub-nodes with op
          op.print(os, child...);
        },
        children
      );
      return os;
    }
    
    // Op est stockÃ© par valeur
    // les Children... sont stockÃ©es dans un tuple
    /* ???? */ 
    Op op;
    /* ???? */ 
    std::tuple<Children...> children;
  };

  //----------------------------------------------
  /*
    add_ est un exemple de type d'operation passable Ã  un node
    Il fournit un operator() qui effectue le calcul et une fonction
    print qui affiche le node.
  */
  //----------------------------------------------
  struct add_ 
  {
    constexpr auto operator()(auto a, auto b) const
    {
      return a + b;
    }

    std::ostream& print(std::ostream& os, auto a, auto b) const
    {
      // This returns std::ostream&, which is fine
      return os << a << " + " << b ;
    }
  };
  
  // On lui associe un operator+ qui consomme des expr et renvoit le node
  template<expr L, expr R>
  constexpr auto operator+(L l, R r)
  {
    return node{add_{}, l, r};
  }

  /*
    Q4. Sur le modÃ¨le de add_, implÃ©mentez 
      - mul_ et un operator* pour la multiplication
      - abs_ et une fonction abs pour le calcul de la valeur absolue
      - fma_ et une fonction fma(a,b,c) qui calcule a*b+c
  */

  // mul_
  struct mul_
  {
    constexpr auto operator()(auto a, auto b) const
    {
      return a * b;
    }

    std::ostream& print(std::ostream& os, auto a, auto b) const
    {
      return os << a << " * " << b;
    }
  };

  template<expr L, expr R>
  constexpr auto operator*(L l, R r)
  {
    return node{mul_{}, l, r};
  }

  // abs_
  struct abs_
  {
    constexpr auto operator()(auto x) const
    {
      using std::abs;
      return abs(x);
    }

    std::ostream& print(std::ostream& os, auto a) const
    {
      return os << "abs(" << a << ")";
    }
  };

  constexpr auto abs(expr auto x)
  {
    return node{abs_{}, x};
  }

  // fma_
  struct fma_
  {
    // Calcule a*b + c
    constexpr auto operator()(auto a, auto b, auto c) const
    {
      return std::fma(a, b, c);
    }

    std::ostream& print(std::ostream& os, auto a, auto b, auto c) const
    {
      return os << "fma(" << a << ", " << b << ", " << c << ")";
    }
  };

  constexpr auto fma(expr auto a, expr auto b, expr auto c)
  {
    return node{fma_{}, a, b, c};
  }

  //---------------------------------------------------------------------------------------
  // To allow 'os << some_expression' we provide this operator<< for any expr:
  //---------------------------------------------------------------------------------------
  template<expr E>
  std::ostream& operator<<(std::ostream& os, E const& e)
  {
    return e.print(os);
  }

} // namespace et

int main()
{
  // Q5. Le mini exemple ci dessous doit fonctionner. 
  constexpr auto f = et::fma(et::_1, et::abs(et::_2), et::_0);

  f.print(std::cout) << "\n";
  std::cout << "f(1,2,3) = " << f(1,2,3) << "\n\n";

  // Tests addition
  constexpr auto add_expr = et::_0 + et::_1;
  std::cout << "Expression add_expr : " << add_expr << "\n";
  std::cout << "add_expr(3,4) = " << add_expr(3,4) << "\n\n";

  // Tests multiplication
  constexpr auto mul_expr = et::_1 * et::_2;
  std::cout << "Expression mul_expr : " << mul_expr << "\n";
  std::cout << "mul_expr(2,3,4) = " << mul_expr(2,3,4) << "\n\n";

  // Tests abs
  constexpr auto abs_expr = et::abs(et::_0);
  std::cout << "Expression abs_expr : " << abs_expr << "\n";
  std::cout << "abs_expr(-5) = " << abs_expr(-5) << "\n\n";

  // A more complex expression
  constexpr auto combo = (et::_0 + et::_1) * et::abs(et::_2);
  std::cout << "Expression combo : " << combo << "\n";
  std::cout << "combo(1,-2,-3) = " << combo(1,-2,-3) << "\n\n";

  return 0;
}
