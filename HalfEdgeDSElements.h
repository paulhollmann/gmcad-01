// ========================================================================= //
// Authors: Matthias Borner                                                  //
// mailto:matthias.borner@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universitšt Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
// ========================================================================= //

#ifndef HALF_EDGE_DS_ELEMENTS_H
#define HALF_EDGE_DS_ELEMENTS_H

#include "Vec3.h"		// vector (x, y, z)
#include <list>

// forward declarations, so elements know each other when defined further below
struct Solid;
struct Face;
struct Loop;
struct Edge;
struct HalfEdge;
struct Vertex;

// data structure elements. this is an minimal extract of the data structure presented in the slides.
// we skip identifiers and pointers to unsorted lists of elements.
// by default all pointers are initialized with nullptr, so you can use "if (some_solid->toFace)" to check, if the pointer is set.
struct Solid
{
	Face* toFace;			// can be any face of the solid
	Solid();
	
	// TODO: create methods for creating and traversing its elements
};

struct Face
{
	Solid* toSolid;					// back to the solid
	Loop* outerLoop;				// to the boundary of the face
	std::list<Loop*> innerLoops;	// to a possible hole. Can be null_ptr. Multiple holes are accessible through innerLoop->nextLoop.
	Face();

	// TODO: create methods for creating and traversing its elements
};

struct Loop
{
	Face* toFace;			// back to the face
	HalfEdge* toHE;			// can be any half edge of the loop
	Loop();

	// TODO: create methods for creating and traversing its elements

};

struct Edge
{
	HalfEdge* he1;
	HalfEdge* he2;
	Edge();
	
	// TODO: create methods for creating and traversing its elements
};

struct HalfEdge
{
	Loop* toLoop;			// back to the loop
	Edge* toEdge;			// back to the parent edge
	HalfEdge* nextHE;		// next half edge
	HalfEdge* prevHE;		// previous half edge
	Vertex* startV;			// vertex at the tail of the half edge
	HalfEdge();
	// TODO: create methods for creating and traversing its elements
	HalfEdge* getConjugate();
};

struct Vertex
{
	HalfEdge* outgoingHE;	// can be any outgoing half edge
	Vec3f coordinates;		// stores the 3d coordinates of the vertex
	Vertex();
	// TODO: create methods for creating and traversing its elements
	HalfEdge* getRandInboundHE(Loop* loop);

	HalfEdge* getOutboundHE(Loop* loop);

	//std::list<Edge*> getEdges();
};


#endif
