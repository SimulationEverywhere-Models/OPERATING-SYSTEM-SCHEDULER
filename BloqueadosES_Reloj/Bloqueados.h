#ifndef __Bloqueados_H
#define __Bloqueados_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "varios.h"     // funciones auxiliares

/** constantes y prototipo de funciones del Bloqueados **/
#define TAM_MAX_BLOQUEADOS 100
#define TIEMPO_ES 45

#define ESPERANDO 0
#define ENVIANDO_ES 1
#define RECIBIENDO_FIN_ES 2
#define DEMORANDO_ENTRADA 3

proceso planificador(proceso[]);

/** declarations **/
class Bloqueados : public Atomic
{
public:
	Bloqueados( const string &name = "Bloqueados" );				  // Default constructor
	~Bloqueados();

	virtual string className() const
		{return "Bloqueados";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &encolar;
	Port &listo;

	const Port &finESfisica;
	Port &hacerESfisica;
	
	int cant;
	proceso procesos[TAM_MAX_BLOQUEADOS];
	int e_s_enProceso;
	int estado;
	Time TIEMPO_PASO_MENSAJE;
	proceso pid; //auxiliar para DEMORAR_ENTRADA
	
	void mostrarCola(char*);
	void actualizar(); 
	void agregarProceso();
};	// class Bloqueados

#endif   //__Bloqueados_H 
