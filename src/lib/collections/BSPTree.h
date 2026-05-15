#pragma once

#include <lib/calc/Plane.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>

template<class TNodeData>
class IBSPTreeBuilder {

public:
    virtual ~IBSPTreeBuilder() {}
    virtual void initRoot(TNodeData& rootNodeData) = 0;
    virtual void initNodes(TNodeData& parentNodeData, Plane& splitPlane, TNodeData& leftNodeData, TNodeData& rightNodeData) = 0;
};

template<class TNodeData>
class BSPTreeNode : public Object {

public:
    Plane splitPlane;
    BSPTreeNode* leftNode;
    BSPTreeNode* rightNode;
    bool isLeaf;
    TNodeData data;

    BSPTreeNode() {
        init();
    }

    void init() {
        leftNode = nullptr;
        rightNode = nullptr;
        isLeaf = true;
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
        parent.leftNode = new BSPTreeNode<TNodeData>();
        parent.rightNode = new BSPTreeNode<TNodeData>();
        builder.initNodes(parent.data, parent.splitPlane, parent.leftNode->data, parent.rightNode->data);

        List<Plane> leftNodeSplitPlanes, rightNodeSplitPlanes;
        for (int i = 1; i < splitPlanes.getCount(); i++) {
            Plane& splitPlane = splitPlanes[i];
            if (parent.splitPlane.isPointInFront(splitPlane.getBasePoint())) {
                rightNodeSplitPlanes.add(splitPlane);
            } else {
                leftNodeSplitPlanes.add(splitPlane);
            }
        }

        buildRec(builder, *parent.leftNode, leftNodeSplitPlanes);
        buildRec(builder, *parent.rightNode, rightNodeSplitPlanes);
    }

    TNodeData& findNodeDataByPoint(BSPTreeNode<TNodeData>& parent, Vector3& point) {
        if (parent.isLeaf) {
            return parent.data;
        } else {
            if (parent.splitPlane.isPointInFront(point)) {
                return findNodeDataByPoint(*parent.rightNode, point);
            } else {
                return findNodeDataByPoint(*parent.leftNode, point);
            }
        }
    }

    void releaseAllNodes() {
        releaseNode(_root.leftNode);
        releaseNode(_root.rightNode);
        _root.init();
    }

    void releaseNode(BSPTreeNode<TNodeData>* node) {
        if (node == nullptr) {
            return;
        } else if (node->isLeaf) {
            delete node;
        } else {
            releaseNode(node->leftNode);
            releaseNode(node->rightNode);
        }
    }
};
