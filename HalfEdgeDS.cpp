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
	/// Create Edges for test element
	Edge* e1 = new Edge();
	Edge* e2 = new Edge();
	Edge* e3 = new Edge();
	Edge* e4 = new Edge();

	Edge* e5 = new Edge();
	Edge* e6 = new Edge();
	Edge* e7 = new Edge();
	Edge* e8 = new Edge();

	Edge* e9 = new Edge();

	/// Create Vertices for test element
	Vertex* v1 = new Vertex();
	Vertex* v2 = new Vertex();
	Vertex* v3 = new Vertex();
	Vertex* v4 = new Vertex();

	//---------- TEST OBJECTS FOR MEKH BEGIN----------------//

	Edge* e10 = new Edge();
	Edge* e11 = new Edge();
	Edge* e12 = new Edge();
	Edge* e13 = new Edge();
	Edge* e14 = new Edge();
	Edge* e15 = new Edge();
	Edge* e16 = new Edge();
	Edge* e17 = new Edge();

	Vertex* v9 = new Vertex();
	Vertex* v10 = new Vertex();
	Vertex* v11 = new Vertex();
	Vertex* v12 = new Vertex();

	
	//---------- TEST OBJECTS FOR MEKH END----------------//

	Vertex* v5 = new Vertex();
	Vertex* v6 = new Vertex();
	Vertex* v7 = new Vertex();
	Vertex* v8 = new Vertex();

	/// Create Loops for test element
	Loop* l1 = new Loop();
	Loop* l2 = new Loop();

	Loop* l3 = new Loop(); 
	Loop* l4 = new Loop();
	Loop* l5 = new Loop();
	Loop* l6 = new Loop();
	Loop* l7 = new Loop();
	Loop* l8 = new Loop();


	/// Create Solids for test element
	Solid* s1 = new Solid();
	//Solid* s2 = new Solid();

	/// Run Euler operations

	// base
	mevvls(*e1, *v1, *v2, *l1, *s1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f);
	mev(*l1, *v2, *e2, *v3, 2.0f, 1.0f, 2.0f);
	mel(*l1, *v1, *v3, *e4, *l2);
	mve(*e4, *v4, *e3, 2.0f, 1.0f, 1.0f);

	
	mev(*l1, *v1, *e5, *v5, 1.0f, 2.0f, 1.0f);
	mev(*l1, *v2, *e6, *v6, 1.0f, 2.0f, 2.0f);
	mev(*l1, *v3, *e7, *v7, 2.0f, 2.0f, 2.0f);
	mev(*l1, *v4, *e8, *v8, 2.0f, 2.0f, 1.0f);

	//mel(*l1, *v5, *v6, *e9, *l3);
	mel(*l1, *v6, *v7, *e10, *l4);
	//mel(*l1, *v7, *v8, *e11, *l5);
	mel(*l1, *v8, *v5, *e12, *l6);
	

	

	//------- Creating inner Edges --------//
	/*
	mev(*l2, *v1, *e13, *v9, 1.25f, 1.0f, 1.25f);
	mev(*l2, *v9, *e14, *v10, 1.75f, 1.0f, 1.25f);
	mev(*l2, *v10, *e15, *v11, 1.75f, 1.0f, 1.75f);
	mev(*l2, *v11, *e16, *v12, 1.25f, 1.0f, 1.75f);
	
	mel(*l2, *v9,*e14, *e13, *v12, *e16, *e16, *e17, *l7);
	
	//kemh(*v1, *v9, *l2, *l8, *e10);
	*/


	/// check datastructure topology
	if (!checkEdges()) std::cout << "WARN: checkEdges NOT valid! (blame the programmer)" << std::endl;
	if (!checkHalfEdges()) std::cout << "WARN: checkHalfEdges NOT valid! (blame the programmer)" << std::endl;
	if (!checkLoops()) std::cout << "WARN: checkLoops NOT valid! (blame the programmer)" << std::endl;
	if (!checkVertices()) std::cout << "WARN: checkVertices NOT valid! (blame the programmer)" << std::endl;
	
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

