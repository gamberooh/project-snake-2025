#include <iostream>
#include "levels.h"
using namespace std;
Levels::Levels() : head(NULL), nlevels(30), level_template({5,0.0,5,0,5,5,NULL,NULL}){

}
void Levels::init(){
  head = NULL;
}
plevel Levels::push_back(plevel f, double time_limit, double time_passed, double speed, int current_score, double multiplier, int bonus_end_level){
  plevel testa = f;
  //puntatori
  while (testa != NULL && testa -> next != NULL){
    testa = testa -> next;
  }
  plevel new_level = new single_level;
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
plevel Levels::create_levels(){
  int i = 0;
  double mult = 1;
  while (i < nlevels){
    head = push_back(head, level_template.time_limit*mult, level_template.time_passed, level_template.speed, level_template.current_score, level_template.multiplier, level_template.bonus_end_level*mult);
    mult += level_template.multiplier;
    i++;
  }
  return head;
}