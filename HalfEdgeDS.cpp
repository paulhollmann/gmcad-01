#include "HalfEdgeDS.h"

#include <stdio.h>		// cout
#include <iostream>		// cout

HalfEdgeDS::HalfEdgeDS()
{
	clearDS();
	createDefaultObject();
}	

HalfEdgeDS::~HalfEdgeDS()
{
	clearDS();
}

void HalfEdgeDS::createDefaultObject()
{
	// WARNING: this example does NOT create a valid topology. It just creates the minimum elements to draw one line.
	// CARE: for every "new" we need a "delete". if an element is added to the according list, it is deleted automatically within clearDS().

	// create example elements.
	/*
	Vertex* v1 = new Vertex;
	Vertex* v2 = new Vertex;
	HalfEdge* he1 = new HalfEdge;
	HalfEdge* he2 = new HalfEdge;
	Edge* e = new Edge;
	// set up connections
	v1->coordinates = Vec3f(1.0f, 2.0f, 3.0f);
	v2->coordinates = Vec3f(3.0f, 2.0f, 1.0f);
	he1->startV = v1;
	he1->nextHE = he2;
	he2->startV = v2;
	he2->nextHE = he1;
	e->he1 = he1;
	e->he2 = he2;
	// add elements to the lists
	vertices.push_back(v1);
	vertices.push_back(v2);
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	edges.push_back(e);
	*/
	Edge* e1 = new Edge();
	Edge* e2 = new Edge();
	Edge* e3 = new Edge();
	Edge* e4 = new Edge();

	Vertex* v1 = new Vertex();
	Vertex* v2 = new Vertex();
	Vertex* v3 = new Vertex();
	Vertex* v4 = new Vertex();
	Loop* l1 = new Loop();
	Loop* l2 = new Loop();
	Solid* s1 = new Solid();
	//Solid* s2 = new Solid();

	mevvls(*e1, *v1, *v2, *l1, *s1, 1.0f, 2.0f, 3.0f, 3.0f, 2.0f, 1.0f);
	mev(*l1,*v2,*e2,*v3, -1.0f, 2.0f, 0);
	mve(*e2, *v4, *e3, 1.0f, 1.0f, 1.0f);
	mel(*l1, *v1, *v3, *e4, *l2);


	if (!checkDS()) std::cout << "WARN: HalfEdgeDS NOT valid! (blame the programmer)" << std::endl;
	
	//mevvls(*e2, *v3, *v4, *l2, *s2, -1.0f, 2.0f, 3.0f, -3.0f, 2.0f, 1.0f);
	// TODO: Create a new VALID test object including all topological elements and linkage. The object should be volumetric and consist of at least one hole (H > 0).

}

void HalfEdgeDS::clearDS()
{
	// for every "new" in this code, we need to call delete. take care, that you delete ALL elements
	for (auto *p : vertices) delete p;
	vertices.clear();
	for (auto *p : halfEdges) delete p;
	halfEdges.clear();
	for (auto *p : edges) delete p;
	edges.clear();
	for (auto *p : loops) delete p;
	loops.clear();
	for (auto *p : faces) delete p;
	faces.clear();
	for (auto *p : solids) delete p;
	solids.clear();
}

void HalfEdgeDS::mevvls(Edge& E1, Vertex& V1, Vertex& V2, Loop& L1, Solid& S1, float x1, float y1, float z1, float x2, float y2, float z2)
{
	Vec3f p1(x1, y1, z1);
	Vec3f p2(x2, y2, z2);

	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();

	Face* f1 = new Face();

	V1.coordinates = p1;
	V2.coordinates = p2;
	V1.outgoingHE = he1;
	V2.outgoingHE = he2;

	he1->toLoop = &L1;
	he2->toLoop = &L1;
	he1->toEdge = &E1;
	he2->toEdge = &E1;
	he1->startV = &V1;
	he2->startV = &V2;
	he1->prevHE = he2;
	he2->prevHE = he1;
	he1->nextHE = he2;
	he2->nextHE = he1;
	

	E1.he1 = he1;
	E1.he2 = he2;

	L1.toFace = f1;
	L1.prevLoop = &L1;
	L1.nextLoop = &L1;
	L1.toHE = he1;
	
	f1->toSolid = &S1;
	f1->outerLoop = &L1;
	f1->innerLoop = nullptr;

	S1.toFace = f1;

	vertices.push_back(&V1);
	vertices.push_back(&V2);
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	edges.push_back(&E1);
	loops.push_back(&L1);
	faces.push_back(f1);
	solids.push_back(&S1);

}

void HalfEdgeDS::mev(Loop& L1, Vertex& V1, Edge& E1, Vertex& V2, float x, float y, float z)
{
	Vec3f p(x, y, z);

	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();

	V2.coordinates = p;
	V2.outgoingHE = he2;

	HalfEdge* inbound_he = V1.getInboundHE(&L1);
	HalfEdge* outbound_he = inbound_he->nextHE;
	inbound_he->nextHE = he1;
	he1->prevHE = inbound_he;
	he1->nextHE = he2;
	he2->prevHE = he1;
	he2->nextHE = outbound_he;
	outbound_he->prevHE = he2;

	he1->startV = &V1;
	he2->startV = &V2;
	he1->toLoop = &L1;
	he2->toLoop = &L1;
	he1->toEdge = &E1;
	he2->toEdge = &E1;

	E1.he1 = he1;
	E1.he2 = he2;

	vertices.push_back(&V2);
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	edges.push_back(&E1);
}

