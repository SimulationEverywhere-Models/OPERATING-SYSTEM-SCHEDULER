/** include files **/
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator

#include "Reloj.h"       // base header
//#include "distri.h"        // class Distribution 
//#include "strutil.h"       // str2Value( ... )

Reloj::Reloj( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
{

}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Reloj::initFunction()
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Reloj::externalFunction( const ExternalMessage &msg )
{
	int time = msg.value();
	holdIn( active, Time( static_cast< float >( time ) ) ) ;
	return *this;
}
/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Reloj::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Reloj::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), out, 1 ) ; 
	//sólo debe indicar el evento, no enviar ningún valor en especial
	return *this ;
}

Reloj::~Reloj()
{
}
