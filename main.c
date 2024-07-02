#include <stdio.h>
#include <raylib.h>
#include "plug.h"
#include <dlfcn.h>

const char* libplug_path = "./libplug.dylib";
void* lp = NULL;

#define dlerror_on_null(x) if(x == NULL) {fprintf(stderr, "ERROR: %s\n", dlerror()); return false;}
#define load_symbol(x, lib) x = dlsym(lib, #x); dlerror_on_null(x)

bool reload_libplug()
{
    if(lp != NULL) {
	dlclose(lp); 
    }
    
    lp = dlopen(libplug_path, RTLD_NOW);
    dlerror_on_null(lp);
    
    load_symbol(plug_init, lp);
    load_symbol(plug_pre_reload, lp);
    load_symbol(plug_post_reload, lp);
    load_symbol(plug_update, lp);

    return true;
}

int main(void)
{
    if(!reload_libplug()){
	return 1;
    }
    
    InitWindow(800, 600, "Raylib_nob");
    SetTargetFPS(60);
    plug_init();

    while(!WindowShouldClose()){
	if(IsKeyPressed(KEY_R)){
	    void* state = plug_pre_reload();
	    reload_libplug();
	    plug_post_reload(state);
	}
	plug_update();
    }

    CloseWindow();

    return 0;
}
