
#define M_PI     3.1415926535897932
#define M_PI_2   1.5707963267948966
#define M_2_PI   6.283185307179586
#define M_3_2_PI 4.71238898038469

//#define angle 5.5
uniform float angle;
uniform float neededTan;

varying vec2 v_texCoord;

void main() {
    vec4 color = vec4(0., 0., 0., 0.);
    float y = 1.-2.*v_texCoord.y;
    float x = 2.*v_texCoord.x-1.;
    float computedTan = x/y;
    //float neededTan = tan(angle);

    if (angle < M_PI_2) {
        if (computedTan < neededTan && x > 0. && y > 0.) {
            color = texture2D(CC_Texture0, v_texCoord);
        }
    } else if (angle < M_PI) {
        if (x > 0. && (computedTan < neededTan || y > 0.)) {
            color = texture2D(CC_Texture0, v_texCoord);
        }
    } else if (angle < M_3_2_PI) {
        if (x > 0. || (computedTan < neededTan && y < 0.)) {
            color = texture2D(CC_Texture0, v_texCoord);
        }
    } else {
        if (x > 0. || y < 0. || computedTan < neededTan) {
            color = texture2D(CC_Texture0, v_texCoord);
        }
    }

    gl_FragColor = color;
}
