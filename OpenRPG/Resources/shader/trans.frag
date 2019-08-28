/* Transition with trans map image */

uniform sampler2D currentScreen;
uniform sampler2D frozenScreen;
uniform sampler2D transMap;
uniform float prog; /* Normalized */
uniform float vague; /* Vague [0, 512] normalized */

void main() {
	vec2 v_texCoord = gl_TexCoord[0].xy;
	vec2 v_texCoord_i = gl_TexCoord[0].xy;
	v_texCoord_i.y = 1 - v_texCoord_i.y;

	float transV = texture2D(transMap, v_texCoord_i).r;
	float cTransV = clamp(transV, prog, prog + vague);
	float alpha = (cTransV - prog) / vague;
	
	vec4 newFrag = texture2D(currentScreen, v_texCoord);
	vec4 oldFrag = texture2D(frozenScreen, v_texCoord);
	
	gl_FragColor = mix(oldFrag, newFrag, alpha);
}