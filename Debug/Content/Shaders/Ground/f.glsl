uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;

varying vec3 coord;

void main()
{
	vec4 controller = texture2D(tex0, gl_TexCoord[0].st);
	vec4 color = texture2D(tex4, vec2(coord.x, coord.z));
	
	vec4 t1 = texture2D(tex1, vec2(coord.x, coord.z));
	vec4 t2 = texture2D(tex2, vec2(coord.x, coord.z));
	vec4 t3 = texture2D(tex3, vec2(coord.x, coord.z));
	
	
	color = mix(color, t1, controller.r);
	color = mix(color, t2, controller.g);
	color = mix(color, t3, controller.b);
	
	color.a = 1.0;
	
	gl_FragColor = color;
}
