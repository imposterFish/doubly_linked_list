/*
 * I don't think that I've ever actually coded up a linked list
 * Why not now? C is a fun language!
 * http://cslibrary.stanford.edu/103/LinkedListBasics.pdf 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vessel_node.h"

/* List structure */
/* https://stackoverflow.com/questions/982388/how-to-implement-a-linked-list-in-c */
typedef struct TAG_VESSEL_NODE {
    VESSEL_NODE *p_next; // Points to the next node
    VESSEL_NODE *p_previous; // Points to the previous node
    VESSEL *p_vessel; // Points to vessel data
} VESSEL_NODE;



size_t vessel_node_forward_length(VESSEL_NODE *p_vessel_node)
{
    size_t length = 0;
    VESSEL_NODE *p_next = NULL;
    if(NULL != p_vessel_node)
    {
        p_next = p_vessel_node->p_next;
        while(NULL != p_next)
        {
            length++;
            p_next = p_next->p_next;
        }
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
    return length;
}

size_t vessel_node_backward_length(VESSEL_NODE *p_vessel_node)
{
    size_t length = 0;
    VESSEL_NODE *p_previous = NULL;
    if(NULL != p_vessel_node)
    {
        p_previous = p_vessel_node->p_previous;
        while(NULL != p_previous)
        {
            length++;
            p_previous = p_previous->p_previous;
        }
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
    return length;
}

size_t vessel_node_total_length(VESSEL_NODE *p_vessel_node)
{
    size_t length = 1; 
    if(NULL != p_vessel_node)
    {
        length = 1; // This node exists
        length += vessel_node_forward_length(p_vessel_node);
        length += vessel_node_backward_length(p_vessel_node);
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
    return length;
}

bool vessel_node_has_previous(VESSEL_NODE *p_vessel_node)
{
    bool has_previous = true;
    if(NULL != p_vessel_node)
    {
        if(NULL == p_vessel_node->p_previous)
        {
            has_previous = false;
        }
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
    return has_previous;
}

bool vessel_node_has_next(VESSEL_NODE *p_vessel_node)
{
    bool has_next = true;
    if(NULL != p_vessel_node)
    {
        if(NULL == p_vessel_node->p_next)
        {
            has_next = false;
        }
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
    return has_next;
}

bool vessel_node_set_next(VESSEL_NODE *p_vessel_node, VESSEL_NODE *p_vessel_next)
{
    bool set = false;
    if(NULL != p_vessel_node && NULL != p_vessel_next)
    {
        p_vessel_node->p_next = p_vessel_next;
        p_vessel_next->p_previous = p_vessel_node;
        set = true;
    }
    else
    {
        printf("Error: p_vessel_node(%p) or p_vessel_next(%p) is NULL\n", p_vessel_node, p_vessel_next);
    }
    return set;
}
bool vessel_node_set_vessel(VESSEL_NODE *p_vessel_node, VESSEL *p_vessel)
{
    bool set = false;
    if(NULL != p_vessel_node && NULL != p_vessel)
    {
        p_vessel_node->p_vessel = p_vessel;
        set = true;
    }
    else
    {
        printf("Error: p_vessel_node(%p) or p_vessel(%p) is NULL\n", p_vessel_node, p_vessel);
    }
    return set;
}

VESSEL_NODE *vessel_node_get_head(VESSEL_NODE *p_vessel_node)
{
    VESSEL_NODE *p_head = NULL;

    if (NULL != p_vessel_node)
    {
        do
        {
            p_head = p_vessel_node->p_previous;
        } while (NULL != p_head);

    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }

    return p_vessel_node;
}

void vessel_node_print_node(VESSEL_NODE *p_vessel_node)
{
    if(NULL != p_vessel_node)
    {
        vessel_print(p_vessel_node->p_vessel);
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
}

void vessel_node_print_list(VESSEL_NODE *p_vessel_node)
{
    VESSEL_NODE *p_head = NULL;
    size_t index = 0;
    if (NULL != p_vessel_node)
    {
        p_head = vessel_node_get_head(p_vessel_node);
        while(NULL != p_head)
        {
            printf("Printing node at index %u: ", index);
            vessel_node_print_node(p_vessel_node);
            index++;
        }
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }

}

bool vessel_node_insert(VESSEL_NODE *p_vessel_node, VESSEL_NODE *p_new_node, size_t index)
{
    bool inserted = false;
    VESSEL_NODE *p_temp = NULL;
    size_t i = 0;

    if(NULL != p_vessel_node && NULL != p_new_node)
    {
        p_temp = p_vessel_node;
        for(i = 0; i < index; i++)
        {
            if (NULL != p_temp)
            {
                if(i != index)
                {
                    p_temp = p_temp->p_next;
                }
                else
                {
                    // p_temp is 
                }
            }
            else
            {
                //
                break;
            }
        }

    }
    else
    {
        printf("Error: p_vessel_node(%p) or p_new_node(%p) is NULL\n", p_vessel_node, p_new_node);
    }
    return inserted;
}

// [!] Unsafe
static void vessel_node_destroy(VESSEL_NODE *p_vessel_node)
{
    if (NULL != p_vessel_node)
    {
        /* We don't want dangling pointers */
        p_vessel_node->p_next = NULL;
        p_vessel_node->p_previous = NULL;

        if (NULL != p_vessel_node->p_vessel)
        {
            vessel_destroy(p_vessel_node->p_vessel);
            p_vessel_node->p_vessel = NULL; 
        }

        free(p_vessel_node);
        p_vessel_node = NULL;
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
}
    
VESSEL_NODE *vessel_node_safe_destroy(VESSEL_NODE *p_vessel_node)
{
    VESSEL_NODE *p_head_node = NULL;
    VESSEL_NODE *p_temp_node_next = NULL;
    VESSEL_NODE *p_temp_node_previous = NULL;

    if (NULL != p_vessel_node)
    {
        /* Re-route the pointers*/
        if(true == vessel_node_has_previous(p_vessel_node))
        {
            /* Before re-routing, find the head */
            p_head_node = vessel_node_get_head(p_vessel_node);

            if(true == vessel_node_has_next(p_vessel_node))
            {
                /* This is a middle node */
                p_temp_node_next = p_vessel_node->p_next;
                p_temp_node_previous = p_vessel_node->p_previous;

                p_temp_node_next->p_previous = p_temp_node_previous;
                p_temp_node_previous->p_next = p_temp_node_next;
            }
            else
            {
                /* This is a tail node */
                p_temp_node_previous = p_vessel_node->p_previous;

                p_temp_node_previous->p_next = p_temp_node_next;
                p_temp_node_previous->p_previous = NULL;
            }
        } // END if(true == vessel_node_has_previous(p_vessel_node))
        else
        {
            if(true == vessel_node_has_next(p_vessel_node))
            {
                /* This is a head node */
                /* The new head will be the next node */
                p_head_node = p_vessel_node->p_next;

                p_temp_node_next = p_vessel_node->p_next;

                p_temp_node_next->p_previous = NULL;
                p_temp_node_next->p_next = p_temp_node_next;
            }
            else
            {
                /* This is the only node */ 
                p_head_node = NULL;      
            }
        }

        vessel_node_destroy(p_vessel_node);
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }

    return p_head_node;
}

void vessel_node_destroy_all(VESSEL_NODE *p_vessel_node)
{
    VESSEL_NODE *p_head = NULL;
    VESSEL_NODE *p_next = NULL;
    if (NULL != p_vessel_node)
    {
        p_head = vessel_node_get_head(p_vessel_node);
        if(NULL != p_head)
        {
            do
            {
                p_next = p_head->p_next;
                vessel_node_destroy(p_head);
                p_head = p_next;
                
            } while (NULL != p_head);
        }
        else
        {
            printf("Unable to get head node\n");
        }
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
}


static void vessel_node_init(VESSEL_NODE *p_vessel_node)
{
    if (NULL != p_vessel_node)
    {
        p_vessel_node->p_next = NULL;
        p_vessel_node->p_vessel = NULL;
    }
    else
    {
        printf("Error: p_vessel_node is NULL\n");
    }
}
/* \brief Creates VESSEL_NODE object
 * \param - void
 * \return - pointer to vessel node or NULL on failure
 */
VESSEL_NODE *vessel_node_create(void)
{
    VESSEL_NODE *p_vessel_node = NULL;
    p_vessel_node = malloc(sizeof(VESSEL_NODE));
    if (NULL != p_vessel_node)
    {
        vessel_node_init(p_vessel_node);
    }
    else
    {
        printf("Error: failure to malloc VESSEL_NODE object\n");
    }
    return p_vessel_node;
}
