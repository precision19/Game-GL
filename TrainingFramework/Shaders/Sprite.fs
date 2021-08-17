precision mediump float;

uniform sampler2D u_texture;
uniform float u_opacity;

varying vec2 v_uv;

void main()
{
	vec4 fragColor = vec4(vec3(texture2D(u_texture, v_uv)), u_opacity);
	gl_FragColor = fragColor;
}
