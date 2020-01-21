#pragma once
struct lista {
    lista *ant,*prox;
    int valor;

};

void local_search(std::vector<cidade>& cidades, std::vector<truck>& caminhao, double& custo_total, std::vector<int> visitas_p_familia, std::vector<int>  cidades_cada_familia, int n_family, int n_city, int n_visitas, int n_veic)
{
	///quantidade de interacoes to local search
	int quant_n0, quant_n1, quant_tudo;
	quant_tudo = 4000; // nao faz nada mesmo
	quant_n0 = 100;
	quant_n1 = 100;


    double custo_otimizado=custo_total;
	//////////////////recria os valores aux
	std::vector <cidade> cidades_aux;

	//criar copia cidade e veiculos na cidade_aux e caminhoes_aux
	std::vector <truck> caminhoes_aux;


	for (int jj = 0; jj < n_city; jj++)
	{
		cidades_aux.push_back({ });
		cidades_aux[jj] = cidades[jj];
	}

		// search N1(s) and obtain s*
		for (int i = 0; i < quant_n0;i++)
		{
			// recria o caminh�o
			for (int j = 0; j <= n_veic; j++)
			{
				caminhoes_aux.push_back({ });
				for (int jj = 0; jj < n_visitas; jj++) // 
				{
					caminhoes_aux[n_veic].rota.push_back({ });
					caminhoes_aux[n_veic].rota[jj] = caminhao[j].rota[jj];
				}
			}

			troca_dentro_rota(caminhoes_aux, n_visitas);
			//gravar_caminhao(caminhoes_aux, n_veic, "line", n_visitas, n_city, cidades_aux, "2", "bayg29.tsp_4_1001_1001_2.txt");
			// testa e atualiza
			custo_otimizado = tempo_total_rota(cidades_aux, caminhoes_aux, n_visitas, n_veic);
			if (custo_total > custo_otimizado)
			{

				for (int i = 0; i < n_city; i++)
				{
					cidades[i] = cidades_aux[i];
				}

				custo_total = custo_otimizado;// tempo_total_rota(cidades_aux, caminhao, n_visitas, n_veic);
				//////////////////////atualiza  vetores
				for (int j = 0; j <= n_veic; j++)
				{
					caminhao[j].rota.push_back({ });
					for (int i = 0; i < n_visitas; i++) // 
					{
						caminhao[j].rota[i] = caminhoes_aux[n_veic].rota[i];
					}
				}

			}

		}

		// search N0(s*) and obtain s**
		for (int i = 0; i < quant_n1; i++)
		{
			// recria o caminh�o
			for (int j = 0; j <= n_veic; j++)
			{
				caminhoes_aux.push_back({ });
				for (int jj = 0; jj < n_visitas; jj++) // 
				{
					caminhoes_aux[n_veic].rota.push_back({ });
					caminhoes_aux[n_veic].rota[jj] = caminhao[j].rota[jj];
				}
			}
			// recria as cidades
			for (int jj = 0; jj < n_city; jj++)
			{
				cidades_aux.push_back({ });
				cidades_aux[jj] = cidades[jj];
			}

			troca_fora_rota(caminhoes_aux, n_visitas, cidades_aux, n_city);
			// testa e atualiza
			custo_otimizado = tempo_total_rota(cidades_aux, caminhoes_aux, n_visitas, n_veic);
			if (custo_total > custo_otimizado)
			{
				custo_total = custo_otimizado;// tempo_total_rota(cidades_aux, caminhao, n_visitas, n_veic);
				/////////////////////atualiza  vetores
				for (int j = 0; j <= n_veic; j++)
				{
					caminhao[j].rota.push_back({ });
					for (int i = 0; i < n_visitas; i++) // 
					{
						caminhao[j].rota[i] = caminhoes_aux[n_veic].rota[i];
					}
				}
				for (int i = 0; i < n_city; i++)
				{
					cidades[i] = cidades_aux[i];
				}

			}

		}

		// search N1(s**) and obtain s***
		for (int i = 0; i < quant_n0; i++)
		{
			// recria o caminh�o
			for (int j = 0; j <= n_veic; j++)
			{
				caminhoes_aux.push_back({ });
				for (int jj = 0; jj < n_visitas; jj++) // 
				{
					caminhoes_aux[n_veic].rota.push_back({ });
					caminhoes_aux[n_veic].rota[jj] = caminhao[j].rota[jj];
				}
			}

			troca_dentro_rota(caminhoes_aux, n_visitas);
			// testa e atualiza
			custo_otimizado = tempo_total_rota(cidades_aux, caminhoes_aux, n_visitas, n_veic);
			if (custo_total > custo_otimizado)
			{

				custo_total = custo_otimizado;// tempo_total_rota(cidades_aux, caminhao, n_visitas, n_veic);

				//////////////////////atualiza  vetores
				for (int j = 0; j <= n_veic; j++)
				{
					caminhao[j].rota.push_back({ });
					for (int i = 0; i < n_visitas; i++) // 
					{
						caminhao[j].rota[i] = caminhoes_aux[n_veic].rota[i];
					}
				}

			}

		}




}


