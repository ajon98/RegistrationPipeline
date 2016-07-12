//
// Created by ferran on 8/07/16.
//

#include "my4PCSkdtree.h"

my4PCSkdtree::my4PCSkdtree(){

}

my4PCSkdtree::my4PCSkdtree(vector<Point *> *P, float _diag) {

    diagonal = _diag;

    kdtree = new Super4PCS::KdTree<double>((int)P->size());

    dataPts = P;

    Super4PCS::KdTree<double>::VectorType p;
    for (int i = 0; i < P->size(); ++i) {
        p << P->at(i)->getX(),
             P->at(i)->getY(),
             P->at(i)->getZ();

        kdtree->add(p);
    }
    kdtree->finalize();
}

my4PCSkdtree::~my4PCSkdtree() {

    delete kdtree;
}

returnData my4PCSkdtree::calcOneNN(Point *queryPoint, float errEps){

    Super4PCS::KdTree<double>::VectorType qP;
    qP << queryPoint->getX(),
            queryPoint->getY(),
            queryPoint->getZ();

    Super4PCS::KdTree<double>::Index resId =
    kdtree->doQueryRestrictedClosest(qP, errEps);

    returnData rd;
    if(resId == Super4PCS::KdTree<double>::invalidIndex()){
        rd.index = -1;
        rd.sqrDist = FLT_MAX;
    }
    else {
        rd.index = resId;
        Point *pnn = new Point(dataPts->at(resId)->getX(), dataPts->at(resId)->getY(), dataPts->at(resId)->getZ());
        rd.sqrDist = queryPoint->sqrDist(pnn);
        delete pnn;
    }

    return rd;
}

returnData my4PCSkdtree::calcOwnNN(Point *queryPoint){

    Super4PCS::KdTree<double>::VectorType qP;
    qP << queryPoint->getX(),
            queryPoint->getY(),
            queryPoint->getZ();

    int queryId = queryPoint->getIndex();

    Super4PCS::KdTree<double>::Index resId = -1;
    int factor = 1;

    while (resId == Super4PCS::KdTree<double>::invalidIndex()) {
        resId = kdtree->doQueryRestrictedClosest(qP, diagonal * 0.01 * factor, queryId);
        ++factor;
    }

    returnData rd;
    if(resId == Super4PCS::KdTree<double>::invalidIndex()){
        rd.index = -1;
        rd.sqrDist = FLT_MAX;
    }
    else {
        rd.index = resId;
        Point *pnn = new Point(dataPts->at(resId)->getX(), dataPts->at(resId)->getY(), dataPts->at(resId)->getZ());
        rd.sqrDist = queryPoint->sqrDist(pnn);
        delete pnn;
    }

    return rd;
}

vector<returnData> my4PCSkdtree::calcNneigh(Point *queryPoint, int nNeigh){

}

void my4PCSkdtree::printStats() {


}