/**
* Make-Edge-Vertex-Vertex-Loop-Solid 
* Start a new Solid by making an Edge E1 starting at new Vertex V1 and ending at new Vertex V2 with given coordinates in new Loop L1 and part of new Solid S1 
*
* Note: old topological Elements as pointers and new Elements as reference?
*
* @param E1 new Edge
* @param V1 starting Vertex for Edge E1
* @param V2 new end Vertex for Edge E1
* @param L1 new Loop
* @param S1 new Solid
* @param x, y, z Vertex V2-coordinates
*/
void HalfEdgeDS::mevvls(Edge& E1, Vertex& V1, Vertex& V2, Loop& L1, Solid& S1, float x1, float y1, float z1, float x2, float y2, float z2)
{
	/// Create new Vectors for coordinates
	Vec3f p1(x1, y1, z1);
	Vec3f p2(x2, y2, z2);

	/// Create new HalfEdges for new Edge
	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();

	/// Create new Face for new Loop
	Face* f1 = new Face();

	/// set new Vertices
	V1.coordinates = p1;
	V2.coordinates = p2;
	V1.outgoingHE = he1;
	V2.outgoingHE = he2;

	/// set new HalfEdges
	he1->toLoop = &L1; // on same Loop
	he2->toLoop = &L1;
	he1->toEdge = &E1; // part of same Edge
	he2->toEdge = &E1;
	he1->startV = &V1; // starting from different Vertices
	he2->startV = &V2;
	he1->prevHE = he2; // pointing to each other
	he2->prevHE = he1;
	he1->nextHE = he2;
	he2->nextHE = he1;
	
	/// set HalfEdges of new Edge
	E1.he1 = he1;
	E1.he2 = he2;

	/// set new Loop
	L1.toFace = f1;
	L1.prevLoop = &L1;
	L1.nextLoop = &L1;
	L1.toHE = he1; // choose any HalfEdge
	
	/// set new Face
	f1->toSolid = &S1;
	f1->outerLoop = &L1;
	f1->innerLoop = nullptr;

	/// set new Solid
	S1.toFace = f1;

	/// insert new Vertices, HalfEdges, Edge, Loop, Face and Solid at the end of the fields and increase size by one
	vertices.push_back(&V1);
	vertices.push_back(&V2);
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	edges.push_back(&E1);
	loops.push_back(&L1);
	faces.push_back(f1);
	solids.push_back(&S1);

}

/**
* Make-Edge-Vertex 
* Make an Edge E1 starting at Vertex V1 and ending at new Vertex V2 with coordinates x,y,z in Loop L1 
* 
* Note: old topological Elements as pointers and new Elements as reference?
* 
* @param L1 Loop where Edge will be added
* @param V1 starting Vertex for Edge E1
* @param E1 new Edge
* @param V2 new Vertex
* @param x, y, z Vertex-coordinates
*/
void HalfEdgeDS::mev(Loop& L1, Vertex& V1, Edge& E1, Vertex& V2, float x, float y, float z)
{
	/// Create new Vector for coordinates
	Vec3f p(x, y, z);

	/// Create new HalfEdges for new Edge
	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();

	/// set new Vertex V2
	V2.coordinates = p;
	V2.outgoingHE = he2;

	/// get necessary HalfEdges
	HalfEdge* inbound_he = V1.getRandInboundHE(&L1);
	HalfEdge* outbound_he = inbound_he->nextHE;
	/// set HalFEdge connections
	inbound_he->nextHE = he1;
	he1->prevHE = inbound_he;
	he1->nextHE = he2; // new Edge goes to and away from V2
	he2->prevHE = he1;
	he2->nextHE = outbound_he;
	outbound_he->prevHE = he2;

	/// set start Vertices for new HalfEdges
	he1->startV = &V1;
	he2->startV = &V2;
	/// set loop for new HalfEdges
	he1->toLoop = &L1;
	he2->toLoop = &L1;
	/// set parent Edge for new HalfEdges
	he1->toEdge = &E1;
	he2->toEdge = &E1;
	///
	L1.toHE = he1;
	L1.toHE = he2;
	/// set HalfEdges of new Edge
	E1.he1 = he1;
	E1.he2 = he2;

	/// insert new Vertex, HalfEdges and Edge at the end of the fields and increase size by one
	vertices.push_back(&V2);
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	edges.push_back(&E1);
}

