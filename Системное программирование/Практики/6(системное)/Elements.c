typedef struct POINTD
{
	double x;
	double y;
}PointD;

typedef struct DISPLAY
{
	double zoom;
	PointD center;
}Display;

typedef struct COORDINATESS
{
	PointD point1;
	PointD point2;
}Coords;


typedef struct TYPEELEMENT
{
	int shape;
	COLORREF colour;
	int size;
}TypeElement;

typedef struct ELEMENT
{
	Coords coords;
	TypeElement typeElement;
}Element;