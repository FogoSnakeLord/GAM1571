
attribute vec2 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;

uniform vec2 u_ObjectTranslation;
uniform vec2 u_ObjectScale; // TODO: pass in as a uniform.
uniform vec2 u_CameraTranslation; // inverse of the camera's position.
uniform vec2 u_ProjectionScale;
uniform vec2 u_uvScale;
uniform vec2 u_uvOffset;

varying vec2 v_UVCoord;
varying vec4 v_Color;

void main()
{
    vec2 objectSpacePosition = a_Position;
    vec2 worldSpacePosition = objectSpacePosition*u_ObjectScale + u_ObjectTranslation;
    vec2 viewSpacePosition = worldSpacePosition + u_CameraTranslation;
    vec2 clipSpacePosition = viewSpacePosition * u_ProjectionScale;
    gl_Position = vec4( clipSpacePosition, 0.0, 1.0 );
    
    //"Width":	512,
	//"Height":	256,
    //"Name":	"player_06",
    //    "X":	130,
    //    "Y":	62,
    //    "W":	64,
    //    "H":	64

    //vec2 uvScale = vec2( 64.0/512.0, 64.0/256.0 );
    //vec2 uvOffset = vec2( 130.0/512.0, 62.0/256.0 );

    v_UVCoord = a_UVCoord * u_uvScale + u_uvOffset;
    v_Color = a_Color;
}
