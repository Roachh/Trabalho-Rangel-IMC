//---------------------------------------------------------------------------

#pragma hdrstop

#include "IMC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include <cmath>

IMC::IMC() {

}

IMC::IMC(double peso, double altura) {
	this->peso = peso;
	this->altura = altura;
}

double IMC::calculaIMC() {
	double imc = (this->peso / (this->altura * this->altura)) * 100;
	imc = std::round(imc);
	imc /= 100;
    return imc;


}

char* IMC::diagnostico() {
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