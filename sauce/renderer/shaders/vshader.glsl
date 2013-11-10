uniform mat4 T;
attribute vec4 v;

void main()
{
	gl_Position = T * v;
}
