#pragma once
#include <fstream>
using namespace std;
struct Vertex
{
	float x, y, z;
	Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
};

std::ostream& operator <<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << "," << vertex.y << "," << vertex.z;
	return stream;
}

/////////classes////////////qq


class cidade {
public:
	cidade () {}
	int x, y, demanda,family;
	//int  demanda,family;
	//double x, y;
	int visitada = -1;
	cidade(int no, int id)
	{
		y = id;
		x = no;
	}


};

class truck {
public:
	//int x, y;
	int capacidade=1000;
	std::vector<int> rota; // custo � a distancia ponto a ponto
	std::vector<double> custo;
	int gasolina = 100000;
	};

class lista_de_caminhos {
public:
    lista_de_caminhos () {}
std::vector <double> rota;
};

class matriz_distancias {
public:
    std::vector<double> ate; // distancia do ponto i at� j

};


std::vector<matriz_distancias> matriz_de_distancias;

// declarando funcoes

double random_mersene(double inicio, double fim);
//funcao para calculo de distancias
double calculo_distancia(int cond, int cordx1, int cordy1, int cordx2, int cordy2);

//void adiciona_cidade(int rand_num2, std::vector <truck>& caminhao, std::vector <cidade>& city, int n_city);
//int posicao_adicionar(int cidade, std::vector <trwuck> caminhao, std::vector<cidade> city2, int n_city);

void ler_arquivo_cidades(int & n_city, std::vector<cidade> &city, std::vector<int>& visitas_p_familia, std::vector<int>& visitou_p_familia, int& n_family);
int caminho_mais_proximo(int n_city, std::vector<cidade> city, int cidadex, double& menordistancia, vector<int>  visitas_p_familia, vector<int> visitou_p_familia);
void vizinho_mais_proximo_grupos_completo(int n_city, int n_family, int n_veic, double& custo_total, int& n_visita, std::vector<cidade>& city, std::vector<truck>& caminhao, std::vector<int>& visitou_p_familia, std::vector<int>& visitas_p_familia, std::vector<int>& cidades_cada_familia);

//retorna a posicao de menor distancia levando em conta a familia*
int vizinho_mais_proximo(int n_city, std::vector<cidade> city, int cidadex, double& menordistancia,int ocupado);
// retorna a posicao de menor distancia n�o levando em conta a familia

// funcoes auxiliares do algoritmo ( adicionando elemento extra a familia)

double  tempo_adicional_cidade(std::vector<cidade> city2, std::vector<truck> caminhao, int cidade_ant, int cidadeq, int cidade_x, int cidade_prox);
double tempo_adicional_cidade_ponta(std::vector<cidade> city2, std::vector<truck> caminhao, int cidade_1, int cidade2, int cidade3);
double tempo_total_rota(std::vector<cidade> cidades, std::vector<truck> caminhao, int n_visitas, int n_veic);

//imagem
double  tempo_triangulo(std::vector<cidade> city2, std::vector<truck> caminhao, int cidade_ant, int cidade_x, int cidade_prox, int n_city);
void adicionar_cidade(int cidadeq, std::vector<cidade>& city2, std::vector <truck>& caminhao, int n_city, int n_veic, int& n_visitas);
void retirar_cidade(std::vector<cidade>& cidade, std::vector<truck>& caminhao, int qual_fam ,int n_veic, int quant_adicionados, int& n_visitas, int n_city);
void retirar_cidade_reordenando(std::vector<cidade>& cidade, std::vector<truck>& caminhao, int qual_fam, int n_veic, int quant_adicionados, int& n_visitas, int n_city);

// funcoes para perturbacao
void troca_dentro_rota(std::vector<truck>& caminhoes_aux, int n_visitas);
void troca_fora_rota(std::vector<truck>& caminhoes_aux, int n_visitas, std::vector<cidade>& cidade_aux, int n_city);
void funcao_artigo(std::vector<cidade>& cidades_aux, std::vector<truck>& caminhoes_aux, double& custo_total, std::vector<int> visitas_p_familia, std::vector<int>  cidades_cada_familia, int n_family, int n_city, int& n_visitas, int n_veic);
void local_search(std::vector<cidade>& cidades, std::vector<truck>& caminhao, double& custo_total, std::vector<int> visitas_p_familia, std::vector<int>  cidades_cada_familia, int n_family, int n_city, int n_visitas, int n_veic);
// funcoes para gerar caminhos iniciais

// funcao para contar numero de membros pertencentes a familia alocado
void contar_familias_vetor(std::vector<truck> caminhao, std::vector<int>  cidades_cada_familia, int n_family);



void vizinho_mais_proximo_grupos_completo(int n_city, int n_family, int n_veic, double & custo_total, int& n_visita, std::vector<cidade>& city, std::vector<truck> &caminhao, std::vector<int>& visitou_p_familia, std::vector<int>& visitas_p_familia, std::vector<int>& cidades_cada_familia )
// � completo por que faz com todos os pontos, a outra funcao acha apenas o ponto mais proximo
{

	int cond;
	int  n; // esse numero muda, mas o maximo de rotas � o numero maximo de veiculos
	int prox_cam; // variavel criada para auxiliar no loop quando o caminh�o n�o encheu mas n�o tem mais capacidade de nenhuma cidade
	double distancia, menordistancia;
	int j_escolhido; // auxiliar sobre a cidade escolhida com a menor distancia

	n_veic = 1; //////exemplo da sala

	caminhao.reserve(n_veic);
	cond = 0; // condicao para todas as cidades serem percorridas


	// cond � a condicao para todas as familias atendidas o numero de vezes requisitado
	// se foi ent�o cond!=0
	// demanda do caminh�o = 
	caminhao.push_back({ 0 });

	caminhao[0].rota.push_back({ 0 });
	caminhao[0].rota[0] = 0;// come�a na matriz
	city[0].visitada = 0; //come�a no caminhao 1


	n_visita = 1;
	n_veic = 0; // come�ar no inicio do vetor



	while ((cond == 0) && (caminhao[n_veic].gasolina > 0))
		// trocar o 0 da gasosa por reserva()
	{
		n = 0;
		j_escolhido = caminho_mais_proximo(n_city, city, caminhao[n_veic].rota[n_visita - 1], menordistancia, visitas_p_familia, visitou_p_familia);
		

		// para saber se escolheu alguma cidade
		if (j_escolhido != -1) {

			caminhao[n_veic].rota.push_back({ j_escolhido });
			caminhao[n_veic].capacidade = caminhao[n_veic].capacidade - city[j_escolhido].demanda;

			visitou_p_familia[city[j_escolhido].family]++;
			city[j_escolhido].visitada = n_veic;
			n_visita++;
			custo_total = custo_total + menordistancia;
			caminhao[n_veic].custo.push_back({ menordistancia }); //  

		}
		else {
			prox_cam = 1;
			n++;
			caminhao.push_back({ 0 }); //aloca outro caminhao
			n_veic++;
			caminhao[n_veic].rota.push_back({ 0 }); // prixima rota inicia na origem tbm


		}
		cond = 1;
		////////////////////////////////////////////////////// teste de familia////////////////////////////////////////////////////
		for (int jj = 0; jj < n_family; jj++)
		{
			if (visitas_p_familia[jj] > visitou_p_familia[jj])
			{
				// anda mais
				cond = 0; // testar familias
			}



		} //if (menordistancia == 9999.0) cond = 1; 
		if (j_escolhido == -1) cond = 1;
		///////////////////////////////////////////////////////
	}


}

