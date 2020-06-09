// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "UnitPrincipal.h"
#include "UnitCadastro.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFormPrincipal *FormPrincipal;
int Paciente::codigoCount = 0;

// ---------------------------------------------------------------------------
__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner) : TForm(Owner) {

}

IMC::IMC(double peso, double altura){
		this->peso = peso;
        this->altura = altura;
	}

float IMC::calculaIMC() {
	return this->peso / (this->altura * this->altura);
}

String IMC::diagnostico() {
	float imc = calculaIMC();
	if (imc < 17) {
		return "Muito abaixo do peso";
	}
	else {
		if (imc >= 17 && imc < 18.5) {
			return "Abaixo do peso";
		}
		else {
			if (imc >= 18.5 && imc < 25) {
				return "Peso normal";
			}
			else {
				if (imc >= 25 && imc < 30) {
					return "Acima do peso";
				}
				else {
					if (imc >= 30 && imc < 35) {
						return "Obesidade I";
					}
					else {
						if (imc >= 35 && imc < 40) {
							return "Obesidade II";
						}
						else {
							if (imc >= 40) {
								return "Obesidade III";
							}
							else {
								return 0;
							}
						}
					}
				}
			}
		}
	}
}

Paciente::Paciente() {
	Paciente::codigoCount += 1;
    this->codigo = Paciente::codigoCount;
}

Paciente::Paciente(String nome, char sexo, String dataNascimento, double peso, double altura) {
	Paciente::codigoCount += 1;
    this->codigo = Paciente::codigoCount;
	this->nome = nome;
	this->sexo = sexo;
	this->dataNascimento = dataNascimento;
    this->imc = new IMC(peso, altura);
}

// ---------------------------------------------------------------------------

void __fastcall TFormPrincipal::btnCadastrarClick(TObject *Sender) {
	Paciente* paciente = new Paciente();
	TFormCadastro *form = new TFormCadastro(paciente, this);
	form->ShowModal();

	if(form->usuarioRegistrou) {

	StringGrid1->Cells[0][Paciente::codigoCount-1] = paciente->codigo;
	StringGrid1->Cells[1][Paciente::codigoCount-1] = paciente->nome;
	StringGrid1->Cells[2][Paciente::codigoCount-1] = paciente->sexo;
	StringGrid1->Cells[3][Paciente::codigoCount-1] = paciente->dataNascimento;
	StringGrid1->Cells[4][Paciente::codigoCount-1] = paciente->imc->peso;
	StringGrid1->Cells[5][Paciente::codigoCount-1] = paciente->imc->altura;
	StringGrid1->Cells[6][Paciente::codigoCount-1] = paciente->imc->calculaIMC();

	}

    delete form;

}
// ---------------------------------------------------------------------------


