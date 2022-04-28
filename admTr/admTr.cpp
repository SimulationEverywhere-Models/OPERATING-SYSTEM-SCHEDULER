/** include files **/
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator

#include "admTr.h"       // base header
#include "varios.h"       // str2Value( ... )

admTr::admTr( const string &name )
: Atomic( name )
, nuevoTrabajo( addInputPort( "nuevoTrabajo" ) )
, finProceso( addInputPort( "finProceso" ) )
, nuevoProceso( addOutputPort( "nuevoProceso" ) )
, finTrabajo( addOutputPort( "finTrabajo" ) )
{

}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &admTr::initFunction()
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &admTr::externalFunction( const ExternalMessage &msg )
{
	if (estado==PASIVO) {
		if (msg.port()==nuevoTrabajo) {
				estado = CREANDO_PROCESO;
				enTransito = msg.value();
				holdIn(active, Time::Zero );
		} else if (msg.port()==finProceso) {
				estado = FINALIZANDO_PROCESO;
				enTransito = msg.value();
				holdIn(active , Time::Zero ) ;
		};
	};
	return *this;
}
/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &admTr::internalFunction( const InternalMessage & )
{
	estado = PASIVO;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &admTr::outputFunction( const InternalMessage &msg )
{
	if (estado==CREANDO_PROCESO) {
		proceso proc = crearProceso(enTransito);
		sendOutput( msg.time(), nuevoProceso, proc ) ;
	} else if (estado==FINALIZANDO_PROCESO) {
		trabajo trab = getTrabajo(enTransito);
		sendOutput( msg.time(), finTrabajo, trab ) ;
	}
	return *this ;
}

admTr::~admTr()
{
}

