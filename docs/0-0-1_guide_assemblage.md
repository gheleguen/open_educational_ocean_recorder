# Guide d'assemblage

## 1/ Préparations, câblages et soudures
### 1.1 Connectique du capteur de température

 - Rassembler le capteur de température (et ses accessoires, le joint et l'écrou), un bloc connectique mâle JST 4 voies (4P Plug Housing), 4 ferrures mâles JST à sertir, ainsi qu'une bride à 2 perforations (ou une plaque alu deux perforations). 
![Photo montrant les éléments nécessaires](pictures/assembly/AG1-1.JPG)
 - A l'aide d'une pince coupante, sectionner le connecteur du capteur déjà en place. Veiller à couper au plus proche du connecteur afin de conserver un maximum de fil.
 - Dénuder chacun des fils au moyen d'une pince à dénuder. 
 - Sertir au bout de chaque fil une ferrure mâle.

![Photo montrant le capteur de température et les 4 fils sertis](pictures/assembly/AG1-2.JPG)

<section style="border: 2px solid red; padding: 20px; border-radius:20px; color: red;">
Attention ! Avant de positionner les ferrures dans le bloc connecteur JST, il faudra passer le capteur dans un trou de la bride. Ceci ne pouvant pas être fait après car le connecteur ne passe pas dans la perforation de la bride. </section>

 - Positionner le joint torique du coté extérieur, puis passer le pénétrateur dans la bride, pour enfin serrer avec l'écrou à la main sans le bloquer. 

![Photo montrant le capteur de température et les 4 fils sertis](pictures/assembly/AG1-3.JPG)

 - Enfoncer chacun des fil dans le connecteur JST. En suivant le schéma ci-dessous. 

![Schèma d'implantation des fils du capteur.](pictures/assembly/connectique_4b_capteur.png)
![Photo montrant le capteur de température et le connecteur JST en place](pictures/assembly/AG1-3B.JPG)



### 1.2 Préparation du micro-controleur 

 - Rassembler l'horloge (la carte RTC), et 2 lignes de broches dupont mâle (1* 16 broches et 1* 12 broches).

![Photo montrant l'horloge RTC au coté des deux connecteurs duponts mâle.](pictures/assembly/AG1-4.JPG)

 - Souder ces deux connecteurs duponts comme suit. 

<section style="border: 2px solid red; padding: 20px; border-radius:20px; color: red;">Attention à veiller à souder les broches sur les emplacements externes,</section>
 - et à positionner les pattes à l'opposé de l'emplacement de la pile. 

![On a soudé les deux broches duponts sur la carte d'horloge RTC](pictures/assembly/AG1-5.JPG)

 - Rassembler l'horloge RTC qui viens d'être soudé ainsi que deux nouvelles lignes de broches (1* 16 broches et 1* 11 broches).

![La carte RTC et des broches](pictures/assembly/AG1-6.JPG)

 - Souder ces broches à l'opposé des broches installé à l'étape précédente. 

![On a soudé les deux nouvelles broches duponts sur la carte d'horloge RTC](pictures/assembly/AG1-7.JPG)

 - Rassembler le microcontrôleur (Adafruit MO), ainsi que deux lignes de broches dupont femelles (1* 16 broches et 1* 12 broches).
 
![La carte Adafruit M0 et des broches femelles](pictures/assembly/AG1-8.JPG)

 - Souder ces broches en veillant au sens. Le coté femelle doit se retrouver au dessus de la carte.
 - C'est ici que viendra se brancher l'horloge RTC. 

![On a soudé les deux broches duponts femelles sur la carte Adafruit M0](pictures/assembly/AG1-9.JPG)

 - Enfin, assembler les deux cartes électronique l'une sur l'autre. 
 - L'horloge RTC viendra donc au dessu du micro-contrôleur. 

![Assemblage des deux cartes électroniques](pictures/assembly/AG1-10.JPG)

### 1.3 Assemblage du circuit secondaire
Le circuit secondaire, va permettre dans un premier temps de faciliter les connexions entre capteurs et voyants. Il permet aussi d'ajouter des composants nécéssaires comme les résistances de tirages sur le capteur qui communique suivant le protocole I2C.

 - Rassembler, une plaque de prototypage adafruit, trois connecteurs JST mâles à souder 5, 4 et 2 broches, 2 résistances de 10 kohm, du fil électrique à souder.

![Fournitures pour soudure sur carte secondaire](pictures/assembly/AG1-11.JPG) 

 - Prendre la plaque de prototypage dans le sens où les lettres des colonnes demeurent dans le bon sens pour la lecture.
 - Souder les 3 connecteurs JST femelles en suivant le plan ci-dessous. Le connecteur 5 broches de G1 à G5, le connecteur de 2 broches de G8 à G9 et le connecteur à 4 broches entre G12 et G15.

![Implantation des 3 connecteurs m^les sur la carte secondaire](pictures/assembly/AG1-12.JPG)

 - Au moyen de trois morceaux de fil (de préférence noir) relier chaque ligne (1, 8 et 12) à la colonne de masse symbolisé par un "-".

![Implantation des ponts de masses](pictures/assembly/AG1-13.JPG)

 - Souder un pont (fil de couleur rouge) entre la ligne 2 et la colonne "+".

![Implantation fil de +](pictures/assembly/AG1-14.JPG) 

 - Souder un pont (fil bleu) entre les ligens 3 et 9. Il s'agit du fil de donnée logique pour contrôler le voyant lumineux. 

![Implantation fil de data bleu](pictures/assembly/AG1-15.JPG)

 - Souder un pont (fil vert) entre les lignes 4 et 13. Il s'agit du SCL, l'horloge pour la lecture du capteur de température. 
 - Souder un pont (fil blanc) entre les lignes 6 et 14. Il s'agit du SDA, le fil de datas pour la lecture du capteur de température. 

![Implantation fil vert SCL et blanc SDA](pictures/assembly/AG1-16.JPG)

 - Souder les deux résistances de 10kohm entre la ligne 13 et le "+" et la seconde entre la ligne 14 et le "+".
 - Se servir d'une des patte de résistance coupé pour faire un pont entre la ligne 15 et la colonne "+".

![Implantation des résistances et de l'alimentation du capteur de température](pictures/assembly/AG1-17.JPG) 
 
### 1.4 Connectiques de la batterie
 - Couper un fil du connecteur de la batterie, le dénuder et le souder à un autre fil de même couleur pour le rallonger de 25cm environ. 
 - Isoler la soudure au moyen de gaine thermorétractable. 
 - Faire de même pour rallonger le second fil. 

<section style="border: 2px solid red; padding: 20px; border-radius:20px; color: red;">Attention pendant cette manipulation à ce qu'aucun fil ne se touche pour éviter un court-circuit.</section>

![Rallonge des fils de la batterie](pictures/assembly/AG1-18.JPG)

 - Rassembler, la batterie, un connecteur femelle JST à 3 broches (je n'avais pas de 2 broches dans ma boite) et 3 ferrures JST femelles.
 - Dénuder un fil de la batterie, et y sertir une ferrure femelle. 
 - Insérer cette ferrure dans le bloc 3 broches JST mâle. Veiller à respecter le même sens que sur la photo.
 - Faire de même avec le second fil et l'insérer dans le bloc JST à l'opposé du premier.

![Implantation du connecteur JST batterie](pictures/assembly/AG1-19.JPG)

 - Rassembler, les fils du boutons (switch) étanche, un connecteur JST de batterie, un connecteur JST mâle 3 broches et 2 ferrures mâle.

![Fournitures pour câblage bouton](pictures/assembly/AG1-20.JPG)

 - Couper un fil du switch au ras du connecteur dupont. Dénuder le fil et le souder au fil rouge du connecteur JST batterie. Protéger la soudure avec de la gaine thermorétractable.

![Soudure fil bouton au fil connecteur](pictures/assembly/AG1-21.JPG)

 - Couper le second fil du switch au ras du connecteur dupont, le dénuder, et le sertir à une ferrure JST mâle. 
 - Faire de même avec le fil noir du connecteur batterie.

![Sertir les fils du connecteur et du switch](pictures/assembly/AG1-22.JPG)

 - Insérer ces ferrures dans le connecteur mâle 3 broches de manière à ce qu'une fois la batterie branché les deux fils noir soit face à face.

![Implantation connectique](pictures/assembly/AG1-23.JPG) 

### 1.5 Connectique du voyant lumineux.
Le voyant lumineux blue robotics, ne requiert pas de résistance additionnelle. 
 - Rassembler, le voyant lumineux, un bloc JST mâle à 3 broches et 2 ferrures mâles.

![Fournitures pour voyant](pictures/assembly/AG1-24.JPG)

 - Couper les deux fils du voyant lumineux, les dénuder et y sertir deux ferrures mâles. 

<section style="border: 2px solid red; padding: 20px; border-radius:20px; color: red;">
Attention avant de passer à l'étape suivante, il est important de placer le voyant sur la bride. En effet, le connecteur ne passera pas au travers de l'écrou.</section>

 - Rassembler le voyant lumineux, son joint torique, son écrou et une bride à 2 trous.

![Plus la bride](pictures/assembly/AG1-25.JPG)

 - Passer les fils du voyant lumineux dans le joint torique puis dans un trou de la bride et enfin dans l'écrou.

![Enfilage](pictures/assembly/AG1-26.JPG)

 - Ne pas graisser le joint qui est en compression. 
 - Serrer à la main légèrement l'écrou sans bloquer.

![Serrage voyant](pictures/assembly/AG1-27.JPG)

 - Insérer les ferrures dans un bloc connecteur JST 3 broches.

![Schèma d'implantation](pictures/assembly/connectique_2b_voyant.png)

 - Pour réaliser la rallonge du voyant lumineux, prendre : 4 ferrures JST femelles, 1 bloc JST femelle 3 broches et un autre de 2 broches, ainsi qu'un fil noir et bleu de 25cm environ. 
 - Dénuder et sertir chaque bout de fil. 
 - Insérer les ferrures dans les blocs en veillant aux polarités en se connectant à la carte d'une part et au voyant lumineux d'autre part. On peut torsader les fils.
 
![Rallonge, voyant lumineux](pictures/assembly/AG1-29.JPG)

### 1.6 Rallonge du capteur de température
 - Pour réaliser la rallonge du capteur de température, couper 4 morceau de fil de 25cm environ (noir, rouge, vert et blanc). Rassembler aussi 8 ferrures JST femelle et 2 bloc connectiques femelles 4 broches.

![Rallonge, capteur](pictures/assembly/AG1-30.JPG)

 - Insérer les ferrures dans un des blocs à 4 broches en suivant l'ordre de la photo.

![Rallonge, capteur](pictures/assembly/AG1-31.JPG)

 - [Tresser les câbles en suivant ce tutoriel](https://youtu.be/7lTFIzm9BLY?si=LTKGTFpY72lfe2tC)
 - Insérer les ferrures opposés dans le secons bloc à 4 broches en suivant l'ordre de la photo.

![Rallonge, capteur](pictures/assembly/AG1-32.JPG)

### 1.7 Rallonge de la carte microcontrôleur
 - Rassembler 5 fils (noir, rouge, blanc, vert et bleu), 5 ferrures femelles JST, 1 bloc JST 5 broches femelles, 5 ferrures dupont femelles et deux bloc dupont 4 broches. 
 - Dénuder les fils. Sur chcun de fil, sertir une ferrure femelle JST d'un bout et de l'autre une ferrure dupont femelle.
 - Insérer les ferrures JST dans le bloc JST à 5 broches dans le sens indiqué.

![Connecteur JST, carte micro controleur](pictures/assembly/AG1-33.JPG)

 - Insérer les ferrures dupont dans les bloc Dupont 4 broches dans le sens indiqué.
 
![Connecteur Dupont, carte micro controleur](pictures/assembly/AG1-34.JPG)

## 2/ Assemblage final
### 2.1 Fixation du switch
 - Rassembler tous les composants du switch étanche. C'est à dire, le pénétrateur, le bouton rotatif, l'écrou et 3 joints dont un est plus épais que les deux autres. 

![Rassembler pour switch](pictures/assembly/AG1-35.JPG)

 - Insérer la vis du pénétrateur dans le joint le plus épais de trois. Insérer le pénétrateur dans le second trou de la bride où se trouve déjà le voyant lumineux. Le joint doit se trouver du coté extérieur.

![Insertion joint torique](pictures/assembly/AG1-36.JPG)

 - Serrer à la main sans bloquer à l'aide de l'écrou. 
 - Retirer l'écrou (argenté) se trouvant sur le bouton poussoir.
 - Visser le bouton poussoir au bout (coté intérieur) du pénétrateur switch.
 
![serrer et positionnement du bouton poussoir](pictures/assembly/AG1-37.JPG)

 - Les deux derniers joints doivent être graissés avec de la graisse silicone.
 - En déposer une légère pointe sur le doit et frotter chacun des joints délicatement. Il ne doit rester aucune goutte.
 - Une fois graissé insérer ces joints dans les rainures du bouton tournant. 

![Positionnement joints sur bouton](pictures/assembly/AG1-38.JPG)

 - Visser le bouton dans le pénétrateur. Si nécéssaire ajouter une pointe de graisse silicone.

![Visser le bouton dans le pénétrateur](pictures/assembly/AG1-39.JPG)

 - A l'aide d'un multimètre tester le bon fonctionnement du Switch.

<section style="border: 2px solid red; padding: 20px; border-radius:20px; color: red;">
Attention ! Laisser le bouton ouvert (le courant ne peut passer) pour les étapes suivantes et surtout avant de brancher la batterie au reste du circuit.</section>