void vizinho_mais_proximo_grupos_completo_graspeado(int n_city, int n_family, int n_veic, double & custo_total, int& n_visita, std::vector<cidade>& city, std::vector<truck> &caminhao, std::vector<int>& visitou_p_familia, std::vector<int>& visitas_p_familia, std::vector<int>& cidades_cada_familia )
// � completo por que faz com todos os pontos, a outra funcao acha apenas o ponto mais proximo
{
    int tamanho_grasp= 1; ///////////////tamanho da lista do grasp

    int cond;
    int  n; // esse numero muda, mas o maximo de rotas � o numero maximo de veiculos
    int prox_cam; // variavel criada para auxiliar no loop quando o caminh�o n�o encheu mas n�o tem mais capacidade de nenhuma cidade
    double distancia, menordistancia;
    int j_escolhido; // auxiliar sobre a cidade escolhida com a menor distancia

    n_veic = 1; //////exemplo da sala

    caminhao.reserve(n_veic);
    cond = 0; // condicao para todas as cidades serem percorridas


    // cond � a condicao para todas as familias atendidas o numero de vezes requisitado
    // se foi ent�o cond!=0
    // demanda do caminh�o =
    caminhao.push_back({ 0 });

    caminhao[0].rota.push_back({ 0 });
    caminhao[0].rota[0] = 0;// come�a na matriz
    city[0].visitada = 0; //come�a no caminhao 1


    n_visita = 1;
    n_veic = 0; // come�ar no inicio do vetor



    while ((cond == 0) && (caminhao[n_veic].gasolina > 0))
        // trocar o 0 da gasosa por reserva()
    {
        n = 0;
        std::vector<int> candidatos_grasp;
        // aqui e aonde a magia do grasp acontece
        int aux_grasp=0;
        int aux_busca_grasp=0;

        while ( (aux_grasp< tamanho_grasp) && (j_escolhido != -1)) {
        j_escolhido = caminho_mais_proximo(n_city, city, caminhao[n_veic].rota[n_visita - 1], menordistancia, visitas_p_familia, visitou_p_familia);
         if (j_escolhido != -1)
             aux_grasp++;
         candidatos_grasp.push_back({j_escolhido});
        city[j_escolhido].visitada = 0; // para nao selecionar o mesmo

        }
        // selecionando a cidade randomicamente
        int escolhida;
        if (aux_grasp>0)
        escolhida= random_mersene(0,aux_grasp);

        // desocupo novamente as cidades
        for ( int ii=0;ii< aux_grasp;ii++)
            city[candidatos_grasp[ii]].visitada=-1;

        j_escolhido= candidatos_grasp[escolhida];

        ////////////////////////////////////

        // para saber se escolheu alguma cidade
        if (j_escolhido != -1) {

            caminhao[n_veic].rota.push_back({ j_escolhido });
            caminhao[n_veic].capacidade = caminhao[n_veic].capacidade - city[j_escolhido].demanda;

            visitou_p_familia[city[j_escolhido].family]++;
            city[j_escolhido].visitada = n_veic;
            n_visita++;
            custo_total = custo_total + menordistancia;
            caminhao[n_veic].custo.push_back({ menordistancia }); //

        }
        else {
            prox_cam = 1;
            n++;
            caminhao.push_back({ 0 }); //aloca outro caminhao
            n_veic++;
            caminhao[n_veic].rota.push_back({ 0 }); // prixima rota inicia na origem tbm


        }
        cond = 1;
        ////////////////////////////////////////////////////// teste de familia////////////////////////////////////////////////////
        for (int jj = 0; jj < n_family; jj++)
        {
            if (visitas_p_familia[jj] > visitou_p_familia[jj])
            {
                // anda mais
                cond = 0; // testar familias
            }



        } //if (menordistancia == 9999.0) cond = 1;
        if (j_escolhido == -1) cond = 1;
        ///////////////////////////////////////////////////////
    }


}




void caminho_inicial_aleatorio(int n_city, int n_family, int n_veic,double &custo_total, int& n_visita, std::vector<cidade>& city, std::vector<truck>& caminhao, std::vector<int>& visitou_p_familia, std::vector<int>& visitas_p_familia, std::vector<int>& cidades_cada_familia)
{

	int cond;
	
	int  n; // esse numero muda, mas o maximo de rotas � o numero maximo de veiculos
	int prox_cam; // variavel criada para auxiliar no loop quando o caminh�o n�o encheu mas n�o tem mais capacidade de nenhuma cidade
	double distancia, menordistancia;
	int j_escolhido; // auxiliar sobre a cidade escolhida com a menor distancia

	n_veic = 1; //////exemplo da sala

	caminhao.reserve(n_veic);
	cond = 0; // condicao para todas as cidades serem percorridas


	// cond � a condicao para todas as familias atendidas o numero de vezes requisitado
	// se foi ent�o cond!=0
	// demanda do caminh�o = 
	caminhao.push_back({ 0 });

	caminhao[0].rota.push_back({ 0 });
	caminhao[0].rota[0] = 0;// come�a na matriz
	city[0].visitada = 0; //come�a no caminhao 1


	n_visita = 1;
	n_veic = 0; // come�ar no inicio do vetor



	while ((cond == 0) && (caminhao[n_veic].gasolina > 0))
		// trocar o 0 da gasosa por reserva()
	{
		n = 0;
		j_escolhido = -1;

		while (j_escolhido < 0)
		{
			int i = random_mersene(1, (n_city - 1));
			if  (city[i].visitada<0)
				if (visitou_p_familia[city[i].family] < visitas_p_familia[city[i].family])
				j_escolhido = i;
		}

		
		double menordistancia = calculo_distancia(1, j_escolhido, caminhao[n_veic].rota[n_visita-1], caminhao[n_veic].rota[n_visita-1], caminhao[n_veic].rota[n_visita-1]);
        //double menordistancia = calculo_distancia(2, city[j_escolhido].x, city[j_escolhido].y, city[caminhao[n_veic].rota[n_visita-1]].x, city[caminhao[n_veic].rota[n_visita-1]].y);

		// para saber se escolheu alguma cidade
		if (j_escolhido != -1) {

			caminhao[n_veic].rota.push_back({ j_escolhido });
			caminhao[n_veic].capacidade = caminhao[n_veic].capacidade - city[j_escolhido].demanda;

			visitou_p_familia[city[j_escolhido].family]++;
			city[j_escolhido].visitada = n_veic;
			n_visita++;
			custo_total = custo_total + menordistancia;
			caminhao[n_veic].custo.push_back({ menordistancia }); //  

		}
		else {
			prox_cam = 1;
			n++;
			caminhao.push_back({ 0 }); //aloca outro caminhao
			n_veic++;
			caminhao[n_veic].rota.push_back({ 0 }); // prixima rota inicia na origem tbm


		}
		cond = 1;
		////////////////////////////////////////////////////// teste de familia////////////////////////////////////////////////////
		for (int jj = 0; jj < n_family; jj++)
		{
			if (visitas_p_familia[jj] > visitou_p_familia[jj])
			{
				// anda mais
				cond = 0; // testar familias
			}

		} //if (menordistancia == 9999.0) cond = 1; 
		if (j_escolhido == -1) cond = 1;
		///////////////////////////////////////////////////////
	}

}

