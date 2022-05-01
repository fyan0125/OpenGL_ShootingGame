#include "Move.h"

vec2 addVector2(vec2 first, vec2 second)
{
	vec2 newVector;
	newVector.x = first.x + second.x;
	newVector.y = first.y + second.y;
	return newVector;
}