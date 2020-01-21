#include <stdlib.h>
#include <string>
#include <math.h>
#include <random>
#include <iostream>
#include <ctime>
//#include <Windows.h>
#include <stdio.h>
#include <omp.h> // threads
//#include <chrono>
#pragma warning(disable : 4996).


//#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>
#include "biblioteca_profe_claudio.h"
#include "biblioteca_perturbacoes.h"




using namespace std;
//using namespace chrono;


//int main(int argc, char* argv[])
int main()
{
    int n_city, n_family, n_veic;
    int click; //click é um interruptor que faz com que na primeira interacao se encontre a melhor solução e na segunda se obtenha o valores necessarios de interação para se alcançar o resultado :)
    click = 0;
    vector <lista_de_caminhos> lista_de_rotas,lista_melhores_rotas; // melhores rotas possui o numero de interações da melhor rota
    string line, subline;
    string argv[2];
    //argv[1] = "./instancias/burma14.tsp_3_1001_1001_2.txt";
    //argv[1] = "burma14.tsp_3_1001_1001_2.txt";
   //argv[1] = "./instancias/burma14.tsp_3_1001_1002_2.txt";
    //argv[1] = "./instancias/burma14.tsp_3_1001_1003_2.txt";
// bayg
    //argv[1] = "./instancias/bayg29.tsp_4_1001_1001_2.txt"; // arquivo de leitura
    // argv[1] = "./instancias/bayg29.tsp_4_1001_1002_2.txt"; // arquivo de leitura
     //argv[1] = "./instancias/bayg29.tsp_4_1001_1003_2.txt"; // arquivo de leitura

//att48
   argv[1] = "./instancias/att48.tsp_5_1001_1001_2.txt";
   //argv[1] = "./instancias/att48.tsp_5_1001_1002_2.txt";
    //argv[1] = "./instancias/att48.tsp_5_1001_1003_2.txt";


    //argv[1] = "./instancias/bier127.tsp_10_1001_1001_2.txt";
   //argv[1] = "./instancias/bier127.tsp_10_1001_1002_2.txt";
    //argv[1] = "./instancias/bier127.tsp_10_1001_1003_2.txt";

    // argv[1] = "./instancias/gr666.tsp_30_1001_1001_2.txt"; // arquivo de leitura

   //argv[1] = "./instancias/bier127.tsp_10_1001_1003_2.txt";
   // argv[1] = "./instancias/bier127.tsp_10_1001_1001_2.txt";


    //argv[1] = "./instancias/att48.tsp_5_1001_1001_2.txt";

    int numero_de_threads = 1;
    int numero_de_interacoes_total = 1;

    // obter numero de visitas totas

    int n_viagens= capta_quantidade_viagens(argv[1]);
    int melhor_tempo=9999999;


    // salvar o valor do vns inicial
    //vector<double> vns_inicial; // double pq nunca se sabe

    for (int i = 0; i < numero_de_threads * numero_de_interacoes_total; i++)
    {
        lista_de_rotas.push_back({  });
        lista_melhores_rotas.push_back({  });
        for (int j = 0; j < n_viagens + 6; j++) { // inclui +2 pois na base não se considera a origem no inicio e no fim e +1 para
            // adicionar no final o custo +1 para o numero de interacoes +1 para o tempo +1 para o valor do VNS inicial
            lista_de_rotas[i].rota.push_back({ 0 });
            lista_melhores_rotas[i].rota.push_back({ 0 });
        }
    }

    while (click != 1)  // se clck =2 ele faz ate encontrar a melhor rota de click=1
    {

        int perd = 0;
        vector <double> interacoes_gastas, interacoes_perdidas;
        std::vector<truck> caminhao_rota_final; // cria um vetor caminhao do tipo truck
        omp_set_num_threads(numero_de_threads);
#pragma omp parallel private(interacoes_gastas)
        {
            printf(" thread %d  de %d\n", omp_get_thread_num(), omp_get_num_threads());

            for (int yy = 0; yy < numero_de_interacoes_total; yy++)
            { 				//using chrono::system_clock;
                //system_clock::time_point t1 = system_clock::now();



                //	std::cout << "Random value: " << generator() << std::endl;
                //printf("%s\n\n", argv[1]);
                //<> pode ser ou float,int
                double custo_total = 0;// variavel a ser minimizada
                int n_visita;// numero da visita( referente ao vetor da rota)
                std::vector<cidade> city; // cria um vetor cidades do tipo cidade
                std::vector<truck> caminhao; // cria um vetor caminhao do tipo truck

                std::vector<int> visitas_p_familia; // demanda de visitas por familia
                std::vector<int> visitou_p_familia; // quantidade de visitas ja feitas por familia
                std::vector<int>cidades_cada_familia;
               // std::vector<matriz_distancias> matriz_d_distancias;

                int numb, aa, bb;
                std::vector<int> gasolina; //OLHA O GAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAASSSSSSSS
                //auxnode.push_back({ 5, 05, 50, 0 });


                //argv[1] = "bier127.tsp_10_1001_1001_2.txt";
                //argv[1] = "a280.tsp_20_1001_1001_2.txt";
                //printf("quantos %d nome do arquivo %s nome da instancia :%s utlimo %s\n\n",argc, argv[0], argv[1], argv[2]);

                //ler_arquivo_cidades(n_city, city, visitas_p_familia, visitou_p_familia,n_family);
                ler_arquivo_cidades_fornaza(argv[1], n_city, city, cidades_cada_familia, visitas_p_familia, visitou_p_familia, n_family);
                //encontrei os pontos, funcao fornaza fica pra mais tarde
                //ler_matriz_distancias(n_city, visitas_p_familia, visitou_p_familia, n_family, matriz_d_distancias); // ler arquivo fornaza

                ifstream infile;

                int tipo_dist; // tipo do calculo que sera feito para calcular a distancia
                tipo_dist = 1; //distancia absoluto!!!

                int cond;
                int  n; // esse numero muda, mas o maximo de rotas é o numero maximo de veiculos
                int prox_cam; // variavel criada para auxiliar no loop quando o caminhão não encheu mas não tem mais capacidade de nenhuma cidade
                double distancia, menordistancia;
                int j_escolhido; // auxiliar sobre a cidade escolhida com a menor distancia
                int auxiliar_thred = omp_get_thread_num();

                n_visita = 1;
                n_veic = 0; // começar no inicio do vetor


                // vizinho mais próximo
                //vizinho_mais_proximo_grupos_completo(n_city, n_family, n_veic, custo_total, n_visita, city, caminhao, visitou_p_familia, visitas_p_familia, cidades_cada_familia);


               /// testes 2opt
                //vizinho_mais_proximo_grupos_completo_graspeado(n_city, n_family, n_veic, custo_total, n_visita, city, caminhao, visitou_p_familia, visitas_p_familia, cidades_cada_familia);
                dois_opt(n_city, n_family, n_veic, custo_total, n_visita, city, caminhao, visitou_p_familia, visitas_p_familia, cidades_cada_familia);
                //caminho_inicial_aleatorio(n_city, n_family, n_veic, custo_total, n_visita, city, caminhao, visitou_p_familia, visitas_p_familia, cidades_cada_familia);
                gravar_caminhao(caminhao, n_veic, "do", n_visita, n_city, city, "1", "doisoptmodif");
                custo_total = tempo_total_rota(city, caminhao, n_visita, n_veic);


                caminhao[n_veic].rota.push_back({ 0 });// volta pra 0
                printf("\n custo %.2f \n",custo_total);
                scanf("%d",&n_veic); // só pra parar



                n_visita++;
                /////////plotar rotas

                //	printf("Capacidade do caminhao inicialmente: %d\n\n", cap_cam_geral);
//**	printf("\n vizinho mais proximo\n");
//**	for (int j = 0; j <= n_veic; j++)
                //**{
                //printf("\n caminhao %d : ", j+1);
                //printf("\n caminhao %d : ", j);
                //**for (int i = 0; i < n_visita; i++)
                // count << caminhao[j].rota[i];
                //**printf("%d ", caminhao[j].rota[i]);

                //**}
                int i = 0;


                contar_familias_vetor(caminhao, cidades_cada_familia, n_family);

                gravar_caminhao(caminhao, n_veic, line, n_visita, n_city, city, "1", argv[1]);
                //printf("\n\notimizado\n\n");
                custo_total = tempo_total_rota(city, caminhao, n_visita, n_veic);
                auxiliar_thred = yy * numero_de_threads + auxiliar_thred;
                lista_de_rotas[auxiliar_thred].rota[n_viagens+5]= custo_total;


                interacoes_gastas.push_back({ perturbacao_familia(city, caminhao, custo_total, visitas_p_familia, cidades_cada_familia, n_family, n_city, n_visita, n_veic,click) - 1 });
                // cidades_cada_familia é um vetor com  o numero de cidades para cada familia

                // condicoes para criar vetor de sobra _ interacoes_perdidadas
                if (click == 1)
                {					//testo se  ja fez uma vez até o final, obtendo assim o valor minimo
                    if (custo_total > melhor_tempo)
                    {
                        perd++;
                        interacoes_perdidas.push_back(custo_total);
                        interacoes_gastas.erase(interacoes_gastas.begin() + yy);
                        yy--;

                    }
                    else
                    {
                        //	printf("\n minimo= %d\n ", interacoes_gastas[yy]);
                        //	printf("\n\n");


                        // custo_total = tempo_total_rota(city, caminhao, n_visita, n_veic);
                        printf("thread %d  custo final :%.f\n", omp_get_thread_num(), custo_total);
                        //***** for (int i = 0; i < n_visita; i++)
                        // count << caminhao[j].rota[i];
                        //*****  printf("%d ", caminhao[0].rota[i]);

                        // salvar rotas no vetor lista_de_rotas para fora do paralelismo

                        int auxiliar_thred = omp_get_thread_num();
                        auxiliar_thred = yy * numero_de_threads + auxiliar_thred;
                        for (int j = 0; j <= 0; j++)
                        {
                            for (int i = 0; i < n_visita; i++) //
                            {

                                lista_melhores_rotas[auxiliar_thred].rota[i] = caminhao[j].rota[i];
                            }
                            lista_melhores_rotas[auxiliar_thred].rota[n_visita] = custo_total;
                        }


                        //system_clock::time_point t2 = system_clock::now();
                        //duration<double> tempo = duration_cast<duration<double>> (t2 - t1);
                        lista_melhores_rotas[auxiliar_thred].rota[n_visita + 1] = interacoes_gastas[yy]; //interacoes
                        lista_melhores_rotas[auxiliar_thred].rota[n_visita + 2] =0;// round(tempo.count());//tempo
                        //cout << "Tempo de trabalho " << tempo.count() << " segundos" << endl;

                    }

                    // plotar lista
                    // system("clear");
                    for (int j = 0; j < numero_de_interacoes_total * numero_de_threads; j++)
                    {
                        printf("\n rota %d ", j);
                        for (int i = 0; i < n_visita; i++) //
                        {
                            printf(" %.f ", lista_melhores_rotas[j].rota[i]);
                        }
                        printf(" custo= %.f, %.f interacoes, %.f segundos  ", lista_melhores_rotas[j].rota[n_visita], lista_melhores_rotas[j].rota[n_visita + 1], lista_melhores_rotas[j].rota[n_visita + 2]);
                    }
                }
                else
                {
                     auxiliar_thred = omp_get_thread_num();
                    auxiliar_thred = yy * numero_de_threads + auxiliar_thred;
                    for (int j = 0; j <= 0; j++)
                    {
                        for (int i = 0; i < n_visita; i++) //
                        {

                            lista_de_rotas[auxiliar_thred].rota[i] = caminhao[j].rota[i];
                        }
                        lista_de_rotas[auxiliar_thred].rota[n_visita] = custo_total;
                        if (custo_total < melhor_tempo)melhor_tempo = custo_total; // salvo o melhor tempo
                    }


                    //system_clock::time_point t2 = system_clock::now();
                    //duration<double> tempo = duration_cast<duration<double>> (t2 - t1);
                    lista_de_rotas[auxiliar_thred].rota[n_visita + 1] = interacoes_gastas[yy]; //interacoes
                    lista_de_rotas[auxiliar_thred].rota[n_visita + 2] = 0;//round(tempo.count());//tempo
                    //cout << "Tempo de trabalho " << tempo.count() << " segundos" << endl;


                    // plotar lista
  // /* no meio
                    for (int j = 0; j < numero_de_interacoes_total * numero_de_threads; j++)
                    {
                        printf("\n rota %.d ", j);
                        for (int i = 0; i < n_visita; i++) //
                        {
                            printf(" %.f ", lista_de_rotas[j].rota[i]);
                        }
                        printf(" custo= %.2f %.f interacoes, %.f segundos VNS= %.2f   ", lista_de_rotas[j].rota[n_visita], lista_de_rotas[j].rota[n_visita + 1], lista_de_rotas[j].rota[n_visita + 2],lista_de_rotas[j].rota[n_viagens+5]);
                    }
//   */
                }



                // gravar
                //printf("\n\n\ custo 2 = %f", custo_total);

                //gravar_caminhao(caminhao,n_veic,line, n_visita,n_city,city,"2", argv[1]);

                //contar_familias_vetor(caminhao, cidades_cada_familia, n_family);
                //system("pause");


                //		yy = numero_de_interacoes_total; // saindo do for
            }


        } //fim da thread
        click++;
    }// fim do while click
    // gravar medias
    FILE * pFile;
    pFile = fopen ("./rotas/lista rotaa.txt","w");
    if (pFile!=NULL)
    {


        for (int j = 0; j < numero_de_interacoes_total * numero_de_threads; j++)
        {
            fprintf(pFile,"rota ");

            for (int i = 0; i < (n_viagens + 5); i++) //
            {
                fprintf(pFile,"	%.f ",lista_de_rotas[j].rota[i]);
            }
            fprintf(pFile,"\n");
        }



        fclose (pFile);
    }
n_viagens=n_viagens+2;
    double best_by_test=lista_de_rotas[0].rota[n_viagens];
    int n_best_by_test =0;
    for (int j = 0; j < numero_de_interacoes_total * numero_de_threads; j++)
    {
        if (lista_de_rotas[j].rota[n_viagens]<best_by_test)
        {
            best_by_test=lista_de_rotas[j].rota[n_viagens];
            n_best_by_test=j;
        }

    }




printf("\nmelhor \n");

    //printf("\n custo= \t %.2f \t %.f \t  interacoes \t  VNS= \t  %.2f ", lista_de_rotas[n_best_by_test].rota[n_viagens], lista_de_rotas[n_best_by_test].rota[n_viagens + 1],lista_de_rotas[n_best_by_test].rota[n_viagens+3]);
    printf("\n  %.2f \t %.f \t  %.2f ", lista_de_rotas[n_best_by_test].rota[n_viagens], lista_de_rotas[n_best_by_test].rota[n_viagens + 1],lista_de_rotas[n_best_by_test].rota[n_viagens+3]);
printf("\n rota \n");
    for (int i = 0; i < n_viagens; i++) //
    {
        printf("\t %.f ", lista_de_rotas[n_best_by_test].rota[i]);
    }

/*
		ofstream outfile;		//criamos objeto da classe ofstream

		outfile.open("listad "+ argv[1] +".txt", ios::out); //salva tempos

		for (int j = 0; j < numero_de_interacoes_total * numero_de_threads; j++)
		{
			outfile << "rota "<< j;
			for (int i = 0; i < (n_viagens + 5); i++) //
			{
				outfile <<"	"<< lista_de_rotas[j].rota[i];
			}
			outfile << "\n";
		}

		outfile.close();

		*/


/*
//    FILE * pFile;
    pFile = fopen (argv[1] ,"w");
    if (pFile!=NULL)
    {

        for (int j = 0; j < numero_de_interacoes_total * numero_de_threads; j++)
        {
            fprintf(pFile,"rota ");
            for (int i = 0; i < (n_viagens + 5); i++) //
            {
                fprintf(pFile," %d", lista_melhores_rotas[j].rota[i]);
            }
            fprintf(pFile,"\n");
        }

    }
*/
    //com ofstream
    ofstream outfile;

		//outfile.open("./rotas" + argv[1] + ".txt"); //salva tempos
		//outfile.open("lista rotaa.txt"); //salva tempos

    if(!outfile)
    {
        cout << "Couldn't open file" << endl;
        return 1;
    }


		for (int j = 0; j < numero_de_interacoes_total * numero_de_threads; j++)
		{
			outfile << "rota " << j;
			for (int i = 0; i < (n_viagens + 5); i++) //
			{
				outfile << "	" << lista_melhores_rotas[j].rota[i];
			}
			outfile << "\n";
		}

		outfile.close();




    //outfile.open("perdas.txt"); //salva tempos

    // grava o que perdeu
    /*
    for (int i = 0; i < perd; i++)
    {

        outfile << i << " " << interacoes_perdidas[i] << "\n";

    }

    outfile.close();
    */

    return 0;

}