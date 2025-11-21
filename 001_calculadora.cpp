/*
    Programando uma calculadora com orientação a objetos
    Aplicando os conceitos de classes, métodos, encapsulamento com public e objetos.

    Quando uma classe é criada, o que existe é apenas um molde (uma receita). Não está ocupando memória.
    A partir do momento em que o objeto é criado com a linha "Calculadora calc", a memória é alocada; isto é,
    os objetos ficam disponíveis para uso.

    Com a metáfora do "bolo pronto". A classe é a receita e o objeto é o bolo pronto.
*/

#include <iostream>
using namespace std;

// classe chamada calculadora :: responsável por conter os métodos necessários para realizar as operações
class Calculadora {

// encapsulando os métodos em public
public:
    // Métodos da calculadora - Organização semelhante as funções
    double somar(double a, double b) {
        return a + b;
    }

    double subtrair(double a, double b) {
        return a - b;
    }

    double multiplicar(double a, double b) {
        return a * b;
    }

    double dividir(double a, double b) {
        if (b == 0) {
            cout << "Erro: divisão por zero!\n";
            return 0;
        }
        return a / b;
    }
};

// função principal
int main() {
    Calculadora calc; // transformando a calculadora em um objeto chamado calc
    double x, y;
    int opcao;

    // interface de interação com o usuário
    cout << "Digite o primeiro numero: ";
    cin >> x;

    cout << "Digite o segundo numero: ";
    cin >> y;

    cout << "Escolha a operacao: ";
    cout << "1 - Somar";
    cout << "2 - Subtrair";
    cout << "3 - Multiplicar";
    cout << "4 - Dividir";

    cout << "Opcao: ";
    cin >> opcao;

    cout << "Resultado: ";

    // switch - case responsável por chamar os métodos dentro da classe
    switch (opcao) {
        case 1:   cout << calc.somar(x, y);        break;
        case 2:   cout << calc.subtrair(x, y);     break;
        case 3:   cout << calc.multiplicar(x, y);  break;
        case 4:   cout << calc.dividir(x, y);      break;
        default:  cout << "Opcao invalida!";       break;
    }

    cout << endl;
    return 0;
}

