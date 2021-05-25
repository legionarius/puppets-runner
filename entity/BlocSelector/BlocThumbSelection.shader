shader_type canvas_item;

uniform float bright_amount = 0;

void fragment() {
    vec4 c = texture(TEXTURE, UV);
    c.rgb += vec3(bright_amount);
    COLOR = c;
}