#include "balfunc.h"
#include <stdio.h>

//calculates the slope of a line from 2 points
float slope_calc(int xc_range, int xf_range, float yc_dmg, float yf_dmg){
    float m = (yf_dmg - yc_dmg) / (xf_range - xc_range);
    return m; 
}

//calculates the y intercept of a line from a point (x and y) and the slope of the line (m)
float y_int(float m, int x, float y){
    float b = y - m*x; 
    return b;
}

//calls weapon struct data to calculate a weapons damage at any given range
int range_dmg_scale(playerweapon *wpn, float dist){
    
    if(dist <= wpn->near_range){

        return wpn->near_dmg; 

    }
    if(dist >= wpn->vfar_range){

        return wpn->vfar_dmg; 

    }
    if(dist >= wpn->near_range && dist < wpn->far_range){
        float m = slope_calc(wpn->near_range, wpn->far_range, wpn->near_dmg, wpn->far_dmg);
        float scaled_dmg = m*dist + y_int(m, wpn->near_range, wpn->near_dmg); 
        
        return (int)scaled_dmg; 

    }
    if(dist >= wpn->far_range && dist < wpn->vfar_range){
        float m = slope_calc(wpn->far_range, wpn->vfar_range, wpn->far_dmg, wpn->vfar_dmg);
        float scaled_dmg = m*dist + y_int(m, wpn->vfar_range, wpn->vfar_dmg);

        return (int)scaled_dmg; 

    }
    return 0;
}

//used in ttk function to simulate the retarded way respawn made headshots work
int player_dmg_rem(float* hs_dmg_rem, int dmg, float hs_mult){
    float dmg_rem_counter = dmg*hs_mult;
    int scaled_dmg_rounded = (int)dmg_rem_counter;
    *hs_dmg_rem += dmg_rem_counter - scaled_dmg_rounded;
    if(*hs_dmg_rem >= 1){
        scaled_dmg_rounded++;
        (*hs_dmg_rem)--; 
    }
    return scaled_dmg_rounded;
}

void print_damage_on_player(playerweapon *wpn, int player_hp, int hs_amount, int dist_from_player){
    int dmg = range_dmg_scale(wpn, (float)dist_from_player);
    float hs_dmg_rem = 0;
    while(player_hp > 0){
        if(hs_amount > 0){
            player_hp -= player_dmg_rem(&hs_dmg_rem, dmg, wpn->hs_multiplier);
            printf("%d\n", player_hp);
            hs_amount--;
        }else{
            player_hp -= dmg; 
            if(player_hp < 0){
                player_hp = 0;
            }
            printf("%d\n", player_hp);
        }
    }
}

/*calculates ttk from the parameters given. dmg given separately from the weapon dmg as to more easily call this function after using range_dmg_scale()
 to calculate a new damage value that would be the dmg variable here*/
float ttk(playerweapon *wpn, int dmg, int player_hp, int hs_amount, int missed_shots){
    float hs_dmg_rem = 0; 
    int dmg_done = 0; 
    int amount_of_shots = 0;  
    int hs_hit = 0; 
    while(dmg_done < player_hp){
        if(missed_shots > 0){
            missed_shots--; 
        }else if(hs_hit < hs_amount){
            dmg_done += player_dmg_rem(&hs_dmg_rem, dmg, wpn->hs_multiplier); 
            hs_hit++;
       }else{
            dmg_done += dmg; 
       }
       amount_of_shots++; 
    }

    return (amount_of_shots-1)/wpn->rps; 
    //remainder is -(player_hp - dmg_done)
}

//prints the range and ttk at that range when a weapon experiences a ttk shift from damage falloff
void print_ttk(playerweapon *wpn, int player_hp, int hs_amount, int missed_shots){
    int dist = 0;
    float kill_time = ttk(wpn, wpn->near_dmg, player_hp, hs_amount, missed_shots);
    printf("%s TTK at %d hammer units with %d missed shots and %d headshots is %.2f\n", wpn->name, dist, missed_shots, hs_amount, kill_time);
    while(dist <= 4000){
        int dmg_per_shot = range_dmg_scale(wpn, dist); 
        float print_checker = kill_time;
        kill_time = ttk(wpn, dmg_per_shot, player_hp, hs_amount, missed_shots);
        if(kill_time != print_checker){
            printf("%s TTK at %d hammer units with %d missed shots and %d headshots is %.2f\n", wpn->name, dist, missed_shots, hs_amount, kill_time);
        }
        dist++; 
    }
    
}

