#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "funcoes.h"
#include "barras.h"
#include <fstream>

using namespace std;

#define MAX_ITERACOES 1
#define NUMERO_FORMIGAS 2000
#define TAMANHO_MOCHILA 3
#define ALFA 0.2
#define BETA 100


struct formigas{
    float mochila[TAMANHO_MOCHILA];
} formiga[NUMERO_FORMIGAS];


int main(){


    srand (time(NULL));
    r2();


    clock_t time_start = clock();


    int iteracoes = 0;
    while(iteracoes < MAX_ITERACOES){
        /*
        for (int q =0; q < 30; q++){

            printf("BARRA %d no vetor %d . %.2f - %.2f aumentou %.2f e seu intervalo eh %.2f\n", barras[q], q, barrasMin[q], barrasMax[q],(barrasMax[q]-barrasMin[q])-3.32, (barrasMax[q]-barrasMin[q]));
        }
        */
        cout << "\nITERACAO DE NUMERO " << iteracoes << endl;
        fullReset();
        solucao();
        iteracoes++;
    }

    cout << "\nTempo de execucao: " << calculate_time(time_start, clock()) << "ms";

}

void solucao(){

    for(int i = 0; i < NUMERO_FORMIGAS; i++){
        salvarBarraDef.clear();
        zerarFormigas(i);
        for(int j =0; j < TAMANHO_MOCHILA; j++){
            sortearBarras();
            montarRamos();
            encherMochila(fluxoEncontrado, i, j);
        }
        procurarMaiorValorMochila(i);
        atualizarFeromonio();
        normalizaBarra();
    }
    maiorContingencia();


}

void sortearBarras(){

    for(int i = 0; i < 2; i++){

        int descobrirPrePreBarra;
        int descobrirPreBarra;
        do{
            float nroAleatorio = r2();
            //cout << nroAleatorio  << endl;
            for(int m = 0; m < sizeof(barras)/sizeof(int); m++){

                if(nroAleatorio >= barrasMin[m] && nroAleatorio <= barrasMax[m]){
                    descobrirPreBarra = m;
                }

            }
            descobrirPrePreBarra = descobrirPreBarra;

            salvarBarraTemp[i] = barras[descobrirPreBarra];

        }while(salvarBarraTemp[0] == salvarBarraTemp[1]);

    salvarBarraDef.push_back(descobrirPrePreBarra);
    }

    printf("\nBARRAS DEFINITIVAS %d e %d\n", salvarBarraTemp[0], salvarBarraTemp[1]);
}

int montarRamos(){

    int contarRamos = 0;
    for(int j = 0; j<634; j++){

        if((((valores[j][2] == salvarBarraTemp[0]) || (valores[j][3] == salvarBarraTemp[0])||(valores[j][4] == salvarBarraTemp[0]) || (valores[j][5] == salvarBarraTemp[0])))
          &&((valores[j][2] == salvarBarraTemp[1]) || (valores[j][3] == salvarBarraTemp[1])||(valores[j][4] == salvarBarraTemp[1]) || (valores[j][5] == salvarBarraTemp[1]))){

                if(valores[j][2] == salvarBarraTemp[0] && valores[j][3] == salvarBarraTemp[1]||
                   valores[j][2] == salvarBarraTemp[1] && valores[j][3] == salvarBarraTemp[0]||
                   valores[j][4] == salvarBarraTemp[0] && valores[j][5] == salvarBarraTemp[1]||
                   valores[j][4] == salvarBarraTemp[1] && valores[j][5] == salvarBarraTemp[0]){
                    goto avanca;
                }

                printf("RAMO %.0f_%.0f|%.0f_%.0f na linha %.0f\n", valores[j][2], valores[j][3],valores[j][4],valores[j][5], valores[j][0]);
                salvarLinha[contarRamos] = j;
                contarRamos++;



        }

        avanca: ;

    }


    if (contarRamos > 1){

        float maioR = 0.0;
        int bla = 0;
        int r = rand() % contarRamos;
        for(int q = 0 ;q < contarRamos;q++){
            if(valores[salvarLinha[q]][1] > maioR){
                maioR = valores[salvarLinha[q]][1];
                bla = q;
            }
        }
        cout << "o maior indice eh " << maioR << "na" << bla << endl;
        fluxoEncontrado = valores[salvarLinha[bla]][1];
        //adicionando feromonio nos fluxos
        valores[salvarLinha[bla]][6] = valores[salvarLinha[bla]][6] + fluxoEncontrado/BETA;
        //printf("A linha escolhida for %d e seu fluxo eh %f\n", salvarLinha[r], fluxoEncontrado);
        cout << "A linha escolhida foi " << valores[salvarLinha[bla]][0] << " e seu fluxo eh " <<fluxoEncontrado <<endl;
        cout << "na linha escolhido o coenficiente de escola eh " << valores[salvarLinha[bla]][6] << endl;
        return fluxoEncontrado;



    }else if(contarRamos == 1){

        fluxoEncontrado = valores[salvarLinha[contarRamos]][1];
        //adicionando feromonio nos fluxos?
        valores[salvarLinha[contarRamos]][6] = valores[salvarLinha[contarRamos]][6] + fluxoEncontrado/BETA;
        cout << "A linha escolhida foi " << salvarLinha[contarRamos] << " e seu fluxo eh " <<fluxoEncontrado <<endl;
        return fluxoEncontrado;


    }else if(contarRamos == 0){

        fluxoEncontrado = 0;
        return fluxoEncontrado;


    }
}

