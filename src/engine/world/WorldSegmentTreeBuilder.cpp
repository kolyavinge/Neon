#include <engine/world/WorldSegmentTreeBuilder.h>
#include <model/common/common.h>
#include <model/common/light.h>

WorldSegmentTreeBuilder::WorldSegmentTreeBuilder() {
    _track = nullptr;
}

void WorldSegmentTreeBuilder::build(Track& track, BSPTree<WorldSegment>& segmentTree) {
    _track = &track;
    Collection<Plane>& splitPlanes = track.getSplitPlanes();
    segmentTree.build(*this, splitPlanes);
    removeEmptySegments(segmentTree);
    // set id for all segments
    List<WorldSegment*> allSegments;
    segmentTree.getDataForAllNodes(output allSegments);
    for (int i = 0; i < allSegments.getCount(); i++) {
        allSegments[i]->setId(i);
    }
}

void WorldSegmentTreeBuilder::initRoot(WorldSegment& rootSegment) {
    rootSegment.setGroundPrimitives(_track->getGroundPrimitives());
    rootSegment.setBarrierPrimitives(_track->getBarrierPrimitives());
    rootSegment.setWorldObjects(_track->getWorldObjects());
    rootSegment.setOuterCorners(_track->getOuterCorners());
    rootSegment.setLights(_track->getLights());
    rootSegment.calculateBoundaryBox();
}

void WorldSegmentTreeBuilder::initNodes(WorldSegment& parentSegment, Plane& splitPlane, WorldSegment& frontChildSegment, WorldSegment& backChildSegment) {
    // ground primitives
    Collection<WorldPrimitive*>& groundPrimitives = parentSegment.getGroundPrimitives();
    for (int i = 0; i < groundPrimitives.getCount(); i++) {
        WorldPrimitive& primitive = *groundPrimitives[i];
        SplittedPosition position = getSplittedPosition(splitPlane, primitive.getPoints());
        if (position == SplittedPosition::front) {
            frontChildSegment.addGroundPrimitive(primitive);
        } else if (position == SplittedPosition::back) {
            backChildSegment.addGroundPrimitive(primitive);
        } else {
            frontChildSegment.addGroundPrimitive(primitive);
            backChildSegment.addGroundPrimitive(primitive);
        }
    }

    // barrier primitives
    Collection<WorldPrimitive*>& barrierPrimitives = parentSegment.getBarrierPrimitives();
    for (int i = 0; i < barrierPrimitives.getCount(); i++) {
        WorldPrimitive& primitive = *barrierPrimitives[i];
        SplittedPosition position = getSplittedPosition(splitPlane, primitive.getPoints());
        if (position == SplittedPosition::front) {
            frontChildSegment.addBarrierPrimitive(primitive);
        } else if (position == SplittedPosition::back) {
            backChildSegment.addBarrierPrimitive(primitive);
        } else {
            frontChildSegment.addBarrierPrimitive(primitive);
            backChildSegment.addBarrierPrimitive(primitive);
        }
    }

    // world objects
    Collection<WorldObject*>& worldObjects = parentSegment.getWorldObjects();
    for (int i = 0; i < worldObjects.getCount(); i++) {
        WorldObject& object = *worldObjects[i];
        SplittedPosition position = getSplittedPosition(splitPlane, object.getBoundaryPoints());
        if (position == SplittedPosition::front) {
            frontChildSegment.addWorldObject(object);
        } else if (position == SplittedPosition::back) {
            backChildSegment.addWorldObject(object);
        } else {
            frontChildSegment.addWorldObject(object);
            backChildSegment.addWorldObject(object);
        }
    }

    // outer corners
    Collection<Line*>& outerCorners = parentSegment.getOuterCorners();
    for (int i = 0; i < outerCorners.getCount(); i++) {
        Line& outerCorner = *outerCorners[i];
        SplittedPosition position = getSplittedPosition(splitPlane, outerCorner.startPoint);
        if (position == SplittedPosition::front) {
            frontChildSegment.addOuterCorner(outerCorner);
        } else {
            backChildSegment.addOuterCorner(outerCorner);
        }
    }

    // lights
    Collection<Light*>& lights = parentSegment.getLights();
    for (int i = 0; i < lights.getCount(); i++) {
        Light& light = *lights[i];
        SplittedPosition position = getSplittedPosition(splitPlane, light.getPosition());
        if (position == SplittedPosition::front) {
            frontChildSegment.addLight(light);
        } else {
            backChildSegment.addLight(light);
        }
    }

    frontChildSegment.calculateBoundaryBox();
    backChildSegment.calculateBoundaryBox();
}

WorldSegmentTreeBuilder::SplittedPosition WorldSegmentTreeBuilder::getSplittedPosition(Plane& splitPlane, Collection<Vector3>& points) {
    int frontPoints = 0;
    for (int i = 0; i < points.getCount(); i++) {
        if (splitPlane.isPointInFront(points[i])) frontPoints++;
    }
    if (frontPoints == points.getCount()) {
        return SplittedPosition::front;
    } else if (frontPoints == 0) {
        return SplittedPosition::back;
    } else {
        return SplittedPosition::frontAndBack;
    }
}

WorldSegmentTreeBuilder::SplittedPosition WorldSegmentTreeBuilder::getSplittedPosition(Plane& splitPlane, Vector3 point) {
    return splitPlane.isPointInFront(point) ? SplittedPosition::front : SplittedPosition::back;
}

void WorldSegmentTreeBuilder::removeEmptySegments(BSPTree<WorldSegment>& segmentTree) {
    auto searchRec = [&](BSPTreeNode<WorldSegment>& node, auto&& self) -> void {
        if (node.isLeaf) return;
        else if (node.frontNode->data.getGroundPrimitives().getCount() == 0 ||
            node.backNode->data.getGroundPrimitives().getCount() == 0) {
            segmentTree.deleteChildrenFor(node);
        } else {
            if (!node.isLeaf) {
                self(*node.frontNode, self);
                self(*node.backNode, self);
            }
        }
    };
    searchRec(segmentTree.getRoot(), searchRec);
}
