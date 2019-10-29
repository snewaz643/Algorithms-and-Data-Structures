/*******************************************************
* This program is the brain of the Pacman game. It     *
* produces the move based on different budgets and     *
* aims to clear a maximum of 11 levels.                *
*                                                      * 
* created for COMP20003 Algorithms and Data Structures * 
* Assignment 2, 2019                                   *
*                                                      *
* by Syed Ahammad Newaz Saif                           *
* Student Number 684933                                *
*                                                      *
* skeleton program created by Nir Lipovetzky           *                                    
*                                                      *
*******************************************************/

/***********
* INCLUDES *
***********/
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "ai.h"
#include "utils.h"
#include "priority_queue.h"

/***************
* HASH DEFINES *
***************/

#define MAX_MOVES 4

/***************
* STRUCTURES   *
***************/

struct heap h;

/***************
* HASH DEFINES *
***************/

float get_reward( node_t* n );


/*********************************************************
* Function:    initialize_ai()                           *
* Parameters:  None                                      *
* Returns:     None                                      *
* Description: Function to initialise the heap 'h'       *
               called by pacman.c                        *
*********************************************************/

void initialize_ai(){
    heap_init(&h);
}

/*********************************************************
* Function:    copy_state()                              *
* Parameters:  state_t* dst, state_t* src                *
* Returns:     None                                      *
* Description: Function to copy a src into a dst state   *
*********************************************************/

void copy_state(state_t* dst, state_t* src)
{
    //Location of Ghosts and Pacman
    memcpy( dst->Loc, src->Loc, 5*2*sizeof(int) );
    
    //Direction of Ghosts and Pacman
    memcpy( dst->Dir, src->Dir, 5*2*sizeof(int) );
    
    //Default location in case Pacman/Ghosts die
    memcpy( dst->StartingPoints, src->StartingPoints, 5*2*sizeof(int) );
    
    //Check for invincibility
    dst->Invincible = src->Invincible;
    
    //Number of pellets left in level
    dst->Food = src->Food;
    
    //Main level array
    memcpy( dst->Level, src->Level, 29*28*sizeof(int) );
    
    //What level number are we on?
    dst->LevelNumber = src->LevelNumber;
    
    //Keep track of how many points to give for eating ghosts
    dst->GhostsInARow = src->GhostsInARow;
    
    //How long left for invincibility
    dst->tleft = src->tleft;
    
    //Initial points
    dst->Points = src->Points;
    
    //Remiaining Lives
    dst->Lives = src->Lives;
    
}

/*********************************************************
* Function:    create_init_node()                        *
* Parameters:  state_t* init_state                       *
* Returns:     Pointer to a node to be inserted into the *
*               heap.                                    *
* Description: Function creates a initial node copying   *
*              state and returning to point of call      *
*********************************************************/

node_t* create_init_node( state_t* init_state )
{   
    // allocate space for the new node in default mode
    node_t * new_n = (node_t *) malloc(sizeof(node_t));
    
    // set it's parent, priority, depth and num_childs 
    // to default values
    new_n->parent = NULL;
    new_n->priority = 0;
    new_n->depth = 0;
    new_n->num_childs = 0;
    
    // copy over the state to the new node
    copy_state(&(new_n->state), init_state);
    
    // add it's default reward
    new_n->acc_reward =  get_reward( new_n );
    return new_n;  
}

/*********************************************************
* Function:    heuristic()                               *
* Parameters:  node_t* n                                 *
* Returns:     Returns the heuristic value of a given    *
*               node as a floating point number.         *
* Description: Function creates a initial node copying   *
*              state and returning to point of call.     *
*********************************************************/

float heuristic( node_t* n )
{
    float h = 0.00;
    float i = 0.00;
    float l = 0.00;
    float g = 0.00;
    
    // If parent doesnt exist then the child can't exist
    if(n -> parent == NULL  )
    {
        return 0.00;
    }
    
    // The parent state must not be Invincible for the child to be Invincible
    if( (n -> state.Invincible == 1) && (n -> parent -> state.Invincible == 0)){
        i = 10.00;
    }
    
    // Lost a life if the lives of the child decreased relative to parent's life
    if(n -> state.Lives < n -> parent -> state.Lives)
    {
        l = 10.00;
    }
    
    // If all the lives are lost
    if(n -> state.Lives <= 0 )
    {
        g = 100.00;
    }
    
    // formula of the heuristic function
    h  = i -l -g;
    
    return h;
}

