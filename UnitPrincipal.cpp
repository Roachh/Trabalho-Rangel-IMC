// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "UnitPrincipal.h"
#include "UnitCadastro.h"
#include "Paciente.h"
#include "Clinica.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

#include <stdio.h>
using namespace std;

TFormPrincipal *FormPrincipal;

// ---------------------------------------------------------------------------

int TFormPrincipal::atualizaGrid() {

	FILE *le = fopen("dados.txt", "rb");

    //Paciente* pacientes[1000];

	if (!le) {
		return 0;
	}



	int i = 0;

	do {
		Clinica::clinica->pacientes[i] = new Paciente();
		fread(&Clinica::clinica->pacientes[i]->codigo,
			sizeof(Clinica::clinica->pacientes[i]->codigo), 1, le);
		fread(&Clinica::clinica->pacientes[i]->nome,
			sizeof(Clinica::clinica->pacientes[i]->nome) + 1, 1, le);
		fread(&Clinica::clinica->pacientes[i]->sexo,
			sizeof(Clinica::clinica->pacientes[i]->sexo), 1, le);
		fread(&Clinica::clinica->pacientes[i]->dataNascimento,
			sizeof(Clinica::clinica->pacientes[i]->dataNascimento) + 1, 1, le);
		fread(&Clinica::clinica->pacientes[i]->imc.peso,
			sizeof(Clinica::clinica->pacientes[i]->imc.peso), 1, le);
		fread(&Clinica::clinica->pacientes[i]->imc.altura,
			sizeof(Clinica::clinica->pacientes[i]->imc.altura), 1, le);
		i++;
	}
	while (!feof(le));

	Clinica::clinica->qtdPacientes = i - 1;

	for (i = 0; i < Clinica::clinica->qtdPacientes; i++) {
		StringGrid1->Cells[0][i] = Clinica::clinica->pacientes[i]->codigo;
		StringGrid1->Cells[1][i] = Clinica::clinica->pacientes[i]->nome;
		StringGrid1->Cells[2][i] = Clinica::clinica->pacientes[i]->sexo;
		StringGrid1->Cells[3][i] = Clinica::clinica->pacientes[i]->dataNascimento;
		StringGrid1->Cells[4][i] = Clinica::clinica->pacientes[i]->imc.peso;
		StringGrid1->Cells[5][i] = Clinica::clinica->pacientes[i]->imc.altura;
		StringGrid1->Cells[6][i] = Clinica::clinica->pacientes[i]->imc.calculaIMC();
	}

	fclose(le);
	return 0;
}


__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner) : TForm(Owner) {

	this->atualizaGrid();
}



// ---------------------------------------------------------------------------

void __fastcall TFormPrincipal::btnCadastrarClick(TObject *Sender) {
	Paciente* paciente = new Paciente();
	TFormCadastro *form = new TFormCadastro(paciente, this);
	form->ShowModal();

	if (form->usuarioRegistrou) {
		Clinica::clinica->atualizaDados(this);
	}

	delete form;

}
