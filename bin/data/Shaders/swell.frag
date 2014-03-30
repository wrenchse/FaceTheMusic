uniform sampler2DRect image;
uniform int imgWidth,imgHeight;
uniform int trueWidth, trueHeight;
uniform float rand;
uniform int flags;
uniform vec2 blur_vec;
uniform float timer;
int flgs;
float pix_w,pix_h;
varying vec3 pos;

void main (void)
{
    pix_w = 1.0;
    pix_h = 1.0;
    flgs = flags;
    
    vec2 texCoord = vec2(pos.x,pos.y);
    vec4 col = texture2DRect(image,texCoord);
    vec4 col_s = texture2DRect(image,(texCoord/2.0 + vec2(float(trueWidth/4),float(trueHeight/4)))
        + vec2(sin(pos.y*0.003+timer*0.5)*(60.0+2.0*rand) ,0));
    
    col = col_s;
 //   col.r = col.r * 2.0;
//	col.g = col.g * sin(rand*1.34+pos.y);
//	col.b = col.b * cos(rand*1.56+pos.x*pos.y);
	
    gl_FragColor.rgba = col.rgba*2.0;
}
