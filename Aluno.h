struct regAluno
{
	string matricula;
	string nome;
};

class Aluno
{
public:

	Aluno()
	{
		this->lerArquivo();
	}
	
	string obterNome(string codigo)
	{
		string n;
		
		registro.matricula=codigo;
		if ( this->procurarMatricula() )
		{
			n = tabelaAlunos[posicao].nome;
		}
		else
		{
			n = "Nao encontrado";
		}
		return n;
	}
	
	void executarCRUD()
	{
		Tela t;
		bool achou;
		string resp;
	
		this->montarTela();
		this->entrarMatricula();
		achou = this->procurarMatricula();
		
		if (not achou)
		{
			resp = t.perguntar("Matricula nao encontrada. Deseja cadastrar um novo aluno? (S/N) : ",24);
			if (resp == "S")
			{
				this->entrarDados();
				resp = t.perguntar("Deseja confirmar o cadastro? (S/N) : ",24);
				if (resp == "S")
				{
					this->tabelaAlunos.push_back(this->registro);
				}
			}
		}
		else
		{
			this->mostrarDados();
			resp = t.perguntar("Deseja alterar, excluir ou voltar? (A/E/V) : ",24);
			
			if (resp=="A")
			{
				this->entrarDados();
				resp = t.perguntar("Deseja confirmar a alteracao? (S/N) : ",24);
				if (resp=="S")
				{
					this->tabelaAlunos[this->posicao] = this->registro;
				}
			}
		
			if (resp=="E")
			{
				resp = t.perguntar("Deseja confirmar a exclusao? (S/N) : ",24);
				if (resp=="S")
				{
					this->tabelaAlunos.erase(this->tabelaAlunos.begin() + this->posicao);
				}
			}
		}
		this->gravarArquivo();
	}

private:		
	regAluno registro;
	vector<regAluno> tabelaAlunos;
	int posicao;

	void montarTela()
	{
		Tela t;
		
		t.montarMoldura(15,7,59,14,1);
		textcolor(YELLOW);
		gotoxy(16,8); cout << "Cadastro de Aluno.";
		textcolor(WHITE);
		gotoxy(16,10); cout << "Matricula : ";
		gotoxy(16,11); cout << "Nome      : ";
	}
	
	void entrarMatricula()
	{
		Tela t;
	
		t.centralizar("Informe a matricula do aluno.",24);
		gotoxy(28,10);
		getline(cin, registro.matricula);
	}
	
	bool procurarMatricula()
	{
		int x;
		bool achei = false;
		
		for (x=0; x<tabelaAlunos.size(); x++)
		{
			if (registro.matricula == tabelaAlunos[x].matricula)
			{
				achei = true;
				this->posicao = x;
				break;
			}
		}
		return achei;
	}

	void entrarDados()
	{
		Tela t;
		
		t.limparArea(28,11,58,13);
		
		t.centralizar("Informe o nome do aluno.",24);
		gotoxy(28,11); getline(cin, registro.nome);
}

	void mostrarDados()
	{
		gotoxy(28,11); cout << this->tabelaAlunos[this->posicao].nome;
	}
	
	void lerArquivo()
	{
		ifstream arquivo;
		arquivo.open("alunos.txt");
		tabelaAlunos.clear();
		while (not arquivo.eof())
		{
			getline(arquivo, registro.matricula, '|');
			getline(arquivo, registro.nome);
			
			if (registro.matricula != "")
			{
				tabelaAlunos.push_back(registro);
			}
		}
		arquivo.close();
	}

	void gravarArquivo()
	{
		ofstream arquivo;
		arquivo.open("alunos.txt");
		for (int i=0; i<tabelaAlunos.size(); i++)
		{
			arquivo << tabelaAlunos[i].matricula << "|";
			arquivo << tabelaAlunos[i].nome  	 << endl;
		}
		arquivo.close();
	}
};
