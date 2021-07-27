precision mediump float;

uniform sampler2D u_texture;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;

uniform float u_tiling;

uniform float u_fogStart;
uniform float u_fogLength;

varying vec2 v_uv;
varying float v_distance;

void main()
{
	vec2 uv_tiled = v_uv * u_tiling;

	vec4 BT = texture2D(u_texture, v_uv);

	vec4 Tex1 = texture2D(u_texture1, uv_tiled);
	vec4 Tex2 = texture2D(u_texture2, uv_tiled);
	vec4 Tex3 = texture2D(u_texture3, uv_tiled);

	float lerpValue =  clamp((v_distance - u_fogStart) / u_fogLength, 0.0, 1.0);
	vec4 fogColor = vec4(0.8, 0.8, 0.8, 1.0);

//	gl_FragColor =  (BT.r * Tex1 + BT.g * Tex2 + BT.b * Tex3) / (BT.r + BT.g + BT.b);
	vec4 fragColor = (BT.r * Tex1 + BT.g * Tex2 + BT.b * Tex3) / (BT.r + BT.g + BT.b);
	gl_FragColor = lerpValue * fogColor + (1.0 - lerpValue) * fragColor;
}
