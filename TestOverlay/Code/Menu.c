extern void log(char *msg);

void foo(void) {
    // Functions resident in an overlay can access all program variables and
    // constants at any time without any precautions because those are never
    // placed in overlays. The string constant below is an example for such
    // a constant resident in the main program.
    log("Calling from MENU overlay");
}
