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

// binary space partitioning
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

    int getCountOfAllNodes() {
        int result = 0;
        auto findRec = [&](BSPTreeNode<TNodeData>& node, auto&& self) -> void {
            result++;
            if (!node.isLeaf) {
                self(*node.frontNode, self);
                self(*node.backNode, self);
            }
        };
        findRec(_root, findRec);

        return result;
    }

    void build(IBSPTreeBuilder<TNodeData>& builder, Collection<Plane>& splitPlanes) {
        if (splitPlanes.getCount() == 0) throw ArgumentException(L"splitPlanes cannot be empty.");
        releaseAllNodes();
        builder.initRoot(_root.data);
        buildRec(builder, _root, splitPlanes);
    }

    TNodeData& findNodeDataByPoint(Vector3 point) {
        auto rec = [&](BSPTreeNode<TNodeData>& parent, auto&& self) -> TNodeData& {
            if (parent.isLeaf) {
                return parent.data;
            } else {
                if (parent.splitPlane.isPointInFront(point)) {
                    return self(*parent.frontNode, self);
                } else {
                    return self(*parent.backNode, self);
                }
            }
        };

        return rec(_root, rec);
    }

    void traverseFromRootToPoint(Vector3 point, auto&& actionFunc) {
        auto rec = [&](BSPTreeNode<TNodeData>& parent, auto&& self) -> void {
            actionFunc(parent.data);
            if (!parent.isLeaf) {
                if (parent.splitPlane.isPointInFront(point)) {
                    return self(*parent.frontNode, self);
                } else {
                    return self(*parent.backNode, self);
                }
            }
        };

        return rec(_root, rec);
    }

    void getDataForAllNodes(output List<TNodeData*>& result) {
        auto rec = [&](BSPTreeNode<TNodeData>& node, auto&& self) -> void {
            result.add(&node.data);
            if (!node.isLeaf) {
                self(*node.frontNode, self);
                self(*node.backNode, self);
            }
        };

        rec(_root, rec);
    }

    void deleteChildrenFor(BSPTreeNode<TNodeData>& node) {
        node.isLeaf = true;
        releaseNode(node.frontNode);
        releaseNode(node.backNode);
        node.frontNode = nullptr;
        node.backNode = nullptr;
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

    void releaseAllNodes() {
        releaseNode(_root.frontNode);
        releaseNode(_root.backNode);
        _root.init();
    }

    void releaseNode(BSPTreeNode<TNodeData>* node) {
        if (node == nullptr) return;
        if (!node->isLeaf) {
            releaseNode(node->frontNode);
            releaseNode(node->backNode);
        }
        delete node;
    }
};
