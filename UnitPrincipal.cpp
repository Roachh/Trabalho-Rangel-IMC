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
#include <string>
using namespace std;

TFormPrincipal *FormPrincipal;

// ---------------------------------------------------------------------------

void TFormPrincipal::limpaColunas() {

	for (int i = 0; i < Clinica::clinica->qtdPacientes; i++) {
		this->StringGridRegistros->Cells[0][i] = "";
		this->StringGridRegistros->Cells[1][i] = "";
		this->StringGridRegistros->Cells[2][i] = "";
		this->StringGridRegistros->Cells[3][i] = "";
		this->StringGridRegistros->Cells[4][i] = "";
		this->StringGridRegistros->Cells[5][i] = "";
		this->StringGridRegistros->Cells[6][i] = "";
		this->StringGridRegistros->Cells[7][i] = "";
	}
}

int TFormPrincipal::atualizaGrid(Paciente* pacientes[1000], int qtdPacientes) {

	for (int i = 0; i < qtdPacientes; i++) {
		StringGridRegistros->Cells[0][i] = pacientes[i]->codigo;
		StringGridRegistros->Cells[1][i] = pacientes[i]->nome;
		StringGridRegistros->Cells[2][i] = pacientes[i]->sexo;
		StringGridRegistros->Cells[3][i] = pacientes[i]->dataNascimento;
		StringGridRegistros->Cells[4][i] = pacientes[i]->imc.peso;
		StringGridRegistros->Cells[5][i] = pacientes[i]->imc.altura;
		StringGridRegistros->Cells[6][i] = pacientes[i]->imc.calculaIMC();
		StringGridRegistros->Cells[7][i] = pacientes[i]->imc.diagnostico();
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

void __fastcall TFormPrincipal::EditNomeKeyUp(TObject *Sender, WORD &Key,
	System::WideChar &KeyChar, TShiftState Shift) {

	filtraGrid();
}

void __fastcall TFormPrincipal::EditCodigoKeyUp(TObject *Sender, WORD &Key,
	System::WideChar &KeyChar, TShiftState Shift) {

	filtraGrid();
}
// ---------------------------------------------------------------------------

void TFormPrincipal::filtraGrid() {

	// unicode string para wchar
	wchar_t* wcharCodigo = this->EditCodigo->Text.c_str();
	wchar_t* wcharNome = this->EditNome->Text.c_str();

	if (wcharCodigo == 0 && wcharNome == 0) {
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

void __fastcall TFormPrincipal::StringGridRegistrosEditingDone(TObject *Sender,
	const int ACol, const int ARow) {
	wchar_t* changedValue = this->StringGridRegistros->Cells[ACol][ARow]
		.c_str();
	wchar_t* codigo = this->StringGridRegistros->Cells[0][ARow].c_str();

	for (int i = 0; i < Clinica::clinica->qtdPacientes; i++) {
		Paciente* paciente = Clinica::clinica->pacientes[i];
		if (Clinica::clinica->pacientes[i]->codigo == stoi(codigo)) {
			switch (ACol) {
			case 0:
				Clinica::clinica->pacientes[i]->codigo = stoi(changedValue);
				break;
			case 1:
				wcstombs(Clinica::clinica->pacientes[i]->nome, changedValue,
					sizeof(Clinica::clinica->pacientes[i]->nome));
				break;
			case 2:
				Clinica::clinica->pacientes[i]->sexo = changedValue[0];
				break;
			case 3:
				wcstombs(Clinica::clinica->pacientes[i]->dataNascimento,
					changedValue,
					sizeof(Clinica::clinica->pacientes[i]->dataNascimento));
				break;
			case 4:
				Clinica::clinica->pacientes[i]->imc.peso = stod(changedValue);
				break;
			case 5:
				Clinica::clinica->pacientes[i]->imc.altura = stod(changedValue);
				break;
			default: ;
			}
		}

		Clinica::clinica->atualizaDados(this);
	}

}
// ---------------------------------------------------------------------------
