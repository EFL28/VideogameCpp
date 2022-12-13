#include <iostream>
#include "stdlib.h"
#include "time.h"
#include <windows.h>

using namespace std;

//Atributos del enemigo 1
int enemy1HP = 200;
string enemy1Name = "Creeper";
bool enemy1Alive = true;
int enemy1Damage = rand();

//Atributos del enemigo 2
int enemy2HP = 200;
string enemy2Name = "Zombie";
bool enemy2Alive = true;
int enemy2Damage = rand();

//Atributos del heroe
string heroName;
int heroDamage;
int heroHP = 700;
bool heroAlive = true;

int attack1 = rand();
int attack2 = rand();
int attack3 = rand();
int limitedAttack = 0;

void gameStart() {

	cout << "Como se llama el heroe?\n";
	cin >> heroName;
	cout << "El nombre del heroe es " << heroName << ".\n";
	cout << "-----------------------------------------" << endl;

	PlaySound(TEXT("GameStart.wav"), NULL, SND_FILENAME);

}

void menuEnemy() {
	cout << "A que enemigo quieres atacar: \n";
	if (enemy1Alive && enemy2Alive) {
		cout << "[1]. " << enemy1Name << endl;
		cout << "[2]. " << enemy2Name << endl;

	}
	else if (enemy1Alive && !enemy2Alive) {
		cout << "[1]. " << enemy1Name << endl;
	}
	else if (!enemy1Alive && enemy2Alive) {
		cout << "[2]. " << enemy2Name << endl;
	}
}

int enemySelection(int &option) {
	while (option >= 3 || option < 1) {
		cout << "Enemy not found, choose again.\n";
		cin >> option;
	}
	switch (option) {
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	default:
		break;
	}
}

void menuAttack() {
	cout << "What attack do you want to use?" << endl;
	cout << "[1]. Physical attack." << endl;
	cout << "[2]. Sword attack." << endl;
	cout << "[3]. Magic attack." << endl;
}

void calcAttack(int option) {

	switch (option) { //EN BASE AL ATAQUE ELEGIDO SE CALCULA CUANTO HACE DE DA�O
	case 1:
		attack1 = rand() % 30 + 0;
		heroDamage = attack1;
		break;
	case 2:
		attack2 = rand() % (50 - 30 + 1) + 30;
		heroDamage = attack2;
		break;
	case 3:
		attack3 = rand() % (100 - 50 + 1) + 50;
		heroDamage = attack3;
		limitedAttack++; // CONTADOR DE USO DEL ATAQUE
		break;
	default:
		break;
	}
}

bool heroCheck() {
	if (heroHP <= 0) {
		cout << "You are dead." << endl;
		cout << "-----------------------------------------" << endl;
		return false;
	}
	else {
		cout << "You have " << heroHP << " health points.\n";
		cout << "-----------------------------------------" << endl;
		return true;
	}
}

bool enemy1Check() {
	if (enemy1HP <= 0) { //CHECK SI EL ENEMIGO SOBREVIVE O NO
		cout << "You hit " << heroDamage << " damage points to the enemy " << enemy1Name << ".\n";
		cout << enemy1Name << " is now dead.\n";
		cout << "-----------------------------------------" << endl;
		return false;
	}
	else {
		cout << "You hit " << heroDamage << " damage points to the enemy " << enemy1Name << ".\n";
		cout << enemy1Name << " has " << enemy1HP << " health points.\n";
		cout << "-----------------------------------------" << endl;
		return true;
	}
}

bool enemy2Check() {
	if (enemy2HP <= 0) {
		cout << "You hit " << heroDamage << " damage points to the enemy " << enemy2Name << ".\n";
		cout << enemy2Name << " is now dead.\n";
		cout << "-----------------------------------------" << endl;
		return false;
	}
	else {
		cout << "You hit " << heroDamage << " damage points to the enemy " << enemy2Name << ".\n";
		cout << enemy2Name << " has " << enemy2HP << " health points.\n";
		cout << "-----------------------------------------" << endl;
		return true;
	}
}

int enemyAttack(int damage) {

	return heroHP - damage;

}

int heroAttack1(int attack) {
	switch (attack) { //DEPENDE DEL ATAQUE SUENA DIFERENTES SONIDOS
	case 1:
		PlaySound(TEXT("fist.wav"), NULL, SND_FILENAME);
		return enemy1HP - heroDamage;
		break;
	case 2:
		PlaySound(TEXT("sword.wav"), NULL, SND_FILENAME);
		return enemy1HP - heroDamage;
		break;
	case 3:
		PlaySound(TEXT("Magic.wav"), NULL, SND_FILENAME);
		return enemy1HP - heroDamage;
		break;
	default:
		break;
	}
}

