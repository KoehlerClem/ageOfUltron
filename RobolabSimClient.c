#include   "../h/Configuration.h"


int main(void) {




	// ---------------- Steak Area -----------------


	/* Hier wird der Struct für einen Point definiert. Der Point hat x,y Coordinaten
	 * in coord gespeichert, einen short Wert für die Kanten und einen bool-Wert des
	 * aussagt ob der Punkt schon besucht wurde! jajaja
	 */
	typedef struct points{
		short coord[2];
		short arrayEdges[4];
		short visited;						// 1 = true, 0 = false
	} point;



	point allPoints[77];					// Das Array in dem Alle Punkte gespeichert werden
	short currentArrayPoint = 1;			// Der Punkt an dem der letzte Punkt in dem Array erstellt wurde
	short currentCoord[2] = {0,0};
	short currentPoint = 0;					// Die aktuelle Coordinate des aktuellen Punktes
	short nextMove = 1;
	short lastPointVisited;
	short nachbarPunkte[4];

	//Füllt alle Points mit werten auf
	short pointsfiller;
	for ( pointsfiller = 0; pointsfiller < 77; pointsfiller++ ){
		allPoints[pointsfiller].coord[0] = 0;
		allPoints[pointsfiller].coord[1] = 0;
		allPoints[pointsfiller].visited = 0;
		allPoints[pointsfiller].arrayEdges[0] = 0;
		allPoints[pointsfiller].arrayEdges[1] = 0;
		allPoints[pointsfiller].arrayEdges[2] = 0;
		allPoints[pointsfiller].arrayEdges[3] = 0;
	}

	void edgeToArray(short pointInArray, int edges){
			switch(edges){
			case 16: allPoints[pointInArray].arrayEdges[0] = 1; break;
			case 32: allPoints[pointInArray].arrayEdges[2] = 1; break;
			case 16*3: allPoints[pointInArray].arrayEdges[0] = 1; allPoints[pointInArray].arrayEdges[2] = 1; break;
			case 16*4: allPoints[pointInArray].arrayEdges[3] = 1; break;
			case 16*5: allPoints[pointInArray].arrayEdges[0] = 1; allPoints[pointInArray].arrayEdges[3] = 1; break;
			case 16*6: allPoints[pointInArray].arrayEdges[2] = 1; allPoints[pointInArray].arrayEdges[3] = 1; break;
			case 16*7: allPoints[pointInArray].arrayEdges[0] = 1; allPoints[pointInArray].arrayEdges[2] = 1; allPoints[pointInArray].arrayEdges[3] = 1; break;
			case 16*8: allPoints[pointInArray].arrayEdges[1] = 1; break;
			case 16*9: allPoints[pointInArray].arrayEdges[0] = 1; allPoints[pointInArray].arrayEdges[1] = 1; break;
			case 16*10: allPoints[pointInArray].arrayEdges[1] = 1; allPoints[pointInArray].arrayEdges[2] = 1; break;
			case 16*11: allPoints[pointInArray].arrayEdges[0] = 1; allPoints[pointInArray].arrayEdges[1] = 1; allPoints[pointInArray].arrayEdges[2] = 1; break;
			case 16*12: allPoints[pointInArray].arrayEdges[1] = 1; allPoints[pointInArray].arrayEdges[3] = 1; break;
			case 16*13: allPoints[pointInArray].arrayEdges[0] = 1; allPoints[pointInArray].arrayEdges[1] = 1; allPoints[pointInArray].arrayEdges[3] = 1; break;
			case 16*14: allPoints[pointInArray].arrayEdges[1] = 1; allPoints[pointInArray].arrayEdges[2] = 1; allPoints[pointInArray].arrayEdges[3] = 1; break;
			case 16*15: allPoints[pointInArray].arrayEdges[0] = 1; allPoints[pointInArray].arrayEdges[1] = 1; allPoints[pointInArray].arrayEdges[2] = 1; allPoints[pointInArray].arrayEdges[3] = 1; break;
			}
		}


	/* Vergleicht zuerst die X-Coordinate des jeweils betrachteten Punktes gegen die übergebene X-Coordinate
	 * und wenn wenn diese Übereistimmt vergleicht die Funktion auch die Y-Coordinate. Wenn diese auch gleich ist
	 * wird true zurückgegeben.
	 */
	short pointExists(short coordToCheck[2]){
		short i;
		for ( i = 0; i < currentArrayPoint; i++ ){
			if ( coordToCheck[0] == allPoints[i].coord[0]){
				if ( coordToCheck[1] == allPoints[i].coord[1]){
					return 1;
				}
			}
		} return 0;
	}

	void createPoint(short coord[2]){
		if (pointExists(coord) == 0){
			allPoints[currentArrayPoint].coord[0] = coord[0];
			allPoints[currentArrayPoint].coord[1] = coord[1];
			currentArrayPoint += 1;
		}
	}


	/* Es wird zuerst überprüft ob an den gegebenen Koordinaten schon ein Punk existiert.
	 * Fals dies nicht der Fall ist wird ein neuer Punkt an den Koordinaten erstellt und
	 * der Wert des current Arrays, also des derzeit vereachteten Punkts zurückgegeben.
	 */





	short getArrayAddressFromCoord(short coordToCheck[]){
		short i;
		for ( i = 0; i < currentArrayPoint; i++ ){
			if ( coordToCheck[0] == allPoints[i].coord[0]){
				if ( coordToCheck[1] == allPoints[i].coord[1]){
					return i;
				}
			}
		} return 0;
	}

	void updatePoints(){
		short coordNorth[2] = {currentCoord[0], currentCoord[1] + 1};
		short coordEast[2] = {currentCoord[0] + 1, currentCoord[1]};
		short coordSouth[2] = {currentCoord[0], currentCoord[1] - 1};
		short coordWest[2] = {currentCoord[0] - 1, currentCoord[1]};
		createPoint(coordNorth);
		allPoints[getArrayAddressFromCoord(coordNorth)].arrayEdges[2] = allPoints[currentPoint].arrayEdges[0];
		createPoint(coordEast);
		allPoints[getArrayAddressFromCoord(coordEast)].arrayEdges[3] = allPoints[currentPoint].arrayEdges[1];
		createPoint(coordSouth);
		allPoints[getArrayAddressFromCoord(coordSouth)].arrayEdges[0] = allPoints[currentPoint].arrayEdges[2];
		createPoint(coordWest);
		allPoints[getArrayAddressFromCoord(coordWest)].arrayEdges[1] = allPoints[currentPoint].arrayEdges[3];
	}


	/* Wenn ein Punkt besucht wird, werden die Kanten des aktuellen Punktes gespeichert,
	 * er als Besucht markiert und die 4 Umliegenden Punkte erstellt, fals es sie noch nicht gibt!
	*/

	void setNeighbourPoints(short coords[2]){
		short northPoint[2] = {coords[0], coords[1] + 1};
		short eastPoint[2] = {coords[0] + 1, coords[1]};
		short southPoint[2] = {coords[0], coords[1] - 1};
		short westPoint[2] = {coords[0] - 1, coords[1]};
		nachbarPunkte[0] = getArrayAddressFromCoord(northPoint);
		nachbarPunkte[1] = getArrayAddressFromCoord(eastPoint);
		nachbarPunkte[2] = getArrayAddressFromCoord(southPoint);
		nachbarPunkte[3] = getArrayAddressFromCoord(westPoint);
	}

	void setNextMove(){

		setNeighbourPoints(currentCoord);

		// Überprüfen auf Kante und nicht besucht

		short i;
		for( i = 0; i < 4; i++){
			if (allPoints[currentPoint].arrayEdges[i] == 1){
				if (allPoints[nachbarPunkte[i]].visited == 0){
					nextMove = i;
					return;
				}
			}
		}

		for( i = 0; i < 4; i++){
			if (allPoints[currentPoint].arrayEdges[i] == 1){
				if (lastPointVisited != nachbarPunkte[i]){
				nextMove = i;
				return;
				}
			}
		}

		for( i = 0; i < 4; i++){
			if (allPoints[currentPoint].arrayEdges[i] == 1){
				nextMove = i;
				return;
			}
		}
	}



	void visitPoint(){
		lastPointVisited = currentPoint;
		//Holt die Adresse in dem Array zu den Aktuellen Coordinaten
		currentPoint = getArrayAddressFromCoord(currentCoord);
		if ( allPoints[currentPoint].visited == 0){
			edgeToArray(currentPoint, Robot_GetIntersections());
			allPoints[currentPoint].visited = 1;
		}
		updatePoints();
		setNextMove();
	}


	/* Setzt den Punkt auf 0,0, empfohlen für den Start der Simulation
	 */
	void setNull(){
		Robot_Move(0,0);
		currentCoord[0] = 0;
		currentCoord[1] = 0;
		visitPoint();
	}

	/* Checkt ob eine bewegung nach Oben möglich ist. Wenn sie möglich ist
	 * wird die CurrentCoord auf die neue Coordinate gesetzt und die Funktion
	 * visitPoint() aufgerufen.
	 */

	/* Bewegt den Roboter einen Punkt nach oben bzw erhöht den y-Wert der
	 * Coordinate um 1 wenn möglich
	 */
	void moveNorth(){
		if (currentCoord[1] != 0){
			Robot_Move(currentCoord[0], currentCoord[1] + 1);
			currentCoord[1] = currentCoord[1] + 1;
			visitPoint();
		}
	}

	/* Bewegt den Roboter einen Punkt nach rechts bzw erhöht den x-Wert der
	 * Coordinate um 1 wenn möglich
	 */
	void moveEast(){
		if (currentCoord[0] != 6){
			Robot_Move(currentCoord[0] + 1, currentCoord[1]);
			currentCoord[0] = currentCoord[0] + 1;
			visitPoint();
		}
	}

	/* Bewegt den Roboter einen Punkt nach unten bzw verringert den y-Wert der
	 * Coordinate um 1 wenn möglich
	 */
	void moveSouth(){
		if (currentCoord[1] != -6){
			Robot_Move(currentCoord[0], currentCoord[1] - 1);
			currentCoord[1] = currentCoord[1] - 1;
			visitPoint();
		}
	}

	/* Bewegt den Roboter einen Punkt nach links bzw verringert den x-Wert der
	 * Coordinate um 1 wenn möglich
	 */
	void moveWest(){
		if (currentCoord[0] != 0){
			Robot_Move(currentCoord[0] - 1, currentCoord[1]);
			currentCoord[0] = currentCoord[0] - 1;
			visitPoint();
		}
	}

	void printStatusPoints(){
		printf("An dem Punkt (%i,%i) sind diese Punkte besucht worden und haben diese Kanten:\n",currentCoord[0],currentCoord[1]);
		short i;
		for ( i = 0; i < currentArrayPoint; i++ ){
			if (allPoints[i].visited == 1){
				printf( "(%i,%i) mit den Kanten Norden: %i Osten: %i Süden: %i Westen: %i!\n",allPoints[i].coord[0],allPoints[i].coord[1],allPoints[i].arrayEdges[0],allPoints[i].arrayEdges[1],allPoints[i].arrayEdges[2],allPoints[i].arrayEdges[3] );
			}
		}
		printf( "bekannt.\n\n\n");
	}

	// ---------------- Bear Heaven -----------------

	void getNewPath(){
		short checkThisCoord[2] = {currentCoord[0], currentCoord[1]};
		setNeighbourPoints(checkThisCoord);

	}



	//endlosschelife
	setNull();printStatusPoints();
	short ever = 0;

	while(ever < 100){
		printf("Current ArrayPoint:%i, Current Point: %i, Verfügbare Kanten: %i, %i, %i, %i!\n", currentArrayPoint, currentPoint, allPoints[currentPoint].arrayEdges[0], allPoints[currentPoint].arrayEdges[1], allPoints[currentPoint].arrayEdges[2], allPoints[currentPoint].arrayEdges[3]);
		switch(nextMove){
		case 0: moveNorth(); break;
		case 1: moveEast(); break;
		case 2: moveSouth(); break;
		case 3: moveWest(); break;
		}
		ever++;

	}



/*
	setNull();printStatusPoints();
	moveSouth();printStatusPoints();
	moveSouth();printStatusPoints();
	moveEast();printStatusPoints();
	moveEast();printStatusPoints();
	moveNorth();printStatusPoints();
	moveEast();printStatusPoints();

	printf("Token: %d\n", Robot_Move(0, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	printf("Token: %d\n", Robot_Move(1, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	//printf("Token: %d\n", Robot_Move(2, 0));

	*/




	return EXIT_SUCCESS;
}
