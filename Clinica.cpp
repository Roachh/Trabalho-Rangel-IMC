// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitPrincipal.h"
#include "Clinica.h"
#include "Paciente.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#include<string.h>

Clinica::Clinica() {
	this->qtdPacientes = 0;
}

Clinica* Clinica::clinica = new Clinica();

void Clinica::filtraDados(char* codigoFiltro, char* nomeFiltro,
	TFormPrincipal* form) {

	if (strlen(codigoFiltro) == 0 && strlen(nomeFiltro) == 0) {
		form->atualizaGrid(clinica->pacientes, clinica->qtdPacientes);
		return;
	}

	// Filtra por codigo todos os pacientes

	Paciente* pacientesFiltradosCodigo[1000];
	int j = 0;

	if (strlen(codigoFiltro) != 0) {
		for (int i = 0; i < clinica->qtdPacientes; i++) {
			if (clinica->pacientes[i]->codigo == stoi(codigoFiltro)) {
				pacientesFiltradosCodigo[j] = new Paciente();
				pacientesFiltradosCodigo[j] = clinica->pacientes[i];
				j++;
			}
		}
	}

	// Filtra por nome os pacientes filtrados por codigo

	Paciente* pacientesFiltrados[1000];
	int k = 0;

	if (strlen(nomeFiltro) == 0) {
		*pacientesFiltrados = *pacientesFiltradosCodigo;
		k = j;
	}

	if (strlen(nomeFiltro) != 0 && strlen(codigoFiltro) != 0) {
		for (int i = 0; i < j; i++) {
			string nome(pacientesFiltradosCodigo[i]->nome);
			if (!nome.find(nomeFiltro)) {
				pacientesFiltrados[k] = new Paciente();
				pacientesFiltrados[k] = pacientesFiltradosCodigo[i];
				k++;
			}
		}
	}

	if (strlen(nomeFiltro) != 0 && strlen(codigoFiltro) == 0) {
		for (int i = 0; i < clinica->qtdPacientes; i++) {
			string nome(clinica->pacientes[i]->nome);
			if (!nome.find(nomeFiltro)) {
				pacientesFiltrados[k] = new Paciente();
				*pacientesFiltrados[k] = *clinica->pacientes[i];
				k++;
			}
		}
	}

	form->limpaColunas();
	if (k != 0) {
		form->atualizaGrid(pacientesFiltrados, k);
	}
}

int Clinica::atualizaDados(TFormPrincipal* form) {

	Clinica* clinica = Clinica::clinica;
	FILE *salva = fopen("dados.txt", "wb");

	if (!salva) {
		return 0;
	}

	for (int i = 0; i < clinica->qtdPacientes; i++) {
		fwrite(&clinica->pacientes[i]->codigo,
			sizeof(clinica->pacientes[i]->codigo), 1, salva);
		fwrite(&clinica->pacientes[i]->nome,
			sizeof(clinica->pacientes[i]->nome) + 1, 1, salva);
		fwrite(&clinica->pacientes[i]->sexo,
			sizeof(clinica->pacientes[i]->sexo), 1, salva);
		fwrite(&clinica->pacientes[i]->dataNascimento,
			sizeof(clinica->pacientes[i]->dataNascimento) + 1, 1, salva);
		fwrite(&clinica->pacientes[i]->imc.peso,
			sizeof(clinica->pacientes[i]->imc.peso), 1, salva);
		fwrite(&clinica->pacientes[i]->imc.altura,
			sizeof(clinica->pacientes[i]->imc.altura), 1, salva);
	}

	fclose(salva);

	form->atualizaGrid(clinica->pacientes, clinica->qtdPacientes);
	return 1;
}

int Clinica::recuperaDados(TFormPrincipal* form) {

	FILE *le = fopen("dados.txt", "rb");

	if (!le) {
		return 0;
	}

	int i = 0;

	do {
		clinica->pacientes[i] = new Paciente();
		fread(&clinica->pacientes[i]->codigo,
			sizeof(clinica->pacientes[i]->codigo), 1, le);
		fread(&clinica->pacientes[i]->nome,
			sizeof(clinica->pacientes[i]->nome) + 1, 1, le);
		fread(&clinica->pacientes[i]->sexo,
			sizeof(clinica->pacientes[i]->sexo), 1, le);
		fread(&clinica->pacientes[i]->dataNascimento,
			sizeof(clinica->pacientes[i]->dataNascimento) + 1, 1, le);
		fread(&clinica->pacientes[i]->imc.peso,
			sizeof(clinica->pacientes[i]->imc.peso), 1, le);
		fread(&clinica->pacientes[i]->imc.altura,
			sizeof(clinica->pacientes[i]->imc.altura), 1, le);
		i++;
	}
	while (!feof(le));

	clinica->qtdPacientes = i - 1;
	fclose(le);
	form->atualizaGrid(clinica->pacientes, clinica->qtdPacientes);

	return 1;
}

void Clinica::addPaciente(Paciente* paciente) {

	clinica->pacientes[qtdPacientes] = paciente;
	clinica->qtdPacientes++;
}
