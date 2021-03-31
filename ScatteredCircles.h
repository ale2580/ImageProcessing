//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATTEREDCIRCLES_H
#define SCATTEREDCIRCLES_H

#include "ImpBrush.h"

class ScatteredCircles : public ImpBrush
{
public:
	int x; int y;
	ScatteredCircles(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif

