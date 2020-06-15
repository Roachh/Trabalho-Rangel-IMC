// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "UnitCadastro.h"
#include "Paciente.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#include <string.h>
#include <stdlib.h>

TFormCadastro *FormCadastro;

// ---------------------------------------------------------------------------
__fastcall TFormCadastro::TFormCadastro(TComponent* Owner) : TForm(Owner) {
}

__fastcall TFormCadastro::TFormCadastro(Paciente* paciente, TComponent* Owner) : TForm(Owner) {

	TFormCadastro::paciente = paciente;
}

// ---------------------------------------------------------------------------

void __fastcall TFormCadastro::btnConfirmarClick(TObject *Sender) {

	usuarioRegistrou = true;
	wcstombs(paciente->nome, EditNome->Text.c_str(), sizeof(paciente->nome));
	paciente->sexo = *EditSexo->Text.FirstChar();
	wcstombs(paciente->dataNascimento, EditDataNascimento->Text.c_str(), sizeof(paciente->dataNascimento));
	paciente->imc.peso = EditPeso->Text.ToDouble();
	paciente->imc.altura = EditAltura->Text.ToDouble();
	Close();
}
// ---------------------------------------------------------------------------
