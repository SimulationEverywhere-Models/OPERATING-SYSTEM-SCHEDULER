#ifndef __Reloj_H
#define __Reloj_H

/** include files **/
#include "atomic.h"     // class Atomic
//#include "except.h"     // class InvalidMessageException

/** declarations **/
class Reloj : public Atomic
{
public:
	Reloj( const string &name = "Reloj" );
	~Reloj();

	virtual string className() const
		{return "Reloj";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	//int time;
	const Port &in ;
	Port &out ;
			
};	// class Reloj


#endif   //__Reloj_H 
