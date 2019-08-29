/* Fade in/out style transition */

uniform sampler2D frozenScreen;
uniform sampler2D currentScreen;
uniform float prog;

void main() {
	vec2 v_texCoord = gl_TexCoord[0].xy;
	vec4 newPixel = texture2D(currentScreen, v_texCoord);
	vec4 oldPixel = texture2D(frozenScreen, v_texCoord);

	gl_FragColor = mix(newPixel, oldPixel, prog);
}