/**
* Make-Vertex-Edge
* Split an Edge E1 at new Vertex V1 with coordinates x,y,z into two parts with new Edge E1 
*
* Note: old topological Elements as pointers and new Elements as reference?
*
* @param E1 Edge to be splitted
* @param V1 Vertex where Edge E1 will end and new Edge E2 start
* @param E2 new Edge
* @param x, y, z Vertex-coordinates
*/
void HalfEdgeDS::mve(Edge& E1, Vertex& V1, Edge& E2, float x, float y, float z)
{
	/// Create new Vector for coordinates
	Vec3f p(x, y, z);
	/// Create new HalfEdges for new Edge
	HalfEdge* rightHE1 = new HalfEdge();
	HalfEdge* rightHE2 = new HalfEdge();

	/// set new Vertex
	V1.coordinates = p;
	V1.outgoingHE = rightHE1;

	/// get necessary Vertices and HalfEdges
	Vertex* leftV = E1.he1->startV;
	Vertex* rightV = E1.he2->startV;
	HalfEdge* leftHE1 = E1.he1;
	HalfEdge* leftHE2 = E1.he2;

	/// set new connections to outer HalfEdges
	rightHE1->nextHE = leftHE1->nextHE;
	leftHE1->nextHE->prevHE = rightHE1;
	rightHE2->prevHE = leftHE2->prevHE;
	leftHE2->prevHE->nextHE = rightHE2;

	/// set connections at Vertex for new HalfEdges
	rightHE1->prevHE = leftHE1;
	rightHE2->nextHE = leftHE2;

	/// set start Vertices for new HalfEdges
	rightHE1->startV = &V1;
	rightHE2->startV = rightV;

	/// set connections at Vertex for old HalfEdges
	leftHE1->nextHE = rightHE1;
	leftHE2->prevHE = rightHE2;

	/// set new starting Vertex for old HalfEdge
	leftHE2->startV = &V1;

	/// set new outgoing HalfEdges for Vertices
	leftV->outgoingHE = leftHE1; // ? nicht schon gesetzt?
	rightV->outgoingHE = rightHE2;

	/// set parent Edge for new HalfEdges
	rightHE1->toEdge = &E2;
	rightHE2->toEdge = &E2;
	/// set Loops for new HalfEdges
	rightHE1->toLoop = leftHE1->toLoop;
	rightHE2->toLoop = leftHE2->toLoop;

	/// set HalfEdges of new Edge
	E2.he1 = rightHE1;
	E2.he2 = rightHE2;

	/// insert new Vertex, HalfEdges and Edge at the end of the fields and increase size by one
	vertices.push_back(&V1);
	halfEdges.push_back(rightHE1);
	halfEdges.push_back(rightHE2);
	edges.push_back(&E2);
}

/**
* Make-Edge-Loop (Simple)
* Make an Edge E1 starting at Vertex V1 and ending at Vertex V2 which closes Loop L1 and make a new Loop L2 on the other side of Loop L1
* NOTE: If one Vertex has more than 1 inbound edge on same Loop use the other overloaded function!
*
* @param L1 Loop which Edge E1 will close
* @param V1 starting Vertex for Edge E1
* @param V2 end Vertex for Edge E1
* @param E1 new Edge
* @param L2 new Loop
*/
void HalfEdgeDS::mel(Loop& L1, Vertex& V1, Vertex& V2, Edge& E1, Loop& L2)
{
	Edge* v1Ei = V1.getRandInboundHE(&L1)->toEdge;
	Edge* v1Eo = V1.getRandInboundHE(&L1)->nextHE->toEdge;
	Edge* v2Ei = V2.getRandInboundHE(&L1)->toEdge;
	Edge* v2Eo = V2.getRandInboundHE(&L1)->nextHE->toEdge;
	this->mel(L1, V1, *v1Ei, *v1Eo, V2, *v2Ei, *v2Eo, E1, L2);
}


