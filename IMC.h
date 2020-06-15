//---------------------------------------------------------------------------

#ifndef IMCH
#define IMCH
//---------------------------------------------------------------------------
#include <string>
using namespace std;

class IMC {
public:
	double peso;
	double altura;
	double calculaIMC();
	IMC(double peso, double altura);
	char* diagnostico();
    IMC();
};

#endif
