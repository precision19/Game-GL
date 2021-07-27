attribute vec3 a_position;
attribute vec2 a_uv;

varying	vec2 v_uv;

uniform mat4 u_wvp;

void main()
{
	gl_Position = u_wvp * vec4(a_position, 1.0);
	v_uv = a_uv;
}
   