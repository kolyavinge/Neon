#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

template<class TNodeData>
class IBSPTreeBuilder {

public:
    virtual ~IBSPTreeBuilder() = default;
    virtual void initRoot(TNodeData& rootNodeData) = 0;
    virtual void initNodes(TNodeData& parentNodeData, Plane& splitPlane, TNodeData& frontNodeData, TNodeData& backNodeData) = 0;
};

template<class TNodeData>
class BSPTreeNode : public Object {

public:
    Plane splitPlane;
    BSPTreeNode* frontNode;
    BSPTreeNode* backNode;
    bool isLeaf;
    TNodeData data = {};

    BSPTreeNode() {
        init();
    }

    void init() {
        frontNode = nullptr;
        backNode = nullptr;
        isLeaf = false;
    }
};

template<class TNodeData>
class BSPTree : public Object {

    BSPTreeNode<TNodeData> _root;

public:
    BSPTree() {
        _root.init();
    }

    ~BSPTree() override {
        releaseAllNodes();
    }

    BSPTreeNode<TNodeData>& getRoot() {
        return _root;
    }

    void build(IBSPTreeBuilder<TNodeData>& builder, Collection<Plane>& splitPlanes) {
        if (splitPlanes.getCount() == 0) throw ArgumentException(L"splitPlanes cannot be empty.");
        releaseAllNodes();
        builder.initRoot(_root.data);
        buildRec(builder, _root, splitPlanes);
    }

    TNodeData& findNodeDataByPoint(Vector3& point) {
        return findNodeDataByPoint(_root, point);
    }

private:
    void buildRec(IBSPTreeBuilder<TNodeData>& builder, BSPTreeNode<TNodeData>& parent, Collection<Plane>& splitPlanes) {
        if (splitPlanes.getCount() == 0) {
            parent.isLeaf = true;
            return;
        }

        parent.splitPlane = splitPlanes.first();
        parent.frontNode = new BSPTreeNode<TNodeData>();
        parent.backNode = new BSPTreeNode<TNodeData>();
        builder.initNodes(parent.data, parent.splitPlane, parent.frontNode->data, parent.backNode->data);

        List<Plane> frontNodeSplitPlanes, backNodeSplitPlanes;
        for (int i = 1; i < splitPlanes.getCount(); i++) {
            Plane& splitPlane = splitPlanes[i];
            Vector3 basePoint = splitPlane.getBasePoint();
            if (parent.splitPlane.isPointInFront(basePoint)) {
                frontNodeSplitPlanes.add(splitPlane);
            } else {
                backNodeSplitPlanes.add(splitPlane);
            }
        }

        buildRec(builder, *parent.frontNode, frontNodeSplitPlanes);
        buildRec(builder, *parent.backNode, backNodeSplitPlanes);
    }

    TNodeData& findNodeDataByPoint(BSPTreeNode<TNodeData>& parent, Vector3& point) {
        if (parent.isLeaf) {
            return parent.data;
        } else {
            if (parent.splitPlane.isPointInFront(point)) {
                return findNodeDataByPoint(*parent.frontNode, point);
            } else {
                return findNodeDataByPoint(*parent.backNode, point);
            }
        }
    }

    void releaseAllNodes() {
        releaseNode(_root.frontNode);
        releaseNode(_root.backNode);
        _root.init();
    }

    void releaseNode(BSPTreeNode<TNodeData>* node) {
        if (node == nullptr) {
            return;
        } else if (node->isLeaf) {
            delete node;
        } else {
            releaseNode(node->frontNode);
            releaseNode(node->backNode);
        }
    }
};
