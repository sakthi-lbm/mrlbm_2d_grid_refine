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

//Grid refinement
#define NODE_1 (201)
#define NODE_2 (202)
#define NODE_3 (203)
#define NODE_4 (204)
#define NODE_F2C (205)
#define NODE_C2F (301)


#define MISSING_DEFINITION (0b11111111111111111111111111111111)

#endif