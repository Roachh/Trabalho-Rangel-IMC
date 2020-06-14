// ---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "UnitPrincipal.h"
#include "UnitCadastro.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

#include <stdio.h>
#include <string.h>
using namespace std;

TFormPrincipal *FormPrincipal;
Clinica* clinica;

// ---------------------------------------------------------------------------
__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner) : TForm(Owner) {
	clinica = new Clinica();

	this->atualizaGrid();
}

Clinica::Clinica() {
	this->qtdPacientes = 0;
}

int TFormPrincipal::atualizaGrid() {

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

	for (i = 0; i < clinica->qtdPacientes; i++) {
		StringGrid1->Cells[0][i] = clinica->pacientes[i]->codigo;
		StringGrid1->Cells[1][i] = clinica->pacientes[i]->nome;
		StringGrid1->Cells[2][i] = clinica->pacientes[i]->sexo;
		StringGrid1->Cells[3][i] = clinica->pacientes[i]->dataNascimento;
		StringGrid1->Cells[4][i] = clinica->pacientes[i]->imc.peso;
		StringGrid1->Cells[5][i] = clinica->pacientes[i]->imc.altura;
		StringGrid1->Cells[6][i] = clinica->pacientes[i]->imc.calculaIMC();
	}

	fclose(le);

	// StringGrid1->Cells[1][i] = paciente.nome;
	// StringGrid1->Cells[3][i] = paciente.dataNascimento;
	// StringGrid1->Cells[4][i] = paciente.imc.peso;
	// StringGrid1->Cells[5][i] = paciente.imc.altura;
	// StringGrid1->Cells[6][i] = paciente.imc.calculaIMC();
	return 0;
}

IMC::IMC(double peso, double altura) {
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

IMC::IMC() {

}

Paciente::Paciente() {
	this->codigo = clinica->qtdPacientes;
	clinica->pacientes[clinica->qtdPacientes] = this;
	clinica->qtdPacientes++;
}

// Paciente::Paciente(char nome[], char sexo, char dataNascimento[], double peso,
// double altura) {
// this->codigo = clinica->qtdPacientes;
// strcpy(this->nome, nome);
// this->sexo = sexo;
// strcpy(this->dataNascimento, dataNascimento);
// // this->imc = new IMC(peso, altura);
// this->imc.peso = peso;
// this->imc.altura = altura;
// }

int Clinica::atualizaDados(TFormPrincipal* form) {

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

// ---------------------------------------------------------------------------

void __fastcall TFormPrincipal::btnCadastrarClick(TObject *Sender) {
	Paciente* paciente = new Paciente();
	TFormCadastro *form = new TFormCadastro(paciente, this);
	form->ShowModal();

	if (form->usuarioRegistrou) {
		clinica->atualizaDados(this);
	}

	delete form;

}
