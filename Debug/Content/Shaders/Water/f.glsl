uniform sampler2D tex0;

void main()
{
	vec4 color = texture2D(tex0, gl_TexCoord[0].st);
	
	gl_FragColor = color * vec4(0.0, 0.0, 1.0, 0.5);
}
