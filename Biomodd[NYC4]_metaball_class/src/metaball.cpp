#include <iostream>
#include "metaball.h"

/*=================================================================
 
    <<<MASTERPROEF || LOUIS(e) >>>
        ------> Pieter Steyaert (@subtivsubtiv) |  metaball class
                11/06/12
 
 -------------------------------------------------------------------
 This class handles the metaball stuff, making connections between
 organisms for exchange of data. 
    => propagations
    => "food aid"
 
 ===================================================================*/


///////////////////////////////////////////
//	CONSTRUCTOR
///////////////////////////////////////////

metaball::metaball(ofVec2f ball1, ofVec2f ball2, int _radius1, int _radius2, int maxDistance, float bendingScalar, ofColor ball1c, ofColor ball2c){
    ofVec2f dirToOther;
    ofVec2f center1, center2;
    
    int radius1, radius2;
    
    if (_radius1 < _radius2) {
        center1 = ball1;
        center2 = ball2;
        radius1 = _radius1; // smallest radius
        radius2 = _radius2;
        ofColor tempC = ball1c;
        ball1c = ball2c;
        ball2c = tempC;
    } else {
        center1 = ball2;
        center2 = ball1;
        radius1 = _radius2;
        radius2 = _radius1;
    }
    
    int distance = ofDist(center1.x, center1.y, center2.x, center2.y);
    
    dirToOther = center1-center2; // the direction of the two balls towards eachother
    dirToOther.normalize();
    dirToOther.rotate(90);        // rotate the vector (to get the outer coordinates)
    
    
    ofVec2f points[4];
    points[0].set(center1.x-dirToOther.x*radius1, center1.y-dirToOther.y*radius1);
    points[1].set(center1.x+dirToOther.x*radius1, center1.y+dirToOther.y*radius1);
    points[2].set(center2.x+dirToOther.x*radius2, center2.y+dirToOther.y*radius2);
    points[3].set(center2.x-dirToOther.x*radius2, center2.y-dirToOther.y*radius2);
    
    
    int offset = min(radius1, 10); 
    
    if ((radius1+radius2+offset)>=distance) { //used for the "pushing" of metaballs
        points[0].rotate(-ofMap(radius1, 0, 200, 0, 160)+ofMap(distance, radius1+radius2+offset,0,  0, 90), center1);
        points[1].rotate(+ofMap(radius1, 0, 200, 0, 160)-ofMap(distance, radius1+radius2+offset,0,  0, 90), center1);
        points[2].rotate(-ofMap(radius2, 0, 200, 0, 160)+ofMap(distance, radius1+radius2+offset,0,  0, 90), center2);
        points[3].rotate(+ofMap(radius2, 0, 200, 0, 160)-ofMap(distance, radius1+radius2+offset,0,  0, 90), center2);
    } else {
        points[0].rotate(-ofMap(radius1, 0, 200, 0, 130), center1);
        points[1].rotate(+ofMap(radius1, 0, 200, 0, 130), center1);
        points[2].rotate(-ofMap(radius2, 0, 200, 0, 130), center2);
        points[3].rotate(+ofMap(radius2, 0, 200, 0, 130), center2);
    }
    
    float tempOffset = 1; // adjust this when you want the angle point to move over to another location... (closer to ball1 for example)
    ofVec2f centerPoints1; centerPoints1.set((points[1].x+points[2].x*tempOffset)/2, (points[1].y+points[2].y)/2);
    ofVec2f centerPoints2; centerPoints2.set((points[3].x*tempOffset+points[0].x)/2, (points[3].y+points[0].y)/2);
    ofVec2f centerDir; centerDir = centerPoints1-centerPoints2;
    
    float bendingOffset = ofMap(distance, (radius1+radius2)/2, maxDistance, 0, 0.65*bendingScalar);
    
    ofVec4f handlePoints; // we cheat: x, y are used for the first handle points, z,w for the second handle points
    handlePoints.set(centerPoints1.x-centerDir.x*bendingOffset, centerPoints1.y-centerDir.y*bendingOffset, centerPoints2.x+centerDir.x*bendingOffset, centerPoints2.y+centerDir.y*bendingOffset);

    ofPolyline metaPoly;
    

    metaPoly.lineTo(points[1].x, points[1].y);
    metaPoly.bezierTo(handlePoints.x, handlePoints.y, handlePoints.x, handlePoints.y, points[2].x, points[2].y); // handle the bezier-handle points here
    
//    cout << "c this? √√" << endl;
//    cout << metaPoly.size() << endl;
//    for (int i = 0; i < metaPoly.size(); i++) {
//        cout << metaPoly.getVertices().at(i) << endl;
//    }
    metaPoly = metaPoly.getResampledByCount(10);
//    cout << "√√√√ this? √√√" << endl;
    
    ofPoint*polyToMesh1 = new ofPoint[10];
    ofPoint*polyToMesh2 = new ofPoint[10];    
    
    for (int i = 0; i < 10; i++) {
        polyToMesh1[i] = metaPoly.getVertices().at(i);
    }
    metaPoly.clear();
    
    metaPoly.lineTo(points[3].x, points[3].y);
    metaPoly.bezierTo(handlePoints.z, handlePoints.w, handlePoints.z, handlePoints.w, points[0].x, points[0].y); // handle the bezier-handle points here
    metaPoly.lineTo(points[0].x, points[0].y);
    
    metaPoly.simplify();
    metaPoly = metaPoly.getResampledByCount(10);
    
    
    for (int i = 0; i < 10; i++) {
        polyToMesh2[i] = metaPoly.getVertices().at(9-i);
    }
    
    metaPoly.clear();
    metaMesh.clear();

//    ungradient version
    
    ofPoint*polyToMesh3 = new ofPoint[20];
    for (int i = 0; i < 10; i++) {
        polyToMesh3[i*2] = polyToMesh1[i];
        polyToMesh3[i*2+1] = polyToMesh2[i];
    }
    
    
    ofColor setColor;
    setColor = ball2c;
    metaMesh.addColor(setColor);
    metaMesh.addVertex(points[0]);
    metaMesh.addColor(setColor);
    metaMesh.addVertex(points[1]);
    metaMesh.addColor(setColor);
    metaMesh.addVertex(polyToMesh3[1]);

    for (int i = 0; i < 18; i++) {
        ofColor setColor;
        setColor.setBrightness(ofMap(i, 0, 18, ball2c.getBrightness(), ball1c.getBrightness()));
        setColor.setSaturation(ofMap(i, 0, 18, ball2c.getSaturation(), ball1c.getSaturation()));
        setColor.setHue(ofMap(i, 0, 18, ball2c.getHue(), ball1c.getHue()));
        metaMesh.addColor(setColor);
        metaMesh.addVertex(polyToMesh3[(((i*3+0)%3)+i)]);
        metaMesh.addColor(setColor);
        metaMesh.addVertex(polyToMesh3[(((i*3+1)%3)+i)]);
        metaMesh.addColor(setColor);
        metaMesh.addVertex(polyToMesh3[(((i*3+2)%3)+i)]);
    }
    setColor = ball1c;
    metaMesh.addColor(setColor);
    metaMesh.addVertex(metaMesh.getVertices().at(metaMesh.getNumVertices()-2));
    metaMesh.addColor(setColor);
    metaMesh.addVertex(points[2]);
    metaMesh.addColor(setColor);
    metaMesh.addVertex(points[3]);
    

    
// This is the "gradient version"
    
/*    for (int i = 0; i < 10; i++) {
        ofColor setColor;
        setColor.setBrightness(ofMap(i, 0, 9, ball2c.getBrightness(), ball1c.getBrightness()));
       setColor.setSaturation(ofMap(i, 0, 9, ball2c.getSaturation(), ball1c.getSaturation()));
       setColor.setHue(ofMap(i, 0, 9, ball2c.getHue(), ball1c.getHue()));
        metaMesh.addColor(setColor);
        metaMesh.addVertex(polyToMesh1[i]);
        metaMesh.addColor(setColor);
        metaMesh.addVertex(polyToMesh2[i]);
    }

    for (int i = 0; i < 18; i++) {
            metaMesh.addTriangle((((i*3+0)%3)+i),(((i*3+1)%3)+i),(((i*3+2)%3)+i));
    } */
    
    

        metaMesh.setMode(OF_PRIMITIVE_TRIANGLES);

    
    
    

}


