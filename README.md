# Project5 (implement Quadtree representation of a given image)

Input: inFile(argv [1]) a text file contains a binary image with header information. The first text-line is the header 
information: numRows numCols minVal maxVal follows by rows and columns of pixels, 0’s and 1’s. An example below 
is a binary image has four (4) rows and five (5) columns, minVal is 0 and maxVal is 1: 
4 5 0 1
0 0 0 1 0 
0 1 1 0 1 
0 0 1 0 1 
1 0 1 1 1


I. Outputs: 
a) outFile1 (argv [2]): the pre-order 
and post-order traversals of the quadtree
 (needs caption for each traversal!)
 b) outFile2 (argv[3]): all the debugging outputs to get some partial credits.
c) outFile3 (argv[4]): to print imgAry and newImgAry, if the two are the same, then your program works.


step 0: inFile, outFile1, outFile2, outFile3<- open from argv []
step 1: numRows, numCols, minVal, maxVal <- read from inFile
step 2: power2Size <- computePower2(numRows, numCols)
output power2Size to outFile2 with caption
step 3: imgAry <- dynamically allocate the array size of power2Size by power2Size 
 zero2DAry (imgAry)
step 4: newImgAry <- dynamically allocate the array size of power2Size by power2Size
zero2DAry (newImgAry)
step 5: loadImage (inFile, imgAry) 
step 6: QtRoot <- BuildQuadTree (imgAry, 0, 0, power2Size, outFile2)
step 7: preOrder (QtRoot, outFile1) 
step 8: postOrder (QtRoot, outFile1) 
step 9: getLeaf (QtRoot, newImgAry)
step 10: outFile3 <-output imgAry to outFile3 with caption
outFile3 <- output newImgAry to outFile3 with caption.
step 11: close all file
