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
	float calculaIMC();
	IMC(double peso, double altura);
	string diagnostico();
    IMC();
};

#endif
