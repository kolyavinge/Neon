#include <common/constants.h>
#include <debug/RenderDebuger.h>
#include <model/world/GameObjectVisibility.h>
#include <model/world/WorldObject.h>
#include <model/world/WorldSegment.h>
#include <stdio.h>

RenderDebuger::RenderDebuger(
    RenderModel3dCollection& renderModel3dCollection) :
    _renderModel3dCollection(renderModel3dCollection) {
    _tick = 0;
    renderTimeMsc = 0;
}

void RenderDebuger::print(GameWorld& gameWorld) {
    _tick++;
    if ((_tick % 20) != 0) return;
    //if (renderTimeMsc < 15) return;

    printf("render: %i ms (*%i: %i)",
        renderTimeMsc,
        (int)CommonConstants::renderFrameRate,
        (int)((float)renderTimeMsc * CommonConstants::renderFrameRate));
    if ((float)renderTimeMsc * CommonConstants::renderFrameRate >= 900.0) {
        printf("\033[1;31m slow");
    }
    printf("\033[0m\n");

    GameObjectVisibility& objectVisibility = gameWorld.getObjectVisibility();
    Collection<WorldSegment*>& visibleSegments = objectVisibility.visibleSegments;
    printf("visible segments: %i\n", visibleSegments.getCount());

    // общее кол-во полигонов в сегментах, но без учета машинок
    int segmentsTotalFaces = 0;
    for (int segmentIndex = 0; segmentIndex < visibleSegments.getCount(); segmentIndex++) {
        WorldSegment& segment = *visibleSegments[segmentIndex];
        VisibilityState state = objectVisibility.getSegmentVisibilityState(segmentIndex);
        for (int j = 0; j < segment.getWorldObjects().getCount(); j++) {
            WorldObject& object = *segment.getWorldObjects()[j];
            segmentsTotalFaces += _renderModel3dCollection.getWorldObjectModel(object.getKind(), state).getTotalFacesCount();
        }
    }
    printf("segments total faces: ");
    printFormatted(segmentsTotalFaces);
    printf("\n");

    for (int segmentIndex = 0; segmentIndex < visibleSegments.getCount(); segmentIndex++) {
        WorldSegment& segment = *visibleSegments[segmentIndex];
        VisibilityState state = objectVisibility.getSegmentVisibilityState(segmentIndex);
        printf("segment id: %i\tstate: %i ", segment.getId(), objectVisibility.getSegmentVisibilityState(segmentIndex));
        int faces = 0;
        for (int j = 0; j < segment.getWorldObjects().getCount(); j++) {
            WorldObject& object = *segment.getWorldObjects()[j];
            faces += _renderModel3dCollection.getWorldObjectModel(object.getKind(), state).getTotalFacesCount();
        }
        printf("faces: ");
        printFormatted(faces);
        printf("\tlights: %i", segment.getLights().getCount());
        if (segment.hasChildren()) printf(" chd ");
        printf("\n");
    }

    printf("- - - - - - - - -\n");
}

void RenderDebuger::printFormatted(int n) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", n);
    int len = (int)strlen(buf);
    int start = (buf[0] == '-') ? 1 : 0;
    for (int i = 0; i < len; i++) {
        if (i > start && (len - i) % 3 == 0) {
            putchar(' ');
        }
        putchar(buf[i]);
    }
}
