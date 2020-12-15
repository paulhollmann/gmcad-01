#define RADPERDEG 0.0174533

#include "HalfEdgeDSRendering.h"

#include <GL/glut.h>

/**
* Render whole datastructure through Vertices and Edges
*/
void renderDS(const HalfEdgeDS& heDS)
{
	for (auto const *v : heDS.getVertices()) renderV(v); // render all vertices as points
	for (auto const *e : heDS.getEdges()) renderE(e); // render all edges as lines
}

void renderDS(const HalfEdgeDS& heDS, const HalfEdge* activeHE, const Loop* activeLoop, const Face* activeFace) 
{
	// render all vertices as points
	for (const Vertex* v : heDS.getVertices()) renderV(v); 
	
	// render all unselected edges as normal lines lines
	for (const Edge* e : heDS.getEdges()) {
		//filter activeHE Edges
		if (activeHE != nullptr && (e->he1 == activeHE || e->he2 == activeHE)) goto skip;

		//filter activeLoop Edges
		if (activeLoop != nullptr){
			HalfEdge* he = activeLoop->toHE;
			while (he != activeLoop->toHE) {
			if (e->he1 == he || e->he2 == he) goto skip;
			he = he->nextHE;
			}
		}

		//filter activeFace Edges
		if (activeFace != nullptr) {
			for (Loop* innerL : activeFace->innerLoops) {
				HalfEdge* he = innerL->toHE;
				while (he != innerL->toHE) {
					if (e->he1 == he || e->he2 == he) goto skip;
					he = he->nextHE;
				}
			}
			HalfEdge* he = activeFace->outerLoop->toHE;
			while (he != activeFace->outerLoop->toHE) {
				if (e->he1 == he || e->he2 == he) goto skip;
				he = he->nextHE;
			}
		}
		renderE(e);
		skip:;
	}


	// TODO draw the selected stuff
}

/**
* Render the Edge with given color-Vector
* 
* @param e Edge passed to GL
* @param color to draw Edge in
*/
void renderE(const Edge* e, const Vec3f& color /*= Vec3f(0.0f, 1.0f, 0.0f)*/)
{
	// TODO: render the edge with the given color
	/// delimits a definition of a Line primitive
	glBegin(GL_LINES);
	// set the begin of the components for the Color
	glColor3fv(&color.x);
	/// define two vertices by their coordinates
	glVertex3fv(&e->he1->startV->coordinates.x);
	glVertex3fv(&e->he2->startV->coordinates.x);
	/// first two Vertices will be grouped into a line
	/// end of line definition
	glEnd(); 
}

/**
* Render the HalfEdge with given Color Vector
* 
* @param he HalfEdge passed to GL
* @param color to draw HalfEdge in
*/
void renderHE(const HalfEdge* he, const Vec3f& color /*= Vec3f(0.0f, 1.0f, 0.0f)*/)
{
	// TODO: render the half-edge with the given color
	/// delimits a definition of a Line primitive
	glBegin(GL_LINES);
	// set the begin of the components for the Color
	glColor3fv(&color.x);
	glVertex3fv(&he->startV->coordinates.x);
	/// find start / end Vertex
	Edge* e = he->toEdge;
	if (e->he1->startV == he->startV)
		glVertex3fv(&e->he2->startV->coordinates.x);
	else
		glVertex3fv(&e->he1->startV->coordinates.x);

	/// first two Vertices will be grouped into a line
	/// end of line definition
	glEnd();
}

/**
* Render the Vertex with given Color Vector
*
* @param v Vertex passed to GL
* @param color to draw Vertex in
*/
void renderV(const Vertex* v, const Vec3f& color /*= Vec3f(1.0f, 0.0f, 1.0f)*/)
{
	// TODO: render the vertex with the given color
	/// delimits a definition of a Point primitive
	glBegin(GL_POINTS);
	// set the begin of the components for the Color
	glColor3fv(&color.x);
	// set the begin of the components for the Coordinates
	glVertex3fv(&v->coordinates.x);
	glEnd();
	/// end of point definition
}
/**
* Render the active HalfEdge as a arrow
*
* @param he HalfEdge to be highlighted
*/
void renderHEActive(const HalfEdge* he)
{
	// TODO: render the currently selected half-edge.
	if (he == nullptr) return;
	// use renderArrow method to visualize the direction of the half-edge
	renderArrow(he->startV->coordinates, he->nextHE->startV->coordinates, 0.05f);
	HalfEdge* heptr = he->nextHE;
	while (heptr != he) {
		renderHE(heptr, Vec3f(0.4f, 0.0f, 1.0f));
		heptr = heptr->nextHE;
	}
}

void renderArrow(const Vec3f& p1, const Vec3f& p2, float diameter)
{
	Vec3f dir = p2 - p1;
	float length = dir.length();
	if (length < 0.00001f) return;

	GLUquadricObj *quadObj;

	glPushMatrix ();

	glTranslated(p1.x, p1.y, p1.z);

	if((dir.x!=0.)||(dir.y!=0.)) {
		glRotated(atan2(dir.y,dir.x)/RADPERDEG,0.,0.,1.);
		glRotated(atan2(sqrt(double (dir.x) * double(dir.x)+ double(dir.y) * double(dir.y)),dir.z)/RADPERDEG,0.,1.,0.);
	} else if (dir.z<0){
		glRotated(180,1.,0.,0.);
	}

	glTranslatef(0,0,length-4*diameter);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2.0*diameter, 0.0, 4.0*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2.0*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0,0,-length+4*diameter);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, diameter, diameter, length-4.0*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix ();
}
