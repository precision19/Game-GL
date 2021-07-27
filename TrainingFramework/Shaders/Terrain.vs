attribute vec3 a_position;
attribute vec2 a_uv;

varying	vec2 v_uv;
varying float v_distance;

uniform vec3 u_cameraPosition;
uniform mat4 u_wvp;

void main()
{
	gl_Position = u_wvp * vec4(a_position, 1.0);
	v_uv = a_uv;

	vec3 distance = vec3(u_cameraPosition.x - a_position.x, u_cameraPosition.y - a_position.y, u_cameraPosition.z - a_position.z);
	v_distance = length(distance.xyz);
}
   