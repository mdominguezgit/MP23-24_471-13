#include "Joc.h"
#include <fstream>
using namespace std;

void Joc::inicialitza(const string& nomFitxer) //Inicialitza el joc llegint la configuració del fitxer especificat
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int tipus, fila, columna, gir;
		fitxer >> tipus >> fila >> columna >> gir;
		m_figuraActual.inicialitza(TipusFigura(tipus), fila, columna);
		for (int i = 0; i < gir; i++)
			m_figuraActual.gira(GIR_HORARI);

		ColorFigura taulerInicial[MAX_FILA][MAX_COL];
		int color;
		for (int i = 0; i < MAX_FILA; i++)
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> color;
				taulerInicial[i][j] = ColorFigura(color);
			}
		m_tauler.inicialitza(taulerInicial);
		fitxer.close();
	}
}

bool Joc::giraFigura(DireccioGir direccio) //Gira al figura actual en la direcció especificada i comprova si col·lisiona 
{
	m_figuraActual.gira(direccio);
	bool colisiona = m_tauler.colisionaFigura(m_figuraActual);
	if (colisiona)
	{
		if (direccio == GIR_HORARI)
			direccio = GIR_ANTI_HORARI;
		else
			direccio = GIR_HORARI;
		m_figuraActual.gira(direccio);
	}
	return !colisiona;
}

bool Joc::mouFigura(int dirX) //Mou la figura horitzontalment i comprova si col·lisiona
{
	m_figuraActual.mou(dirX);
	bool colisiona = m_tauler.colisionaFigura(m_figuraActual);
	if (colisiona)
		m_figuraActual.mou(-dirX);
	return !colisiona;
}

int Joc::baixaFigura() //Baixa la figura una posició i retorna les files completades
{
	int nFiles = 0;
	m_figuraActual.baixa();
	if (m_tauler.colisionaFigura(m_figuraActual))
	{
		m_figuraActual.puja();
		nFiles = m_tauler.colocaFigura(m_figuraActual);
		m_figuraActual.inicialitza(NO_FIGURA, -1, -1);
	}
	return nFiles;
}

void Joc::escriuTauler(const string& nomFitxer) //Guarda l'estat actual del tauler al fitxer especificat
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		if (m_figuraActual.getTipus() != NO_FIGURA)
			m_tauler.dibuixaFigura(m_figuraActual);
		ColorFigura tauler[MAX_FILA][MAX_COL];
		m_tauler.getValorsTauler(tauler);
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer << int(tauler[i][j]) << " ";
			}
			fitxer << endl;
		}

		fitxer.close();
	}
}