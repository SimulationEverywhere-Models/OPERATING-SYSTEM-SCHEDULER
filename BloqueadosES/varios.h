#ifndef __VARIOS
#define __VARIOS

/** tipos generales **/
#define proceso int
#define trabajo int

/*Los procesos constan de 3 secciones y 5 digitos en total:
 *   id  -  E/S  -  procesamiento
 *   XX      X           XX 	  (cantidad de dígitos por sección)
 * 
 * Procesamiento: indica la cantidad de veces que va a pasar por el estado 
 * 				  PROCESANDO (indirectamente representa la cantidad de 
 * 				  procesamiento que realiza ese proceso)
 * E/S: indica la cantidad de veces que va a pasar por el estado HACIENDO_E_S 
 * 	    (indirectamente representa la cantidad de E/S que realiza ese proceso)
 * Ambos se van actualizando a medida que se ejecuta el proceso.
 * 
 * ID: identificador del proceso. Fijo durante la vida del proceso.
 * 
 * Para ello se definen las siguiente constantes que serán utilizadas al
 * actualizar dichos valores.
 */
#define POSICION_E_S 100
#define POSICION_PROCESAMIENTO 1

#define debug cout

proceso crearProceso(trabajo);
trabajo getTrabajo(proceso);

#endif   //__VARIOS
