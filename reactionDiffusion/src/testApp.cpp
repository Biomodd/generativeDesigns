#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(25);

    b = 70;
    w = ofGetWidth()-b*2;
    h = ofGetHeight()-b*2;

    dt = 3;

    mD = false;

    displayBlur = true;

    startA = 4.0;
    startI = 4.0;

    min = 2;
    max = 10;

    diffA = 0.35;
    diffI = 0.37;
    vDiffA = 0.01;
    vDiffI = 0.05;

    Alpha = 16;
    vAlpha = 0.0;
    betaMean = 12.0;
    betaNoise = 0.0;
    vNoise = 0.000;

     // define arrays
    A = new float*[h];  // chemical A
    I = new float*[h];  // chemical B
    dA = new float*[h];     // chemical A derivative
    dI = new float*[h];     // chemical B derivative
    beta = new float*[h];   // decay

    for(int i=0; i<h; i++) {
        A[i] = new float[w];
        I[i] = new float[w];
        dA[i] = new float[w];
        dI[i] = new float[w];
        beta[i] = new float[w];
    }
    // initialize chemical concentrations, and decay noise field
    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            A[i][j] = startA;
            I[i][j] = startI;
            beta[i][j] = betaMean + betaNoise * ofRandomf();
        }
    }


    pixels = new unsigned char[w*h*3];  // pixel array

    fillImage();

    canvasH = 250;
    canvasW = 400;

    drawCircle(w/2, h/3, 20);
    drawCircle(w/2, h/3*2, 20);
    drawCircle(w/3, h/2, 20);
    drawCircle(w/3*2, h/2, 20);
    //gui = new ofxUICanvas(b+(w/2)-canvasW/2,b+(h/3.5*3)-canvasH/2,canvasW,canvasH);




    }

//--------------------------------------------------------------
void testApp::update(){

     for(int i=0; i<h; i++) {
                for(int j=0; j<w; j++) {
                    float AI = A[i][j] * I[i][j];
                    float Alp = Alpha + vAlpha *(j/float(w));
                    float Beta = vNoise>0 ? betaMean + vNoise * (i/float(h)) : beta[i][j];
                    float diffAx = diffA + (j/float(w))*vDiffA;
                    float diffIy = diffI + (i/float(h))*vDiffI;
                    //float sp = speed + vSpeed*(i/float(h));
                    //cout << "i" << i <<" j " << j << " lap " << diffusion(A,i,j) << endl;
                    dA[i][j] = 0.03*(Alp - AI) + diffAx*diffusion(A,i,j);
                    dI[i][j] = 0.03*(AI - I[i][j] - Beta) + diffIy * diffusion(I,i,j);


                }
            }

            for(int i=0; i<h; i++) {
                for(int j=0; j<w; j++) {
                    if(i==0 || i==h-1 || j==0 || j==w-1) {
                        // mask borders
                        A[i][j] = startA;
                        I[i][j] = startI;
                    } else {
                        // update chemicals + constrain concentration to min+max
                        A[i][j] = constrain(A[i][j] + dt * dA[i][j], min, max);
                        //cout << A[i][j] << endl;
                        I[i][j] = constrain(I[i][j] + dt * dI[i][j], min, max);
                    }
                }
            }

    fillImage();




}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0,0,0);
    imageOut.draw(ofGetWidth()/2 - w/2,ofGetHeight()/2 - h/2);
    glFlush();

}

// *********************************non-default functions

void testApp::fillImage() {

    // calculates pixel values based on the Inhibitor
    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            pixels[i*w*3 + j*3 + 0] = 0; //(unsigned char) 255*(I[i][j]/max);
            pixels[i*w*3 + j*3 + 1] = 0.6*(unsigned char) 255*(I[i][j]/max);
            pixels[i*w*3 + j*3 + 2] = 0.5*((unsigned char) 255*(I[i][j]/max));
        }
    }

    //if(displayBlur) superFastBlur(pixels,w,h,2.0);


    // copies pixel into output image
    imageOut.setFromPixels( pixels, w, h, OF_IMAGE_COLOR);
}

//----------------------------------------------------

float testApp::diffusion(float** chem,int x,int y) {
    // diffusion algorithm
    if(x>0 && x<w-1 && y>0 && y<h-1) {
        float v = chem[x-1][y] + chem[x+1][y] + chem[x][y-1] + chem[x][y+1];
        return -(chem[x][y] - v/4.0);
    } else return 0.0;
}

//------------------------------------------------------

float testApp::constrain(float v, float min, float max) {
    if(v<min) return min;
    else if(v>max) return max;
    else return v;
}

//--------------------------------------------------------

void testApp::drawCircle(int x, int y, float maxr) {
    // use mouse to draw circles of minimum concentration onto the screen
    A[x][y] = min;
    I[y][y] = min;
    for(int r=1; r<maxr; r++) {
        for(float a = 0; a<2*PI; a+=PI/(2*r)) {
            int nx = int(x + sin(a)*r);
            int ny = int(y + cos(a)*r);
            if(nx>0 && nx<w-1 && ny>0 && ny<h-1) {
                A[ny][nx] = min;
                I[ny][nx] = min;
            }
        }
    }
}





//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if(mD) {
        drawCircle(x-(ofGetWidth()/2 - w/2),y-(ofGetHeight()/2 - h/2),dist(x,y,mX,mY)*0.3);
        mX = x;
        mY = y;
    }
}

float testApp::dist(float x1, float y1, float x2, float y2) {
    return sqrt( pow(x2-x1,2) + pow(y2-y1,2) );
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if (button == 0){
        mD = true;
        mX = x;
        mY = y;
    }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    mD=false;

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
