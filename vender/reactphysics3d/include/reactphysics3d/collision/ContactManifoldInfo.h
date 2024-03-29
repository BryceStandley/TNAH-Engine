/********************************************************************************
* ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
* Copyright (c) 2010-2020 Daniel Chappuis                                       *
*********************************************************************************
*                                                                               *
* This software is provided 'as-is', without any express or implied warranty.   *
* In no event will the authors be held liable for any damages arising from the  *
* use of this software.                                                         *
*                                                                               *
* Permission is granted to anyone to use this software for any purpose,         *
* including commercial applications, and to alter it and redistribute it        *
* freely, subject to the following restrictions:                                *
*                                                                               *
* 1. The origin of this software must not be misrepresented; you must not claim *
*    that you wrote the original software. If you use this software in a        *
*    product, an acknowledgment in the product documentation would be           *
*    appreciated but is not required.                                           *
*                                                                               *
* 2. Altered source versions must be plainly marked as such, and must not be    *
*    misrepresented as being the original software.                             *
*                                                                               *
* 3. This notice may not be removed or altered from any source distribution.    *
*                                                                               *
********************************************************************************/

#ifndef REACTPHYSICS3D_CONTACT_MANIFOLD_INFO_H
#define REACTPHYSICS3D_CONTACT_MANIFOLD_INFO_H

// Libraries
#include <reactphysics3d/mathematics/mathematics.h>
#include <reactphysics3d/configuration.h>
#include <reactphysics3d/engine/OverlappingPairs.h>

/// ReactPhysics3D namespace
namespace reactphysics3d {

// Structure ContactManifoldInfo
/**
 * This structure contains informations about a collision contact
 * manifold computed during the narrow-phase collision detection.
 */
struct ContactManifoldInfo {

    public:

        // -------------------- Attributes -------------------- //

        /// Memory allocator
        MemoryAllocator& allocator;

        /// Indices of the contact points in the mPotentialContactPoints array
        Array<uint> potentialContactPointsIndices;

        /// Overlapping pair id
        uint64 pairId;

        // -------------------- Methods -------------------- //

        /// Constructor
        ContactManifoldInfo(uint64 pairId, MemoryAllocator& allocator)
            : allocator(allocator), potentialContactPointsIndices(allocator, 4), pairId(pairId) {

        }


};

}

#endif
