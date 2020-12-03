#include "HalfEdgeDSElements.h"

#include <iostream>
#include <iomanip>

Solid::Solid()
	: toFace(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements


Face::Face()
	: toSolid(nullptr)
	, outerLoop(nullptr)
	, innerLoop(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements


Loop::Loop()
	: toFace(nullptr)
	, nextLoop(nullptr)
	, prevLoop(nullptr)
	, toHE(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements


Edge::Edge()
	: he1(nullptr)
	, he2(nullptr)
{
}
	
// TODO: create methods for creating and traversing its elements


HalfEdge::HalfEdge()
	: toLoop(nullptr)
	, toEdge(nullptr)
	, nextHE(nullptr)
	, prevHE(nullptr)
	, startV(nullptr)
{
}

HalfEdge* HalfEdge::getConjugate()
{
	if (this->toEdge->he1 == this) {
		return this->toEdge->he2;
	}
	return this->toEdge->he1;
}
	
// TODO: create methods for creating and traversing its elements


Vertex::Vertex()
	: outgoingHE(nullptr)
	, coordinates(Vec3f())
{
}
	
// TODO: create methods for creating and traversing its elements
