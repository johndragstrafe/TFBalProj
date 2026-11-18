#include <stdio.h>
#include "balfunc.h" 

int main(){

    playerweapon volt = {"Volt", 0, 0, 0, 0, 0, 0, 0};
        volt.rps = 11;
        volt.near_dmg = 25;
        volt.far_dmg = 17; 
        volt.vfar_dmg = 12;
        volt.near_range = 1000; 
        volt.far_range = 1500; 
        volt.vfar_range = 3000; 
        volt.hs_multiplier = 1.5;

    playerweapon *voltweapon = &volt;

    playerweapon car = {"Car", 0, 0, 0, 0, 0, 0, 0};
        car.rps = 14.1; 
        car.near_dmg = 25; 
        car.far_dmg = 13; 
        car.vfar_dmg = 9; 
        car.near_range = 1000; 
        car.far_range = 1500; 
        car.vfar_range = 3000; 
        car.hs_multiplier = 1.5; 

    playerweapon *carweapon = &car; 

    playerweapon r101 = {"R101", 0, 0, 0, 0, 0, 0, 0};
        r101.rps = 13.5; 
        r101.near_dmg = 20; 
        r101.far_dmg = 17;
        r101.vfar_dmg = 12; 
        r101.near_range = 1500; 
        r101.far_range = 2000; 
        r101.vfar_range = 3500; 
        r101.hs_multiplier = 1.5; 

    playerweapon *r101weapon = &r101; 

    int wpn1_hs_amount = 0;
    int wpn2_hs_amount = wpn1_hs_amount;  
    int player_hp = 120;
    int wpn1_missed_shots = 0; 
    int wpn2_missed_shots = 0;

    //compare_ttk_with_graphs(carweapon, voltweapon, player_hp, wpn1_hs_amount, wpn2_hs_amount, wpn1_missed_shots, wpn2_missed_shots);
    //print_and_graph_ttk(carweapon, player_hp, wpn1_hs_amount, wpn1_missed_shots);
    graph_two_ttks(carweapon, voltweapon, player_hp, wpn1_hs_amount, wpn2_hs_amount, wpn1_missed_shots, wpn2_missed_shots);
    //print_ttk(carweapon, player_hp, wpn1_hs_amount, wpn1_missed_shots);

}