uniform float time;

void main() {
	vec4 pos = gl_Vertex;
	
	pos.y = pos.y + sin(time/500+pos.x+pos.z) * 0.25;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_FrontColor = gl_Color;
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * pos;
}
