varying vec3 normal, lightDir0, halfVector0, eyeToVert, nEyeToVert, worldPos;

uniform vec3 cameraPosition;

void main()
{	
	lightDir0 = normalize(vec3(gl_LightSource[0].position));
	normal = normalize(gl_NormalMatrix * gl_Normal);
	halfVector0 = normalize(gl_LightSource[0].halfVector.xyz);
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	eyeToVert = cameraPosition - (gl_ModelViewMatrix * gl_Vertex).xyz;
	worldPos = (gl_ModelViewMatrix * gl_Vertex).xyz;
	nEyeToVert = normalize(eyeToVert);
}
