// project5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include<iostream>
#include<string>
#include<fstream>
using namespace std;


class QtNode {
public:
    int color;
    int upperR;
    int upperC;
    int size;

    QtNode* NWkid;
    QtNode* NEkid;
    QtNode* SWkid;
    QtNode* SEkid;

    QtNode(int c,int uR, int uC, int s) {
        //to creat a QtNode
        color = c;
        upperC = uC;
        upperR = uR;
        size = s;
        NWkid = nullptr;
        NEkid = nullptr;
        SWkid = nullptr;
        SEkid = nullptr;
    }

    void printQtNode(ofstream &outFile2) {
        if (this->NEkid == nullptr && this->NWkid == nullptr && this->SEkid == nullptr && this->SWkid == nullptr)
        {
           outFile2<< "color: " << color << " upperR: " << upperR << " upperC: " << upperC << " Size: " << size << " NWkid's color: " << "-1"
                << " NEkid's color: " << "-1" << " SWkid's color: " << "-1" << " SEkid's color: " << "-1" << endl;
        }
        else {
            outFile2 << "color: " << color << " upperR: " << upperR << " upperC: " << upperC << " Size: " << size;
            if (this->NWkid != nullptr) {
                outFile2 << " NWkid's color: " << this->NWkid->color;
            }
            else { outFile2 << " NWkid's color: " << "NULL"; }
            if (this->NEkid != nullptr)
            {
                outFile2 << " NEkid's color: " << this->NEkid->color;
            }
            else { outFile2 << " NEkid's color: " << "NULL"; }
            if (this->SWkid != nullptr)
            {
                outFile2 << " SWkid's color: " << this->SWkid->color;
            }
            else { outFile2 << " SWkid's color: " << "NULL"; }
            if (this->SEkid != nullptr)
            {
                outFile2 << " SEkid's color: " << this->SEkid->color<<endl;
            }
            else { outFile2 << " SEkid's color: " << "NULL" << endl; }
        }
    }

};
class QuadTree{
public:
    QtNode* QtRoot;
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int power2Size;
    int** imgAry;
    int** newimgAry;
    
    QuadTree() {
        QtRoot = nullptr;
        numRows = 0;
        numCols = 0;
        minVal = 0;
        maxVal = 0;
        power2Size = 0;
        imgAry = nullptr;
        newimgAry = nullptr;
        
    }

    void zero2DAry(int** ary) {
        for (int i = 0; i < power2Size; i++) {
            ary[i] = new int[power2Size];
            for (int j = 0; j < power2Size; j++) {
                ary[i][j] = 0;
            }
        }
      
    }
    int computerPower2(int numR, int numC) {
        int size = max(numR, numC);
        int power2Size = size;
        while (size > power2Size)
            power2Size *= 2;
        return power2Size;
    }
    void loadImage(ifstream &inFile, int** imgAry) {
        int a = 0;
        if (!inFile.is_open()) {
            cout << "Unable to open" << endl;
        }
        else
        {
           string  img;
          // cout << "load image part:" << endl;
           for (int i = 0; i < power2Size; i++) {
               for (int j = 0; j < power2Size; j++) {
                   inFile >> img;
                   a = stoi(img);
                   //cout << a;
                  imgAry[i][j] = a;
                 // cout << imgAry[i][j] <<" ";
               }
              // cout << endl;
           }
       }
    }
    QtNode* buildQuadTree(int** imgary,int upR, int upC,int size,ofstream &outFile2) {
        QtNode *node = new QtNode(-1, upR, upC, size);
        int halfSize;
        if (size == 1) {
            node->color = imgary[upR][upC];
           // cout << "when size equal 1: imgary[" << upR << "]" << "[" << upC << "]= " <<imgary[upR][upC] << endl;
        }
        else
        {
            halfSize = size / 2;
            node->NWkid = buildQuadTree(imgary, upR, upC, halfSize,outFile2 );
            node->NEkid = buildQuadTree(imgary, upR, upC + halfSize, halfSize,outFile2);
            node->SWkid = buildQuadTree(imgary, upR + halfSize, upC, halfSize, outFile2);
            node->SEkid = buildQuadTree(imgary, upR + halfSize, upC + halfSize, halfSize, outFile2);
            int sumColor = addKidsColor(*node);
            //cout << "thi is the sum: " << sumColor << endl;
            if (sumColor == 0) {
                //cout << "sum of 0 part run: " << endl;
                node->color = 0;
                node->NEkid = nullptr;
                node->NWkid = nullptr;
                node->SEkid = nullptr;
                node->SWkid = nullptr;
            }
            else if (sumColor == 4) {
                //cout << "sum of 4 part run: " << endl;
                node->color = 1;
                node->NEkid = nullptr;
                node->NWkid = nullptr;
                node->SEkid = nullptr;
                node->SWkid = nullptr;

            }
            else
                node->color = 5;
            
        }
       node->printQtNode(outFile2);
       return node;
    }

