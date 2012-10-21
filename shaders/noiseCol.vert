varying vec4 position;
uniform float time;
uniform float amount;
uniform float maxOffset;

float map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
    
	
    float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
    
    
    if(outputMax < outputMin){
        if( outVal < outputMax )outVal = outputMax;
        else if( outVal > outputMin )outVal = outputMin;
    }else{
        if( outVal > outputMax )outVal = outputMax;
        else if( outVal < outputMin )outVal = outputMin;
    }
    
    return outVal;
    
}


void main() {
	
    //	gl_Position = ftransform();
	
	position = gl_Vertex;
    
    vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    
    float scalar = amount;
    float offset = maxOffset;
    
    //finally set the pos to be that actual position rendered
    float val = noise1(vec4(position.x*scalar, 
                        position.y*scalar, 
                        position.z*scalar, 
                        time*4.0));
    
    float newX = map(val, 0.0, 1.0, 1.0-offset, 1.0+offset);

    pos *= vec4(newX, newX, 1.0, 1.0);
    
	gl_Position = pos;
    gl_FrontColor =  gl_Color;	
    
    
}