uniform sampler2D DiffuseTex;

void main()
{
	gl_FragColor = texture2D(DiffuseTex, gl_TexCoord[0]);
}