//prints ttk separately for easy copy and pasting 
void print_ttk_data_usefully(playerweapon *wpn, int player_hp, int hs_amount, int missed_shots){
    int dist = 0;
    float kill_time = ttk(wpn, wpn->near_dmg, player_hp, hs_amount, missed_shots);
    printf("%s distances \n%d\n", wpn->name, dist);
    while(dist <= 4000){
        int dmg_per_shot = range_dmg_scale(wpn, dist); 
        float print_checker = kill_time;
        kill_time = ttk(wpn, dmg_per_shot, player_hp, hs_amount, missed_shots);
        if(kill_time != print_checker){
            printf("%d\n", dist);
        }
        dist++; 
    }
    printf("\n");

    dist = 0; 
    kill_time = ttk(wpn, wpn->near_dmg, player_hp, hs_amount, missed_shots);
    printf("%s TTKs \n%.2f\n", wpn->name, kill_time);
    while(dist <= 4000){
        int dmg_per_shot = range_dmg_scale(wpn, dist); 
        float print_checker = kill_time;
        kill_time = ttk(wpn, dmg_per_shot, player_hp, hs_amount, missed_shots);
        if(kill_time != print_checker){
            printf("%.2f\n", kill_time);
        }
        dist++; 
    }

    printf("\n");

}

//prints dmg values to test_file.txt and graphs them using gnuplot
void print_and_graph_dmg(playerweapon *wpn, int player_hp){
    char const *file_name = "test_file.txt";

    FILE* GNUpipe = NULL; 

    FILE *file = fopen(file_name, "w");

    if(file == NULL){
        printf("%s could not be opened\n", file_name);
    }

    int dist; 
    int dmg; 
    for(dist = 0; dist <= 4000; dist++){
        int dmg = range_dmg_scale(wpn, dist); 
        fprintf(file, "%d %d\n", dist, dmg);
    }
    fclose(file);

    GNUpipe = popen("gnuplot -p", "w");

    if(GNUpipe != NULL){
        fprintf(GNUpipe, "plot 'test_file.txt' w l linewidth 3\n");

    }else{
        perror("popen failed");
    
    }
    pclose(GNUpipe);

}

//graphs the difference in ttk at particular ranges of 2 weapons
void compare_ttk_with_graphs(playerweapon *wpn1, playerweapon *wpn2, int player_hp, int wpn1_hs_amount, int wpn2_hs_amount, int wpn1_missed_shots, int wpn2_missed_shots){
     char const *file_name = "test_file.txt";

    FILE* GNUpipe = NULL; 

    FILE *file = fopen(file_name, "w");

    if(file == NULL){
        printf("%s could not be opened\n", file_name);
    }

    int dist; 
    float dmg1; 
    float dmg2; 
    for(dist = 0; dist <= 4000; dist++){
        int dmg1 = range_dmg_scale(wpn1, dist);
        float ttk1 = ttk(wpn1, dmg1, player_hp, wpn1_hs_amount, wpn1_missed_shots);
        int dmg2 = range_dmg_scale(wpn2, dist);
        float ttk2 = ttk(wpn2, dmg2, player_hp, wpn2_hs_amount, wpn2_missed_shots);
        float ttk_diff = ttk1 - ttk2; 
        fprintf(file, "%d %f\n", dist, ttk_diff); 
    }

    GNUpipe = popen("gnuplot -p", "w");

    if(GNUpipe != NULL){
        fprintf(GNUpipe, "set title '%s TTK subtracted from %s TTK'\nplot 'test_file.txt' w l linewidth 3\n", wpn2->name, wpn1->name);

    }else{
        perror("popen failed");
    
    }
    pclose(GNUpipe);

}

//prints the ttk of a specified weapon to a text file and graphs the file
void print_and_graph_ttk(playerweapon *wpn, int player_hp, int hs_amount, int missed_shots){
    
    char const *file_name = "wpn_file.txt";

    FILE* GNUpipe = NULL; 

    FILE *file = fopen(file_name, "w");

    if(file == NULL){
        printf("%s could not be opened\n", file_name);
        return;
    }

    int dist;  
    for(dist = 0; dist <= 4000; dist++){
        int dmg = range_dmg_scale(wpn, dist); 
        float p_ttk = ttk(wpn, dmg, player_hp, hs_amount, missed_shots);
        fprintf(file, "%d %f\n", dist, p_ttk);
    }
    fclose(file);

    GNUpipe = popen("gnuplot -p", "w");

    if(GNUpipe != NULL){
        fprintf(GNUpipe, "set title '%s TTK (%d headshots)' font 'aptos, 24'\nset xlabel 'range (hammer units)'\nset ylabel 'TTK (seconds)'\nset bmargin 4\nset lmargin 12\nplot 'wpn_file.txt' w l linewidth 3\n", wpn->name, hs_amount);

    }else{
        perror("popen failed");
        return;
    }
    pclose(GNUpipe);
}