void encherMochila(float fluxoEncontrado, int numeroFormiga, int posicaoMochila){
    formiga[numeroFormiga].mochila[posicaoMochila] = fluxoEncontrado;
}

void procurarMaiorValorMochila(int numeroFormiga){

    float maiorValor = 0;
    //cout << "Valores de de fluxo na mochila:" << endl;
    for(int p = 0; p < TAMANHO_MOCHILA; p++){

        //cout << formiga[numeroFormiga].mochila[p] << endl;

        if(formiga[numeroFormiga].mochila[p] > maiorValor){
            maiorValor = formiga[numeroFormiga].mochila[p];
        }
    }

    if(maiorValor > maiorValorDoCodigo){
        maiorValorDoCodigo = maiorValor;
    }


    cout << "\nMaior valor da mochila eh: " << maiorValorDoCodigo << endl;

    for(int j = 0; j < salvarBarraDef.size(); j++){
        cout << "posicao " << j << " tem valor de " << barras[salvarBarraDef[j]] << endl;
    }

    //Neste ponto, os valores menores serão divido pelo maiordo código e multiplicado por umas constante ALFA

    for(int k = 0; k< TAMANHO_MOCHILA ; k++){
        divisaoFeromonio[k] = ((formiga[numeroFormiga].mochila[k]/maiorValorDoCodigo)*ALFA);
    }

    for(int m = 0; m < TAMANHO_MOCHILA; m++){
        cout << divisaoFeromonio[m] << endl;
    }

}

void atualizarFeromonio(){

    int controle = 0;

    for(int i = 0; i < 2*TAMANHO_MOCHILA; i+=2){


        if(i == 0){
            barrasMax[salvarBarraDef[i]] =  barrasMax[salvarBarraDef[i]] + divisaoFeromonio[i];
            barrasMax[salvarBarraDef[i+1]] = barrasMax[salvarBarraDef[i+1]] + divisaoFeromonio[i];
            controle++;
        }else{
            barrasMax[salvarBarraDef[i]] =  barrasMax[salvarBarraDef[i]] + divisaoFeromonio[i-controle];
            barrasMax[salvarBarraDef[i+1]] = barrasMax[salvarBarraDef[i+1]] + divisaoFeromonio[i-controle];
            controle++;
        }
    }

}

void normalizaBarra(){

    for(int i =0; i < 30; i++){


        if(barrasMin[i] > barrasMax[i]){
            barrasMax[i] = barrasMin[i];
        }
        float diminui = barrasMax[i]-barrasMin[i+1];
        if(diminui > 0){
            barrasMax[i+1] = barrasMax[i+1] + diminui + 0.01;
        }

        barrasMin[i+1] = barrasMax[i] + 0.01;

        //printf("BARRA %d no vetor %d . %.2f - %.2f aumentou %.2f e seu intervalo eh %.2f\n", barras[i], i, barrasMin[i], barrasMax[i],(barrasMax[i]-barrasMin[i])-3.32, (barrasMax[i]-barrasMin[i]));
    }

}

void maiorContingencia(){
    ofstream myfile;
    myfile.open("file.sql");


    int maiorValor = 0;
    int maisGrave = 0;
    for(int i = 0; i < 634; i++){
        myfile << valores[i][0] << "," << valores[i][6] << endl;
    }



}

void zerarFormigas(int numeroFormiga){
    for(int j = 0; j < TAMANHO_MOCHILA; j++){

        formiga[numeroFormiga].mochila[j] = -1;
    }
}

void fullReset(){
    //int barras[22] = {1,2,3,4,5,6,8,9,10,12,14,15,16,18,19,21,22,23,24,25,27,29};
    //float barrasMin[22] = {0,(1*4.54),(2*4.54),(3*4.54),(4*4.54),(5*4.54),(6*4.54),(7*4.54),(8*4.54),(9*4.54),(10*4.54),(11*4.54),(12*4.54),(13*4.54),(14*4.54),(15*4.54),(16*4.54),(17*4.54),(18*4.54),(19*4.54),(20*4.54),(21*4.54)};
    //float barrasMax[22] = {(4.54-0.01),(2*4.54-0.01),(3*4.54-0.01),(4*4.54-0.01),(5*4.54-0.01),(6*4.54-0.01),(7*4.54-0.01),(8*4.54-0.01),(9*4.54-0.01),(10*4.54-0.01),(11*4.54-0.01),(12*4.54-0.01),(13*4.54-0.01),(14*4.54-0.01),(15*4.54-0.01),(16*4.54-0.01),(17*4.54-0.01),(18*4.54-0.01),(19*4.54-0.01),(20*4.54-0.01),(21*4.54-0.01),(22*4.54)};
    for(int i; i < 40; i++){
        divisaoFeromonio[i] = 0;
    }
    maiorValorDoCodigo = 0;
    salvarBarraDef.clear();
}


//aux

double calculate_time(clock_t start, clock_t end) {
	return 1000.0 * ((double) (end - start) / (double) CLOCKS_PER_SEC);
}


float r2(){
    return ((double)rand() / (double)RAND_MAX) * barrasMax[29] ;
}

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}

