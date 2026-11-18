#ifndef BALFUNC_H
#define BALFUNC_H 

typedef struct weapon {
    char name[20]; 
    float rps;
    float near_dmg;
    float far_dmg; 
    float vfar_dmg; 
    int near_range; 
    int far_range; 
    int vfar_range; 
    float hs_multiplier; 
}playerweapon; 

float slope_calc(int xc_range, int xf_range, float yc_dmg, float yf_dmg);

float y_int(float m, int x, float y);

int range_dmg_scale(playerweapon *wpn, float dist);

float ttk(playerweapon *wpn, int dmg, int player_hp, int hs_amount, int missed_shots);

void print_ttk(playerweapon *wpn, int player_hp, int hs_amount, int missed_shots);

void print_damage_on_player(playerweapon *wpn, int player_hp, int hs_amount, int dist_from_player);

void print_ttk_data_usefully(playerweapon *wpn, int player_hp, int hs_amount, int missed_shots);

void print_and_graph_dmg(playerweapon *wpn, int player_hp);

void compare_ttk_with_graphs(playerweapon *wpn1, playerweapon *wpn2, int player_hp, int wpn1_hs_amount, int wpn2_hs_amount, int wpn1_missed_shots, int wpn2_missed_shots);

void print_and_graph_ttk(playerweapon *wpn, int player_hp, int hs_amount, int missed_shots);

void graph_two_ttks(playerweapon *wpn1, playerweapon *wpn2, int player_hp, int wpn1_hs_amount, int wpn2_hs_amount, int wpn1_missed_shots, int wpn2_missed_shots);

void mastiff_ttk_graph(playerweapon *shotgun, int player_hp);

void mastiff_ttk_and_dmg(playerweapon *shotgun, int player_hp);

#endif