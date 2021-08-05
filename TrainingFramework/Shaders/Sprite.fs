precision mediump float;

uniform sampler2D u_texture;

varying vec2 v_uv;

void main()
{
	vec4 texColor = texture2D(u_texture, v_uv);
	if (texColor.a == 0.0)
		discard;
	gl_FragColor = texColor;
}
