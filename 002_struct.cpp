/*
 Definição e Uso de um struct (Classe Simples)


 Crie um tipo definido pelo usuário chamado Token usando a sintaxe struct, conforme o exemplo do calculador.

 1. Este tipo deve conter um membro char para armazenar o kind (tipo) do token e um double para armazenar o value (valor).
 2. No programa principal (main), crie um objeto Token (por exemplo, t) e inicialize-o para representar o número 2.3.
 3. Utilize o caractere '8' como indicador do tipo (kind) para "número".
 4. Acesse os membros do objeto (t.kind e t.value) usando o operador ponto (.) para atribuir e, em seguida, imprima o valor do token.

 Foco: Criação de tipos simples definidos pelo usuário e acesso a membros de dados.
*/

#include <iostream>
using namespace std;

struct Token{
    char kind;
    double value;
};

int main(){
    Token t;

    t.value = 2.3;
    t.kind = '8';

    cout << t.value << "\n";
    cout << t.kind  << "\n";

    return 0;
}
