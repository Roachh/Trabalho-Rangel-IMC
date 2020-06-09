// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "UnitPrincipal.h"
#include "UnitCadastro.h"



// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
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
	paciente->nome = Edit1->Text;
	paciente->sexo = *Edit2->Text.FirstChar();
	paciente->dataNascimento = Edit3->Text;
    paciente->imc = new IMC(Edit4->Text.ToDouble(), Edit5->Text.ToDouble());
	Close();
    //teste
}
// ---------------------------------------------------------------------------
