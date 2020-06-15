//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitPrincipal.h"
#include "Clinica.h"
#include "Paciente.h"




//---------------------------------------------------------------------------
#pragma package(smart_init)


Clinica::Clinica() {
	this->qtdPacientes = 0;
}

Clinica* Clinica::clinica = new Clinica();


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

	form->atualizaGrid();
	return 1;
}