#ifndef GLOBAL_DOT_H    /* This is an "include guard" */
#define GLOBAL_DOT_H

/**
 * This tells the compiler that g_myglobal exists somewhere.
 * Without "extern", this would create a new variable named
 * g_myglobal in _every file_ that included it. Don't miss this!
 */
extern int g_myglobal; /* _Declare_ g_myglobal, that is promise it will be _defined_ by
                        * some module. */
extern int g_breadTextFontSize; /* _Declare_ g_myglobal, that is promise it will be _defined_ by
                        * some module. */
#endif /* GLOBAL_DOT_H */
