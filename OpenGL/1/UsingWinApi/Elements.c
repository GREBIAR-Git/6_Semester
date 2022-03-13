typedef struct COORDINATESS
{
	POINT point1;
	POINT point2;
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