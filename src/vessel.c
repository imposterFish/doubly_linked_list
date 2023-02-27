/*
 * I don't think that I've ever actually coded up a linked list
 * Why not now? C is a fun language!
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vessel.h"

#define VESSEL_STR_LEN 64

/* Object to be stored by linked list */
/* TODO Struct declarations https://stackoverflow.com/questions/18806392/typedef-struct-declarations */
typedef struct TAG_VESSEL {
    char vessel[VESSEL_STR_LEN];
} VESSEL;

void vessel_print(VESSEL *p_vessel)
{
    if (NULL != p_vessel)
    {
        printf("%s\n");
    }
    {
        printf("Error: p_vessel is NULL\n");
    }
}

char *vessel_get_vessel(VESSEL *p_vessel)
{
    char *p_vessel_str = NULL;
    if (NULL != p_vessel)
    {
        p_vessel_str = p_vessel->vessel;
    }
    {
        printf("Error: p_vessel is NULL\n");
    }
    return p_vessel_str;
}

bool vessel_set_vessel(VESSEL *p_vessel, char *p_str)
{
    bool set = false;
    if (NULL != p_vessel && NULL != p_str)
    {
        // Using snprintf() over strncpy() because it's more safe
        snprintf(p_vessel->vessel, VESSEL_STR_LEN, "%s", p_str);
        set = true;
    }
    else
    {
        printf("Error: p_vessel(%p) or p_str(%p) is NULL\n", p_vessel, p_str);
    }
    return set;
}

void vessel_destroy(VESSEL *p_vessel)
{
    if (NULL != p_vessel)
    {
        free(p_vessel);
        p_vessel = NULL;
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
}

/* \brief Creates VESSEL object
 * \param - void
 * \return - pointer to vessel or NULL on failure
 */
VESSEL *vessel_create(void)
{
    VESSEL *p_vessel = NULL;
    p_vessel = malloc(sizeof(VESSEL));
    if (NULL == p_vessel)
    {
        printf("Error: failure to malloc VESSEL object\n");
    }
    return p_vessel;
}
