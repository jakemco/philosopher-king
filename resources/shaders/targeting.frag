
uniform vec3 ship;

varying vec3 normal, lightDir0, halfVector0, eyeToVert, nEyeToVert, worldPos;

void main()
{
	vec4 color = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	
	vec3 n,halfV;
	float NdotL,NdotHV;
	n = normalize(normal);
	
	float edge = max(dot(n, nEyeToVert), 0);
	
	if (edge < 0.3) {
		color = vec4(0, 0, 0, 1);
	} else {
	
		color += gl_FrontMaterial.ambient * gl_LightSource[0].ambient * 2;
		
		NdotL = max(dot(n,lightDir0),0.0);
		
		if (NdotL > 0.0) {
			if (NdotL < 0.1) {
				NdotL = 0.0;
			} else if (NdotL < 0.3) {
				NdotL = 0.1;
			} else if (NdotL < 0.5) {
				NdotL = 0.3;
			} else if (NdotL < 0.9) {
				NdotL = 0.5;
			}
			
			color += gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * NdotL;
		}
	}
	
	if (length(eyeToVert) < 100) {
		if (mod(worldPos.y + 1 + ship.y,4) < 0.1 ||
			mod(worldPos.x + 4.5 + ship.x,9) < 0.1 ||
			mod(worldPos.z + ship.z,10) < 0.1) {
			color = vec4(1, 1, 0.5, 1);
		}
	}
	
	if (eyeToVert.z > 40 && eyeToVert.z < 41) {
		color = vec4(1,0,0,1);
	}
	
	gl_FragColor = color;
}
