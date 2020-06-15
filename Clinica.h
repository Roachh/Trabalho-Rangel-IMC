// ---------------------------------------------------------------------------

#ifndef ClinicaH
#define ClinicaH
// ---------------------------------------------------------------------------

#include <string>
using namespace std;

class TFormPrincipal;
class Paciente;

class Clinica {
public:
	string nome;
	Paciente* pacientes[1000];
	int qtdPacientes;
	static Clinica* clinica;

	Clinica* getInstance();
	void filtraDados(char* codigoFiltro, char* nomeFiltro,
		TFormPrincipal* form);
	int atualizaDados(TFormPrincipal* form);
	int recuperaDados(TFormPrincipal* form);
    void addPaciente(Paciente* paciente);

private:
	Clinica();
};

#endif