//graphs two weapon ttks on the same graph using separate text files
void graph_two_ttks(playerweapon *wpn1, playerweapon *wpn2, int player_hp, int wpn1_hs_amount, int wpn2_hs_amount, int wpn1_missed_shots, int wpn2_missed_shots){
    char const *data_file1 = "wpn_file1.txt";

    char const *data_file2 = "wpn_file2.txt";

    FILE* GNUpipe = NULL; 

    FILE *file = fopen(data_file1, "w");

    if(file == NULL){
        printf("%s could not be opened\n", data_file1);
    }

    int dist; 
    for(dist = 0; dist <= 4000; dist++){
        int dmg = range_dmg_scale(wpn1, dist); 
        float p_ttk = ttk(wpn1, dmg, player_hp, wpn1_hs_amount, wpn1_missed_shots);
        fprintf(file, "%d %f\n", dist, p_ttk);
    }
    fclose(file);

    file = fopen(data_file2, "w");

    if(file == NULL){
        printf("%s could not be opened\n", data_file2);
        return;
    }

    for(dist = 0; dist <= 4000; dist++){
        int dmg = range_dmg_scale(wpn2, dist); 
        float p_ttk = ttk(wpn2, dmg, player_hp, wpn2_hs_amount, wpn2_missed_shots);
        fprintf(file, "%d %f\n", dist, p_ttk);
    }
    fclose(file);

    GNUpipe = popen("gnuplot -p", "w");

    if(GNUpipe != NULL){
        fprintf(GNUpipe, "set title '%s TTK and %s TTK (%d headshots)'\nplot 'wpn_file1.txt' title '%s ttk' w l linewidth 3, 'wpn_file2.txt' title '%s ttk' w l linewidth 3\n", wpn1->name, wpn2->name, wpn1_hs_amount, wpn1->name, wpn2->name);

    }else{
        perror("popen failed");
        return;
    }
    pclose(GNUpipe);

}

void mastiff_ttk_graph(playerweapon *shotgun, int player_hp){
    char const *file_name = "test_file.txt";

    FILE* GNUpipe = NULL; 

    FILE *file = fopen(file_name, "w");

    if(file == NULL){
        printf("%s could not be opened\n", file_name);
    }

    int dist; 
    int dmg; 
    int bolts_to_kill; 
    for(dist = 0; dist <= 4000; dist++){
        dmg = range_dmg_scale(shotgun, dist); 
        for(bolts_to_kill = 0; (bolts_to_kill*dmg) < player_hp; bolts_to_kill++){}
        fprintf(file, "%d %d\n", dist, bolts_to_kill);
    }
    fclose(file);

    GNUpipe = popen("gnuplot -p", "w");

    if(GNUpipe != NULL){
        fprintf(GNUpipe, "set title '%s bolts to kill by range'\nplot 'test_file.txt' w l linewidth 3\n", shotgun->name);

    }else{
        perror("popen failed");
        return;
    }
    pclose(GNUpipe);

}

void mastiff_ttk_and_dmg(playerweapon *shotgun, int player_hp){
    char const *data_file1 = "wpn_file1.txt";

    char const *data_file2 = "wpn_file2.txt";

    FILE* GNUpipe = NULL; 

    FILE *file = fopen(data_file1, "w");

    if(file == NULL){
        printf("%s could not be opened\n", data_file1);
    }
    int dmg; 
    int dist; 
    for(dist = 0; dist <= 1000; dist++){
        dmg = range_dmg_scale(shotgun, dist); 
        fprintf(file, "%d %d\n", dist, dmg);
    }
    fclose(file);

    file = fopen(data_file2, "w");

    if(file == NULL){
        printf("%s could not be opened\n", data_file2);
        return;
    }

    int bolts_to_kill; 
    for(dist = 0; dist <= 1000; dist++){
        dmg = range_dmg_scale(shotgun, dist); 
        for(bolts_to_kill = 0; (bolts_to_kill*dmg) < player_hp; bolts_to_kill++){}
        fprintf(file, "%d %d\n", dist, bolts_to_kill);
    }
    fclose(file);

    GNUpipe = popen("gnuplot -p", "w");

    if(GNUpipe != NULL){
        fprintf(GNUpipe, "set title '%s bolts to kill and damage per bolt'\nplot 'wpn_file1.txt' title 'dmg per bolt' w l linewidth 3, 'wpn_file2.txt' title 'bolts to kill' w l linewidth 3\n", shotgun->name);

    }else{
        perror("popen failed");
        return;
    }
    pclose(GNUpipe);


}
