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

void TFormPrincipal::limpaColunas() {

	for (int i = 0; i < Clinica::clinica->qtdPacientes; i++) {
		this->StringGrid1->Cells[0][i] = "";
		this->StringGrid1->Cells[1][i] = "";
		this->StringGrid1->Cells[2][i] = "";
		this->StringGrid1->Cells[3][i] = "";
		this->StringGrid1->Cells[4][i] = "";
		this->StringGrid1->Cells[5][i] = "";
		this->StringGrid1->Cells[6][i] = "";
	}
}

int TFormPrincipal::atualizaGrid(Paciente* pacientes[1000], int qtdPacientes) {

	for (int i = 0; i < qtdPacientes; i++) {
		StringGrid1->Cells[0][i] = pacientes[i]->codigo;
		StringGrid1->Cells[1][i] = pacientes[i]->nome;
		StringGrid1->Cells[2][i] = pacientes[i]->sexo;
		StringGrid1->Cells[3][i] = pacientes[i]->dataNascimento;
		StringGrid1->Cells[4][i] = pacientes[i]->imc.peso;
		StringGrid1->Cells[5][i] = pacientes[i]->imc.altura;
		StringGrid1->Cells[6][i] = pacientes[i]->imc.calculaIMC();
	}
	return 0;
}

__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner) : TForm(Owner) {

	Clinica::clinica->recuperaDados(this);
}

// ---------------------------------------------------------------------------

void __fastcall TFormPrincipal::btnCadastrarClick(TObject *Sender) {

	Paciente* paciente = new Paciente();
	TFormCadastro *form = new TFormCadastro(paciente, this);
	form->ShowModal();

	if (form->usuarioRegistrou) {
		Clinica::clinica->addPaciente(paciente);
		Clinica::clinica->atualizaDados(this);
	}

	delete form;
}

// ---------------------------------------------------------------------------

void __fastcall TFormPrincipal::Edit2KeyUp(TObject *Sender, WORD &Key,
	System::WideChar &KeyChar, TShiftState Shift) {

	filtraGrid();
}

void __fastcall TFormPrincipal::Edit1KeyUp(TObject *Sender, WORD &Key,
	System::WideChar &KeyChar, TShiftState Shift) {

	filtraGrid();
}
// ---------------------------------------------------------------------------

void TFormPrincipal::filtraGrid() {

	// unicode string para wchar
	wchar_t* wcharCodigo = this->Edit1->Text.c_str();
	wchar_t* wcharNome = this->Edit2->Text.c_str();

	if(wcharCodigo == 0 && wcharNome == 0) {
        return;
    }

	// wchar para char
	char codigoFiltro[10];
	char nomeFiltro[15];
	wcstombs(codigoFiltro, wcharCodigo, sizeof(codigoFiltro));
	wcstombs(nomeFiltro, wcharNome, sizeof(nomeFiltro));

	Clinica::clinica->filtraDados(codigoFiltro, nomeFiltro, this);
}

// ---------------------------------------------------------------------------
