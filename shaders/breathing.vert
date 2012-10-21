#version 120

uniform float timeValX = 1.0;
uniform float timeValY = 1.0;
uniform vec2 center;
uniform float maxDistance = 5;
uniform float maxOffset = 1.5;
uniform float minOffset = 0.8;

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



void main(){

	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	//get our current vertex position so we can modify it
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	



	//lets also figure out the distance between the center and the vertex and apply a repelling force away from the center
	vec2 d = vec2(pos.x, pos.y) - center;
	float len =  sqrt(d.x*d.x + d.y*d.y);
	if( len < maxDistance && len > 0  ){
	/*	
		//lets get the distance into 0-1 ranges
		float pct = len / maxDistance; 
		
		//this turns our linear 0-1 value into a curved 0-1 value
		pct *= pct;

		//flip it so the closer we are the greater the repulsion
		pct = 1.0 - pct;
		
		//normalize our repulsion vector
		d /= len;
		
		//apply the repulsion to our position
		pos.x += d.x * pct * 90.0f;
		pos.y += d.y * pct * 90.0f;*/
        
        pos.x = pos.x * map(len, 0, maxDistance, maxOffset, minOffset);
        pos.y = pos.y * map(len, 0, maxDistance, maxOffset, minOffset);
	}


	
	//finally set the pos to be that actual position rendered
	gl_Position = pos;

	//modify our color
	vec4 col = gl_Color;
	gl_FrontColor =  col;	
}
