/*
    Usando vetores em C++
*/

//bibliotecas
#include <iostream>
#include <vector>

int main(){
    //criando as variáveis e o vetor usados neste projeto
    std::vector<double> tempv;
    double temp, sum;

    //salvando a temperatura registrada em um vetor
    while(std::cin>>temp){
        tempv.push_back(temp);
    }

    //mostrando e somando todos os elementos do mesmo vetor
    for(int i = 0; i < tempv.size(); i++){
        std::cout << tempv[i] << ", ";
        sum += tempv[i];
    }
    std::cout << std::endl;

    //retornando a temperatura média (construída por intermédio e artifício da média aritmética)
    std::cout << "temperatura M.  : " << sum/tempv.size() << std::endl; 
    
    //retornando o valor exato
    return EXIT_SUCCESS;
}