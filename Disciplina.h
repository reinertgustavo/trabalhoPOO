struct regDisciplina
{
	string codigo;
	string nome;
};

class Disciplina
{
public:
	Disciplina()
	{
		this->lerArquivo();
	}
	
	string obterNome(string codigo)
	{
		string n;
		registro.codigo = codigo;
		if ( this->procurarCodigo() )
		{
			n = tabelaDisciplinas[posicao].nome;
		}
		else
		{
			n = "Nao encontrada";
		}
		return n;
	}

	void executarCRUD()
	{
		Tela t;
		bool achou;
		string resp;

		this->montarTela();
		this->entrarCodigo();
		achou = this->procurarCodigo();
		
		if (not achou)
		{
			resp = t.perguntar("Disciplina nao encontrada. Deseja cadastrar uma nova disciplina? (S/N) : ",24);
			if (resp == "S")
			{
				this->entrarDados();
				resp = t.perguntar("Deseja confirmar o cadastro? (S/N) : ",24);
				if (resp == "S")
				{
					this->tabelaDisciplinas.push_back(this->registro);
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
					this->tabelaDisciplinas[this->posicao] = this->registro;
				}
			}
			
			if (resp=="E")
			{
				resp = t.perguntar("Deseja confirmar a exclusao? (S/N) : ",24);
				if (resp=="S")
				{
					this->tabelaDisciplinas.erase(this->tabelaDisciplinas.begin() + this->posicao);
				}
			}
		}
		this->gravarArquivo();
	}
  
private:
	regDisciplina registro;
	vector<regDisciplina> tabelaDisciplinas;
	int posicao;
	
	void montarTela()
	{
		Tela t;
		
		t.montarMoldura(15,7,59,14,1);
		textcolor(YELLOW);
		gotoxy(16,8); cout << "Cadastro de Disciplina.";
		textcolor(WHITE);
		gotoxy(16,10); cout << "Codigo    : ";
		gotoxy(16,11); cout << "Nome      : ";
	}
	
	void entrarCodigo()
	{
		Tela t;
		
		t.centralizar("Informe o codigo da disciplina.",24);
		gotoxy(28,10);
		getline(cin, registro.codigo);
	}
	
	bool procurarCodigo()
	{
		int x;
		bool achei = false;
		
		for (x=0; x<tabelaDisciplinas.size(); x++)
		{
			if (registro.codigo == tabelaDisciplinas[x].codigo)
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
		
		t.centralizar("Informe o nome da disciplina.",24);
		gotoxy(28,11); getline(cin, registro.nome);
	}
	
	void mostrarDados()
	{
		gotoxy(28,11); cout << this->tabelaDisciplinas[this->posicao].nome;
	}
	
	void lerArquivo()
	{
		ifstream arquivo;
		arquivo.open("disciplinas.txt");
		tabelaDisciplinas.clear();
		while (not arquivo.eof())
		{
			getline(arquivo, registro.codigo, '|');
			getline(arquivo, registro.nome);
			
			if (registro.codigo != "")
			{
				tabelaDisciplinas.push_back(registro);
			}
		}
		arquivo.close();
	}
	
	void gravarArquivo()
	{
		ofstream arquivo;
		arquivo.open("disciplinas.txt");
		for (int i=0; i<tabelaDisciplinas.size(); i++)
		{
			arquivo << tabelaDisciplinas[i].codigo << "|";
			arquivo << tabelaDisciplinas[i].nome << endl;
		}
		arquivo.close();
	}
};
