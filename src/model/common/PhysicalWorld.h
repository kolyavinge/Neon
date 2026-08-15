#pragma once

#include <lib/system.h>
#include <model/common/RigidBody.h>
#include <model/common/WorldSegment.h>
#include <lib/collections/BSPTree.h>

class PhysicalWorld : Object {

    List<RigidBody> _rigidBodies;
    BSPTree<WorldSegment> _worldSegmentsTree;

public:
    PhysicalWorld();
    void init();
    RigidBody& createNewRigidBody();
    //Collection<RigidBody>& getRigidBodies();
};
