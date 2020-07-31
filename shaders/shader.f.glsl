void main(void) {
    gl_FragColor = vec4(0.4 * (gl_FragCoord.y / 1080.0), 0.2 * (gl_FragCoord.x / 1920.0), 0.0, 1.0);
}
