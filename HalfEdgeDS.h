// ========================================================================= //
// Authors: Matthias Borner                                                  //
// mailto:matthias.borner@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universität Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
// ========================================================================= //

#ifndef HALF_EDGE_DS_H
#define HALF_EDGE_DS_H

#include <stdlib.h>		// standard library
#include <vector>		// std::vector<>
#include <list>			// std::list<>

#include "HalfEdgeDSElements.h"

// Handles creating, verifying and modifying a half edge data structure.
// Also manages memory. Since we heavily rely on raw pointers, we need to use "new" and "delete", else we get memory leaks.
class HalfEdgeDS
{

protected:

	// class members: lists of pointers to the elements. these are unsorted. the next element is not necessarily connected to the previous one.
	// so this class owns all created data structure elements and is responsible for adding new ones and deleting old ones.
	std::list<Solid*> solids;
	std::list<Face*> faces;
	std::list<Loop*> loops;
	//std::list<Loop*> innerLoops;
	std::list<Edge*> edges;
	std::list<HalfEdge*> halfEdges;
	std::list<Vertex*> vertices;

public:

	// empty constructor which creates an example object
	HalfEdgeDS();

	// deletes the content of the data structure
	~HalfEdgeDS();

	// creates a default example object
	void createDefaultObject();
	void buildDefaultObject();

	// clears the data structure completely
	void clearDS();

	// getters with read only access, returned as reference, so nothing gets copied
	const std::list<Solid*>& getSolids() const { return solids; }
	const std::list<Face*>& getFaces() const { return faces; }
	const std::list<Loop*>& getLoops() const { return loops; }
	const std::list<Edge*>& getEdges() const { return edges; }
	const std::list<HalfEdge*>& getHalfEdges() const { return halfEdges; }
	const std::list<Vertex*>& getVertices() const { return vertices; }

	// overloading the << operator to print our information of the class
	friend std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds);

	// TODO: Extend the interface of the this data structure by implementing at least four euler operators
	void mevvls(Edge& E1, Vertex& V1, Vertex& V2, Loop& L1, Solid& S1, float x1, float y1, float z1, float x2, float y2, float z2);

	void mev(Loop& L1, Vertex& V1, Edge& E1, Vertex& V2, float x, float y, float z);

	void mve(Edge& E1, Vertex& V1, Edge& E2, float x, float y, float z);

	void mel(Loop& L1, Vertex& V1, Vertex& V2, Edge& E1, Loop& L2);

	void kemh(Vertex& V1, Vertex& V2, Loop& L1, Loop& L2, Edge& E1);

	bool checkDS();

	// TODO: Check if the data structure is correct using the Euler-Poincare formula

	bool checkEulerPoincare();

private:

	bool checkVertices();
	bool checkHalfEdges();
	bool checkEdges();
	bool checkLoops();
	bool checkFaces();

	int state = -1;

	/// Create Edges for test element
	Edge* e1,* e2,* e3,* e4,* e5,* e6,* e7,* e8,* e9,* e10,* e11,* e12;
	/// Create Vertices for test element
	Vertex* v1,* v2,* v3,* v4,* v5,* v6,* v7,* v8;

	Loop* l1,* l2,* l3,* l4,* l5,* l6;
	Solid* s1;

	// Test of MEKH
	Edge* e13,* e14,* e15,* e16,* e17;
	Vertex* v9,* v10,* v11,* v12,* v13,* v14,* v15,* v16;
	Edge* e21,* e22,* e23,* e24,* e25,* e26,* e27,* e28;
	Loop* l7,* l8,* l9,* l10,* l11,* l12;
};

// ostream << operator to print some info of the data structure
std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds);

#endif