double calculo_distancia(int cond, int cordx1, int cordy1, int cordx2, int cordy2)	 //indo de 1 para 2
{
	double distancia;

	// 1 para abs
	switch (cond)
	{
	    case 1: // matriz de distancias

        {
           distancia= matriz_de_distancias[cordx1].ate[cordy1]; // cordx1 e cordx2 foram usadas para passar o numero das cidades
          break;
        }

	case 2:
		distancia = sqrt(pow((cordx1 - cordx2), 2) + pow((cordy1 - cordy2), 2));
		break;



	}

	return distancia;
}

int encontra_posicao_cidade_caminhao(int cidadex, std::vector <truck> caminhao,int n_veic, std::vector<cidade>& city2)
{
	int auxiliar = 0;

	while (caminhao[n_veic].rota[auxiliar] != cidadex)
		auxiliar++;

	return auxiliar;

}

/// funcoes para perturbacao

void adicionar_cidade(int cidadeq, std::vector<cidade>& city2, std::vector <truck>& caminhao, int n_city, int n_veic, int& n_visitas)
{
	// cidadeq= cidade que quero adicionar
	//city2 � o vetor cidade auxiliar

	int cidadex, cidade_posic_caminhao, cidade_ant, cidade_prox; //criei o auxiliar s� pra poder usar a funcao vizinho mais proximo
										// ele recebe a menor distancia at� o vizinho mais proximo
	auto it = caminhao[n_veic].rota.begin(); // medo
	double tempo_ant, tempo_prox, f, auxilia;
	cidadex = vizinho_mais_proximo(n_city, city2, cidadeq, auxilia, n_veic);// cidadex � para quem ela ira adicionar - 
																				// a cidade ocupada
	cidade_posic_caminhao = encontra_posicao_cidade_caminhao(cidadex, caminhao, n_veic, city2);

	if (cidade_posic_caminhao == 0) { cidade_ant = 0; }
	else
	{
		cidade_ant = caminhao[n_veic].rota[cidade_posic_caminhao - 1];
	}

	if (cidade_posic_caminhao >= (n_visitas - 1)) {
				cidade_prox = n_visitas - 1;
	}
	else {
		cidade_prox = caminhao[n_veic].rota[cidade_posic_caminhao + 1];
	}
	int posic_x, posic_ant, posic_prox;

	if (cidade_ant >= 0) {
		if (cidade_prox >= n_city)//		1			2		3		4
		{ // s� faco com 3- ta no ultimo

			tempo_ant = tempo_adicional_cidade_ponta(city2, caminhao, cidade_ant, cidade_posic_caminhao, cidadeq); // cauda
			tempo_prox = tempo_adicional_cidade_ponta(city2, caminhao, cidade_ant,  cidadeq, cidade_posic_caminhao); // cauda
		}
		else
		{
			tempo_ant = tempo_adicional_cidade(city2, caminhao, cidade_ant, cidade_posic_caminhao, cidadeq, cidade_prox);// calcula o tempo ao adicionar a cidade antes do ponto mais proximo
			tempo_prox = tempo_adicional_cidade(city2, caminhao, cidade_ant, cidadeq, cidade_posic_caminhao, cidade_prox);// calcula o tempo ao adicionar a cidade antes do ponto mais proximo
		}
	}
	else
	{
		tempo_prox = tempo_adicional_cidade_ponta(city2, caminhao, cidadeq, cidade_posic_caminhao, cidade_prox); // cabe�a
		tempo_ant = tempo_adicional_cidade_ponta(city2, caminhao, cidade_posic_caminhao, cidadeq, cidade_prox); // cabe�a
	}

	city2[cidadeq].visitada = n_veic; // aloca a cidade
	n_visitas++;
	if (tempo_ant > tempo_prox) {

		caminhao[n_veic].rota.insert((it + cidade_posic_caminhao), cidadeq);
		
		
	}
	else
	{
		caminhao[n_veic].rota.insert((it + cidade_posic_caminhao +1), cidadeq);
	}

	
}
// retirar o maximo local
void retirar_cidade(std::vector<cidade>& cidade, std::vector<truck>& caminhao, int qual_fam, int n_veic, int quant_adicionados, int& n_visitas, int n_city)
{
//   retirar_cidade(cidades_aux,                                  caminhoes_aux, qual_fam, visitas_p_familia[rand_num1], n_veic, quant_adicionados, n_visitas, n_city);
	int maiortempo, tempo_calculado, iant, iprox, i_delete;

	while (quant_adicionados > 0)
	{
		maiortempo = -1;
		for (int i = 0; i < n_visitas; i++)
		{
			if (cidade[caminhao[n_veic].rota[i]].family == qual_fam)
			{
				if (i <= 0) iant = 0; else iant = i - 1;
				if (i >= n_visitas - 1) { iprox = n_visitas - 2; }

				else

				{
					iprox = i + 1;
				}
				tempo_calculado = tempo_triangulo(cidade, caminhao, iant, i, iprox, n_city);
				tempo_calculado= tempo_calculado- calculo_distancia(1, caminhao[0].rota[iant], caminhao[0].rota[iprox], cidade[caminhao[0].rota[iprox]].x, cidade[caminhao[0].rota[iprox]].y);
                //tempo_calculado= tempo_calculado- calculo_distancia(2, cidade[caminhao[0].rota[iant]].x, cidade[caminhao[0].rota[iant]].y, cidade[caminhao[0].rota[iprox]].x, cidade[caminhao[0].rota[iprox]].y);

                if ((tempo_calculado >= maiortempo)) {
					// familia=-1 s�o pontos que n�o podem ser alterados- fixos- origem
					i_delete = i;
					maiortempo = tempo_calculado;
				}
			}
		}
		cidade[caminhao[n_veic].rota[i_delete]].visitada = -1;
		caminhao[n_veic].rota.erase(caminhao[n_veic].rota.begin() +i_delete);// apaga do caminhao
		

		quant_adicionados--;
		n_visitas--;
	}

}