/***********************************************************
* Function:    get_reward()                                *
* Parameters:  node_t* n                                   *
* Returns:     Returns the reward for a node at a          *
*              particular state of action.                 *
* Description: Function uses the formula in the spec using * 
*              heuristic value of discount formula to find *
*              the reward of a node.                       *
***********************************************************/

float get_reward ( node_t* n ){
    float reward = 0.00;
    
    // if parent exist then only use formula  
    // r(n) = h(n) + change_in_score from child to parent node
    if(n-> parent)
    {
        reward = heuristic(n) + ((n-> state.Points) - (n -> parent -> state.Points));
        
    }
    
    // finally account discount factor
    float discount = pow(0.99,n->depth);
    
    return discount * reward;
}

/***************************************************************
* Function:    applyAction()                                   *
* Parameters:  node_t* n, node_t** new_node, move_t action     *
* Returns:     Returns a flag stating if an applicable action  * 
*              happened or not.                                *
* Description: Apply an action to node n and return a new node *
*              resulting from executing the action.            * 
***************************************************************/

bool applyAction(node_t* n, node_t** new_node, move_t action )
{
    
    bool changed_dir = false;
    
    // copy the state of the old node to the new node
    copy_state( & ( (*new_node) ->  state), &(n -> state));
    
     // point  it out to the parent
    (*new_node) -> parent = n;
    
    // apply the action on the new_node
    changed_dir = execute_move_t( &((*new_node)->state), action );
    
    return changed_dir;
    
}

/****************************************************************
* Function:    avg_propagateBackScoreToFirstAction()            *
* Parameters:  node_t* n                                        *
* Returns:     Returns back the tree containing the accumulated *
*              reward                                           *
* Description: It moves up the subtree collecting average of    *
*              the rewards up to the root of the tree.          * 
****************************************************************/

node_t* avg_propagateBackScoreToFirstAction(node_t* node, float * best_action_score)
{
    node_t * curr = node;
    
    // loop through the current node's parent's parent and check 
    // it did not reach the root
    while(curr -> parent -> parent)
    {
        // increment it's children
        curr -> parent -> num_childs++;
        // move up the tree
        curr = curr -> parent;
    }
    
    if(curr -> num_childs > 0)
    {   
        // accumulate the reward subtree by subtree
        best_action_score[curr -> move] = (best_action_score[curr -> move] * (curr -> num_childs -1) + node -> acc_reward)/(curr -> num_childs );
    }
    
    return curr;
    
   
}

/*****************************************************************
* Function:    max_propagateBackScoreToFirstAction()             *
* Parameters:  node_t* n                                         *
* Returns:     Returns back the tree containing the accumulated  *
*              reward                                            *
* Description: It moves up the subtree collecting maximum of     *
*              the rewards of the children up to the root of the *
*              tree.                                             * 
*****************************************************************/

node_t* max_propagateBackScoreToFirstAction(node_t* new_node, float* best_action_score)
{
    node_t* curr = new_node;
    float max_score = curr -> acc_reward;
    
    // loop through the current node's parent's parent 
    // and check it did not reach the root
    while(curr -> parent -> parent)
    {   
        // increment it's children
        curr -> parent -> num_childs++;
        // move up the tre
        curr = curr -> parent;
    }

    // find the max(max_score, curr -> acc_reward)
    if(max_score > best_action_score[curr-> move])
    {
        // put the max value in the array
        best_action_score[curr-> move] = max_score;
    }
    return curr;
}

/******************************************************************
* Function:    update_nodes()                                     *
* Parameters:  node_t* parent_node,node_t* child_node,move_t move *
* Returns:     None                                               *
* Description: Updates the child node and links to the parent     *
*              node                                               * 
******************************************************************/

void update_nodes(node_t* parent_node, node_t* child_node, move_t move)
{
     // update child node's depth, priority, parent, move, number of
     // children and reward(accumulated)
     child_node -> depth = parent_node -> depth + 1;
     child_node -> priority = (-1)* (child_node -> depth);
     child_node -> parent = parent_node;
     child_node -> move = move;
     child_node -> num_childs = 0;
     child_node -> acc_reward = parent_node -> acc_reward + get_reward(child_node);
}

/********************************************************************
* Function:    get_next_move()                                      *
* Parameters:  state_t init_state, int budget,                      *
*              propagation_t propagation, char* stats,              *
*              output_t* outputfile                                 *
* Returns:     Returns the best action for the pacman based on the  *
*              other functions that uses heuristic function with    *
*              the given formula in the spec.                       *
* Description: Find best action by building all possible paths up   *
*              to budget and back propagate using either max or avg *
*              and write the output to outputfile.                  *     
********************************************************************/