/**
* Make-Edge-Loop (Advanced)
* Make an Edge E1 starting at Vertex V1 and ending at Vertex V2 which closes Loop L1 and make a new Loop L2 on the other side of Loop L1
* 
* @param L1 Loop which Edge E1 will close
* @param V1 starting Vertex for Edge E3
* @param E1inner Edge on the (new) inner loop next to V1
* @param E1ounter Edge on the (existing) outer loop next to V1
* @param V2 end Vertex for Edge E3
* @param E2inner Edge on the (new) inner loop next to V2
* @param E2ounter Edge on the (existing) outer loop next to V2
* @param E3 new Edge
* @param L2 new Loop
*/
void HalfEdgeDS::mel(Loop& L1, Vertex& V1, Edge& E1inner, Edge& E1outer, Vertex& V2, Edge& E2inner, Edge& E2outer, Edge& E3, Loop& L2)
{
	/// get necessary HalfEdges
	HalfEdge* leftOutboundHE,* leftInboundHE,* rightOutboundHE,* rightInboundHE;
	if (E1inner.he1->startV == &V1)
		leftOutboundHE = E1inner.he1;
	else if (E1inner.he2->startV == &V1)
		leftOutboundHE = E1inner.he2;
	else
		std::cout << "ERR: mel E1inner not near V1";

	if (E1outer.he1->nextHE->startV == &V1)
		leftInboundHE = E1outer.he1;
	else if (E1outer.he2->nextHE->startV == &V1)
		leftInboundHE = E1outer.he2;
	else
		std::cout << "ERR: mel E1outer not near V1";


	if (E2outer.he1->startV == &V2)
		rightOutboundHE = E2outer.he1;
	else if (E2outer.he2->startV == &V2)
		rightOutboundHE = E2outer.he2;
	else
		std::cout << "ERR: mel E2outer not near V2";

	if (E2inner.he1->nextHE->startV == &V2)
		rightInboundHE = E2inner.he1;
	else if (E2inner.he2->nextHE->startV == &V2)
		rightInboundHE = E2inner.he2;
	else
		std::cout << "ERR: mel E2outer not near V2";


	/// Create new HalfEdges for new Edge
	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();

	/// set connections on "clockwise" Loop
	leftInboundHE->nextHE = he1;
	he1->prevHE = leftInboundHE;
	he1->nextHE = rightOutboundHE;
	rightOutboundHE->prevHE = he1;

	/// set connections on "counter-clockwise" Loop
	rightInboundHE->nextHE = he2;
	he2->prevHE = rightInboundHE;
	he2->nextHE = leftOutboundHE;
	leftOutboundHE->prevHE = he2;

	/// set Loops for new HalfEdges
	he1->toLoop = &L1;
	he2->toLoop = &L2;

	/// set new Loop for HalfEdges succesive to he2
	HalfEdge* he = he2->nextHE;
	while (he != he2)
	{
		he->toLoop = &L2;
		he = he->nextHE;
	}

	/// set start Vertices for new HalfEdges
	he1->startV = &V1;
	he2->startV = &V2;

	/// set parent Edge for new HalfEdges
	he1->toEdge = &E3;
	he2->toEdge = &E3;

	/// set HalfEdges of new Edge
	E3.he1 = he1;
	E3.he2 = he2;

	/// set any HalfEdge of Loop as reference to ensure the HalfEdge is on the Loop
	L1.toHE = he1;
	L2.toHE = he2;

	//handle faces

	/// insert new HalfEdges, Edge and Loop at the end of the fields and increase size by one
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	edges.push_back(&E3);
	loops.push_back(&L2);
	if (!checkLoops()) std::cout << "WARN: checkLoops NOT valid! (blame the programmer)" << std::endl;

}

