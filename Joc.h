#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
	Joc() {}
	void inicialitza(const string& nomFitxer);
	bool novaFigura();
	void novaFigura(InfoFigura figura);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	int colocaFigura();
	void escriuTauler(const string& nomFitxer);
	void dibuixa();
	void ProximaFigura();
	void generaSeguent();

private:
	Tauler m_tauler;
	Figura m_figuraActual;
	Figura m_figuraSeguent;
};

#endif