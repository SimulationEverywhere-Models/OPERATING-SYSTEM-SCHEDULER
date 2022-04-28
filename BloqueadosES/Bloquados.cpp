/** include files **/
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator

#include "Bloqueados.h"       // base header
#include "varios.h"       // str2Value( ... )

Bloqueados::Bloqueados( const string &name )
: Atomic( name )
, encolar( addInputPort( "encolar" ) )
, finESfisica( addInputPort( "finESfisica" ) )
, listo( addOutputPort( "listo" ) )
, hacerESfisica( addOutputPort( "hacerESfisica" ) )
, TIEMPO_PASO_MENSAJE(0,0,0,1)
{
	string parametroTiempo( MainSimulator::Instance().getParameter(description(), "demora"));
	if (parametroTiempo != "" ) {
		TIEMPO_PASO_MENSAJE = Time(parametroTiempo);
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Bloqueados::initFunction()
{
	cant = 0;
	e_s_enProceso = 0;
	estado = ESPERANDO;
	pid = -1;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Bloqueados::externalFunction( const ExternalMessage &msg )
{

	if (msg.port()==encolar) {
//cout << "llego mensaje de encolar" << endl;		
		if (estado=ESPERANDO) {
			pid = msg.value();
			agregarProceso();
		} else {
			estado = DEMORANDO_ENTRADA;
			pid = msg.value();			
			holdIn( active, TIEMPO_PASO_MENSAJE);
		}
	} else if (msg.port()==finESfisica) {
//cout << "llego mensaje de fin de E/S cant(" << cant << ")" << endl;		
		e_s_enProceso=0;
		estado = RECIBIENDO_FIN_ES;
		//holdIn( active, Time::Zero) ;
		holdIn( active, TIEMPO_PASO_MENSAJE);
	};
	//mostrarCola("---");
	return *this;
}
/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Bloqueados::internalFunction( const InternalMessage & )
{
	if (estado==RECIBIENDO_FIN_ES) {
		actualizar();
		cant--;
		if (cant > 0) {
//cout << "esta RECIBIENDO_ES y quedan procesos" << endl;
			e_s_enProceso=1;
			estado = ENVIANDO_ES;
			holdIn( active, Time::Zero);
			//holdIn( active, TIEMPO_PASO_MENSAJE);
		} else {
//cout << "esta RECIBIENDO_ES y no hay mas procesos en la cola" << endl;						
			estado = ESPERANDO;
			passivate();			
		}
	} else 	if (estado==ENVIANDO_ES) {
//cout << "esta ENVIANDO_ES" << endl;					
		estado = ESPERANDO;
		passivate();
	} else 	if (estado==DEMORANDO_ENTRADA) {
		agregarProceso();
	}

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Bloqueados::outputFunction( const InternalMessage &msg )
{
	if (estado==ENVIANDO_ES) {
		sendOutput( msg.time(), hacerESfisica, TIEMPO_ES);
	} else if (estado==RECIBIENDO_FIN_ES) {
		sendOutput( msg.time(), listo, procesos[0]) ;
	}
	return *this ;
}

Bloqueados::~Bloqueados()
{
	if (procesos) delete procesos;
}

//actualiza la cola "pisando" al proceso elegido
void Bloqueados::actualizar()
{
	for (int i=0; i<cant-1; i++) {
		procesos[i]=procesos[i+1];
	}	
}
void Bloqueados::mostrarCola(char* msg) 
{
	cout << msg << endl;
	cout << "(" << cant << ") ";
	cout << "[ ";
	for (int i=0; i<cant; i++) {
		cout << procesos[i] << " ";
	}
	cout << "]" << endl;
}

void Bloqueados::agregarProceso() {
	if (cant<TAM_MAX_BLOQUEADOS) {
		procesos[cant]=pid;
		cant++;	
//cout << "cant vale: " << cant << endl;			
		if (e_s_enProceso==0) {
//cout << "encolo y es la primera" << endl;				
			e_s_enProceso=1;
			estado = ENVIANDO_ES;
			holdIn( active, Time::Zero);
			//holdIn( active, TIEMPO_PASO_MENSAJE);
		} else {
//cout << "encolo y ya hay otra en proceso" << endl;
			estado = ESPERANDO;
			passivate();
		}			
	}
//cout << "Al salir de argregar, cant vale: " << cant << endl;	
//mostrarCola("");
//cout << "------------------" << endl;	
}