    int addKidsColor(QtNode &node) {
        int sum = 0;
        sum = node.NEkid->color + node.NWkid->color + node.SEkid->color + node.SWkid->color;

        return sum;
    }
    bool isLeaf(QtNode& node) {
        if (node.color == 1 || node.color == 0)
            return true;
        else
            return false;
    }
    void getLeaf(QtNode& qt, int** newImgAry) {
        if (isLeaf(qt))
            fillnewImgAry(qt, newImgAry);
        else
        {
            getLeaf(*qt.NWkid, newImgAry);
            getLeaf(*qt.NEkid, newImgAry);
            getLeaf(*qt.SWkid, newImgAry);
            getLeaf(*qt.SEkid, newImgAry);
        }
    }

    void fillnewImgAry(QtNode& qt, int** newImgAry) {
        int color = 0; int R = 0; int C = 0; int sz = 0;
        color = qt.color; R = qt.upperR; C = qt.upperC; sz = qt.size;
        for (int i = R; i < R + sz; i++) {
            for (int j = C; j < C + sz; j++) {
                newImgAry[i][j] = color;
            }
        }
    }
    void preOrder(QtNode &qt,ofstream &outFile1) {
        if (isLeaf(qt))
            qt.printQtNode(outFile1);
        else
        {
            qt.printQtNode(outFile1);
            preOrder(*qt.NWkid, outFile1);
            preOrder(*qt.NEkid, outFile1);
            preOrder(*qt.SWkid, outFile1);
            preOrder(*qt.SEkid, outFile1);
        }

    }
    void postOrder(QtNode& qt, ofstream &outFile1) {
        if (isLeaf(qt))
            qt.printQtNode(outFile1);
        else
        {
            preOrder(*qt.NWkid, outFile1);
            preOrder(*qt.NEkid, outFile1);
            preOrder(*qt.SWkid, outFile1);
            preOrder(*qt.SEkid, outFile1);
            qt.printQtNode(outFile1);
        }
    }

};
int main(int argc, const char* argv[])
{

    QuadTree *qt = new QuadTree();
    ifstream inFile = ifstream(argv[1]);
    ofstream *outFile1 = new ofstream (argv[2]);
    ofstream *outFile2 = new ofstream(argv[3]);
    ofstream *outFile3 = new ofstream(argv[4]);
    string img; string row; string rol; string minV; string maxV;
    inFile >> row >> rol >> minV >> maxV; // read the first line of 4 value for row, clo, minValue and max Value
    int numR = stoi(row); int numL = stoi(rol); int numMin = stoi(minV); int numMax = stoi(maxV); //convert the string type to int
    qt->power2Size = qt->computerPower2(numR, numL);
    int pow = qt->power2Size;
    *outFile2 << "This is the pwer2size we get after running the method: " << pow << endl; 
    qt->imgAry = new int* [qt->power2Size];
    for (int i = 0; i < qt->power2Size; i++) {
        qt->imgAry[i] = new int[qt->power2Size];
    }

    qt->newimgAry = new int* [qt->power2Size];
    for (int i = 0; i < qt->power2Size; i++) {
        qt->newimgAry[i] = new int[qt->power2Size];
    }
    qt->zero2DAry(qt->imgAry);
    qt->zero2DAry(qt->newimgAry);
    qt->loadImage(inFile, qt->imgAry);
    qt->QtRoot = qt->buildQuadTree(qt->imgAry, 0, 0, qt->power2Size, *outFile2);

    *outFile1 << "===================this is PreOrder part===================" << endl;
    qt->preOrder(*qt->QtRoot, *outFile1);
    *outFile1 << "===================this is PostOrder part===================" << endl;
    qt->postOrder(*qt->QtRoot, *outFile1);

    qt->getLeaf(*qt->QtRoot, qt->newimgAry);


    *outFile3 << "===================this is the part for ImgAry================" << endl;
    for (int i = 0; i < qt->power2Size; i++) {
        for (int j = 0; j < qt->power2Size; j++) {
            *outFile3 << qt->imgAry[i][j] << " ";
        }
        *outFile3 << endl;
    }
    *outFile3 << "===================this is the part for newImgAry================" << endl;
    for (int i = 0; i < qt->power2Size; i++) {
        for (int j = 0; j <qt->power2Size; j++) {
           *outFile3<< qt->newimgAry[i][j] << " ";
        }
          *outFile3 << endl;
    }

    inFile.close();
    outFile1->close();
    outFile2->close();
    outFile3->close();

}

