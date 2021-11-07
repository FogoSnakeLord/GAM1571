
varying vec4 v_Color;
uniform float u_Red;
uniform vec4 u_Colour;
void main()
{
    gl_FragColor = u_Colour+vec4(u_Red,0,0,0);
}
