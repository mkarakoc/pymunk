/* Copyright (c) 2007 Scott Lembcke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @defgroup misc Misc
/// @{

#ifndef CHIPMUNK_HEADER
#define CHIPMUNK_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CP_ALLOW_PRIVATE_ACCESS
	#define CP_ALLOW_PRIVATE_ACCESS 0
#endif

#if CP_ALLOW_PRIVATE_ACCESS == 1
	#define CP_PRIVATE(symbol) symbol
#else
	#define CP_PRIVATE(symbol) symbol##_private
#endif

void cpMessage(const char *message, const char *condition, const char *file, int line, int isError);
#ifdef NDEBUG
	#define	cpAssertWarn(condition, message)
#else
	#define cpAssertWarn(condition, message) if(!(condition)) cpMessage(message, #condition, __FILE__, __LINE__, 0)
#endif

#ifdef NDEBUG
	#define	cpAssert(condition, message)
#else
	#define cpAssert(condition, message) if(!(condition)) cpMessage(message, #condition, __FILE__, __LINE__, 1)
#endif

#include "chipmunk_types.h"
	
// Maximum allocated size for various Chipmunk buffers
#define CP_BUFFER_BYTES (32*1024)

//TODO allow redifinition
#define cpcalloc calloc
#define cprealloc realloc
#define cpfree free

typedef struct cpArray cpArray;
typedef struct cpHashSet cpHashSet;

typedef struct cpBody cpBody;
typedef struct cpShape cpShape;
typedef struct cpConstraint cpConstraint;

typedef struct cpArbiter cpArbiter;

typedef struct cpSpace cpSpace;

#include "cpVect.h"
#include "cpBB.h"
#include "cpSpatialIndex.h"

#include "cpBody.h"
#include "cpShape.h"
#include "cpPolyShape.h"

#include "cpArbiter.h"	
#include "constraints/cpConstraint.h"

#include "cpSpace.h"

/// Version string.
extern const char *cpVersionString;

/// Initialize Chipmunk.
/// Must be called before anything else or your program will crash.
void cpInitChipmunk(void);

/// Calculate the moment of inertia for a circle.
/// @c r1 and @c r2 are the inner and outer diameters. A solid circle has an inner diameter of 0.
cpFloat cpMomentForCircle(cpFloat m, cpFloat r1, cpFloat r2, cpVect offset);

/// Calculate area of a hollow circle.
/// @c r1 and @c r2 are the inner and outer diameters. A solid circle has an inner diameter of 0.
cpFloat cpAreaForCircle(cpFloat r1, cpFloat r2);

/// Calculate the moment of inertia for a line segment.
/// Beveling radius is not supported.
cpFloat cpMomentForSegment(cpFloat m, cpVect a, cpVect b);

/// Calculate the area of a fattened (capsule shaped) line segment.
cpFloat cpAreaForSegment(cpVect a, cpVect b, cpFloat r);

/// Calculate the moment of inertia for a solid polygon shape assuming it's center of gravity is at it's centroid. The offset is added to each vertex.
cpFloat cpMomentForPoly(cpFloat m, int numVerts, const cpVect *verts, cpVect offset);

/// Calculate the signed area of a polygon. A Clockwise winding gives positive area.
/// This is probably backwards from what you expect, but matches Chipmunk's the winding for poly shapes.
cpFloat cpAreaForPoly(const int numVerts, const cpVect *verts);

/// Calculate the natural centroid of a polygon.
cpVect cpCentroidForPoly(const int numVerts, const cpVect *verts);

/// Center the polygon on the origin. (Subtracts the centroid of the polygon from each vertex)
void cpRecenterPoly(const int numVerts, cpVect *verts);

/// Calculate the moment of inertia for a solid box.
cpFloat cpMomentForBox(cpFloat m, cpFloat width, cpFloat height);

#ifdef __cplusplus
}

static inline cpVect operator *(const cpVect v, const cpFloat s){return cpvmult(v, s);}
static inline cpVect operator +(const cpVect v1, const cpVect v2){return cpvadd(v1, v2);}
static inline cpVect operator -(const cpVect v1, const cpVect v2){return cpvsub(v1, v2);}
static inline cpBool operator ==(const cpVect v1, const cpVect v2){return cpveql(v1, v2);}
static inline cpVect operator -(const cpVect v){return cpvneg(v);}

#endif
#endif
//@}