int heroAttack2(int attack) {
	switch (attack) { //DEPENDE DEL ATAQUE SUENA DIFERENTES SONIDOS
	case 1:
		PlaySound(TEXT("fist.wav"), NULL, SND_FILENAME);
		return enemy2HP - heroDamage;
		break;
	case 2:
		PlaySound(TEXT("sword.wav"), NULL, SND_FILENAME);
		return enemy2HP - heroDamage;
		break;
	case 3:
		PlaySound(TEXT("Magic.wav"), NULL, SND_FILENAME);
		return enemy2HP - heroDamage;
		break;
	default:
		break;
	}
}

int main() {
	srand(time(NULL));
	int enemyOption;
	int attackOption;

	gameStart();

	while (heroAlive && (enemy1Alive || enemy2Alive)) {
		menuEnemy();
		cin >> enemyOption; //ELECCION DE ENEMIGO Y APARCION DE MENU PARA ESCOGER ATAQUE
		enemySelection(enemyOption);
		menuAttack();
		cin >> attackOption; //ELECCION DE ATAQUE

		while (attackOption > 3 || attackOption < 1) {
			cout << "Attack not identified, try again\n";
			cin >> attackOption;
		}
		calcAttack(attackOption);

		if (enemySelection(enemyOption) == 1) {
			if (enemy1Alive) { //CHECK ENEMIGO1 VIVO
				if (attackOption == 3 && limitedAttack >= 4) { //SI ESCOGEMOS ATAQUE 3 PERO YA HA SIDO ESCOGIDO 4 VECES ANTES NO SE UTILIZA
					while (attackOption >= 3 || attackOption < 1) {
						cout << "You can't use this attack." << endl;
						cout << "[1]. Physical attack." << endl;
						cout << "[2]. Sword attack." << endl;
						cin >> attackOption;
					}
					calcAttack(attackOption);
				}
				enemy1HP = heroAttack1(attackOption);
				enemy1Alive = enemy1Check();

			}
			else { //SI EL ENEMIGO1 ESTA MUERTO Y LE ATACAMOS FALLAMOS EL ATAQUE
				cout << "You miss the attack to " << enemy1Name << " because it's already dead." << endl;
				cout << "-----------------------------------------" << endl;
			}
		}
		else if (enemySelection(enemyOption) == 2) { //MISMO PROCESO PERO CON EL ENEMIGO2
			if (enemy2Alive) {
				if (attackOption == 3 && limitedAttack >= 4) { //SI ESCOGEMOS ATAQUE 3 PERO YA HA SIDO ESCOGIDO 4 VECES ANTES NO SE UTILIZA
					while (attackOption >= 3) {
						cout << "You can't use this attack." << endl;
						cout << "[1]. Physical attack." << endl;
						cout << "[2]. Sword attack." << endl;
						cin >> attackOption;
					}
					calcAttack(attackOption);
				}
				enemy2HP = heroAttack2(attackOption);
				enemy2Alive = enemy1Check();
			}
			else { //SI EL ENEMIGO2 ESTA MUERTO Y LE ATACAMOS FALLAMOS EL ATAQUE
				cout << "You miss the attack to " << enemy2Name << " because it's already dead." << endl;
				cout << "-----------------------------------------" << endl;
			}
		}

		if (enemy1Alive && enemy2Alive) { //SI AMBOS ESTAN VIVOS ATACAN
			enemy1Damage = rand() % 100;
			heroHP = enemyAttack(enemy1Damage);

			enemy2Damage = rand() % 100;
			heroHP = enemyAttack(enemy2Damage);

			cout << "The " << enemy1Name << " hit you " << enemy1Damage << " damage points.\n";
			cout << "The " << enemy2Name << " hit you " << enemy2Damage << " damage points.\n";
			cout << "-----------------------------------------" << endl;

			heroAlive = heroCheck();
		}
		else if (enemy1Alive && !enemy2Alive) { //SI SOLO ESTA EL ENEMIGO1 VIVO ATACA
			enemy1Damage = rand() % 100;
			heroHP = enemyAttack(enemy1Damage);

			cout << "The " << enemy1Name << " hit you " << enemy1Damage << " damage points.\n";
			cout << "-----------------------------------------" << endl;

			heroAlive = heroCheck();
		}
		else if (!enemy1Alive && enemy2Alive) { //SI SOLO ESTA EL ENEMIGO2 VIVO ATACA
			enemy2Damage = rand() % 100;
			heroHP = enemyAttack(enemy2Damage);

			cout << "The " << enemy2Name << " hit you " << enemy2Damage << " damage points.\n";
			cout << "-----------------------------------------" << endl;

			heroAlive = heroCheck();
		}
		else if (!enemy1Alive && !enemy2Alive) { //NINGUN ENEMIGO ESTA VIVO
			cout << "Both enemies are dead" << endl;
		}
	}
}