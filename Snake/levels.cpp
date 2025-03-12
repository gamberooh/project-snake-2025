#include "levels.h"  // Inclusione del file di intestazione

Levels::Levels() : head(NULL), nlevels(30), level_template({1,5,0.0,5,0,0.1,100,NULL,NULL}){
}
void Levels::init(){
  head = NULL;
}
plevel Levels::push_back(plevel f, int id_level, double time_limit, double time_passed, double speed, int current_score, double multiplier, int bonus_end_level){
  plevel testa = f;
  //puntatori
  while (testa != NULL && testa -> next != NULL){
    testa = testa -> next;
  }
  plevel new_level = new single_level;
  new_level -> id_level = id_level;
  new_level -> time_limit = time_limit;
  new_level -> time_passed = time_passed;
  new_level -> speed = speed;
  new_level -> current_score = current_score;
  new_level -> multiplier = multiplier;
  new_level -> bonus_end_level = bonus_end_level;
  new_level -> next = NULL;
  //settare il nuovo livello
  if (testa == NULL){
    new_level -> back = NULL;
    return new_level;
  } //push front
  else{                //push back all'ultimo nodo
    if (testa -> back == NULL){
      f -> next = new_level;
      new_level -> back = f;
    }  //aggiugere dopo il primo elemento
    else{
      testa -> next = new_level;
      new_level -> back = testa;
    }
  }
  return f;
}
void Levels::create_levels(){
  int i = 1;
  double mult = 1;
  while (i < nlevels+1){
    head = push_back(head, i, level_template.time_limit, level_template.time_passed, level_template.speed*mult, level_template.current_score, level_template.multiplier, level_template.bonus_end_level*mult);
    mult += level_template.multiplier;
    i+=1;
  }
}
void Levels::print_id_levels(){
  plevel testa = head;
  int i = 0;
  while (testa != NULL){
    cout << "Id livello: " << testa -> id_level << ", tempo massimo: " << testa -> time_limit << ", tempo trascorso: " << testa -> time_passed << ", velocità serpente: " << testa -> speed << ", punti accumulati: " << testa -> current_score << ", moltiplicatore: " << testa -> multiplier << ", bonus livello completato: " << testa -> bonus_end_level << endl;
  	testa = testa -> next;
    i+=1;
  }
}

