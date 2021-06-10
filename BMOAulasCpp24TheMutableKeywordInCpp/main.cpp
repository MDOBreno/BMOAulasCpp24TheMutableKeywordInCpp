//
//  main.cpp
//  BMOAulasCpp24TheMutableKeywordInCpp
//
//  Created by Breno Medeiros on 10/06/21.
//

#include <iostream>
#include <string>


class Entidade {
private:
    std::string m_Nome;
    mutable int m_ContandoParaDebug = 0;
    
public:
    const std::string& GetNome() const {
        //m_Nome = ""; //Descomentar essa linha causa erro
        m_ContandoParaDebug++;
        return m_Nome;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    const Entidade e; //Um dos motivo pelo qual definimos uma entidade como constante é porque so assim
    e.GetNome();      // poderemos chamar metodos constantes como estamos fazendo nessa linha.
    //Mas agora surge um dilema quando quisermos usar a variavel 'm_ContandoParaDebug' para contar
    // quantas vezes esse metodo é chamado, mesmo que essa variavel 'm_ContandoParaDebug' tenha que ficar
    // dentro da classe Entidade e nao seja entendida humanamente como um atributo de Entidade. Alem disso,
    // como ja dissemos acima, se a instancia 'e' deixasse de ser 'const' nao conseguiriamos usar 'e.GetNome();'.
    // Entao a solucao é definir 'm_ContandoParaDebug' como 'mutable', para ela ela "drible" a restricao 'const'.
    
    //O segundo caso de quando usamos 'mutable' é quando usamos uma FuncaoLambda.
    //Primeiro vamos explicar o que é uma FuncaoLambda, que é justamente quando voce cria uma funcao qualquer
    // que chamarei de 'X' e a "armazena em uma variavel", para que essa "variavel" possa ser usada como
    // parametro/argumento de outra funcao 'Y'. Dessa forma poderemos usar 'X' dentro de 'Y', como veremos abaixo:
    int x=8;
    auto FL1 = [&]() { //Aqui nos podemos passar como argumento dessaas formas: '&x', 'x', '&', '='.
    // Esses dois ultimos('&' e '=') sevem para passar tudo do escopo 'main()' dentro ou por 'referencia' ou 'valor'
        x++;
        std::cout << x << std::endl;
    };
    FL1();
    
    x=8;
    auto FL2 = [=]() { //Como estamos usando o '[=]', então precisamos escrever a linha abaixo para capturar
        int y = x;     // o valor de 'x', já que optamos por nao passar por referencia(ou seja, '[&]').
        y++;
        std::cout << y << std::endl;
    };
    FL2();
    
    //Agora que já explicamos o que é uma FuncaoLambda, e a limitacao de '[=]', veremos o uso de 'mutable':
    x=8;
    auto FL3 = [=]() mutable {//Definindo 'mutable' estamos permitindo que, mesmo 'x' tendo sido passado como 'valor'(ou
        x++;                  // seja uma copia), consigamos ter uma outra variavel interna 'x' com mesmo nome e valor.
        std::cout << x << std::endl;
    };
    FL3();
    //Obs: Mesmo usando '[=]' com 'mutable', o que mudarmos na variavel 'x' internamente NAO MUDA o 'x' externo.
    
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
