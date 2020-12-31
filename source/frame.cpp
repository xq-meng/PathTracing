#include "frame.h"

bool Frame::load_obj(string objfilename)
{
    ifstream objfile(objfilename);
    if(!objfile.is_open())
        return false;

    vector<vector3D> vertice_pos;
    vector<vector3D> vertice_nor;
    string keyWords;
    string line;
    Material* matl = nullptr;
    string mtllibName;

    int linecount = 0;

    while(objfile){
        getline(objfile, line);
        keyWords = "";
        linecount++;
        stringstream lineStream(line);
        lineStream >> keyWords;
        if(keyWords == "mtllib"){
            lineStream >> mtllibName;
            mtllibName = objfilename.substr(0, objfilename.find_last_of("/") + 1) + mtllibName;
            cout << mtllibName << endl;
            this->load_mtl(mtllibName);
        }
        else if(keyWords == "v"){
            double x, y, z;
            lineStream >> x >> y >> z;
            vector3D vertPos(x, y, z);
            vertice_pos.push_back(vertPos);
        }
        else if(keyWords == "vn"){
            double x, y, z;
            lineStream >> x >> y >> z;
            vector3D vertNor(x, y, z);
            vertice_nor.push_back(vertNor);
        }
        else if(keyWords == "usemtl"){
            string matlName;
            lineStream >> matlName;
            matl = &(this->matlList[matlName]);
        }
        else if(keyWords == "f"){
            string segStr;
            vector<int> elemVertPosId;
            vector<int> elemVertNorId;
            vector<vector3D> elemVertPos(3);
            vector<vector3D> elemVertNor(3);
            while(lineStream >> segStr){
                int posId = stoi(segStr.substr(0, segStr.find_first_of('/') + 1));
                int norId = stoi(segStr.substr(segStr.find_last_of('/') + 1, segStr.length() - segStr.find_last_of('/')));
                elemVertPosId.push_back(posId);
                elemVertNorId.push_back(norId);
            }
            // Normal sitution: triangle face
            for(unsigned int i = 0; i < 3; i++){
                elemVertPos[i] = vertice_pos[static_cast<unsigned int>(elemVertPosId[i] - 1)];
                elemVertNor[i] = vertice_nor[static_cast<unsigned int>(elemVertNorId[i] - 1)];
            }
            Element* curElem = new Element(elemVertPos, elemVertNor, matl);
            curElem->updateAABBBox();
            this->elems.push_back(curElem);
            // Special sitution: quadrangle face
            // Split one quadrangle into two triangles, the first triangle is settled before.
            // Assume the four vertice are aligned in clockwise or anticlockwise.
            //if(elemVertPosId.size() == 4){
            //    elemVertPos[1] = elemVertPos[2];
            //    elemVertPos[2] = vertice_pos[static_cast<unsigned int>(elemVertPosId[static_cast<unsigned int>(elemVertPosId.size() - 1)] - 1)];
            //    elemVertNor[1] = elemVertNor[2];
            //    elemVertNor[2] = vertice_nor[static_cast<unsigned int>(elemVertNorId[static_cast<unsigned int>(elemVertNorId.size() - 1)] - 1)];
            //    Element* curSplitElem = new Element(elemVertPos, elemVertNor, matl);
            //    curSplitElem->updateAABBBox();
            //    this->elems.push_back(curSplitElem);
            //}
            // Special sitution: multiple edge facet
            // Assume all vertice are aligned in clockwise or anticlockwise.
            if(elemVertPosId.size() > 3){
                for(unsigned int i = 3; i < elemVertPosId.size(); i++){
                    elemVertPos[1] = vertice_pos[static_cast<unsigned int>(elemVertPosId[static_cast<unsigned int>(i - 1)] - 1)];
                    elemVertPos[2] = vertice_pos[static_cast<unsigned int>(elemVertPosId[static_cast<unsigned int>(i)] - 1)];
                    elemVertNor[1] = vertice_nor[static_cast<unsigned int>(elemVertNorId[static_cast<unsigned int>(i - 1)] - 1)];
                    elemVertNor[2] = vertice_nor[static_cast<unsigned int>(elemVertNorId[static_cast<unsigned int>(i)] - 1)];
                    Element* curSplitElem = new Element(elemVertPos, elemVertNor, matl);
                    curSplitElem->updateAABBBox();
                    this->elems.push_back(curSplitElem);
                }
            }
        }
    }
    this->updateBox();
    this->buildKDtree();
    return true;
}

bool Frame::load_mtl(string mtlfilename)
{
    ifstream mtlfile(mtlfilename);
    if(!mtlfile.is_open())
        return false;

    string line;
    string keyWords;
    string curMatlStr;

    while(mtlfile){
        getline(mtlfile, line);
        stringstream lineStream(line);
        lineStream >> keyWords;
        if(keyWords == "newmtl"){
            lineStream >> curMatlStr;
        }
        else if(keyWords == "Kd"){
            double r, g, b;
            lineStream >> r >> g >> b;
            vector3D kd(r, g, b);
            this->matlList[curMatlStr].Kd = kd;
        }
        else if(keyWords == "Ka"){
            double r, g, b;
            lineStream >> r >> g >> b;
            vector3D ka(r, g, b);
            this->matlList[curMatlStr].Ka = ka;
        }
        else if(keyWords == "Tf"){
            double r, g, b;
            lineStream >> r >> g >> b;
            vector3D tf(r, g, b);
            this->matlList[curMatlStr].Tf = tf;
        }
        else if(keyWords == "Ni"){
            double ni;
            lineStream >> ni;
            this->matlList[curMatlStr].Ni = ni;
        }
        else if(keyWords == "Ks"){
            double r, g, b;
            lineStream >> r >> g >> b;
            vector3D ks(r, g, b);
            this->matlList[curMatlStr].Ks = ks;
        }
        else if(keyWords == "Ns"){
            double ns;
            lineStream >> ns;
            this->matlList[curMatlStr].Ns = ns;
        }
    }
    return true;
}

void Frame::updateBox()
{
    this->boundingBox.initialize(this->elems[0]->box.bottom_left, this->elems[0]->box.top_right);
    for(unsigned int i = 1; i < this->elems.size(); i++){
        this->boundingBox.fitVertex(this->elems[i]->box.bottom_left);
        this->boundingBox.fitVertex(this->elems[i]->box.top_right);
    }
}

void Frame::buildKDtree()
{
    this->kdTree.build(this->elems, this->boundingBox, 0);
}

bool Frame::intersect(Ray itRay, Intersection &itsn)
{
    return this->kdTree.intersect(itRay, itsn);
    // for debug.
    //bool isInct = false;
    //for(unsigned int i = 0; i < this->elems.size(); i++){
    //    if(elems[i]->box.isHit(itRay)){
    //        Intersection tmp_itsn;
    //        if(elems[i]->getIntersection(itRay, tmp_itsn)){
    //            if(!isInct){
    //                isInct = true;
    //                itsn = tmp_itsn;
    //            }
    //            else{
    //                if(itsn.distance > tmp_itsn.distance)
    //                    itsn = tmp_itsn;
    //            }
    //        }
    //    }
    //}
    //return isInct;
}

bool Frame::isShield(Ray r, double length)
{
    return this->kdTree.isShield(r, length);
}
