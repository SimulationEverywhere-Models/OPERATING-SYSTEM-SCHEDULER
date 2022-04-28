#ifndef __admTr_H
#define __admTr_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "varios.h"     // funciones auxiliares

/** estados del admTr **/
#define PASIVO 0
#define CREANDO_PROCESO 1
#define FINALIZANDO_PROCESO 2

/** declarations **/
class admTr : public Atomic
{
public:
	admTr( const string &name = "admTr" );				  // Default constructor
	~admTr();

	virtual string className() const
		{return "admTr";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &nuevoTrabajo ;
	Port &nuevoProceso ;

	const Port &finProceso ;
	Port &finTrabajo ;
	
	int estado;
	proceso enTransito;
			
};	// class admTr

#endif   //__admTr_H 
