#include "./ATDs/list.h"
#include "./ATDs/stack.h"
#include "util.c"

// Applies the Monotone Chain algorithm to calculate a group of points's convex hull
// Returns a list with the hull's vertices
list *convexHull(list *allPoints);