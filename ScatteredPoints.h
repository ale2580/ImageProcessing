//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef SCATTEREDPOINTS_H
#define SCATTEREDPOINTS_H

#include "ImpBrush.h"

class ScatteredPoints : public ImpBrush
{
public:
	int x; int y;
	ScatteredPoints(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif
