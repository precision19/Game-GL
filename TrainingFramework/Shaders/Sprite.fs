precision mediump float;

uniform sampler2D u_texture;
uniform float u_opacity;

varying vec2 v_uv;

void main()
{
	vec4 texColor = vec4(1.0, 1.0, 1.0, u_opacity) *  texture2D(u_texture, v_uv);
	gl_FragColor = texColor;
}
