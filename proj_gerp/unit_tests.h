#include "Gerp.h"
#include "processing.h"
#include <cassert>
#include <fstream>

void compToWord() {
    assert(stripNonAlphaNum("co@^$!m\np15:") == "comp15");
    assert(stripNonAlphaNum("c o m!$#^p%&#15") == "comp15");
    assert(stripNonAlphaNum("c!#o$^mp. 15") == "comp15");
    assert(stripNonAlphaNum("Co*(m)p_15") == "Comp15");
    assert(stripNonAlphaNum("c-0m&*)p/15") == "c0mp15");
    assert(stripNonAlphaNum("co&&m___p%15") == "comp15");
    assert(stripNonAlphaNum("co+++M?p!:15") == "coMp15");
    assert(stripNonAlphaNum("@#co~m~'p?@!.15") == "comp15");
}

void noneToNone() {
    assert(stripNonAlphaNum("") == "");
    assert(stripNonAlphaNum("@^$!:") == "");
    assert(stripNonAlphaNum("!$#^") == "");
    assert(stripNonAlphaNum("!#$^.") == "");
    assert(stripNonAlphaNum("*(  \n)") == "");
    assert(stripNonAlphaNum("-&*)") == "");
    assert(stripNonAlphaNum("&&___") == "");
    assert(stripNonAlphaNum("+++?!") == "");
    assert(stripNonAlphaNum("@#~~'?@!:") == "");
}

