#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Disciplina {
	string nome;
	int qntCreditos;
	list<string> conteudo;
};

struct Aluno {
	string nome;
	string cpf;
	int idade;
	string matricula;
	list<Disciplina> disciplinas;
};

struct No {
	Aluno aluno;
	No *next;
};

struct FilaAlunos {
	No *primeiro;
	No *ultimo;
};

FilaAlunos criarFila() {
	FilaAlunos fila;
	fila.primeiro = NULL;
	fila.ultimo = NULL;
	return fila;
}

void Enqueue (FilaAlunos &fila, Aluno *aluno){
	No *novoNo = new No{*aluno, NULL};
	if (fila.primeiro == NULL){
		fila.primeiro = novoNo;
		fila.ultimo = novoNo;
	}else {
		fila.ultimo->next = novoNo;
		fila.ultimo = novoNo;
	}
}

void Dequeue (FilaAlunos &fila){
	if (fila.primeiro == NULL){
		cout << "A fila esta vazia, nao eh possivel remover." << endl;
		return;
	}
	No *temp = fila.primeiro;
	fila.primeiro = fila.primeiro->next;
	delete temp;
}

bool isEmpty (const FilaAlunos &fila){
	return fila.primeiro == NULL;
}

Aluno Front (const FilaAlunos &fila){
	if (fila.primeiro != NULL){
		return fila.primeiro->aluno;
	}else {
		cout << "A fila esta vazia." << endl;
		return Aluno(); 
	}
}

int Size (const FilaAlunos &fila) {
	int tamanho = 0;
	No *atual = fila.primeiro;
	while (atual != NULL){
		tamanho++;
		atual = atual->next;
	}
	return tamanho;
}

void adicionarDisciplina (Aluno &aluno, Disciplina &disciplina){
	aluno.disciplinas.push_back(disciplina);
}

void removerDisciplina(Aluno &aluno, const string &nomeDisciplina) {
    list<Disciplina>::iterator it = aluno.disciplinas.begin();
    while (it != aluno.disciplinas.end()) {
        if (it->nome == nomeDisciplina) {
            it = aluno.disciplinas.erase(it);
            cout << "Disciplina " << nomeDisciplina << " removida" << endl;
            return; 
        } else {
            ++it;
        }
    }
    
    cout << "Disciplina nao encontrada: " << nomeDisciplina << endl;
}

void listarDisciplinas(Aluno &aluno){
	if(aluno.disciplinas.empty()){
		cout << "O aluno nao esta matriculado em nenhuma disciplina" << endl;
		return;
	}
	cout << "-----------------------------------------------" << endl; 
	cout << "Disciplinas do aluno: " << aluno.nome << endl;
	for (list<Disciplina>::iterator it = aluno.disciplinas.begin(); it != aluno.disciplinas.end(); ++it) {
        const Disciplina& disciplina = *it;
        cout << "Nome: " << disciplina.nome << endl;
	}
	
	cout << "-----------------------------------------------" << endl;
}

void adicionarConteudo(Disciplina &disciplina, const string &novoConteudo){
	disciplina.conteudo.push_back(novoConteudo);
}

void removerConteudo(Disciplina &disciplina, const string conteudo){
	disciplina.conteudo.remove(conteudo);
}

void listarConteudo(const Disciplina &disciplina){
	cout << "Conteudos da disciplina " << disciplina.nome << ":" << endl;
	list<string>::const_iterator it = disciplina.conteudo.begin();
	while (it != disciplina.conteudo.end()){
		cout << "- " << *it << endl;
		++it;
	}
}

void listarAlunos(const FilaAlunos &fila) {
	cout << "---------------------------------------" << endl;
    No *atualAluno = fila.primeiro;
    
    while (atualAluno != NULL) {
        Aluno aluno = atualAluno->aluno;
        
        cout << "Nome do aluno: " << aluno.nome << endl;
        cout << "CPF: " << aluno.cpf << endl;
        cout << "Idade: " << aluno.idade << endl;
        cout << "Matricula: " << aluno.matricula << endl;
        
        list<Disciplina>::iterator itDisciplina = aluno.disciplinas.begin();
        
        while(itDisciplina != aluno.disciplinas.end()){
        	Disciplina disciplina = *itDisciplina;
        	cout << "Disciplina: " << disciplina.nome << endl;
        	cout << "Creditos: " << disciplina.qntCreditos << endl;
        	
        	list<string>::iterator itConteudo = disciplina.conteudo.begin();
        	
        	while (itConteudo != disciplina.conteudo.end()){
        		cout << "Conteudo: " << *itConteudo << endl;
        		++itConteudo;
			}
			++itDisciplina;
		}
		atualAluno = atualAluno->next;
		cout << "---------------------------------------" << endl;
    }
}




int main() {
	FilaAlunos fila = criarFila();
	
	Aluno aluno1;
	aluno1.nome = "Pericles";
	aluno1.cpf = "065.330.163-42";
	aluno1.idade = 20;
	aluno1.matricula = "123456";
	
	Disciplina disciplina1;
	disciplina1.nome = "Estrutura de Dados";
	disciplina1.qntCreditos = 8;
	disciplina1.conteudo.push_back("Pilha");
	
	Aluno aluno2;
	aluno2.nome = "Pablo";
	aluno2.cpf = "123.456.789-10";
	aluno2.idade = 18;
	aluno2.matricula = "789456123";
	
	Disciplina disciplina2;
	disciplina2.nome = "Banco de Dados";
	disciplina2.qntCreditos = 4;
	disciplina2.conteudo.push_back("Modelo logico");
	
	Aluno aluno3;
	aluno3.nome = "Rennan";
	aluno3.cpf = "456.123.789-05";
	aluno3.idade = 22;
	aluno3.matricula = "1148435";
	
	adicionarDisciplina(aluno1, disciplina1);
	adicionarDisciplina(aluno1, disciplina2);
	adicionarDisciplina(aluno3, disciplina1);
	
	adicionarDisciplina(aluno2, disciplina2);
	
	adicionarConteudo(disciplina1, "fila");
	removerConteudo(disciplina1, "Pilha");
	
	Enqueue(fila, &aluno1);
	Enqueue(fila, &aluno2);
	Enqueue(fila, &aluno3);
	
	cout << "O tamanho da fila: " << Size(fila) << endl;
	
	if (!isEmpty(fila)){
		Aluno primeiroAluno = Front(fila);
		cout << "Primeiro aluno da fila: " << primeiroAluno.nome << endl;
	}
	
	Dequeue(fila);
	
	cout << "O tamanho da fila apos a remocao: " << Size(fila) << endl;
	
	listarDisciplinas(aluno1);
	
	removerDisciplina(aluno1, "Estrutura de Dados");
	
	listarDisciplinas(aluno1);
	
	listarConteudo(disciplina1);
	
	listarAlunos(fila);
	
	return 0;
	
}
