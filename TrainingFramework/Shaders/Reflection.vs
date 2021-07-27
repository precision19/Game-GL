attribute vec3 a_position;
attribute vec2 a_uv;
attribute vec3 a_color;

varying	vec2 v_uv;
varying vec3 vColor;

uniform mat4 u_wvp;

void main()
{
	gl_Position = u_wvp * vec4(a_position, 1.0);
	v_uv = a_uv;
	vColor = a_color;
}
   