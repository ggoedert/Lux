#ifndef LUX_COLOR_H
#define LUX_COLOR_H

enum {
    black,
    darkBlue,
    darkGreen,
    blue,
    brown,
    grey,
    green,
    aqua,
    magenta,
    purple,
    gray,
    lightBlue,
    orange,
    pink,
    yellow,
    white
};

enum {
    dhgr_black     = black,     //hgr_black
    dhgr_darkBlue  = darkBlue,  //hgr_purple
    dhgr_darkGreen = darkGreen, //hgr_green
    dhgr_blue      = blue,      //hgr_blue
    dhgr_brown     = brown,     //hgr_black
    dhgr_grey      = grey,      //hgr_blue
    dhgr_green     = green,     //hgr_green
    dhgr_aqua      = aqua,      //hgr_blue
    dhgr_magenta   = magenta,   //hgr_orange
    dhgr_purple    = purple,    //hgr_purple
    dhgr_gray      = gray,      //hgr_blue
    dhgr_lightBlue = lightBlue, //hgr_white
    dhgr_orange    = orange,    //hgr_orange
    dhgr_pink      = pink,      //hgr_purple
    dhgr_yellow    = yellow,    //hgr_green
    dhgr_white     = white      //hgr_white
};

enum {
    hgr_black  = dhgr_black,
    hgr_blue   = dhgr_blue,
    hgr_green  = dhgr_green,
    hgr_purple = dhgr_purple,
    hgr_orange = dhgr_orange,
    hgr_white  = dhgr_white
};

#endif
