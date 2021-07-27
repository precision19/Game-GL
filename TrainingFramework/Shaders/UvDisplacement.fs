precision mediump float;

uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

uniform float u_time;

varying vec2 v_uv;

void main()
{
	vec4 v4_disp = texture2D(u_texture1, vec2(v_uv.x, v_uv.y + u_time));
	vec2 disp = vec2(v4_disp.x, v4_disp.y);
	vec2 offset = (2.0 * disp - 1.0);
	vec2 v_uv_displaced = v_uv + offset;

	vec4 fire_color = texture2D(u_texture, v_uv_displaced);
	vec4 AlphaValue = texture2D(u_texture2, v_uv_displaced);

	gl_FragColor = fire_color;
}
