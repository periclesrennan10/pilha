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

int main() {
	FilaAlunos fila = criarFila();
	
	Aluno aluno1;
	aluno1.nome = "Pericles";
	aluno1.cpf = "987.654.321.01";
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
	aluno2.disciplinas.push_back(disciplina1);
	
	aluno1.disciplinas.push_back(disciplina1);
	
	Enqueue(fila, &aluno1);
	Enqueue(fila, &aluno2);
	
	cout << "O tamanho da fila: " << Size(fila) << endl;
	
	if (!isEmpty(fila)){
		Aluno primeiroAluno = Front(fila);
		cout << "Primeiro aluno da fila: " << primeiroAluno.nome << endl;
	}
	
	Dequeue(fila);
	
	cout << "O tamanho da fila apos a remocao: " << Size(fila) << endl;
	
	return 0;
	
}









