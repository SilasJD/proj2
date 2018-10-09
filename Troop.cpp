/* Name: Silas Dunigan
   Title: Troop.cpp
   Date: 18 October 2017
   Description: Responsible for creating and managing troops */

#include "Troop.h"

Troop::Troop(string name, int health, int damage, string target, bool isFlying){
  m_name = name; // creates a troop and assigns the a name,
  m_health = health;// health
  m_damage = damage;// damage
  m_target = target;// where they can attack
  m_isFlying = isFlying; // and whether theyre flying or not
}
string Troop::GetName(){
  return m_name; // gives current troops name
}
void Troop::SetName(string name){
  m_name = name; // changes current troops name
}
int Troop::GetHealth(){
  return m_health; // gives current troops health
}
void Troop::SetHealth(int health){
  m_health = health; // changes current troops health
 
}
int Troop::GetDamage(){
  return m_damage; // gives current troops damage
}
string Troop::GetTarget(){
  return m_target; // gives current troops targets
}
bool Troop::GetIsFlying(){
  return m_isFlying; // tells whether the current troop can 1 (fly) or 0(not fly)
}
