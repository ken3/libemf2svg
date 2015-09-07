#include "polyclipping/clipper.hpp"
#include "clipperWrapper.h"

using namespace ClipperLib;

extern "C" {

clipSegmentList * bezierToLine(clipSegmentList *seg, uint32_t depth){

    // end of recursion
    if (depth == 0){
        return seg;
    }

    // each iteration transforms a bezier curve into 2 smaller bezier curves
    clipSegmentList *newSeg1 = (clipSegmentList *)malloc(sizeof(clipSegmentList));
    clipSegmentList *newSeg2 = (clipSegmentList *)malloc(sizeof(clipSegmentList));

    // some matrix products
    newSeg1->seg.st.x = seg->seg.st.x;
    newSeg1->seg.c1.x = seg->seg.st.x / 2 + seg->seg.c1.x * 1 / 2;
    newSeg1->seg.c2.x = seg->seg.st.x / 4 + seg->seg.c1.x * 2 / 4 + seg->seg.c2.x * 1 / 4;
    newSeg1->seg.en.x = seg->seg.st.x / 8 + seg->seg.c1.x * 3 / 8 + seg->seg.c2.x * 3 / 8 + seg->seg.en.x / 8;

    newSeg1->seg.st.y = seg->seg.st.y;
    newSeg1->seg.c1.y = seg->seg.st.y / 2 + seg->seg.c1.y * 1 / 2;
    newSeg1->seg.c2.y = seg->seg.st.y / 4 + seg->seg.c1.y * 2 / 4 + seg->seg.c2.y * 1 / 4;
    newSeg1->seg.en.y = seg->seg.st.y / 8 + seg->seg.c1.y * 3 / 8 + seg->seg.c2.y * 3 / 8 + seg->seg.en.y / 8;


    newSeg2->seg.st.x = seg->seg.st.x / 8 + seg->seg.c1.x * 3 / 8 + seg->seg.c2.x * 3 / 8 + seg->seg.en.x / 8;
    newSeg2->seg.c1.x =                     seg->seg.c1.x * 1 / 4 + seg->seg.c2.x * 2 / 4 + seg->seg.en.x / 4;
    newSeg2->seg.c2.x =                                             seg->seg.c2.x * 1 / 2 + seg->seg.en.x / 2;
    newSeg2->seg.en.x =                                                                     seg->seg.en.x    ;

    newSeg2->seg.st.y = seg->seg.st.y / 8 + seg->seg.c1.y * 3 / 8 + seg->seg.c2.y * 3 / 8 + seg->seg.en.y / 8;
    newSeg2->seg.c1.y =                     seg->seg.c1.y * 1 / 4 + seg->seg.c2.y * 2 / 4 + seg->seg.en.y / 4;
    newSeg2->seg.c2.y =                                             seg->seg.c2.y * 1 / 2 + seg->seg.en.y / 2;
    newSeg2->seg.en.y =                                                                     seg->seg.en.y    ;


    newSeg1->seg.type = LINE;
    newSeg2->seg.type = LINE;

    newSeg1->next = NULL;
    newSeg2->next = NULL;

    // free the input bezier curve
    free(seg);

    // recursion
    clipSegmentList *newSegList1 = bezierToLine(newSeg1, depth - 1);
    clipSegmentList *newSegList2 = bezierToLine(newSeg2, depth - 1);
    clipSegmentList *ptr = newSegList1;
    while (ptr->next != NULL)
        ptr = ptr->next;

    // link the two new bezier curves
    ptr->next = newSegList2;

    return newSegList1;
}


clipSegmentList *arcToLine(clipSegmentList *seg, uint32_t depth){
    clipSegmentList *out = NULL;
    return out;
}

clipSegmentList merge(clipSegmentList form1, clipSegmentList form2, operation op){
    //Paths subj(2), clip(1), solution;

    ////define outer blue 'subject' polygon
    //subj[0] << 
    //    IntPoint(180,200) << IntPoint(260,200) <<
    //    IntPoint(260,150) << IntPoint(180,150);

    ////define subject's inner triangular 'hole' (with reverse orientation)
    //subj[1] << 
    //    IntPoint(215,160) << IntPoint(230,190) << IntPoint(200,190);

    ////define orange 'clipping' polygon
    //clip[0] << 
    //    IntPoint(190,210) << IntPoint(240,210) << 
    //    IntPoint(240,130) << IntPoint(190,130);

    ////draw input polygons with user-defined routine ... 

    ////perform intersection ...
    //Clipper c;
    //c.AddPaths(subj, ptSubject, true);
    //c.AddPaths(clip, ptClip, true);
    //c.Execute(ctIntersection, solution, pftNonZero, pftNonZero);
    
    clipSegmentList out;
    return out;
}
}
