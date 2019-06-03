#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;

void start_game();
/*************************************/
void handle_input(pair<int,int> *&player_position, int **&mapa, int size_of_map);
/*************************************/
void draw(int **mapa, pair<int,int> player_position, pair<int,int> meta_position,int size_of_map);
/*************************************/
void generate_map(int **&mapa,int *&size_of_map, pair<int,int>*&player_pos , pair<int,int>*&meta_pos);
/*************************************/
void check_winning(int &counter, bool &won,int **&mapa,int *&size_of_map, pair<int,int>*&player_pos , pair<int,int>*&meta_pos );
/*************************************/
int main()
{
    srand(time(NULL));
    cout << "Witaj w grze. " << endl;
    cout << "Wpisz 1 aby poznac zasady \n2. Aby rozpoczac gre" << endl;
    int choice;
    choice = getch();
    while(! (choice == static_cast<int>('1') || choice== static_cast<int>('1') )){
        choice = getch();
    }
    if(choice == '1'){
            system("cls");
        cout << "W S A D - przyciski kontrolne" << endl;
        cout << "Esc - zakoncz gre - wyjdz" << endl;
        cout << "P- symbol gracza" << endl;
        cout << "M - symbol mety" << endl;
        cout << "Cel gry - dojscie do mety  przechodzac przez wszytkie pola jak najbardziej mozliwie tylko raz" << endl;
        cout << "Nacisnij dowolny przycisk aby rozpoczac" << endl;
        char c = getche();
        start_game();
    }
    else if(choice == '2'){
        start_game();
    }
    return 0;
}
//start game function -> game loop;
void start_game(){
    system("cls");
    system("color 0A");
    int **mapa; // wazna zmienna
    int *size_of_map;
    pair<int,int> *player_pos;
    pair<int,int> *meta_pos;
    generate_map(mapa,size_of_map,player_pos,meta_pos);



    int winning_counter = 0 ;
    bool won = false;
    while(!won){
        system("cls");
        check_winning(winning_counter,won,mapa,size_of_map,player_pos,meta_pos);
        draw(mapa,*player_pos,*meta_pos,*size_of_map);
        handle_input(player_pos,mapa,*size_of_map);
    }
    cout << "Zagrales  " << winning_counter << " razy" << endl;
}

/**********************************************/
void handle_input(pair<int,int> *&player_position, int **&mapa,int size_of_map){
    char c = getch();
    pair<int,int> new_player_pos = *player_position;
    switch(c){
        case 'a':{
            int x= (player_position->first) -1;
            if(x >= 0){
                new_player_pos = pair<int,int>(x,player_position->second);
                mapa[player_position->second][player_position->first]+=1;
            }
            break;
        }
        case 'd':{
            int x = (player_position->first) +1;
            if(x < size_of_map){
                new_player_pos = pair<int,int>(x,player_position->second);
                mapa[player_position->second][player_position->first]+=1;
            }
            break;
        }
        case 'w':{
            int y = (player_position->second) -1;
            if(y >= 0){
               new_player_pos = pair<int,int>(player_position->first,y);
               mapa[player_position->second][player_position->first]+=1;
            }
            break;
        }
        case 's':{
            int y = (player_position->second) + 1;
            if(y < size_of_map){
               new_player_pos = pair<int,int>(player_position->first,y);
               mapa[player_position->second][player_position->first]+=1;
            }
            break;
        }
        case 27:{
            cout << "Exit" << endl;
           exit(1);
            break;
        }
        default: break;

    }
    *player_position  = new_player_pos;

}
/**********************************************/
void draw(int **mapa, pair<int,int> player_position, pair<int,int> meta_position,int size_of_map){
    for(int i=0; i<size_of_map; i++){
        for(int j=0; j<size_of_map; j++){
           if( j == player_position.first && i == player_position.second ){
                cout << " " << "P";
           }
           else if(j == meta_position.first && i == meta_position.second){
                 cout << " " << "M";
           }
           else{
            cout << " " << mapa[i][j];
           }
        }
        cout << endl;
    }
}
/********************************/
void generate_map(int **&mapa,int *&size_of_map, pair<int,int> *&player_pos , pair<int,int> *&meta_pos){
    delete mapa;
    delete size_of_map;
    delete player_pos;
    delete meta_pos;
     //cout << "Gra sie rozpoczela" << endl;
     size_of_map = new int;
     *size_of_map = rand()%8+2;
     //cout << *size_of_map << " size of map" << endl;
    mapa = new int*[*size_of_map];
    for(int i=0; i<*size_of_map ; i++){
        mapa[i] = new int[*size_of_map];
    }
    for( int i=0; i<*size_of_map; i++){
     for( int j=0; j<*size_of_map; j++){
        mapa[i][j] = 0;
        }
    }
     int x = rand()%*size_of_map,y = rand()%*size_of_map; // tymczasowa zmienna
     player_pos = new pair<int,int>(x,y);
     do{
        x = rand()%*size_of_map;
        y = rand()%*size_of_map;
    }while( x==player_pos->first && y==player_pos->second);
    meta_pos = new pair<int,int>(x,y);
    //cout << "meta_pos:  " << meta_pos->first << " " << meta_pos->second << endl;
}
void check_winning(int &counter, bool &won,int **&mapa,int *&size_of_map, pair<int,int>*&player_pos , pair<int,int>*&meta_pos ){
    if(player_pos->first == meta_pos->first && player_pos->second==meta_pos->second){ //won if meta and player position are the same
        int mistakes = 0; //
        for(int i=0; i<*size_of_map; i++){
            for(int j=0; j<*size_of_map; j++){
                if( i == player_pos->second && j==player_pos->first){
                    //doing nothing
                }
                else if( mapa[i][j] != 1){
                    mistakes++;
                }
            }
        }
        if( mistakes == 0){
            cout << "Brawo! Jestes mistrzem tej gry! ***" << endl;
        }
        else if( mistakes > 0 && mistakes <= 2){
            cout << "Brawo! Ukonczyles poziom bardzo dobrze, ale nie najlepiej! **" << endl;
        }
        else if( mistakes > 2){
            cout << "Ukonczyles  poziom . *";
        }
        counter++;
        cout << "Czy chcesz zagrac jeszcze raz?" << endl;
        cout << "wpisz y lub n:" << endl;
        char c;
        do{
            c = getch();
        }while(!(c == 'y' || c == 'n'));
        if(c == 'y'){
            generate_map(mapa,size_of_map,player_pos,meta_pos);
            system("cls");
        }else{
            won = true;
            delete mapa;
            delete size_of_map;
            delete player_pos;
            delete meta_pos;
        }
    }
}


//end????
