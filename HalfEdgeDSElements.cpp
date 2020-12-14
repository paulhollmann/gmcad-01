#include "HalfEdgeDSElements.h"

#include <iostream>
#include <iomanip>

/**
* Constructor for a Solid with its Face
*/
Solid::Solid()
	: toFace(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements

/**
* Constructor for a Face with its Solid, outer and inner Loop
*/
Face::Face()
	: toSolid(nullptr)
	, outerLoop(nullptr)
	, innerLoop(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements

/**
* Constructor for a Loop with  its Face, its neighbors in Loop List and any HalfEdge on it
*/
Loop::Loop()
	: toFace(nullptr)
	, nextLoop(nullptr)
	, prevLoop(nullptr)
	, toHE(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements

/**
* Constructor for a Edge with numerous pointers
*/
Edge::Edge()
	: he1(nullptr)
	, he2(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements

/**
* Constructor for a HalfEdge with its Loop, its parent Edge, neighbors in HaldEdge list and starting Vertex
*/
HalfEdge::HalfEdge()
	: toLoop(nullptr)
	, toEdge(nullptr)
	, nextHE(nullptr)
	, prevHE(nullptr)
	, startV(nullptr)
{
}

// TODO: create methods for creating and traversing its elements

/**
* Get conjugate HalfEdge at this parent Edge
* 
* @return conjugate HalfEdge
*/
HalfEdge* HalfEdge::getConjugate()
{
	/// get parent Edge and compare this HalfEdge with both directional HalfEdges
	if (this->toEdge->he1 == this) {
		/// return the other HalfEdge
		return this->toEdge->he2;
	}
	return this->toEdge->he1;
}
	


/**
* Constructor for a Vertex with HalfEdge and coordinates
*/
Vertex::Vertex()
	: outgoingHE(nullptr)
	, coordinates(Vec3f())
{
}
	
// TODO: create methods for creating and traversing its elements

/**
* Get Halfedge pointing into the Vertex on given Loop
* 
* @param loop where to search for HalfEdge 
* @return HalfEdge on loop starting at this vertex
*/

HalfEdge* Vertex::getRandInboundHE(Loop* loop) {
	/// get any Halfedge of the Loop
	HalfEdge* he = loop->toHE;
	/// continue through loop until startvertex is this vertex
	while (he->startV != this)
	{
		he = he->nextHE;
	}
	return he->prevHE;
}

HalfEdge* Vertex::getOutboundHE(Loop* loop) {
	/// get any Halfedge of the Loop
	HalfEdge* he = loop->toHE;
	/// continue through loop until startvertex is this vertex
	while (he->startV != this)
	{
		he = he->nextHE;
	}
	return he;
}