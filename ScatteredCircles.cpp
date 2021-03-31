//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredcircles.h"
#include <iostream>
using namespace std;

extern float frand();

ScatteredCircles::ScatteredCircles(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
	this->x = 0;
	this->y = 0;
}

void ScatteredCircles::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	this->x = target.x;
	this->y = target.y;

	glPointSize((float)size);

	BrushMove(source, target);
}

void ScatteredCircles::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int frameSize = pDoc->m_pUI->getSize();
	
	//circle parameters
	static const int circle_points = 20;
	static const float angle = 2.0f * 3.1416f / circle_points;
	int radius = pDoc->m_pUI->getSize() / 2;
	int size = pDoc->m_pUI->getSize();
	int numCir = rand() % 2 + 3; //3 or 4circles
	
	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}


	//left mouse stuff
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBegin(GL_POINTS);
	SetColor(source);

	

	
		if (pDoc->m_pUI->myBool) {
			//cout << "MYBOOL TRUE" << endl;
			if (CheckBoundary(target)) {

				//cout << "SIZE" << pDoc->m_pUI->getSize() << endl;
				for (int j = 0; j < numCir; j++) {
					
					if (size == 1) {

						glBegin(GL_POINTS);
						//double angle1 = 0.0;
						int i;
						int randX = (rand() % 2)+3;
						int randY = (rand() %2)+3;

						Point p = Point(randX + target.x, randY + target.y);
						SetColor(p);
						
							glVertex2d(p.x, p.y );
							//angle1 += angle;
							//cout << "size*cosangle" << 180 * pDoc->m_nSize * cos(angle1) / M_PI << endl;
						
						glEnd();
					
					
					}
					else {
						glBegin(GL_POLYGON);
						double angle1 = 0.0;
						int i;
						int randX = (rand() % size) - radius;
						int randY = (rand() % size) - radius;

						Point p = Point(randX + target.x, randY + target.y);
						SetColor(p);
						for (i = 0; i < circle_points; i++)
						{
							glVertex2d(p.x + radius * cos(angle1), p.y + radius * sin(angle1));
							angle1 += angle;
							//cout << "size*cosangle" << 180 * pDoc->m_nSize * cos(angle1) / M_PI << endl;
						}
					}
					glEnd();
				}


			}
		}
		else {

			//cout << "SIZE" << pDoc->m_pUI->getSize() << endl;
			for (int j = 0; j < numCir; j++) {

				if (size == 1) {

					glBegin(GL_POINTS);
					//double angle1 = 0.0;
					int i;
					int randX = (rand() % 2) + 3;
					int randY = (rand() % 2) + 3;

					Point p = Point(randX + target.x, randY + target.y);
					SetColor(p);

					glVertex2d(p.x, p.y);
					//angle1 += angle;
					//cout << "size*cosangle" << 180 * pDoc->m_nSize * cos(angle1) / M_PI << endl;

					glEnd();


				}
				else {
					glBegin(GL_POLYGON);
					double angle1 = 0.0;
					int i;
					int randX = (rand() % size) - radius;
					int randY = (rand() % size) - radius;

					Point p = Point(randX + target.x, randY + target.y);
					SetColor(p);
					for (i = 0; i < circle_points; i++)
					{
						glVertex2d(p.x + radius * cos(angle1), p.y + radius * sin(angle1));
						angle1 += angle;
						//cout << "size*cosangle" << 180 * pDoc->m_nSize * cos(angle1) / M_PI << endl;
					}
				}
				glEnd();
			}


		}
		//glEnd();
	

}

void ScatteredCircles::BrushEnd(const Point source, const Point target)
{
	// do nothing so far

}