void retirar_cidade_reordenando(std::vector<cidade>& cidade, std::vector<truck>& caminhao, int qual_fam, int n_veic, int quant_adicionados, int& n_visitas, int n_city)
{
	// caminhao � o gabarito inicial,caminhoes_melhor_rota fica salvo a melhor rota,caminhoes_aux2 � auxiliar para ordenacao

	//   retirar_cidade(cidades_aux,                                  caminhoes_aux, qual_fam, visitas_p_familia[rand_num1], n_veic, quant_adicionados, n_visitas, n_city);

	int melhor_tempo, tempo_calculado, i_delete;
	while (quant_adicionados > 0)
	{
		// vetores auxiliares
		
		std::vector <truck> caminhoes_melhor_rota; // usado para guardar a melhor ordem e melhor exclusao temporaria
		//std::vector <truck> caminhoes_aux2; //usado para ordenar e testar um valor excluido
		melhor_tempo = 9999999; // tempo_total_rota(cidade, caminhao, n_visitas, n_veic);

		// gabarito para melhor rota
		for (int j = 0; j <= n_veic; j++)
		{
			caminhoes_melhor_rota.push_back({ });
			for (int i = 0; i < n_visitas; i++) // 
			{
				caminhoes_melhor_rota[n_veic].rota.push_back({ });
				caminhoes_melhor_rota[n_veic].rota[i] = caminhao[j].rota[i];

			}
		}


		/// fim da criacao dos vetores auxiliares

		for (int i = 1; i < n_visitas-1; i++) // se sao 19 visitas, vai de 1 a 18, mas n�o pego o ultimo, logo 1-17, chegou no 18 sai
		{
			if (cidade[caminhao[n_veic].rota[i]].family == qual_fam)
			{

					std::vector <truck> caminhoes_aux2;
					// copia da copia do caminhao -> aux2
					for (int j = 0; j <= n_veic; j++)
					{
						caminhoes_aux2.push_back({ });
						for (int i = 0; i < n_visitas; i++) // 
						{
							caminhoes_aux2[n_veic].rota.push_back({ });
							caminhoes_aux2[n_veic].rota[i] = caminhao[j].rota[i];

						}
					}
					// deleto o item atual para teste
					caminhoes_aux2[n_veic].rota.erase(caminhoes_aux2[n_veic].rota.begin() + i);// apaga do caminhao

					// para cada item a deletar fa�o n trocas

					for (int ww = 0; ww < 100; ww++) //para cada interacao, fa�o n trocas
					{
						troca_dentro_rota(caminhoes_aux2, n_visitas-1);// visitas -1 por que foi deletado um item do vetorrr
						//gravar_caminhao(caminhoes_aux, n_veic, "a", n_visitas, n_city, cidades_aux, "2", "b"); // coisa
						//break;
						tempo_calculado = tempo_total_rota(cidade, caminhoes_aux2, n_visitas-1, n_veic);
																	
						if( melhor_tempo > tempo_calculado)
						{

							melhor_tempo = tempo_calculado;// tempo_total_rota(cidades_aux, caminhao, n_visitas, n_veic);

							//////////////////////atualiza  vetores
						i_delete = i;
							int j = 0;
								//	caminhoes_aux[j].rota.push_back({ });
								for (int ii = 1; ii < n_visitas-1; ii++) // 
								{
									caminhoes_melhor_rota[j].rota[ii] = caminhoes_aux2[n_veic].rota[ii];
								}
							
						}

					}
			}
		}
		// atualiza de acordo com a cidade retirada



		cidade[caminhao[n_veic].rota[i_delete]].visitada = -1;

		caminhao[n_veic].rota.erase(caminhao[n_veic].rota.begin() + i_delete);// apaga do caminhao
		


	
		
		quant_adicionados--;
		n_visitas--;


		//atualiza os vetores
		for (int j = 0; j <= n_veic; j++)
		{
			//caminhoes_melhor_rota.push_back({ });
			for (int i = 0; i < n_visitas; i++) // 
			{
				caminhao[n_veic].rota[i] = caminhoes_melhor_rota[j].rota[i];

			}
		}

	}					
}


double  tempo_triangulo(std::vector<cidade> city2, std::vector<truck> caminhao, int cidade_ant, int cidade_x, int cidade_prox,int n_city)
{
    double tempo;
	tempo = 0;
	cidade_ant = caminhao[0].rota[cidade_ant];
	cidade_x = caminhao[0].rota[cidade_x];
	cidade_prox = caminhao[0].rota[cidade_prox];
	if (cidade_prox >= n_city) cidade_prox = n_city - 1;
	tempo = tempo + calculo_distancia(1, cidade_ant, cidade_x, cidade_x, cidade_x);
	tempo = tempo + calculo_distancia(1, cidade_x, cidade_prox, cidade_prox,cidade_prox);
    //tempo = tempo + calculo_distancia(2, city2[cidade_ant].x, city2[cidade_ant].y, city2[cidade_x].x, city2[cidade_x].y);
    //tempo = tempo + calculo_distancia(2, city2[cidade_x].x, city2[cidade_x].y, city2[cidade_prox].x, city2[cidade_prox].y);

    return tempo;
}

double tempo_adicional_cidade_ponta(std::vector<cidade> city2, std::vector<truck> caminhao,int cidade_1,int cidade_2,int cidade_3)
{
    double tempo;
	tempo = 0;


    tempo = tempo + calculo_distancia(1, cidade_2, cidade_3, cidade_3, cidade_3);
    tempo = tempo + calculo_distancia(1, cidade_1, cidade_2, cidade_2, cidade_2);
    //tempo = tempo + calculo_distancia(2, city2[cidade_1].x, city2[cidade_1].y, city2[cidade_2].x, city2[cidade_2].y);
    //tempo = tempo + calculo_distancia(2, city2[cidade_2].x, city2[cidade_2].y, city2[cidade_3].x, city2[cidade_3].y);



    return tempo;
}

double  tempo_adicional_cidade(std::vector<cidade> city2, std::vector<truck> caminhao,int cidade_ant,int cidadeq,int cidade_x, int cidade_prox)
{
    double tempo;
	tempo = 0;
	/*
	cidade_ant = caminhao[0].rota[cidade_ant];
	cidade_x = caminhao[0].rota[cidade_x];
	cidadeq = caminhao[0].rota[cidadeq];
	cidade_prox = caminhao[0].rota[cidade_prox];
	*/
    tempo =  tempo+ calculo_distancia(1, cidade_ant, cidadeq, cidadeq, cidadeq);
    tempo = tempo + calculo_distancia(1, cidadeq, cidade_x, cidade_x, cidade_x);
    tempo = tempo + calculo_distancia(1, cidade_x, cidade_prox, cidade_prox, cidade_prox);

//    tempo =  tempo+ calculo_distancia(2, city2[cidade_ant].x, city2[cidade_ant].y, city2[cidadeq].x, city2[cidadeq].y);
//	tempo = tempo + calculo_distancia(2, city2[cidadeq].x, city2[cidadeq].y, city2[cidade_x].x, city2[cidade_x].y);
//	tempo = tempo + calculo_distancia(2, city2[cidade_x].x, city2[cidade_x].y, city2[cidade_prox].x, city2[cidade_prox].y);

    return tempo;
}

