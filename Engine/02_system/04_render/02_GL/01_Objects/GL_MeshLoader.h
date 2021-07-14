#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class GL_VAO;
class VertexAttribute;

class GL_MeshLoader{
public:
	static GL_VAO* loadMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices,VertexAttribute* attribute1);
	static GL_VAO* loadMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, VertexAttribute* attribute1, VertexAttribute* attribute2);
	static GL_VAO* loadMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, VertexAttribute* attribute1, VertexAttribute* attribute2, VertexAttribute* attribute3);
};