///////////////////////////////////////////
//	PUBLIC METHODS
///////////////////////////////////////////


void metaball::makeMesh(int distance){
 /*   metaMesh.clear();
    
    ofxDelaunay triangulator;

       int nPoints = 0; // random points
    while (nPoints<20) {
//        ofSeedRandom(nPoints);
        ofVec3f rPoint = ofVec3f(ofRandom(metaPoly.getBoundingBox().x, metaPoly.getBoundingBox().x+metaPoly.getBoundingBox().width ), ofRandom(metaPoly.getBoundingBox().y, metaPoly.getBoundingBox().y+metaPoly.getBoundingBox().height), 0);
        
        if (ofInsidePoly(rPoint.x, rPoint.y, metaPoly.getVertices())) {
            triangulator.addPoint(rPoint.x, rPoint.y, 0);
            nPoints++;
        }
    }
//    ofSeedRandom();
    metaPoly = metaPoly.getResampledByCount(100);
    for (int i = 0; i < metaPoly.getVertices().size(); i++) {
        triangulator.addPoint(metaPoly.getVertices().at(i).x,metaPoly.getVertices().at(i).y,0);
    }
    
    triangulator.triangulate();
    
    XYZ *p = triangulator.getPoints();
    ITRIANGLE *v = triangulator.getTriangles();
    
    for(int i=0; i < triangulator.getNumTriangles() ; i++){
        
        ofVec3f vec1 = ofVec3f(p[v[i].p1].x, p[v[i].p1].y,p[v[i].p1].z);
        ofVec3f vec2 = ofVec3f(p[v[i].p2].x, p[v[i].p2].y,p[v[i].p2].z);
        ofVec3f vec3 = ofVec3f(p[v[i].p3].x, p[v[i].p3].y,p[v[i].p3].z);

        ofColor c1 = ofColor::white;
        c1.setBrightness(ofRandom(150-100, 150+100));
        ofColor c2 = c1;
        ofColor c3 = c1;
        
        metaMesh.addColor(ofColor(c1));
        metaMesh.addVertex(vec1);
        metaMesh.addColor(ofColor(c1));
        metaMesh.addVertex(vec2);
        metaMesh.addColor(ofColor(c1));
        metaMesh.addVertex(vec3);
    }
    
    ofSeedRandom();
    
    for(int i = 0; i < triangulator.getNumTriangles(); i++){
        ofVec2f p1, p2, p3; 
        p1 = metaMesh.getVertex(0+i*3);
        p2 = metaMesh.getVertex(1+i*3);
        p3 = metaMesh.getVertex(2+i*3);
        
        int maxDist = distance/3;
        
        if ((p1.distance(p2)<=maxDist)&&(p1.distance(p3)<=maxDist)&&(p2.distance(p3)<=maxDist)) {
            metaMesh.addTriangle(0 + i *3, 1 + i * 3, 2 + i*3);            
        }

    }    */
}

void metaball::drawMetaball(){

    ofSetColor(255);
    ofFill();
    metaMesh.draw();



    

    ofNoFill();
    ofMesh tempM = metaMesh;




//    metaMesh.drawVertices();
}

void metaball::destroy(){
    metaMesh.clear();
    
}