int caminho_mais_proximo(int n_city, std::vector<cidade> city,int cidadex, double &menordistancia, vector<int>  visitas_p_familia, vector<int> visitou_p_familia)
{


	double  distancia;
	int j_escolhido;
	menordistancia = 99999999;
	j_escolhido = -1; /////// condicao para saber se encontrou alguem
	for (int i = 0; i < n_city; i++)
	{
	                    // 1 para calculo pela matriz 2 para distancia euclidiana
		//distancia = calculo_distancia(2, city[i].x, city[i].y, city[cidadex].x, city[cidadex].y,matriz_de_distancias);
        distancia = calculo_distancia(1, i,cidadex, city[cidadex].x, city[cidadex].y);
// para a distancia com matriz as coord x e y da cidade 1 foram usadas para passar o numero das cidades 1 e 2

		//distancia = 0;
		if ((distancia < menordistancia) &&( cidadex != i)&& (city[i].visitada <0)) // visitada tava maior que zero
		{
			if (visitou_p_familia [ city[i].family] < (visitas_p_familia[city[i].family])) { //criei 2 ifs para n�o ficar muito longo
				j_escolhido = i;
				menordistancia = distancia;
			}
			
		}




	}

	return j_escolhido;
}

int vizinho_mais_proximo(int n_city, std::vector<cidade> city, int cidadex, double& menordistancia,int ocupado)
{
	//ocupado � um inteiro que indica o veiculo que passa pelo ponto
	//se -1 significa que a cidade n�o foi vizitada ainda
	// uso >0 para quando quero procurar o vizinho mais proximo ja vizitado

	double  distancia;
	int j_escolhido;
	menordistancia = 99999999;
	j_escolhido = -1; /////// condicao para saber se encontrou alguem
	for (int i = 0; i < n_city; i++)
	{
        //distancia = calculo_distancia(2, city[i].x, city[i].y, city[cidadex].x, city[cidadex].y,matriz_de_distancias);
        distancia = calculo_distancia(1, i,cidadex, city[cidadex].x, city[cidadex].y);
// para a distancia com matriz as coord x e y da cidade 1 foram usadas para passar o numero das cidades 1 e 2

        //distancia = 0;
		if ((distancia < menordistancia) && (cidadex != i) && (city[i].visitada ==ocupado)) // visitada tava maior que zero
		{

			j_escolhido = i;
			menordistancia = distancia;
		}


	}

	return j_escolhido;
}

void gravar_caminhao(std::vector<truck>vetor_caminhao, int veic, string line, int n_visit, int n_city, std::vector<cidade> city, string intera,string nome_simulacao)
{
	ofstream outfile;		//criamos objeto da classe ofstream

	//outfile.open("./electro/hello/script"+nome_simulacao + intera + ".js"); //abre o arquivo descrito acima
	outfile.open("./electro/hello/script"+nome_simulacao + intera + ".js"); //abre o arquivo descrito acima

	outfile << "var N = " << n_city << ", E=" << n_visit << ";\n";
	outfile << "caminho=[] ;\n caminho = [";

	for (int j = 0; j < veic + 1; j++)
		for (int i = 0; i < n_visit; i++)
		{
			if (i != n_visit - 1)
			{
				outfile << vetor_caminhao[j].rota[i] << ",";
			}
			else {
				outfile << vetor_caminhao[0].rota[n_visit - 1] << "];\n ";
			}
}

	outfile << "var g = { nodes: [] , edges : [] }; \n ";
	
	outfile << "node_aux= []; \n";

	for (int i=0;i<n_city;i++)
		outfile <<"node_aux["<< i<< "]=["<<city[i].family<<","<< city[i].x << ","<< city[i].y<< "];\n";
		
	outfile.close();
	
}
// funcao fornaza


double random_mersene(double inicio, double fim)
{
	std::random_device rd{};

	// Use Mersenne twister engine to generate pseudo-random numbers.
	std::mt19937 engine{ rd() };

	// "Filter" MT engine's output to generate pseudo-random double values,
	// **uniformly distributed** on the closed interval [0, 1].
	// (Note that the range is [inclusive, inclusive].)
	std::uniform_real_distribution<double> dist{ inicio, fim };

	// Generate pseudo-random number.
	double x = dist(engine);
	return x;
}

int capta_quantidade_viagens(string line)
{
	ifstream infile;
	string  subline; //line	
	int numb, aa, bb,aux; //auxiliares para a leitura
	size_t found;

	infile.open(line); //abre o arquivo descrito acima
	///////////////
	if (infile.is_open()) {
		infile >> aa >> numb >> bb;
	}
// numero de viagens esta em bb

// pular ate a matriz de dist
   // getline(infile, line);
    for (int i = 0; i < numb; i++)
    { infile >> aux;}

    //getline(infile, line);
    for (int i = 0; i < numb; i++)
    { infile >> aux;}
double auxm;
    // matriz de distancia
    for (int i = 0; i < aa+1; i++)
    {

        //getline(infile, line);
        matriz_de_distancias.push_back({});

        for (int j = 0; j < aa+1; j++)
        {
            infile >> auxm;
            if (auxm<0) auxm=0;
            matriz_de_distancias[i].ate.push_back({auxm});

        }
    }



    infile.close();


	return bb; // numero de viagens
}

