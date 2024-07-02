#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <raylib.h>

typedef struct{
    Color background;
} Plug;

static Plug *p = NULL;

void plug_init(void)
{
    p = malloc(sizeof(*p));
    assert(p != NULL);
    memset(p, 0, sizeof(*p));

    p->background = GREEN;
    
    TraceLog(LOG_INFO, "-------------------------");
    TraceLog(LOG_INFO, "Initialized Plugin");
    TraceLog(LOG_INFO, "-------------------------");
}

void* plug_pre_reload(void)
{
    return p;
}

void plug_post_reload(void* state)
{
    p = state;
}

void plug_update(void)
{
    BeginDrawing();
    ClearBackground(GREEN);
    EndDrawing();
}
