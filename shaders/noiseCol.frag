varying vec4 position;

uniform float time;
uniform float colorAmount;


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
    float scalar1 = colorAmount;

	float val = noise1(vec4(position.x/scalar1, 
                            position.y/scalar1, 
                            position.z/scalar1, 
                            time*4.0))+0.5;


	gl_FragColor = vec4 (val, 0.6*val, 0.05, 1);	
    
}
