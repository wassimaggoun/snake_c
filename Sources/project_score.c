#include "project_score.h"
#include "alloc.h"


score_table* new_score_table(int n_g, int n_s) {
    
}

void delete_score_table(score_table *st) {
    if (st == NULL) return;
    for (int i = 0; i < st->nb_snakes; ++i) {
    for (int j = 0; j <= st->nb_games; ++j) {
      free(st->scores[i][j]);
    }
    free(st->scores[i]);
  }
  multiple_free(st->scores, st ->game_to_score,st->score_to_game,st,NULL);
}

void move_to_next_game(score_table *st) {
    if (st && st->cu_game < st->nb_games) st->cu_game++;
}

void update_single_score(score_table *st, int i, snake *s, int t) {
    if (!st || !s || i < 0 || i >= st->nb_snakes) return;

    int idx = st->game_to_score[i];
    single_score *sc = st->scores[idx][st->cu_game];

    sc->filled = true;
    sc->vals[SC_MAIN] = s->score;
    sc->vals[SC_STUDENTS] = s->students;
    sc->vals[SC_LENGTH] = s->length;
    sc->vals[SC_VISITED] = s->distance;
    sc->vals[SC_TIME] = t;
}


void compute_final_scores(score_table *st) {
    if (!st) return;

    for (int i = 0; i < st->nb_snakes; i++) {
        single_score *final = st->scores[i][st->nb_games];
        final->filled = true;
        for (int k = 0; k < SC_SIZE; k++) {
            final->vals[k] = 0;
            for (int j = 0; j < st->nb_games; j++) {
                if (st->scores[i][j]->filled)
                    final->vals[k] += st->scores[i][j]->vals[k];
            }
        }
    }

}


void sort_scores(score_table *st, int n_g, score_type type) {
    if (!st || n_g < 0 || n_g > st->nb_games || type >= SC_SIZE) return;

    for (int i = 0; i < st->nb_snakes - 1; i++) {
        for (int j = i + 1; j < st->nb_snakes; j++) {
            int val_i = st->scores[i][n_g]->vals[type];
            int val_j = st->scores[j][n_g]->vals[type];

            if (val_j > val_i) {
                single_score **tmp_scores = st->scores[i];
                st->scores[i] = st->scores[j];
                st->scores[j] = tmp_scores;

                int tmp = st->score_to_game[i];
                st->score_to_game[i] = st->score_to_game[j];
                st->score_to_game[j] = tmp;

                st->game_to_score[st->score_to_game[i]] = i;
                st->game_to_score[st->score_to_game[j]] = j;
            }
        }
    }
}

