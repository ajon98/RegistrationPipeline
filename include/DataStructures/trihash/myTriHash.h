//
// Created by ferran on 18/01/16.
//

#ifndef PIPELINE_MYTRIHASH_H
#define PIPELINE_MYTRIHASH_H


#include "../IDataStructure.h"
#include "../../point.h"
#include "./AdapterDataStruct.h"
#include "../../../external/MoreStructures/TriHash/TriHash.h"
#include "../../../external/MoreStructures/AuxiliaryClasses/point3D.h"


class myTriHash : public IDataStructure {


public:

    // Elements -----------------------------------------------------------
    TriHash *trihash;
    AdapterDataStruct *ads;
    float diagonal;

    // Methods ------------------------------------------------------------
    myTriHash();
    myTriHash(vector<Point *> *P, float _diag);
    ~myTriHash();

    returnData calcOneNN(Point *queryPoint, float errEps);
    returnData calcOwnNN(Point *queryPoint);
    vector<returnData> calcNneigh(Point *queryPoint, int nNeigh);
};


#endif //PIPELINE_MYTRIHASH_H
