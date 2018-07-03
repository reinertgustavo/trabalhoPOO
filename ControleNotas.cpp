#include <iostream>
#include <string>
#include <vector>
#include <conio2.h>
#include <fstream>

using namespace std;

#include "Tela.h"
#include "Aluno.h"
#include "Disciplina.h"
#include "Nota.h"

main()
{
	Tela tela;
	Aluno alunos;
	Disciplina disciplinas;
	Nota notas;

	notas.definirPonteiros(&alunos, &disciplinas);

	string opcao;
	vector<string> opcoes;
	
	opcoes.push_back("1 - Alunos     ");
	opcoes.push_back("2 - Disciplinas");
	opcoes.push_back("3 - Notas      ");
	opcoes.push_back("4 - Boletim    ");
	opcoes.push_back("0 - Sair       ");
	
	while (true)	
	{
		textcolor(WHITE);
		clrscr();

		tela.montarMoldura(1,23,80,25,0);

		tela.montarMoldura(1,1,80,3,0);
		tela.centralizar("Controle de Notas",2);
		
		opcao = tela.mostrarMenuBarras(5,5,opcoes);
		
		if (opcao=="1") alunos.executarCRUD();
		if (opcao=="2") disciplinas.executarCRUD();
		if (opcao=="3") notas.executarCRUD();
		if (opcao=="4") notas.emitirBoletim();
		if (opcao=="0") break;
	}
}
