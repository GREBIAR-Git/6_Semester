typedef struct POINTD
{
	double x;
	double y;
}POINTD;

typedef struct COORDINATESS
{
	POINTD point1;
	POINTD point2;
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