void ler_arquivo_cidades_fornaza(string line, int& n_city, std::vector<cidade>& city, std::vector<int>& cidades_cada_familia, std::vector<int>& visitas_p_familia, std::vector<int>& visitou_p_familia, int& n_family) //, std::vector<matriz_distancias>& matriz_d_distancias
{
	// para leitura
	ifstream infile;
	string  subline; //line	
	double numb, aa, bb; //auxiliares para a leitura
	size_t found;

		infile.open(line); //abre o arquivo descrito acima

	if (infile.is_open()) {
		//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpa buffer
		///fflush(stdin);
		infile >> n_city >> n_family >> bb;

		n_city++; // adicionando a origem
		///// tamanho das familias
		getline(infile, line);

		for (int i = 0; i < n_family; i++)
		{
			infile >> aa;
			cidades_cada_familia.push_back(aa);
		}

		/////////necessidade de cada familia
		getline(infile, line);

			for (int i = 0; i < n_family; i++)
			{
				infile>> aa;
				visitas_p_familia.push_back(aa);
				visitou_p_familia.push_back(0);
			}

		// matriz de distancia

		/*
        for (int i = 0; i < n_city; i++)
        {
            matriz_de_distancias.push_back({});

            for (int j = 0; j < n_city; j++)
            {
                infile >> bb;
                if (bb<0) bb=0;
                matriz_de_distancias[i].ate.push_back({bb});

            }
        }

*/

		while (getline(infile, line))
		{
			
			found = line.find("DISPLAY_DATA_SECTION");

			if (found != std::string::npos) {
				int qual_fam, quantos_ja_foram;
				qual_fam = 0; quantos_ja_foram = 1;

				////////////////origem
				infile >> numb >> aa >> bb;

				city.push_back(cidade(aa, bb));
				city[0].family = -1;
				///////////////////////

				for (int i = 1; i < n_city; i++)
				{

					
					if (quantos_ja_foram > cidades_cada_familia[qual_fam]) {

						qual_fam++;
						quantos_ja_foram = 1;
					}

					quantos_ja_foram++;
					infile >> numb >> aa >> bb;

					aa=(trunc(aa*100))/100;
                    bb=trunc(bb*100)/100;
					city.push_back(cidade(aa, bb));
					city[i].family = qual_fam;
				}

			}



		}

	}
	else {
		printf("nao aabriu");
	return;
	}


	//city[n_city-1].family = n_family - 1; // gambiarrinha
}



// fun��o minha le Augerat
void ler_arquivo_cidades( int& n_city, std::vector<cidade>& city, std::vector<int>& visitas_p_familia, std::vector<int>& visitou_p_familia, int& n_family)
{
	
	// para leitura
	ifstream infile;
	string line, subline;
	int numb, aa, bb; //auxiliares para a leitura
	size_t found;



		line = "Antwerp1.txt";
	
		
	
	infile.open(line); //abre o arquivo descrito acima

		if (infile.is_open()) {
			//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpa buffer
			///fflush(stdin);
			while (getline(infile, line))
			{
				found = line.find("DIMENSION ");
				if (found != std::string::npos) {
					subline = line.substr(line.find(":") + 1);
					n_city = atoi(subline.c_str());
					city.reserve(n_city);
				}

				found = line.find("NODE_COORD_SECTION");

				if (found != std::string::npos) {
					for (int i = 0; i < n_city; i++)
					{
						infile >> numb >> aa >> bb;

						city.push_back(cidade(aa, bb));
						city[i].family = numb;
					}

				}

				found = line.find("DEMAND_SECTION");
				if (found != std::string::npos) {

					for (int i = 0; i < n_city; i++)
					{
						infile >> numb >> aa;
						city[i].demanda = aa;// recebe o valor da demanda
						city[i].visitada = -1; //n�o foi visitada

					}

				}
				found = line.find("N_FAMILIA ");
				if (found != std::string::npos) {
					subline = line.substr(line.find(":") + 1);
					n_family = atoi(subline.c_str());
					visitas_p_familia.reserve(n_family);
					visitou_p_familia.reserve(n_family);

				}

				found = line.find("VISITAS_FAMILIA");
				if (found != std::string::npos) {

					for (int i = 0; i < n_family; i++)
					{
						infile >> numb >> aa;
						visitas_p_familia.push_back(aa);
						visitou_p_familia.push_back(0);
					}

				}

			}

		}
		else {
			printf("n�o aabriu");
			return;
		}


		
}


