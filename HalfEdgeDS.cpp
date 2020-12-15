#include "HalfEdgeDS.h"

#include <stdio.h>		// cout
#include <iostream>		// cout

HalfEdgeDS::HalfEdgeDS()
{
	clearDS();
	buildDefaultObject();
}	

HalfEdgeDS::~HalfEdgeDS()
{
	clearDS();
}

void HalfEdgeDS::createDefaultObject()
{
	for (int i = 0; i < 10; i++)
	{
		buildDefaultObject();
	}
}

void HalfEdgeDS::buildDefaultObject()
{
	// WARNING: this example does NOT create a valid topology. It just creates the minimum elements to draw one line.
	// CARE: for every "new" we need a "delete". if an element is added to the according list, it is deleted automatically within clearDS().
	/*Vertex* v1 = new Vertex;
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
	edges.push_back(e);*/

	/// increase state for showcase purposes
	state++;
	
	/// Run Euler operations

	//------- Creating a base cube with inner object --------//
	
	switch (this->state) {
	case 0:
		/// Create Edges for test element
		this->e1 = new Edge();
		this->e2 = new Edge();
		this->e3 = new Edge();
		this->e4 = new Edge();

		this->e5 = new Edge();
		this->e6 = new Edge();
		this->e7 = new Edge();
		this->e8 = new Edge();

		this->e9 = new Edge();
		this->e10 = new Edge();
		this->e11 = new Edge();
		this->e12 = new Edge();

		/// Create Vertices for test element
		this->v1 = new Vertex();
		this->v2 = new Vertex();
		this->v3 = new Vertex();
		this->v4 = new Vertex();

		this->v5 = new Vertex();
		this->v6 = new Vertex();
		this->v7 = new Vertex();
		this->v8 = new Vertex();

		/// Create Vertices for inner element (MEKH)
		this->e13 = new Edge();
		this->e14 = new Edge();
		this->e15 = new Edge();
		this->e16 = new Edge();
		this->e17 = new Edge();

		this->v9 = new Vertex();
		this->v10 = new Vertex();
		this->v11 = new Vertex();
		this->v12 = new Vertex();

		this->v13 = new Vertex();
		this->v14 = new Vertex();
		this->v15 = new Vertex();
		this->v16 = new Vertex();

		this->e21 = new Edge();
		this->e22 = new Edge();
		this->e23 = new Edge();
		this->e24 = new Edge();
		this->e25 = new Edge();
		this->e26 = new Edge();
		this->e27 = new Edge();
		this->e28 = new Edge();


		/// Create Loops for test element
		// basic square
		this->l1 = new Loop(); // conceptional outer Loop
		this->l2 = new Loop();

		// finish cube
		this->l3 = new Loop();
		this->l4 = new Loop();
		this->l5 = new Loop();
		this->l6 = new Loop();

		// hole
		this->l7 = new Loop();
		this->l8 = new Loop();

		this->l9 = new Loop();
		this->l10 = new Loop();
		this->l11 = new Loop();
		this->l12 = new Loop();

		/// Create Solids for test element
		s1 = new Solid();

		break;
	case 1:
		mevvls(*e1, *v1, *v2, *l1, *s1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f);
		break;
	case 2:
		mev(*l1, *v2, *e2, *v3, 2.0f, 1.0f, 2.0f);
		break;
	case 3:
		mev(*l1, *v3, *e3, *v4, 2.0f, 1.0f, 1.0f);
		break;
	case 4:
		mel(*l1, *v4, *v1, *e4, *l2);
		//state = 6;
		break;
	case 5:
		// Creating upwards edges
		mev(*l1, *v1, *e5, *v5, 1.0f, 2.0f, 1.0f);
		mev(*l1, *v2, *e6, *v6, 1.0f, 2.0f, 2.0f);
		mev(*l1, *v3, *e7, *v7, 2.0f, 2.0f, 2.0f);
		mev(*l1, *v4, *e8, *v8, 2.0f, 2.0f, 1.0f);
		break;
	case 6:
		mel(*l1, *v5, *v6, *e9, *l3);
		mel(*l1, *v6, *v7, *e10, *l4);
		mel(*l1, *v7, *v8, *e11, *l5);
		mel(*l1, *v8, *v5, *e12, *l6);
		break;
	case 7:
		// Creating inner Edges
		mev(*l2, *v1, *e13, *v9, 1.25f, 1.0f, 1.25f);
		mev(*l2, *v9, *e14, *v10, 1.25f, 1.0f, 1.75f);
		mev(*l2, *v10, *e15, *v11, 1.75f, 1.0f, 1.75f);
		mev(*l2, *v11, *e16, *v12, 1.75f, 1.0f, 1.25f);
		break;
	case 8:
		// Closing inner loop
		mel(*l2, *v12, *v9, *e17, *l7);
		break;
	case 9:
		// Separate inner loop
		kemh(*v1, *v9, *l2, *l8, *e13);
		break;
	case 10:
		// Creating inner upwards edges
		mev(*l7, *v9, *e21, *v13, 1.25f, 1.5f, 1.25f);
		mev(*l7, *v10, *e22, *v14, 1.25f, 1.5f, 1.75f);
		mev(*l7, *v11, *e23, *v15, 1.75f, 1.5f, 1.75f);
		mev(*l7, *v12, *e24, *v16, 1.75f, 1.5f, 1.25f);
		break;
	case 11:
		mel(*l7, *v13, *v14, *e25, *l9);
		break;
	case 12:
		mel(*l9, *v14, *v15, *e26, *l10);
		break;
	case 13:
		mel(*l10, *v16, *v15, *e27, *l11);
		break;
	case 14:
		mel(*l10, *v16, *v13, *e28, *l12);
		break;
		
		
		/**/
		/*

		//------- Basic MVE Example --------//
	case 1:
		mevvls(*e1, *v1, *v2, *l1, *s1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f);
		break;
	case 2:
		mev(*l1, *v2, *e2, *v3, 2.0f, 1.0f, 2.0f);
		break;
	case 3:
		mel(*l1, *v1, *v3, *e3, *l2);
		break;
	case 4:
		mve(*e3, *v4, *e4, 2.0f, 1.0f, 1.0f);
		*/
	}
	std::cout << *this << std::endl;
	
	

	/// check datastructure correctness
	if (!checkFaces()) std::cout << "WARN: checkFaces NOT valid! (blame the programmer)" << std::endl;
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
	L1.toHE = he1; // choose any HalfEdge
	
	/// set new Face
	f1->toSolid = &S1;
	f1->outerLoop = &L1;

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
	//leftV->outgoingHE = leftHE1; // ? nicht schon gesetzt?
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
* Make-Edge-Loop
* Make an Edge E1 starting at Vertex V1 and ending at Vertex V2 which closes Loop L1 and make a new Loop L2 on the other side of Loop L1
*
* @param L1 Loop which Edge E1 will close
* @param V1 starting Vertex for Edge E1
* @param V2 end Vertex for Edge E1
* @param E1 new Edge
* @param L2 new Loop
*/
void HalfEdgeDS::mel(Loop& L1, Vertex& V1, Vertex& V2, Edge& E1, Loop& L2)
{
	/// Zur Start HE auf dem Loop traversieren
	HalfEdge* startHe = L1.toHE;
	while (startHe->startV != &V1) {
		startHe = startHe->nextHE;
	}

	/// Start HE kopieren, um später zu bearbeiten
	HalfEdge* connectionHE = startHe;
	HalfEdge* backConnectionHE = startHe->prevHE;

	/// Alle Folgenden HE dem neuen Loop zuweisen
	while (startHe->startV != &V2) {
		startHe->toLoop = &L2;
		startHe = startHe->nextHE;
	}

	/// Neue und Halfedges von v1 nach v2 erstellen 
	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();

	he1->startV = &V1;
	he2->startV = &V2;

	V1.outgoingHE = he1;
	V2.outgoingHE = he2;

	he1->toEdge = &E1;
	he2->toEdge = &E1;

	he1->toLoop = &L1;
	he2->toLoop = &L2;

	/// Halfedges der Edge zuweisen
	E1.he1 = he1;
	E1.he2 = he2;

	/// Sicherstellen, dass Loops mit HE verbunden sind
	L1.toHE = he1;
	L2.toHE = he2;

	/// Kanten des inneren Loops verbinden und schließen
	startHe->prevHE->nextHE = he2;
	he2->prevHE = startHe->prevHE;
	he2->nextHE = connectionHE;
	connectionHE->prevHE = he2;


	/// Kanten des äußeren Loops verbinden und schließen

	backConnectionHE->nextHE = he1;
	he1->prevHE = backConnectionHE;
	startHe->prevHE = he1;
	he1->nextHE = startHe;

	
	Face* f2 = new Face();
	f2->outerLoop = &L2;
	L2.toFace = f2;


	edges.push_back(&E1);
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	loops.push_back(&L2);
	faces.push_back(f2);
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

	// remove the Edge
	edges.remove(&E1);	
	// remove the HalfEdges of the Edge
	halfEdges.remove(E1.he1);
	halfEdges.remove(E1.he2);
	//delete Edges
	delete E1.he1;
	delete E1.he2;
	delete &E1;

	//TODO
	L1.toFace->innerLoops.push_back(&L2);
	L2.toFace = L1.toFace;

	loops.push_back(&L2);
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

	/// H: Number of Holes
	int H = 0;
	/// Run through all Faces and count inner loops
	for (Face* f : faces)
	{
		H += f->innerLoops.size();
	}
	//std::cout << " " << H << " inner Loops" << std::endl;

	/// R: Number of Rings: "Volume breaktroughs"
	int R = (- V + E - F + 2 * S + H)/2;
	std::cout << "Existieren " << R << " Volumendurchbrueche? j/n :" << std::endl;
	std::string c;
	std::cin >> c;
	if (c == "j")
		std::cout << "Dein Objekt ist topologisch korrekt." << std::endl;
	else if (c == "n")
		std::cout << "Dein Objekt ist nicht topologisch korrekt." << std::endl;
	else 
		std::cout << "Unerkannter Buchstabe. Bitte starte den Befehl neu und gib j oder n an." << std::endl;
	return false;
}

bool HalfEdgeDS::checkVertices()
{
	for (Vertex* v : vertices) 
	{
		if (v->outgoingHE == nullptr) return false;
		if (v->outgoingHE->startV != v) return false;
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
			if (i > 10000) return false;
		} 
		while (he != l->toHE);
		if (l->toFace == nullptr) return false;
	}
	return true;
}

bool HalfEdgeDS::checkFaces() {
	for (Face* f : faces)
	{
		if (f->outerLoop == nullptr) std::cout << "ERR: f->outerLoop" <<  " == nullptr" << std::endl;
		if (f->outerLoop == nullptr) return false;
		if (f->outerLoop->toFace != f) std::cout << "ERR: f->outerLoop->toFace " << " == nullptr" << std::endl;
		if (f->outerLoop->toFace != f) return false;
		if (f->innerLoops.size() > 0)
		{
			for (Loop* il : f->innerLoops) {
				if (il->toFace != f) std::cout << "ERR: innerloop->toFace" << il->toFace << " !=  " << f << std::endl;
				if (il->toFace != f) return false;
			}
		}
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
