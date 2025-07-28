#ifndef NODETYPEMAP_HPP
#define NODETYPEMAP_HPP

#include <stdint.h>
/*
+----+----+
|  8 |  4 |
+----+----+
|  1 |  2 |
+----+----+
*/
#define BULK (15)
#define SOLID (0)

// FACE
#define NORTH (3)
#define SOUTH (12)
#define WEST (10)
#define EAST (5) 

// CORNER
#define NORTH_WEST (2)
#define NORTH_EAST (1)
#define SOUTH_WEST (8)
#define SOUTH_EAST (4)

#define MISSING_DEFINITION (0b11111111111111111111111111111111)

#endif