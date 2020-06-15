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

void __fastcall TFormCadastro::Button1Click(TObject *Sender) {

	usuarioRegistrou = true;
	wcstombs(paciente->nome, Edit1->Text.c_str(), sizeof(paciente->nome));
	paciente->sexo = *Edit2->Text.FirstChar();
	wcstombs(paciente->dataNascimento, Edit3->Text.c_str(), sizeof(paciente->dataNascimento));
	//paciente->imc = new IMC(Edit4->Text.ToDouble(), Edit5->Text.ToDouble());
	paciente->imc.peso = Edit4->Text.ToDouble();
	paciente->imc.altura = Edit5->Text.ToDouble();
	Close();
}
// ---------------------------------------------------------------------------