move_t get_next_move( state_t init_state, int budget, propagation_t propagation, char* stats, output_t* outputfile)
{
    // starting time of the algorithm
    clock_t start = clock();
    
    // defaulting of the best action moves
    float best_action_score[MAX_MOVES];
    
    for( unsigned i = 0; i < MAX_MOVES; i++ )
    { 
        best_action_score[i] = INT_MIN;
    }
    
    unsigned generated_nodes = 0;
    unsigned expanded_nodes = 0;
    unsigned max_depth = 0;
    //move_t move;
    node_t *initial_act;
    float max_score;
    move_t best_action;
    
    // created the explored array with the given budget and number of nodes
    node_t** explored =  malloc(sizeof(node_t*) * (budget*4) ); 
    
    // initial node created
    node_t* n = create_init_node( &init_state );
   
    
    // push the node on to the heap
    heap_push( &h, n ); 
    
    // main body of the algorithm starts here
    while( h.count > 0)
    {
        // pop off node from the heap
        n = heap_delete(&h);
        
        //node inserted into the explored array
        explored[expanded_nodes++] = n; 
        
        if( expanded_nodes <= budget ) 
        {
            // checking each applicable action
            for( unsigned moves = left ; moves < 4; moves++ )
            {
                // create a new node and update expanded
                node_t* new_node = (node_t*)malloc(sizeof(node_t));
                generated_nodes++;
                
                // if a valid action was applied
                
                if( applyAction( n, &new_node, moves ) )
                {
                    // update nodes linking the parent node to the child node
                    update_nodes(n, new_node, moves);
                    
                    // getting max(max_depth, new_node -> depth)
                    if( (new_node) -> depth > max_depth)
                    {
                        max_depth = (new_node) -> depth;
                    }
                    
                    // push it to the heap
                    heap_push( &h, new_node );
                    
                    // if average propagation prompted
                    if(propagation)
                    {
                       // return back the node of the average propagation
                       initial_act = avg_propagateBackScoreToFirstAction( new_node, best_action_score );
                    
                    }else{
                      // maximum propagation is prompted and we return the node of maximum
                      // propagation
                      initial_act  = max_propagateBackScoreToFirstAction( new_node, best_action_score );
                    }
                    
                }else{
                    // else delete if life is lost
                    free(new_node);
                }
            }
        }
    }
    
    best_action = 0;
    max_score = best_action_score[0];
    int counter = 1;
    
    // pick up all duplicate maximum scores
    for (int j = 1; j< MAX_MOVES; j++) {
        if (best_action_score[j] > max_score) {
            max_score = best_action_score[j];
            counter = 1;
        } else if (best_action_score[j]==max_score) {
            // increase count helping get duplicates
            counter++;
        }
    }
    
    // use any of the maximum score by random 
    int new_counter = rand()%counter;
    for (int l=0; l < MAX_MOVES; l++) {
        if (best_action_score[l]==max_score) 
        {
            if (new_counter == 0) 
            {
                best_action=l; 
                break;
            }
            // reach the end of the counter by decrementing
            new_counter--;
        }
    }
    
    // print out the current statistics : Max Depth, Expanded nodes, Generated nodes
    sprintf(stats, "Max Depth: %d Expanded nodes: %d  Generated nodes: %d\n",max_depth,expanded_nodes,generated_nodes);
  
    // print the appropriate action as Selected action : 
    if(best_action == left)
        sprintf(stats, "%sSelected action: Left\n",stats);
    if(best_action == right)
        sprintf(stats, "%sSelected action: Right\n",stats);
    if(best_action == up)
        sprintf(stats, "%sSelected action: Up\n",stats);
    if(best_action == down)
        sprintf(stats, "%sSelected action: Down\n",stats);
    
    // print score left, right, up, down
    sprintf(stats, "%sScore Left %f Right %f Up %f Down %f",stats,best_action_score[left],best_action_score[right],best_action_score[up],best_action_score[down]);
    
    // free up all memory of the pointers used
    for(int k = 0; k < expanded_nodes; k++)
    {
        free(explored[k]);
    }
    free(explored);
    emptyPQ(&h);
    
    // starting time of the algorithm
    clock_t end = clock();
    
    // time elapsed
    double secs= ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // find max(max_depth, outputfile -> max_depth) and update
    // outputfile's max_depth
    if (max_depth > outputfile -> max_depth)
    {
        outputfile-> max_depth = max_depth;
        
    }
    
    // outputfile's total generated, total expanded nodes 
    // and time recorded
    outputfile -> total_generated+=generated_nodes;
    outputfile -> total_expanded+=expanded_nodes;
    outputfile -> time+=secs;
    
    return best_action;
}