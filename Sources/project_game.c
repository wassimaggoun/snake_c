#include "project_game.h"
#include "alloc.h"
#include "project_snake.h"

game *new_game(int hsize, int vsize, mask *m, int nh, int ns, int vs, int ls) {
    if (hsize<=0 || vsize<=0 ||nh<0 || nh>2 || ns<0 ||vs<0){
        return NULL;
    }
    if (ls<=0){
        ls=1;
    }
    game *g=(game*)malloc(sizeof(game));
    if (g==NULL){
        return NULL;
    }
    
    if (m==NULL){
        g->b = new_board_nomask(hsize,vsize);
    } else {
        if (m->hsize!=hsize || m->vsize!= vsize || m->grid == NULL || m->nbmasked >= m->hsize + m->vsize){
            free(g);
            return NULL;
        }
        g->b = new_board_mask(m);
    }
    if (g->b==NULL){
        free(g);
        return NULL;
    }
    g->nb_ais=ns;
    g->nb_players=nh;
    g->nb_alive=nh+ns;
    g->nb_turns=0;
    int total_snakes = nh+ns;
    if (g->b->empty_cells_count < 2 * total_snakes) {
        delete_board(g->b);
        free(g);
        return NULL;
    }
    g->snakes_array =(snake**)malloc(total_snakes*sizeof(snake*));
    if (g->snakes_array==NULL){
        delete_board(g->b);
        free(g);
        return NULL;
    }
    for (int i=0; i<total_snakes; i++){
        g->snakes_array[i]=new_snake(g->b, vs, ls);
        if (g-> snakes_array[i]==NULL){
            for (int j=0; j<i; j++){
                delete_snake(g->snakes_array[j]);
            }
            free(g->snakes_array);
            delete_board(g->b);
            free(g);
            return NULL;
        }
    }
    return g;

}

void delete_game(game *g){
    if (g == NULL) return;
    delete_board(g->b);
    int nb_snakes = g->nb_ais + g->nb_players;
    for (int i=0 ; i< nb_snakes ; i++){
    delete_snake(g->snakes_array[i]);
    }
    multiple_free(g->snakes_array,g,NULL);
}
void set_direction_player1(game *g, direction dir){
    if (g==NULL || g->nb_players < 1) return;
    snake *s = g->snakes_array[g->nb_ais];
    if (!s->alive) return;
    if (dir != opposite(s->move)){
    s->move = dir;
    }
}

void set_direction_player2(game *g, direction dir){
    if (g == NULL || g->nb_players < 2) return;
    snake *s = g->snakes_array[g->nb_ais + 1];
    if (!s->alive) return;
    if (dir != opposite(s->move)) {
    s->move = dir;
    }
}

void implement_turn_all_snakes(game *g, score_table *st) {
    if (!g || g->nb_alive ==0){
        return ;
    }
    int total_players = g->nb_ais + g->nb_players;
    for (int i=0; i< total_players; i++){
        snake *s = g->snakes_array[i];
        if (s && s->alive){
            bool died = implement_turn_snake(s, g->b);
            if (died){
                g->nb_alive--;
                if (st){
                    int time = get_time_counter() / 1000;
                    update_single_score(st, i, s,time);
                }
            }
        }
    }
    g->nb_turns++;
}

