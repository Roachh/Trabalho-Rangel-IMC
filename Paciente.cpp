// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitPrincipal.h"
#include "Clinica.h"
#include "Paciente.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

Paciente::Paciente() {

	this->codigo = Clinica::clinica->qtdPacientes;
}

Paciente::Paciente(Clinica* clinica) {

	this->codigo = clinica->qtdPacientes;
	clinica->pacientes[clinica->qtdPacientes] = this;
	clinica->qtdPacientes++;
}
