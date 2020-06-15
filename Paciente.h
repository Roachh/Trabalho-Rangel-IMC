//---------------------------------------------------------------------------

#ifndef PacienteH
#define PacienteH
//---------------------------------------------------------------------------
#include "IMC.h"

class Clinica;


class Paciente {
public:
	int codigo;
	char nome[15];
	char sexo;
	char dataNascimento[10];
	IMC imc;
	Paciente();
	Paciente(Clinica* clinica);
};

#endif
