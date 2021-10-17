
attribute vec2 a_Position;
attribute float a_Alpha;

uniform vec2 u_Offset;

varying vec4 v_Color;

void main()
{
    vec2 pos = a_Position + u_Offset;

    gl_Position = vec4( pos, 0.0, 1.0 );

    v_Color = vec4( 0.0, a_Alpha, 0.0, a_Alpha );
}
