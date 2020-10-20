#include "./ATDs/list.h"

// Applies the Monotone Chain algorithm to calculate a group of points's convex hull
// Returns a list with the hull's vertices in counter-clockwise
list *convexHull(list *allPoints);