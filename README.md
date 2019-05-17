# cproj
Projet de programmation : Réalisation d'un éditeur d'images en C

Syntaxe du projet :

open IMAGE_PATH = ouvre l’image IMAGE_PATH dans la fenêtre WINDOW_ID qui nous sera communiqué

symétrieverticale WINDOW_ID = réalise une symétrie verticale de l'image se trouvant dans la window WINDOW_ID

symétriehorizontale WINDOW_ID = réalise une symétrie horizontale de l'image se trouvant dans la window WINDOW_ID

rotation WINDOW_ID NB =  réalise une rotation de l'image se trouvant dans la window WINDOW_ID d'angle NB * 90

remplissage WINDOW_ID COLOR1 COLOR2 COLOR3 = remplissage de la window WINDOW_ID par la couleur r,g,b : COLOR1,COLOR2,COLOR3

remplassement WINDOW_ID COLOR1 COLOR2 COLOR3 NB = remplassement des pixels inferieur ou egale a NB de la window WINDOW_ID par la couleur r,g,b : COLOR1,COLOR2,COLOR3

negatif WINDOW_ID = Met en négatif l'image se trouvant dans la window WINDOW_ID

gris WINDOW_ID NB = Met en niveau de gris avec en pourcentage NB l'image se trouvant dans la window WINDOW_ID

noirblanc WINDOW_ID = Met en noir et blanc l'image se trouvant dans la window WINDOW_ID

quit = quit le programme

save WINDOW_ID NAME = telecharge l'image se trouvant dans la window WINDOW_ID avec le nom NAME au format png et BMP