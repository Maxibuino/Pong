#include <Gamebuino-Meta.h>


// Caracteristiques de la balle
int balle_posX = 20;
int balle_posY = 20;
int balle_speedX = 1;
int balle_speedY = 1;
int balle_taille = 3;

// Dimensions des deux raquettes
int raquette_hauteur = 12;
int raquette_largeur = 3;

// Caracteristiques de la raquette1
int raquette1_posX = 10;
int raquette1_posY = 30;

// Caractéristiques de la raquette2
int raquette2_posX = gb.display.width() - 13;
int raquette2_posY = 30;
int raquette2_centreY = raquette2_posY + raquette_hauteur / 2;

// Score
int score_gauche = 0;
int score_droit = 0;

void setup() {
  gb.begin();
}

void loop() {
  while (!gb.update());
  gb.display.clear();

  //Contrôle de la raquette1
  if (gb.buttons.repeat(BUTTON_UP, 0)) {
    raquette1_posY = raquette1_posY - 1;
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 0)) {
    raquette1_posY = raquette1_posY + 1;
  }

  //IA de la raquette2
if (balle_posY < raquette2_centreY) {
  // Faire une chose
  raquette2_posY = raquette2_posY - 1;
}
else if (balle_posY > raquette2_centreY) {
  // Faire une autre chose
  raquette2_posY = raquette2_posY +1;
}

  balle_posX = balle_posX + balle_speedX;
  balle_posY = balle_posY + balle_speedY;

  if (balle_posY < 0) { // rebond en haut
    balle_speedY = 1;
  }

  if (balle_posY > gb.display.height() - balle_taille) { // rebond en bas
    balle_speedY = -1;
  }

  //collision balle et raquette1
  if ( (balle_posX == raquette1_posX + raquette_largeur)
       && (balle_posY + balle_taille >= raquette1_posY)
       && (balle_posY <= raquette1_posY + raquette_hauteur) ) {
    balle_speedX = 1;
  }

  //collision balle et raquette2
  if ( (balle_posX + balle_taille == raquette2_posX)
       && (balle_posY + balle_taille >= raquette2_posY)
       && (balle_posY <= raquette2_posY + raquette_hauteur) ) {
    balle_speedX = -1;
  }

  // balle passe bord gauche
  if (balle_posX < 0) {
    balle_posX = 20;
    balle_posY = 20;
    balle_speedX = 1;
    balle_speedY = 1;
    score_droit = score_droit + 1;
  }

  //balle passe bord droit
  if (balle_posX > gb.display.width() - balle_taille) {
    balle_posX = 20;
    balle_posY = 20;
    balle_speedX = 1;
    balle_speedY = 1;
    score_gauche = score_gauche + 1;
  }

  // Contrôle du score
  if (score_gauche >= 7) {
    score_gauche = 0;
    score_droit = 0;
  }
  if (score_droit >= 7) {
    score_gauche = 0;
    score_droit = 0;
  }

  //Afficher la balle
  gb.display.fillRect(balle_posX, balle_posY, balle_taille, balle_taille);
  //Afficher la raquette1
  gb.display.fillRect(raquette1_posX, raquette1_posY, raquette_largeur, raquette_hauteur);
  //Afficher la raquette2
  gb.display.fillRect(raquette2_posX, raquette2_posY, raquette_largeur, raquette_hauteur);
  // Afficher les scores
  // Score Gauche
  gb.display.setColor(RED);
  gb.display.setFontSize(1);
  gb.display.setCursor(35, 4);
  gb.display.print(score_gauche);
  gb.display.setCursor(42, 4);
  gb.display.print(score_droit);

}
