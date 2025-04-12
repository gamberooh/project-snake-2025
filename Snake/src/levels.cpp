// #include "../include/levels.h"  // Inclusione del file di intestazione
//
// Levels::Levels() : curr(NULL), nlevels(30), level_template({1,5,0.0,5,0,0.1,100}){}
//
// void Levels::pushBack(const int id){
//   plevel tmp = curr;
//   //puntatori
//   while (tmp != NULL && tmp -> next != NULL){
//     tmp = tmp -> next;
//   }
//
//   plevel new_level = new single_level;
//   new_level -> data = newLevelStat(id);
//   new_level -> next = NULL;
//
//   //settare il nuovo livello
//   if (curr == NULL){
//     new_level -> back = NULL;
//     curr = new_level;
//   } //push front
//
//   else{                //push back all'ultimo nodo
//     if (testa -> back == NULL){
//       f -> next = new_level;
//       new_level -> back = f;
//     }  //aggiugere dopo il primo elemento
//     else{
//       testa -> next = new_level;
//       new_level -> back = testa;
//     }
//   }
// }
//
// stat Levels::newLevelStat(const int id) const {
//   stat newLevelData;
//   double multiplier = level_template.multiplier;
//
//   newLevelData.id = id;
//   newLevelData.timeLimit = level_template.timeLimit;
//   newLevelData.time_passed = 0;
//   newLevelData.speed = level_template.speed  * multiplier;
//   newLevelData.current_score = 0;
//   newLevelData.multiplier = multiplier;
//   newLevelData.bonus_end_level = int(level_template.bonus_end_level * multiplier);
//   return newLevelData;
// }
//
// void Levels::createLevels(){
//   int i = 1;
//   double mult = 1;
//   while (i < nlevels+1){
//     pushBack(i);
//     mult += level_template.multiplier;
//     i+=1;
//   }
// }
//
// void Levels::print_idLevels(){
//   plevel testa = curr;
//   int i = 0;
//   while (testa != NULL){
//     cout << "Id livello: " << testa -> id_level << ", tempo massimo: " << testa -> timeLimit << ", tempo trascorso: " << testa -> time_passed << ", velocità serpente: " << testa -> speed << ", punti accumulati: " << testa -> current_score << ", moltiplicatore: " << testa -> multiplier << ", bonus livello completato: " << testa -> bonus_end_level << endl;
//   	testa = testa -> next;
//     i+=1;
//   }
// }
//
