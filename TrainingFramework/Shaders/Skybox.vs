attribute vec3 a_position;

varying vec4 v_pos;

uniform mat4 u_wvp;

void main()
{
 	gl_Position = u_wvp * vec4(a_position, 1.0);
 	v_pos = vec4(a_position, 1.0);
}