void HalfEdgeDS::mve(Edge& E1, Vertex& V1, Edge& E2, float x, float y, float z) {

	Vec3f p(x, y, z);
	HalfEdge* rightHE1 = new HalfEdge();
	HalfEdge* rightHE2 = new HalfEdge();

	V1.coordinates = p;
	V1.outgoingHE = rightHE1;

	Vertex* leftV = E1.he1->startV;
	Vertex* rightV = E1.he2->startV;
	HalfEdge* leftHE1 = E1.he1;
	HalfEdge* leftHE2 = E1.he2;

	rightHE1->nextHE = leftHE1->nextHE;
	leftHE1->nextHE->prevHE = rightHE1;
	rightHE2->prevHE = leftHE2->prevHE;
	leftHE2->prevHE->nextHE = rightHE2;

	rightHE1->prevHE = leftHE1;
	rightHE2->nextHE = leftHE2;

	rightHE1->startV = &V1;
	rightHE2->startV = rightV;

	leftHE1->nextHE = rightHE1;
	leftHE2->prevHE = rightHE2;
	leftHE2->startV = &V1;

	leftV->outgoingHE = leftHE1;
	rightV->outgoingHE = rightHE2;

	rightHE1->toEdge = &E2;
	rightHE2->toEdge = &E2;
	rightHE1->toLoop = leftHE1->toLoop;
	rightHE2->toLoop = leftHE2->toLoop;

	E2.he1 = rightHE1;
	E2.he2 = rightHE2;

	vertices.push_back(&V1);
	halfEdges.push_back(rightHE1);
	halfEdges.push_back(rightHE2);
	edges.push_back(&E2);
}

void HalfEdgeDS::mel(Loop& L1, Vertex& V1, Vertex& V2, Edge& E1, Loop& L2) {

	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();

	HalfEdge* leftInboundHE = V1.getInboundHE(&L1);
	HalfEdge* leftOutboundHE = leftInboundHE->getConjugate();
	
	HalfEdge* rightInboundHE = V2.getInboundHE(&L1);
	HalfEdge* rightOutboundHE = rightInboundHE->getConjugate();

	leftInboundHE->nextHE = he1;
	he1->prevHE = leftInboundHE;
	he1->nextHE = rightOutboundHE;
	rightOutboundHE->prevHE = he1;

	rightInboundHE->nextHE = he2;
	he2->prevHE = rightInboundHE;
	he2->nextHE = leftOutboundHE;
	leftOutboundHE->prevHE = he1;

	he1->toLoop = &L1;
	he2->toLoop = &L2;
	HalfEdge* he = he2->nextHE;
	while (he != he2)
	{
		he->toLoop = &L2;
		he = he->nextHE;
	}
	he1->startV = &V1;
	he2->startV = &V2;

	he1->toEdge = &E1;
	he2->toEdge = &E1;

	E1.he1 = he1;
	E1.he2 = he2;
	
	L1.toHE = he1;
	L2.toHE = he2;

	//handle faces

	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	edges.push_back(&E1);
	loops.push_back(&L2);
}

bool HalfEdgeDS::checkDS() 
{
	return checkVertices() && checkHalfEdges() && checkEdges() && checkLoops();
}

bool HalfEdgeDS::checkEulerPoincare()
{
	return false;
}

bool HalfEdgeDS::checkVertices()
{
	for (Vertex* v : vertices) 
	{
		if (v->outgoingHE == nullptr) return false;
	}
	return true;
}

bool HalfEdgeDS::checkHalfEdges()
{
	for (HalfEdge* he : halfEdges)
	{
		if (he->startV == nullptr) return false;
		if (he->nextHE == nullptr) return false;
		if (he->prevHE == nullptr) return false;
		if (he->toEdge == nullptr) return false;
		if (he->toLoop == nullptr) return false;
		if (he->prevHE->nextHE != he) return false;
		if (he->nextHE->prevHE != he) return false;
		if (he->getConjugate() == nullptr) return false;
	}
	return true;
}

bool HalfEdgeDS::checkEdges()
{
	for (Edge* e : edges)
	{
		if (e->he1 == nullptr) return false;
		if (e->he2 == nullptr) return false;
	}
	return true;
}

bool HalfEdgeDS::checkLoops()
{
	for (Loop* l : loops)
	{
		if (l->toHE == nullptr) return false;
		HalfEdge* he = l->toHE;
		do 
		{
			he = he->nextHE;
		} 
		while (he != l->toHE);
	}
	return true;
}

std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds)
{
	os << "Elements in the lists of the data structure:" << std::endl;
	os << "  " << ds.solids.size() << " solids, "
		<< ds.faces.size() << " faces, "
		<< ds.loops.size() << " loops, "
		<< ds.edges.size() << " edges, "
		<< ds.halfEdges.size() << " halfEdges, "
		<< ds.vertices.size() << " vertices.";
	return os;
}
