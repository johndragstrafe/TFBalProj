#include <stdio.h>
#include "balfunc.h" 

int main(){

    playerweapon volt = {"Volt", 0, 0, 0, 0, 0, 0, 0};
        volt.rps = 11;
        volt.near_dmg = 25;
        volt.far_dmg = 15; 
        volt.vfar_dmg = 13;
        volt.near_range = 1000; 
        volt.far_range = 1480; 
        volt.vfar_range = 3030; 
        volt.hs_multiplier = 1.4;

    playerweapon *voltweapon = &volt;

    playerweapon car = {"Car", 0, 0, 0, 0, 0, 0, 0};
        car.rps = 14.1;
        car.near_dmg = 21;
        car.far_dmg = 14;
        car.vfar_dmg = 9;
        car.near_range = 1150;
        car.far_range = 1535;
        car.vfar_range = 2735;
        car.hs_multiplier = 1.4;

    playerweapon *carweapon = &car; 

    playerweapon r97 = {"R97", 0, 0, 0, 0, 0, 0, 0};
        r97.rps = 18;
        r97.near_dmg = 18; 
        r97.far_dmg = 12;
        r97.vfar_dmg = 9;
        r97.near_range = 1000;
        r97.far_range = 1500; 
        r97.vfar_range = 2993; 
        r97.hs_multiplier = 1.3; 

    playerweapon *r97weapon = &r97; 

    playerweapon alternator = {"Alternator", 0, 0, 0, 0, 0, 0, 0};
        alternator.rps = 6;
        alternator.near_dmg = 40; 
        alternator.far_dmg = 25;
        alternator.vfar_dmg = 18;
        alternator.near_range = 1000;
        alternator.far_range = 1600; 
        alternator.vfar_range = 2800; 
        alternator.hs_multiplier = 1.3; 

    playerweapon *alternatorweapon = &alternator; 

    playerweapon flatline = {"Flatline", 0, 0, 0, 0, 0, 0, 0};
        flatline.rps = 10; 
        flatline.near_dmg = 26; 
        flatline.far_dmg = 22;
        flatline.vfar_dmg = 15; 
        flatline.near_range = 1500; 
        flatline.far_range = 2000; 
        flatline.vfar_range = 3500; 
        flatline.hs_multiplier = 1.35; 

    playerweapon *flatlineweapon = &flatline; 
    
    playerweapon r101 = {"R101", 0, 0, 0, 0, 0, 0, 0};
        r101.rps = 13.5; 
        r101.near_dmg = 22; 
        r101.far_dmg = 17;
        r101.vfar_dmg = 12; 
        r101.near_range = 1500; 
        r101.far_range = 2000; 
        r101.vfar_range = 3500; 
        r101.hs_multiplier = 1.35; 

    playerweapon *r101weapon = &r101; 

    playerweapon pseudoesaw = {"Devotion", 0, 0, 0, 0, 0, 0, 0};
        pseudoesaw.rps = 15;
        pseudoesaw.near_dmg = 19;
        pseudoesaw.far_dmg = 13;
        pseudoesaw.vfar_dmg = 10;
        pseudoesaw.near_range = 1000;
        pseudoesaw.far_range = 2000;
        pseudoesaw.vfar_range = 3000;
        pseudoesaw.hs_multiplier = 1.5;
    
    playerweapon *pseudoesawweapon = &pseudoesaw;

    playerweapon mastiff = {"Mastiff", 0, 0, 0, 0, 0, 0, 0};
        mastiff.rps = 1.3; 
        mastiff.near_dmg = 24; 
        mastiff.far_dmg = 10; 
        mastiff.vfar_dmg = mastiff.far_dmg; 
        mastiff.near_range = 280; 
        mastiff.far_range = 780; 
        mastiff.vfar_range = mastiff.far_range; 
        mastiff.hs_multiplier = 1.0; 

    playerweapon *mastiffweapon = &mastiff; 

    int wpn1_hs_amount = 0;
    int wpn2_hs_amount = wpn1_hs_amount;  
    int player_hp = 120; 
    int wpn1_missed_shots = 0; 
    int wpn2_missed_shots = 0;
    int dist_from_player = 500;

    //compare_ttk_with_graphs(carweapon, pseudoesawweapon, player_hp, wpn1_hs_amount, wpn2_hs_amount, wpn1_missed_shots, wpn2_missed_shots);
    //print_damage_on_player(carweapon, player_hp, wpn1_hs_amount, dist_from_player);
    //print_and_graph_dmg(alternatorweapon, player_hp);
    print_and_graph_ttk(carweapon, player_hp, wpn1_hs_amount, wpn1_missed_shots);
    //print_ttk(alternatorweapon, player_hp, wpn1_hs_amount, wpn1_missed_shots);
    //print_ttk(r101weapon, player_hp, wpn1_hs_amount, wpn1_missed_shots);
    //graph_two_ttks(r101weapon, pseudoesawweapon, player_hp, wpn1_hs_amount, wpn2_hs_amount, wpn1_missed_shots, wpn2_missed_shots);
    //mastiff_ttk_graph(mastiffweapon, player_hp);
    //mastiff_ttk_and_dmg(mastiffweapon, player_hp);
    


    return 0;
}
