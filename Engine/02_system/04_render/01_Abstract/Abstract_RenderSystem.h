#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Abstract_RenderSystem{
public:
	virtual void loadShaders()=0;
	virtual void loadPipelines()=0;
};