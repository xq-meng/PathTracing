#include "kdtree.h"

KDTreeNode::KDTreeNode()
{
    this->isLeaf = false;
    this->left = nullptr;
    this->right = nullptr;
}

void KDTreeNode::build(vector<Element *> &elementList, AABB &ogBox, int depth)
{

    this->box.initialize(ogBox.bottom_left, ogBox.top_right);
    this->elemNum = elementList.size();

    // If the node depth>10 or the tris in this node less than 10, set as the leaf node
    if (depth > 10 || elementList.size()< 2){
        this->isLeaf = true;
        for (int i=0; i<elementList.size(); i++){
            this->elems.push_back(elementList[i]);
        }
        return;

    }

    float Ti = 80.0f;
    float Tt = 1.0f;
    int nSplits = 10 * 2;// Split the longest axis into nSplit sections
    vector <Element *> leftTriangles;
    vector <Element *> rightTriangles;

    // Calculate the SAH cost without split, set as the Minimum SAH cost at first
    float EmptySAHCost = Ti * elementList.size();

    float MinSAHCost = EmptySAHCost;

    // Calculate total area of the AABBox
    float axisLength[3];
    for (int i=0; i<3; i++){
        axisLength[i] = this->box.top_right[i] - this->box.bottom_left[i];
    }
    float totalArea = 2 * (axisLength[0] * axisLength[1] + axisLength[1] * axisLength[2] + axisLength[2] * axisLength[0]);

    int bestSplitAxis = 0;
    int bestSpilts = 0;

    for (int t=0; t<3;t++){
        // Calculate the SAH cost for the sample splits

        float steplength = axisLength[t] / nSplits; //Length of every step
        float sideArea = 2 * axisLength[(t+1)%3] * axisLength[(t+2)%3];
        float unitSplitArea = 2 * (axisLength[(t+1)%3] + axisLength[(t+2)%3]);


        for (int i=1; i<nSplits; i++){
            float Length_left = steplength * i;
            float leftArea = sideArea + Length_left * unitSplitArea;
            float rightArea = totalArea - Length_left * unitSplitArea;

            int  N_left = 0;
            int  N_right = 0;

            for (int j=0; j<elementList.size(); j++){
                if (elementList[j]->box.bottom_left[t] <= box.bottom_left[t] + Length_left){
                    N_left ++;
                }

                if (elementList[j]->box.top_right[t] >= box.bottom_left[t] + Length_left){
                    N_right ++;
                }
            }
            int minus=0;
            if (N_left==0|| N_right==0) {
                minus--;
            }
            float sampleCost = Tt * (2 + minus) + Ti *(leftArea * N_left + rightArea * N_right) /totalArea;
            if (sampleCost < MinSAHCost){
                MinSAHCost = sampleCost;
                bestSpilts = i;
                bestSplitAxis = t;
            }
        }
    }
    this->splitAxis = bestSplitAxis;


    if (bestSpilts == 0) {
        // Don't need split
        this->isLeaf = true;
        for (int i=0; i<elementList.size(); i++){
            this->elems.push_back(elementList[i]);
        }
        return;
    }
    else {

        float Length_left = axisLength[this->splitAxis] / nSplits * bestSpilts;
        float splitCandidate = box.bottom_left[this->splitAxis] + Length_left;

        for (int i=0; i<elementList.size(); i++){
            if (elementList[i]->box.bottom_left[this->splitAxis] <= splitCandidate){
                leftTriangles.push_back(elementList[i]);
            }
            if (elementList[i]->box.top_right[this->splitAxis] >= splitCandidate){
                rightTriangles.push_back(elementList[i]);
            }
        }

        if (leftTriangles.size() > 0){

            this->left = new KDTreeNode;
            AABB leftBox;
            vector3D tr = box.top_right;// Top-right vertex of the left box
            tr[this->splitAxis] =  splitCandidate;
            leftBox.initialize(box.bottom_left, tr);
            this->left->build(leftTriangles, leftBox, depth+1);
        }
        else{
            this->left = nullptr;
        }

        if (rightTriangles.size() > 0){

            this->right = new KDTreeNode;
            AABB rightBox;
            vector3D bl = box.bottom_left;// Bottom-left vertex of the right box
            bl[this->splitAxis] =  splitCandidate;
            rightBox.initialize(bl, box.top_right);
            this->right->build(rightTriangles, rightBox, depth+1);
        }
        else{
            this->right = nullptr;
        }
    }
}


bool KDTreeNode::intersect(Ray &r, Intersection &itsn)
{
    if(!this->box.isHit(r)) // if aabbox is not hitted, return
        return false;
    bool isInct = false;
    if(this->isLeaf){
        for(unsigned int i = 0; i < static_cast<unsigned int>(this->elemNum); i++){
            if(this->elems[i]->box.isHit(r)){
                Intersection tmp_itsn;
                if(this->elems[i]->getIntersection(r, tmp_itsn)){
                    if(isInct == false){
                        isInct = true;
                        itsn = tmp_itsn;
                    }
                    else if(itsn.distance > tmp_itsn.distance){
                        itsn = tmp_itsn;
                    }
                }
            }
        }
        return isInct;
    }
    Intersection left_itsn;
    Intersection right_itsn;
    if(this->left != nullptr && this->left->intersect(r, left_itsn)){
        isInct = true;
        itsn = left_itsn;
    }
    if(this->right != nullptr && this->right->intersect(r, right_itsn)){
        if(!isInct){
            isInct = true;
            itsn = right_itsn;
        }
        else if(right_itsn.distance < left_itsn.distance){
            itsn = right_itsn;
        }
    }
    return isInct;

}

bool KDTreeNode::isShield(Ray &r, double length)
{
    if(this->box.isHit(r)){
        if(this->isLeaf){
            for(unsigned int i = 0; i < this->elems.size(); i++){
                if(this->elems[i]->box.isHit(r)){
                    Intersection tmp_itsn;
                    if(this->elems[i]->getIntersection(r, tmp_itsn))
                        if(tmp_itsn.distance < length && tmp_itsn.distance > 1e-6){
                            //cout << "ict_dis" << tmp_itsn.distance << endl;
                            return true;
                        }
                }
            }
            return false;
        }
        else{
            if(this->left != nullptr){
                bool leftShield = this->left->isShield(r, length);
                if(leftShield)  return true;
            }
            if(this->right != nullptr){
                bool rightShield = this->right->isShield(r, length);
                if(rightShield) return true;
            }
            return false;
        }
    }
    else
        return false;
}