double perturbacao_familia(std::vector<cidade>& cidades, std::vector<truck>& caminhao, double& custo_total, std::vector<int> visitas_p_familia, std::vector<int>  cidades_cada_familia, int n_family, int n_city, int& n_visitas, int n_veic,int click)
{
	int quant, posic; //nfam
	int aa,n_interacoes;
    double custo_otimizado;
	int metodo_perturbacao;
	int estacionario = 0;
	cidade b;
	std::vector <cidade> cidades_aux;
	std::vector <int> adicionados;
	std::vector <truck> caminhoes_aux;
	int interacoes_perturbacao = 150;
	int reordena = 14; //(ww)
	int reordenass = 12; //(ss)->dentro de ww
	int interacoes_final;
	// local search
	for ( aa = 0; aa <= 10; aa++)
	{ // fa�o 10 vezes o local search

		local_search(cidades, caminhao, custo_total, visitas_p_familia, cidades_cada_familia, n_family, n_city, n_visitas, n_veic);
		/*
	printf("\n interacao %d  local search-> ", aa);

		for (int i = 0; i < n_visitas; i++)
			printf("%d ", caminhao[0].rota[i]);

		printf(" custo %d", custo_total);
		*/
	}

	n_interacoes = 0;
	//perturbacoes para fugir do minimo local
	for (aa = 0; aa < interacoes_perturbacao; aa++)
	{ // fa�o n vezes tudo
		n_interacoes++;
		estacionario++;
		srand(time(NULL));
		//////////////////recria os valores aux
		std::vector <cidade> cidades_aux;
		std::vector <int> adicionados;

		//criar copia cidade e veiculos na cidade_aux e caminhoes_aux
		std::vector <truck> caminhoes_aux;

		for (int jj = 0; jj < n_city; jj++)
		{
			cidades_aux.push_back({ });
			cidades_aux[jj] = cidades[jj];
		}
		for (int j = 0; j <= n_veic; j++)
		{
			caminhoes_aux.push_back({ });
			for (int jj = 0; jj < n_visitas; jj++) // 
			{
				caminhoes_aux[n_veic].rota.push_back({ });
				caminhoes_aux[n_veic].rota[jj] = caminhao[j].rota[jj];
			}
		}


		
			//				omp_set_num_threads(4);

			funcao_artigo(cidades_aux, caminhoes_aux, custo_total, visitas_p_familia, cidades_cada_familia, n_family, n_city, n_visitas, n_veic);

			custo_otimizado = tempo_total_rota(cidades_aux, caminhoes_aux, n_visitas, n_veic);

			if (custo_total > custo_otimizado)
			{
                interacoes_final=aa;
				estacionario = 0;
				custo_total = custo_otimizado;// tempo_total_rota(cidades_aux, caminhao, n_visitas, n_veic);

				//////////////////////atualiza  vetores
				for (int i = 0; i < n_city; i++)
				{
					cidades[i] = cidades_aux[i];
				}
				for (int j = 0; j <= n_veic; j++)
				{
					//caminhao[j].rota.push_back({ });
					for (int i = 0; i < n_visitas; i++) // 
					{
						caminhao[j].rota[i] = caminhoes_aux[n_veic].rota[i];
					}
				}

			}
			
			// reordena
			
			for (int ww = 0; ww < reordena; ww++)
			{
				std::vector <truck> caminhoes_aux2;
				// copia da copia do caminhao

				for (int j = 0; j <= n_veic; j++)
				{
					caminhoes_aux2.push_back({ });
					for (int i = 0; i < n_visitas; i++) // 
					{
						caminhoes_aux2[n_veic].rota.push_back({ });
						caminhoes_aux2[n_veic].rota[i] = caminhoes_aux[j].rota[i];
					}
				}

				// interacoes com a copia da copia dentro da rota
				for (int ss = 0; ss < reordenass; ss++)
				{
					troca_dentro_rota(caminhoes_aux2, n_visitas);
					custo_otimizado = tempo_total_rota(cidades_aux, caminhoes_aux2, n_visitas, n_veic);
					// testa se as novas combina��es sao boas 
					if (custo_total > custo_otimizado)
					{
                        interacoes_final=aa;
                        custo_total = custo_otimizado;// tempo_total_rota(cidades_aux, caminhao, n_visitas, n_veic);
						estacionario = 0;
						//////////////////////atualiza  vetores
						for (int j = 0; j <= n_veic; j++)
						{
							//	caminhoes_aux[j].rota.push_back({ });
							for (int i = 0; i < n_visitas; i++) // 
							{
								caminhoes_aux[j].rota[i] = caminhoes_aux2[n_veic].rota[i];
								caminhao[j].rota[i] = caminhoes_aux2[n_veic].rota[i];
							}
						}

						// tambem atualiza as cidaddes, pois estou reordenando as cidades que vieram da perturbacao
						for (int i = 0; i < n_city; i++)
						{
							cidades[i] = cidades_aux[i];
							//cidades_aux2[i]=cidades_aux[i];

						}


					}

				}
			}

			
			/*
			printf("\n interacao %d  artigo -> ", aa);

			for (int i = 0; i < n_visitas; i++)
				printf("%d ", caminhao[0].rota[i]);

			printf(" custo %d", custo_total);
			
			*/
		custo_otimizado = tempo_total_rota(cidades_aux, caminhoes_aux, n_visitas, n_veic);

		if (custo_total > custo_otimizado)
		{
            interacoes_final=aa;
			custo_total = custo_otimizado;// tempo_total_rota(cidades_aux, caminhao, n_visitas, n_veic);

			//////////////////////atualiza  vetores
			for (int i = 0; i < n_city; i++)
			{
				cidades[i] = cidades_aux[i];
			}
			for (int j = 0; j <= n_veic; j++)
			{
				caminhao[j].rota.push_back({ });
				for (int i = 0; i < n_visitas; i++) // 
				{
					caminhao[j].rota[i] = caminhoes_aux[n_veic].rota[i];
				}
			}

		}


		//////////////////////atualiza  vetores
		//printf("\n interacao %d- \n", );
	//	if (estacionario > 600) aa = 99999999999;
		if (click==3)
	 if (custo_total < 33710)
	    {
		contar_familias_vetor(caminhao, cidades_cada_familia, n_family);// quest�o de seguran�a
		aa = 9999999;
	    }
	// else interacoes_perturbacao++;
	}

	return interacoes_final;
}
//perturba��o para fugir do minimo local
void funcao_artigo(std::vector<cidade>& cidades_aux, std::vector<truck>& caminhoes_aux, double& custo_total, std::vector<int> visitas_p_familia, std::vector<int>  cidades_cada_familia, int n_family, int n_city, int& n_visitas, int n_veic)
{
	int quant_adicionados;
	int qual_fam;
	int rand_num1, rand_num2, posicao_elem_random, posicao_elem_random_fam, random_aux;
	//printf(" numeros gerados %.4f", random_mersene(0, 2));
	srand(time(NULL));
	quant_adicionados = 0;
	//qual_fam = 0; // caixeiro rand() %(n_family-1); // escolhe uma familia aleatoriament
	qual_fam =  random_mersene(0, n_family); //  rand() % (n_family);
	//qual_fam = 8;// debungin...
	rand_num1 =1+ rand() % (cidades_cada_familia[qual_fam]-1); // quantos vou adicionar da familia
	//rand_num1 = 3; //debuging...

	posicao_elem_random_fam = 1;// n� zero
	for (int nfam = 0; nfam < qual_fam; nfam++)
	{
		posicao_elem_random_fam = posicao_elem_random_fam + cidades_cada_familia[nfam];
	}
	//int adicionei[4];
	for (int k = 0; k < round(rand_num1); k++)
	{
				
		rand_num2 = random_mersene(0, (cidades_cada_familia[qual_fam] ));// //qual deles eu vou adicionar??
//		random_aux = 0;
																   //rand_num2 = 1;// debuging...
		// encontrar o membro da rand_num2� posicao na familia
		//
	
		//posicao_elem_random_fam++;
		posicao_elem_random = posicao_elem_random_fam + rand_num2; // +1 para somar o elemento origem que n�o tem familia
		//posicao_elem_random = 21;
		srand(time(NULL));
		if (cidades_aux[posicao_elem_random].visitada < 0) // ainda n�o foi alocado
		{
			//adicionei[quant_adicionados] = posicao_elem_random;
			adicionar_cidade(posicao_elem_random, cidades_aux, caminhoes_aux, n_city, n_veic, n_visitas); // posicao para adicionar o a cidade
			quant_adicionados++;
			//cidades_aux[rand_num2].visitada = n_veic;
		}

	}
	//gravar_caminhao(caminhoes_aux, n_veic, "a", n_visitas, n_city, cidades_aux, "2", "a"); // coisa
	//retirar_cidade(cidades_aux, caminhoes_aux, qual_fam, n_veic, quant_adicionados, n_visitas, n_city);

	// metodo de retirada- 0 para greedy, 1 para random
	int metodo_retirada =   random_mersene(0, 2);
	//gravar_caminhao(caminhoes_aux, n_veic, "line", n_visitas, n_city, cidades_aux, "2", "bayg29.tsp_4_1001_1002_2.txt");
	//printf("\n moed %d", metodo_retirada);
	if (metodo_retirada==0)
	retirar_cidade_reordenando(cidades_aux, caminhoes_aux, qual_fam, n_veic, quant_adicionados, n_visitas, n_city);
	else // escolhe randomicamente quem vai retira
	{
		//int exclui[20];
		for (int iii = 0; iii < quant_adicionados; iii++)
		{
			
			int elemento_retirar = -1;
			while (elemento_retirar == -1)
			{
				rand_num1 = rand() % (cidades_cada_familia[qual_fam]); // qual elemento vou retirar
				

				if ((cidades_aux[posicao_elem_random_fam + rand_num1 ].visitada > -1))
					elemento_retirar = rand_num1; // 
			}
			posicao_elem_random = posicao_elem_random_fam + elemento_retirar ; // numero da cidade
		//	posicao_elem_random = 21;

			int posicao_no_caminhao = 0;

			while (caminhoes_aux[n_veic].rota[posicao_no_caminhao] != posicao_elem_random)
				posicao_no_caminhao++;
			cidades_aux[posicao_elem_random].visitada = -1;

			//int posicao_no_caminhao = encontra_posicao_cidade_caminhao(posicao_elem_random,caminhoes_aux,0,cidades_aux);
		//	exclui[iii] = posicao_elem_random;
			caminhoes_aux[n_veic].rota.erase(caminhoes_aux[n_veic].rota.begin() + posicao_no_caminhao);// apaga do caminhao
			n_visitas--;

		}
		int posicao_no_caminhao = 0;
	}
}

