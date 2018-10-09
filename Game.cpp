/* Name: Silas Dunigan
   Title: Game.cpp
   Date: 18 October 2017
   Description: Runs and controls Clash UMBC */

#include "Game.h"
#include "Troop.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

Game::Game(){
  cout << "Please enter your name: ";
  getline(cin,m_name,'\n'); // saves name as private variable m_name
  cout << "Hello " << m_name << endl; // greets player
  do{
    cout << "How many troops would you like on each team?(Choose between 2 and 5 troops.): ";
    cin >> m_max; // takes in how many troops the player wants and saves it as private variable m_max
  }while(m_max < 2 || m_max > 5); // makes sure there are between 2 and 5 troops
  LoadTroops(); // loads troops from txt file and saves them to a private vector m_troop
  RandomizeTeam(); // applies m_max random troops from m_troop to m_player and m_computer
  DisplayTeams(); // outputs the the players and computers team
   StartGame(); // tests for win and starts game
}
void Game::LoadTroops(){
  string name; // creates local variables to send to Troop.cpp to create Troops
  int health;
  int damage;
  string target;
  bool isFlying;
  ifstream myfile("proj2_troops.txt");
  while(myfile >> name){ // reads in troop info while file still has info to give
    myfile >> health >> damage >> target >> isFlying;
    
    Troop x(name, health, damage, target, isFlying); // creates troop
    m_troop.push_back(x); // adds recently created troop to the end of private vector m_troop
  }
	
}
void Game::RandomizeTeam(){
  int randI = 0;
  int i =0;
  int j =0;
  srand(time(0)); // seeds random to the current time
  while(i != m_max){ // doesn't give each team more than the requested amount of troops
    randI = rand()%49; // picks a number between 0 and 49
    Troop y(m_troop[randI]); // creates a random troop based on the number in the previous line
    m_player.push_back(y); // adds that troop to private vector m_player
    i++;
  }
  while(j != m_max){ // does the same thing as above for the computer
    randI = rand()%49;
    Troop z(m_troop[randI]);
    m_computer.push_back(z);
    j++;
  }
}
void Game::StartGame(){
  
  if (m_player[0].GetHealth() <= 0){ // tests to see if the troop in the first slot of the vector's health is above 0
    m_player.erase(m_player.begin()+0); // if not, the troop is erased from the vector and destroyed from the team(death)
  }else if (m_computer[0].GetHealth() <= 0){ // tests the same thing for the computers team
    m_computer.erase(m_computer.begin()+0);
  }
  if (m_player.size() == 0 || m_computer.size() == 0){ // tests to see if either of the teams have 0 troops left
    if (m_computer.size() == 0){ // if computer has zero troops, then the player wins
      cout << "Congratulations! You have won!" << endl;
    }else if(m_player.size()== 0){ // if the player has zero troops, then the computer wins
      cout << "The computer has beaten you! Thanks for playing!" << endl;
    }
  }else if(m_player.size() != 0 || m_computer.size() != 0) { // if neither of the teams have 0 troops, the game continues

    MainMenu(); // asks the player what they want to do next
  }
}
void Game::DisplayTroops(){

}
void Game::ChangeTroop(){
  int troopNum = 0;
  cout << "\n*******************" << endl;
  cout << m_name << "'s Team" << endl;
  int playSize = m_player.size();
  for(int i = 0; i<playSize; i++)
    cout << i+1 << ". " <<m_player[i].GetName() << "  " << m_player[i].GetHealth() <<  endl; // displays the players team
  cout << "Which troop would you like to use?: ";
  cin >> troopNum; // takes in the troop that the player wants to select as their main attacker
  troopNum = troopNum - 1; // vectors start at 0
  Troop temp = m_player[0]; // creates temporary troop for the first spot
  m_player[0] = m_player[troopNum]; // replaces the first spot with the troop selected
  m_player.erase(m_player.begin()+troopNum); // erases the troop in the spot where the selected troop used to be so there arent duplicate troops
  m_player.push_back(temp); // adds the troop that was origonally  in the first spot to the end of the vector
  cout << "The troop you have chosen is: " << m_player[0].GetName() << endl; // outputs the troop chosen
  StartGame(); 

}
void Game::MainMenu(){
  int menuChoice = 0;
  do{
    cout << "\nWhat would you like to do? \n\n1.Display Team\n2.Change Current Troop\n3.Attack!\n4.Quit" << endl; 
    cin >> menuChoice; // displays menu and gets users input on what they want to do 
  }while(menuChoice < 1 or menuChoice > 4); // makes sure the user selects a choice between 1 and 4
  if (menuChoice == 1){
    DisplayTeam(); // if the user chooses 1, it displays the players team
  }else if (menuChoice == 2){
    ChangeTroop(); // if the user chooses 2, it changes the troop
  }else if(menuChoice == 3){
    Attack(); // if the player chooses 3, it attacks the other team and the other team attacks back
  }else if (menuChoice == 4){
    cout << "Thanks for playing!" << endl; // if the play chooses 4, the program ends
  }  
}
void Game::DisplayTeams(){
  cout << "\n*******************" << endl;
  cout << m_name << "'s Team" << endl;
  int playerSize = m_player.size();
  int compSize = m_computer.size();
  for(int i = 0; i<playerSize; i++)// prints while i is less than the size of the vector
    if (m_player[i].GetHealth()<0)
      cout << "" << endl; // if the health of the troop is less than 0, the troop won't print because it's dead
    else
      cout << m_player[i].GetName() << "  " << m_player[i].GetHealth() << endl; // if not, the troop prints its name and health
  cout << "******************* \nComputer's Team" << endl;
  for (int i = 0; i<compSize; i++){ // does same thing for computers team
    if (m_computer[i].GetHealth() < 0)
      cout << "" << endl;
    else
      cout << m_computer[i].GetName() << "  " << m_computer[i].GetHealth() << endl;
  }
}
void Game::DisplayTeam(){
  cout << "\n*******************" << endl; // does the same thing as DisplayTeams(), but just for the players team. 1st choice on MainMenu()
  cout << m_name << "'s Team" << endl;
  int playSize = m_player.size();
  for(int i = 0; i<playSize; i++)
    cout << m_player[i].GetName() << "  " << m_player[i].GetHealth() <<  endl;
  StartGame();

}
void Game::Attack(){
  if (m_player[0].GetTarget() == "Ground" && m_computer[0].GetIsFlying() == 1){ // test to see if the troop cannot attack their enemy
    cout << m_player[0].GetName() << " cannot attack the enemy team, because they are airborn!" << endl;
  }else{ // otherwise, the troop is able to attack the enemy
    cout << m_player[0].GetName() << " attacked " << m_computer[0].GetName() << " and did " << m_player[0].GetDamage() << " damage!" << endl; // outputs the attack information
    int newHealth = 0;
    newHealth = m_computer[0].GetHealth() - m_player[0].GetDamage(); // computes the new health of the computer
    m_computer[0].SetHealth(newHealth);// updates the health of the  computer after attack
    if (m_computer[0].GetHealth() < 0) // if the health after the attack is < 0, the enemy has died
      cout << "You have killed " << m_computer[0].GetName() << "!" << endl;
    else // otherwise, the player is notified of the enemy troops new health after attack
      cout << m_computer[0].GetName() << "'s health is now " << m_computer[0].GetHealth() << endl;
  }
  if (m_computer[0].GetTarget() == "Ground" && m_player[0].GetIsFlying() == 1) // same as player attack
    cout << m_computer[0].GetName() << " cannot attack your team, because they are airborn!" << endl;
  else{
    cout << "\n" <<  m_computer[0].GetName() << " attacked " << m_player[0].GetName() << " and did " << m_computer[0].GetDamage() << " damage!" << endl;
    int newHealth = 0;
    newHealth = 0;
    newHealth = m_player[0].GetHealth() - m_computer[0].GetDamage();
    m_player[0].SetHealth(newHealth);
    if (m_player[0].GetHealth() < 0)
      cout << "The enemy has killed " << m_player[0].GetName() << "!" << endl;
    else
      cout << m_player[0].GetName() << "'s health is now " << m_player[0].GetHealth() << endl;
  }
  DisplayTeams(); // displays teams after attack has occured
  StartGame(); // tests to see if win and continues game
}
