#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>

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
  concept expr = requires( /* ???? */ )
  {
    /* ???? */  
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

    std::ostream& print(std::ostream& os) const
    {
      // Pour terminal<I>, affiche "arg<I>" et renvoit os.
      /* ???? */ 
    }

    template<typename... Args>
    constexpr auto operator()(Args&&... args) const
    {
      // Construit un tuple de tout les args et renvoit le ID-eme via std::get
      // Veillez Ã  bien repsecter le fait que args est une reference universelle
      /* ???? */ 
    }
  };

  // Generateur de variable numÃ©rotÃ©e
  template<int ID>
  inline constexpr auto arg =  terminal<ID>{};

  // Variables _0, _& et _2 sont prÃ©dÃ©finies
  inline constexpr auto _0  = arg<0>;
  inline constexpr auto _1  = arg<1>;
  inline constexpr auto _2  = arg<2>;

  //---------------------------------------------------------------------------------------
  /*
    Le deuxieme Ã©lÃ©ment  d'un systeme d'EXPRESSION TEMPLATE est la classe de noeud. 
    Un NODE reprÃ©sente un opÃ©ratuer ou une fonction dans l'ARBRE DE SYNTAXE. 

    Il est dÃ©finit par le type de l'OPERATION effectuÃ©e au passage du noeud et d'une
    liste variadique de ses sous-nodes.

    Q3 ComplÃ©tez l'implÃ©mentation de la structure template node ci dessous en suivant les demandes
  */
  //---------------------------------------------------------------------------------------
  template<typename Op, typename... Children>
  struct node
  {
    // Faite en sorte que node vÃ©rifie le concept expr
    /* ???? */ 

    // Construisez un node Ã  partir d'une instande de Op et d'une liste variadique de Children
    // Ce constructeur sera constexpr
    /* ???? */ 

    // L'operateur() de node permet d'avaluer le sous arbre courant de maniÃ¨re 
    // rÃ©cursive. Les paramÃ¨tres args... reprÃ©sentent dans l'ordre les valeurs des
    // variables contenus dans le sous arbre.
    // Par exemple, le node {op_add, terminal<1>, termnal<0>} appelant operator()(4, 9)
    // doit renvoyer op_add(9, 4);
    // Renseignez vous sur std::apply pour vous simplifier la vie
    // Pensez qu'un node contient potentiellement d'autre node.
    template<typename... Args>
    constexpr auto operator()(Args&&... args) const
    {
      /* ???? */ 
    }

    // Affiche un node en demandant Ã  Op d'afficher les sous arbres
    std::ostream& print(std::ostream& os) const
    {
      /* ???? */ 
    }
    
    // Op est stockÃ©e par valeur
    // les Children... sont stockÃ©es dans un tuple
    /* ???? */  op;
    /* ???? */  children;
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
      - fma_ et une fonction fma(a,b,c) qui calcul a*b+c
  */

  
}

int main()
{
  // Q5. Le mini exemple ci dessous doit fonctionner. ComplÃ©tez le avec une sÃ©rie de tests
  // exhaustif de tout les cas qui vous paraissent nÃ©cessaire.
  constexpr auto f = et::fma(et::_1, abs(et::_2),et::_0);

  f.print(std::cout) << "\n";

  std::cout << f(1,2,3) << "\n";
}