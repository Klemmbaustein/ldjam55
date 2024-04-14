//! #include "shared.frag"

// #params
uniform vec3 u_color = vec3(1);
uniform float u_opacity = 0.5;

void main()
{
	RETURN_COLOR_OPACITY(u_color, u_opacity);
}