void dois_opt(int n_city, int n_family, int n_veic, double & custo_total, int& n_visita, std::vector<cidade>& city, std::vector<truck> &caminhao, std::vector<int>& visitou_p_familia, std::vector<int>& visitas_p_familia, std::vector<int>& cidades_cada_familia )
// � completo por que faz com todos os pontos, a outra funcao acha apenas o ponto mais proximo
{
    int tamanho_grasp = 1; ///////////////tamanho da lista do grasp
    int cond;
    int n; // esse numero muda, mas o maximo de rotas � o numero maximo de veiculos
    int prox_cam; // variavel criada para auxiliar no loop quando o caminh�o n�o encheu mas n�o tem mais capacidade de nenhuma cidade
    double distancia, menordistancia;
    int j_escolhido; // auxiliar sobre a cidade escolhida com a menor distancia

    // para comparar

    n_veic = 1; //////exemplo da sala

    caminhao.reserve(n_veic);
    cond = 0; // condicao para todas as cidades serem percorridas


    // cond � a condicao para todas as familias atendidas o numero de vezes requisitado
    // se foi ent�o cond!=0
    // demanda do caminh�o =
    caminhao.push_back({0});

    caminhao[0].rota.push_back({0});
    caminhao[0].rota[0] = 0;// come�a na matriz
    city[0].visitada = 0; //come�a no caminhao 1


    // rota base
    lista *ptr_inibase = (lista *) malloc(sizeof(lista));
    lista *head_base;

    ptr_inibase->valor=0;
    head_base=ptr_inibase;
    ptr_inibase->prox=NULL;
    ptr_inibase->ant=NULL;

    // rota que entra para modificacoes
    lista *ptr = (lista *) malloc(sizeof(lista));;
    lista *ptrini;// = (lista*) malloc(sizeof(lista));
    lista *ptraloc;//
    lista *aux ;
    lista *aux2 = ptr;
    lista *head,*head_aux;

    ptr->valor = 0;
    ptr->ant = NULL;
    ptr->prox = NULL;
    ptrini = ptr;
    ptrini->ant = NULL;
    ptrini->prox = NULL;

    // rota salva temporariamente como melhor
    lista *ptr_melhor = (lista *) malloc(sizeof(lista));
    lista *ptrini_melhor;// = (lista*) malloc(sizeof(lista));
    lista *aux_melhor = (lista *) malloc(sizeof(lista));
    lista *head_melhor;


    n_visita = 1;
    n_veic = 0; // come�ar no inicio do vetor

//n_visita >=4 jaa é possivel realizar o 2opt

    ptr->valor=head_base->valor;
    //free(ptr_melhor);

    while ((cond == 0) && (caminhao[n_veic].gasolina > 0) ) //&& (n_visita < 15)
        // trocar o 0 da gasosa por reserva()
    {

        if (n_visita<5){

            j_escolhido = caminho_mais_proximo(n_city, city, caminhao[n_veic].rota[n_visita - 1], menordistancia, visitas_p_familia, visitou_p_familia);
       city[j_escolhido].visitada=0;
       visitou_p_familia[city[j_escolhido].family]++;
       ptraloc=(lista *) malloc(sizeof(lista));
       ptr=head_base; // aponta para o pai
            aux2=ptr;
       ptr->prox=ptraloc;
       ptr=ptraloc;
       ptr->valor=j_escolhido;
       ptr->prox=NULL;
       ptr->ant=aux2;
       head_base=ptr;

       caminhao[0].rota.push_back({j_escolhido});
    n_visita++;
        }
        else
         {

            j_escolhido = -1;
            // zerando o vetor que vai fazer as alteracoes e a melhor

            n = 0;
            menordistancia = 9999999;
            for (int ii = 1; ii < n_city; ii++) {

                if ((city[ii].visitada < 0) &&
                    (visitou_p_familia[city[ii].family] < visitas_p_familia[city[ii].family])) {
                    // gerando copia para modificacoes
                    // copia da base

                    ptr = (lista *) malloc(sizeof(lista));
                    ptr->valor = ptr_inibase->valor;
                    ptrini = ptr; // inicio
                    ptr->ant = NULL;
                    ptr->prox = NULL;

                    aux = ptr_inibase->prox;
                    // copia da base- ptr e aux2 na cabeça
                    while (aux != NULL) {
                        aux2 = ptr; // salva o anterior
                        ptraloc = (lista *) malloc(sizeof(lista));
                        ptr->prox = ptraloc;
                        ptr = ptraloc;
                        ptr->ant = aux2;
                        ptr->valor = aux->valor;
                        ptr->prox = NULL;
                        aux = aux->prox;
                        aux2 = ptr;
                    }

                    // fim da copia da base

                    // adiciona o no em questao
                    ptraloc = (lista *) malloc(sizeof(lista));
                    ptr->prox = ptraloc;
                    ptr = ptraloc;
                    ptr->ant = aux2;
                    ptr->valor = ii;
                    ptr->prox = NULL;
                    head_aux = ptr;
                    lista *p;
                    for (p = ptrini; p != NULL; p = p->prox)
                        printf("info = %d\n", p->valor);
                    // scanf("%d",&n_visita);
                    /////entra no 2opt

                    // onde a magia do 2opt acontece
                    // para a distancia com matriz as coord x e y da cidade 1 foram usadas para passar o numero das cidades 1 e 2

                    lista *p1, *p2, *p3, *p4, *auxpos;
                    // p3 e p4 é a barra a ser adicionada

                    p1 = ptrini;
                    p2 = ptrini->prox;
                    p3 = head_aux->ant;
                    p4 = head_aux;

                    while ((p2 != p3) ) {  //&& (p2->valor != 0) && (p3->valor != 0)
                        double soma1, soma2;
                        soma1 = calculo_distancia(1, p1->valor, p2->valor, 0, 0);
                        soma1 = soma1 + calculo_distancia(1, p3->valor, p4->valor, 0, 0);
                        // modificado
                        soma2 = calculo_distancia(1, p1->valor, p3->valor, 0, 0);
                        soma2 = soma2 + calculo_distancia(1, p2->valor, p4->valor, 0, 0);

                        if (soma2 < soma1) // muda
                        {
                            p1->prox = p3;
                            auxpos = p1;
                            p1 = p3;

                            while ((p1 != p2) ) { //&& (p1->valor != 0) && (p1->valor != 0)

                                p1->prox = p1->ant;
                                p1->ant = auxpos;
                                auxpos = p1;
                                p1 = p1->prox;

                            }
                            p1->ant = auxpos;
                            p2->prox = p4;


                            // reseta o vetor
                            p1 = ptrini;
                            p2 = ptrini->prox;
                            p3 = head_aux->ant;
                            p4 = head_aux;

                            // preciso retirar isso, gambiarra para atualizar vetor que nem precisaria existir!!!!
                            int pp = 0;
                            for (p = ptrini; p != NULL; p = p->prox) {
                                caminhao[0].rota[pp] = p->valor;
                                pp++;
                            }


                            // gravar_caminhao(caminhao, n_veic, "do", n_visita, n_city, city, "1", "doisoptmodif");
                            //
                        } else {
                            if (p2->prox != p3) {
                                p1 = p2;
                                p2 = p2->prox;
                            } else {
                                p1 = ptrini;
                                p2 = ptrini->prox;
                                p4 = p3->ant;
                                p3 = p3->ant;

                            }
                        }
                    }
                    distancia = 0;
                    for (p = ptrini; p != NULL; p = p->prox)
                        distancia = distancia + p->valor;

                    if (distancia < menordistancia) {
                        j_escolhido = ii;
                        ptrini_melhor = ptrini;
                        menordistancia = distancia;
                    }
                }

                /*
                if (j_escolhido != -1) {
                    ptr_inibase = ptrini_melhor;
                    city[j_escolhido].visitada = 0;
                    visitou_p_familia[city[j_escolhido].family]++;

                    caminhao[0].rota.push_back({0});
                    n_visita++;

                    // atualizando o caminhao
                    lista *p;
                    int f = 0;
                    for (p = ptrini; p != NULL; p = p->prox) {
                        caminhao[0].rota[f] = p->valor;
                        f++;
                    }
                }
                */
            } // fim do for de todas as cidades

            if (j_escolhido != -1)
             {
                ptr_inibase = ptrini_melhor;
                city[j_escolhido].visitada = 0;
                visitou_p_familia[city[j_escolhido].family]++;

                caminhao[0].rota.push_back({0});
               // n_visita++;

                // atualizando o caminhao
                lista *p;
                int f = 0;
                for (p = ptrini; p != NULL; p = p->prox) {
                    caminhao[0].rota[f] = p->valor;
                    f++;
                }
             }

            // salva na base

            city[j_escolhido].visitada=0;
            visitou_p_familia[city[j_escolhido].family]++;
            ptraloc=(lista *) malloc(sizeof(lista));
            ptr->prox=ptraloc;
            ptr=ptraloc;
            ptr->valor=j_escolhido;
            ptr->prox=NULL;
            ptr->ant=aux2;
            aux2=ptr;
            caminhao[0].rota.push_back({j_escolhido});
            n_visita++;
            // fim de salvar na base


            cond = 1;
            ////////////////////////////////////////////////////// teste de familia////////////////////////////////////////////////////
            for (int jj = 0; jj < n_family; jj++) {
                if (visitas_p_familia[jj] > visitou_p_familia[jj]) {
                    // anda mais
                    cond = 0; // testar familias
                }


            } //if (menordistancia == 9999.0) cond = 1;
            if (j_escolhido == -1) cond = 1;
            ///////////////////////////////////////////////////////
        }
    }

   // gravar_caminhao(caminhao, n_veic, "do", n_visita, n_city, city, "1", "doisopt");


/*
lista *p;
    printf("\napos\n");
    for (p = ptrini; p != NULL; p = p->prox)
        printf("info = %d\n", p->valor);
  */

    //scanf("%d", &n_visita);



/*

    while ((cond == 0) && (caminhao[n_veic].gasolina > 0))
// trocar o 0 da gasosa por reserva()
{
n = 0;

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
*/
double custo_tt=0;
    lista *p;
    printf("\ndentro");
    for (p = ptr_inibase; p->prox != NULL; p = p->prox)
        custo_tt=custo_tt+calculo_distancia(1, p->valor, p->prox->valor, 0, 0);
        printf("%.f\n\n",custo_tt );


}


