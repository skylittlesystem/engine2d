uniform vec2 pos;
attribute vec4 v;

void main()
{
	vec4 p = vec4(pos, 0, 1);
	gl_Position = p + v;
}
