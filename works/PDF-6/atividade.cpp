/*
    Programando as melhorias da calculadora de terminal para aprender boas práticas da programação.
    Abaixo coloquei alguns comentários. Fiz modificações próprias para a leitura do código ficar mais fácil para mim.

    Há mudanças que foram feitas para o aprendizado como o uso do "std::".
    ~ Francisco Passos 
*/


// incluindo as bibliotecas para o projeto
#include <iostream>
#include <stdexcept>
#include <string>

// para melhor organização e compreensão do código, não usei o código "using namespace std;"

/*
    removendo as "constantes mágicas" do resto do código. 


    slide 11 - 20
*/ 
const char number = '8';   
const char quit   = 'q';   
const char print  = ';';  

const std::string prompt = "> ";
const std::string result = "= "; 


// funções responsáveis por tratar os erros
[[noreturn]] void error(std::string s) {
    throw std::runtime_error(s);
}

[[noreturn]] void error(std::string s1, std::string s2) {
    error(s1 + s2);
}

/*
trocando o struct por uma class -> primeira questão da prova
armazena o valor do token e o seu tipo
*/
class Token {
public:
    char kind;
    double value = 0;
};

/*
essa classe é responsável por transformar as entradas em tokens


slide 27 - 28
*/
class Token_stream {
public:
    Token get();
    void putback(Token);
    void ignore(char c); 

private:
    bool full = false;
    Token buffer;
};

Token_stream ts; //objeto

/*
    Apenas o Token_stream pode acessar o private. Mesmo que buffer e full estejam encapusulados como "private", 
    os métodos bool e full podem ser acessados por a função estar como: Token_stream::putback. 
    Isso acontece em outras funções como: Token_stream::get e Token_stream::ignore. Porém daria erro caso eles
    tentassem ser acessados em int main, por exemplo. 

    buffer = t;
    full = true;


    explicando a função: 
        essa função é responsável por Colocar um token de volta no fluxo, para que ele seja lido 
        novamente depois.
        Quando o 
*/
void Token_stream::putback(Token t) {
    if (full) {
        error("putback() into a full buffer");
    }
    buffer = t;
    full = true;
}

/*
    A função é responsável por identificar a entrada e separar como números, operadores, parenteses e etc.
    Após a identificação, ele retorna um token; 
*/
Token Token_stream::get() {
    //se o buffer estiver cheio, ele retorna o token guardado
    if (full) {
        full = false;
        return buffer;
    }

    // sem entrada == erro
    char ch;
    if (!(std::cin >> ch)) {
        error("no input"); 
    }

    // identificando o caractere
    switch (ch) {
        case '(': case ')': case ';': case 'q':
        case '+': case '-': case '*': case '/':
            return Token{ch}; 

        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            /*
                putback devolve o primeiro caractere do número,
                permitindo que cin >> val leia o número completo (ex: 3.14
            */
            std::cin.putback(ch);
            double val;
            std::cin >> val;
            return Token{number, val};
        }

        // qualquer coisa que não seja os caracteres acima é erro; logo "bad token".
        default:
            error("Bad token");
    }
}

/*
A função abaixo serve para finalizar o programa automaticamente quando o programa se depara com algum caractere inválido.
Ele vai "ignorando" o que está escrito até achar o ";" para terminar o programa. 


slide 27 - 28
*/
void Token_stream::ignore(char c) {
    if (full && buffer.kind == c) {
        full = false;
        return;
    }

    full = false;

    char ch;
    while (std::cin >> ch){
        if (ch == c) {
            return;
        } 
    }
}


double expression();

double primary() {
    Token t = ts.get();

    switch (t.kind) {
        // Caso o usuário esqueça de fechar o parêntese, acontece um erro.
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }

        case number:
            return t.value;

        default:
            error("primary expected");
    }
}

double term() {
    double left = primary();
    while (true) {
        Token t = ts.get();

        switch (t.kind) {
            case '*':
                left *= primary();
                break;

            case '/': {
                double d = primary();
                if (d == 0) {
                    error("divide by zero");
                }
                left /= d;
                break;
            }

            default:
                ts.putback(t);
                return left;
        }
    }
}

double expression() {
    double left = term();
    while (true) {
        Token t = ts.get();

        switch (t.kind) {
            case '+':
                left += term();
                break;

            case '-':
                left -= term();
                break;

            default:
                ts.putback(t);
                return left;
        }
    }
}

/*


slide 29
*/
void clean_up_mess() {
    ts.ignore(print); //print == ';'
}

/*
por boas práticas de programação, o bloco de código abaixo foi retirado do main e se tornou uma função. 


slide 21 - 23
*/
void calculate() {
    while (std::cin){ 
        try {
            std::cout << prompt;

            Token t = ts.get();
            while (t.kind == print) {
                t = ts.get();
            }

            if (t.kind == quit) {
                return;
            }
            ts.putback(t);

            std::cout << result << expression() << '\n';
        }
        catch (std::exception& e) {
            std::cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
}

/*
função principal
tratando erros com try e catch por boas práticas
*/
int main() {
    try { 
        calculate();
        return 0;
    }
    catch (...) {
        std::cerr << "exception\n";
        return 2;
        /*
            Tipos de retorno de uma função:
            0 :: tudo ok
            1 :: erro tratado, mas esperado
            2 :: erro desconhecido/genérico
        */
    }
}