/**
* Kill-Edge-Make-Hole
* 
* Note ONLY outer loop to inner loop NOT inner loop to two inner loops
*
* @param V1 starting Vertex for Edge E1
* @param V2 end Vertex for Edge E1
* @param L1 Loop that will be split
* @param L2 new Loop
* @param E1 Edge to kill
*/
void HalfEdgeDS::kemh(Vertex& V1, Vertex& V2, Loop& L1, Loop& L2, Edge& E1)
{

	// Get next HalfEdge of the Edge which will deleted
	
	HalfEdge* he1 = E1.he1;
	if (he1->startV != &V1) {
		he1 = E1.he2;
	}

	he1 = he1->nextHE;
	//he1->getConjugate();
	// Add Edge to loop L2
	he1->toLoop = &L2;
	L2.toHE = he1;
	
	// get the next HalfEdge, to create clockwise loop
	HalfEdge* he = he1->nextHE;
	while (he->startV != &V2)
	{
		he->toLoop = &L2;
		if (he->nextHE->startV == &V2) {
			he->nextHE = he1;
			he1->prevHE = he;
			break;
		}
		he = he->nextHE;
	}
	
	// Close Loop L1
	if (E1.he1->startV == &V1) {
		E1.he1->prevHE->nextHE = E1.he2->nextHE;
		E1.he2->nextHE->prevHE = E1.he1->prevHE;
		L1.toHE = E1.he1->prevHE->nextHE;
	}
	else {
		E1.he2->prevHE->nextHE = E1.he1->nextHE;
		E1.he1->nextHE->prevHE = E1.he2->prevHE;
		L1.toHE = E1.he2->prevHE->nextHE;
	}

	
	


	std::cout << "Ausgehende Edge " << &V1.outgoingHE << " Eingehende Edge " << V1.getRandInboundHE(&L1) << std::endl;
	// remove the Edge
	edges.remove(&E1);	
	// remove the HalfEdges of the Edge
	halfEdges.remove(E1.he1);
	halfEdges.remove(E1.he2);
	//delete Edges

	//delete E1.he1;
	//delete E1.he2;
	delete &E1;
	// Push Loop in loop list
	loops.push_back(&L2);
	innerLoops.push_back(&L2);
	}

/**
* Run selfmade check functions
*/
bool HalfEdgeDS::checkDS() 
{
	return checkVertices() && checkHalfEdges() && checkEdges();//&& checkLoops();
}

/*
* Check Euler Poincare formula
*/

bool HalfEdgeDS::checkEulerPoincare()
{
	/// V - E + F = 2 (S - R) + H
	// Left side of formula
	int V = getVertices().size();
	int E = getEdges().size();
	int F = getFaces().size();

	// Right side of Formula
	/// S: Number of Shells = 1 (no support for inner Shells)
	int S = 1;

	/// R: Number of Rings: "Volume breaktroughs"
	int R = 0;

	int H = V - E + F - 2 * (S - R);
	/// H: Number of Holes
	std::cout << "Existieren " << "H" << " L�cher? j/n";
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
		if (he->startV == nullptr) std::cout << "WARN: he->startV == nullptr" << he << std::endl;
		if (he->nextHE == nullptr) std::cout << "WARN: he->nextHE == nullptr" << he << std::endl;
		if (he->prevHE == nullptr) std::cout << "WARN: he->prevHE == nullptr" << he << std::endl;
		if (he->toEdge == nullptr) std::cout << "WARN: he->toEdge == nullptr" << he << std::endl;
		if (he->toLoop == nullptr) std::cout << "WARN: he->toLoop == nullptr" << he << std::endl;
		if (he->startV == nullptr) return false;
		if (he->nextHE == nullptr) return false;
		if (he->prevHE == nullptr) return false;
		if (he->toEdge == nullptr) return false;
		if (he->toLoop == nullptr) return false;
		if (he->prevHE->nextHE != he) std::cout << "WARN: he->prevHE->nextHE != he" << he << std::endl;
		if (he->nextHE->prevHE != he) std::cout << "WARN: he->nextHE->prevHE != he" << he << std::endl;
		if (he->getConjugate() == nullptr) std::cout << "WARN: getConjugate() == nullptr" << he << std::endl;
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
		int i = 0;
		do 
		{
			if (he->toLoop != l) std::cout << "ERR: he" << he << " not on loop, but should be!" << std::endl;
			if (he->toLoop != l) std::cout << "ERR: he" << he << " not on loop " << l << ", but should be!" << std::endl;
			if (he == nullptr) return false;
			he = he->nextHE;
			i++;
			if (i > 1000) return false;
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
