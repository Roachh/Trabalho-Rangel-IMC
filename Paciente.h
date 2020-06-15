//---------------------------------------------------------------------------

#ifndef PacienteH
#define PacienteH
//---------------------------------------------------------------------------
#include "IMC.h"


class Paciente {
public:
	int codigo;
	char nome[15];
	char sexo;
	char dataNascimento[10];
	IMC imc;
	Paciente();
};

#endif