void troca_dentro_rota(std::vector<truck>& caminhoes_aux, int n_visitas)
{
	int quem_troca1, quem_troca2, aux;
	int rand_num1, rand_num2, posicao_elem_random, random_aux;
	srand(time(NULL));



	int quantas_trocas = 1;// rand() % 4;
	for (int f = 0; f < quantas_trocas; f++)
	{

		quem_troca1 = random_mersene(1, (n_visitas - 1));// 1 + rand() % (n_visitas - 2); // n�o troca os cantos- vai de 1 a n-2
	quem_troca2 = random_mersene(1, (n_visitas - 1)); //1+ rand() % (n_visitas-2);
	aux = caminhoes_aux[0].rota[quem_troca1];
	caminhoes_aux[0].rota[quem_troca1] = caminhoes_aux[0].rota[quem_troca2];
	caminhoes_aux[0].rota[quem_troca2] = aux;
	}
}

void troca_fora_rota(std::vector<truck>& caminhoes_aux, int n_visitas, std::vector<cidade>& cidade_aux, int n_city)
{
	int quem_troca1, quem_troca2, aux;
	// quem_troca1 � uma cidade qualquer
	// quem_troca2 � uma cidade onde o caminhao passa
	srand(time(NULL));

	int quantas_trocas = 1;// rand() % 3;
	for (int f=0;f<quantas_trocas;f++) 
	{
			quem_troca1 = rand() % n_city;
			quem_troca2 = 1 + rand() % (n_visitas - 2); // troca 1 fora da rota troca 2 dentro da rota
						// procurando um vazio			
			int maximo = 0; // numero maximo de buscas no vetor cidades, caso a demanda seja o numero maximo- economizando parametro
			while ((cidade_aux[quem_troca1].family != cidade_aux[caminhoes_aux[0].rota[quem_troca2]].family) &&
				 (maximo<200) || (quem_troca1 == caminhoes_aux[0].rota[quem_troca2])|| (cidade_aux[quem_troca1].visitada > -1))
			{															// condicao para nao ser igual
				maximo++;
				srand(time(NULL));
				quem_troca1 = rand() % n_city;
			} 


			// procurando um ocupado
			//quem_troca2 = rand() % n_visitas; // posicao no caminhao
			if (maximo < 198) 
				{
				cidade_aux[caminhoes_aux[0].rota[quem_troca2]].visitada = -1; // deixo a cidade vazia
				cidade_aux[quem_troca1].visitada = 0;
				caminhoes_aux[0].rota[quem_troca2] = quem_troca1;
				}
	}
	//int custo_otimizado2 = tempo_total_rota(cidade_aux, caminhoes_aux, n_visitas, 0);
}
// em mudanca
void troca_fora_rota_ordenando(std::vector<truck>& caminhoes_aux, int n_visitas, std::vector<cidade>& cidade_aux, int n_city)
{
	int quem_troca1, quem_troca2, aux;
	srand(time(NULL));

	int quantas_trocas = rand() % 3;
	for (int f = 0; f < quantas_trocas; f++)
	{
		quem_troca1 = rand() % n_city;
		quem_troca2 = 1 + rand() % (n_visitas - 2); // troca 1 fora da rota troca 2 dentro da rota
					// procurando um vazio			
		int maximo = 0; // numero maximo de buscas no vetor cidades, caso a demanda seja o numero maximo- economizando parametro
		while ((cidade_aux[quem_troca1].family != cidade_aux[caminhoes_aux[0].rota[quem_troca2]].family) &&
			(cidade_aux[quem_troca1].visitada > -1) && (maximo < 200))
		{
			maximo++;
			srand(time(NULL));
			quem_troca1 = rand() % n_city;
		}


		// procurando um ocupado
		//quem_troca2 = rand() % n_visitas; // posicao no caminhao

		cidade_aux[caminhoes_aux[0].rota[quem_troca2]].visitada = -1; // deixo a cidade vazia
		cidade_aux[quem_troca1].visitada = 0;
		caminhoes_aux[0].rota[quem_troca2] = quem_troca1;
	}
}

double tempo_total_rota(std::vector<cidade> cidades, std::vector<truck> caminhao,int n_visitas,int n_veic)
{
    double tempot = 0;
	int i;

	for (i =1; i < n_visitas; i++)
	{

	    // 1 para calculo com matriz 2 para distancia euclidiana
		tempot = tempot + calculo_distancia(1, caminhao[n_veic].rota[i - 1], caminhao[n_veic].rota[i], cidades[caminhao[n_veic].rota[i]].x, cidades[caminhao[n_veic].rota[i]].y);	 //indo de 1 para 2
        //tempot = tempot + calculo_distancia(2, cidades[caminhao[n_veic].rota[i - 1]].x, cidades[caminhao[n_veic].rota[i - 1]].y, cidades[caminhao[n_veic].rota[i]].x, cidades[caminhao[n_veic].rota[i]].y);	 //indo de 1 para 2


	}
	//tempot = tempot + calculo_distancia(1, cidades[caminhao[n_veic].rota[i - 1]].x, cidades[caminhao[n_veic].rota[i - 1]].y, cidades[caminhao[n_veic].rota[0]].x, cidades[caminhao[n_veic].rota[0]].y);	 //indo de 1 para 2

	return tempot;

}
/*int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		printf(" sou a thread %d de um total de %d  soma %d\n", id, nt, kkk(id, nt));
*/

void contar_familias_vetor(std::vector<truck> caminhao, std::vector<int>  cidades_cada_familia, int n_family)
{
	std::vector<int> inicios_familias,numero_cada_familia;
	int cond = 1;
	inicios_familias.push_back({ cidades_cada_familia[0] });
	numero_cada_familia.push_back({0 });
	int i = 1;
	while (cond!= 0)
	{	
		numero_cada_familia.push_back({ 0 });
		inicios_familias.push_back({ cidades_cada_familia[i] + inicios_familias[i - 1] });
		i++;
		if (i >= n_family)cond = 0;

	}
	i = 1;
	while (caminhao[0].rota[i] != 0)
	{
		cond = 1;
		int j = 0;
		while (cond != 0)
		{
			if (caminhao[0].rota[i]<= inicios_familias[j])
			{
				cond = 0;
				numero_cada_familia[j]++;
			}
			else
			j++;
		}

		i++;
	}


	cond = 0;
}