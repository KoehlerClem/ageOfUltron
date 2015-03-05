#include   "../h/Configuration.h"

int main(void) {


	// ---------------- Steak Area -----------------

	/* Hier wird der Struct für einen Point definiert. Der Point hat x,y Coordinaten
	 * in coord gespeichert, einen int Wert für die Kanten und einen bool-Wert des
	 * aussagt ob der Punkt schon besucht wurde!
	 */
	typedef struct points{
		short coord[2];
		int edges;
		int visited;						// 1 = true, 0 = false
	} point;

	point allPoints[77];					// Das Array in dem Alle Punkte gespeichert werden
	short currentArrayPoint = 1;			// Der Punkt an dem der letzte Punkt in dem Array erstellt wurde
	short currentCoord[2] = {0,0};			// Die aktuelle Coordinate des aktuellen Punktes

	//Füllt alle Points mit werten auf
	int pointsfiller;
	for ( pointsfiller = 0; pointsfiller < 76; pointsfiller++ ){
		allPoints[pointsfiller].coord[0] = 0;
		allPoints[pointsfiller].coord[1] = 0;
		allPoints[pointsfiller].edges = 0;
		allPoints[pointsfiller].visited = 0;
	}


	/* Vergleicht zuerst die X-Coordinate des jeweils betrachteten Punktes gegen die übergebene X-Coordinate
	 * und wenn wenn diese Übereistimmt vergleicht die Funktion auch die Y-Coordinate. Wenn diese auch gleich ist
	 * wird true zurückgegeben.
	 */
	int pointExists(short coordToCheck[2]){
		int i;
		for ( i = 0; i < currentArrayPoint; i++ ){
			if ( coordToCheck[0] == allPoints[i].coord[0]){
				if ( coordToCheck[1] == allPoints[i].coord[1]){
					return 1;
				}
			}
		} return 0;
	}


	/* Es wird zuerst überprüft ob an den gegebenen Koordinaten schon ein Punk existiert.
	 * Fals dies nicht der Fall ist wird ein neuer Punkt an den Koordinaten erstellt und
	 * der Wert des current Arrays, also des derzeit vereachteten Punkts zurückgegeben.
	 */
	void createPoints(short x, short y){
		short coord[2] = {x, y};
		if (pointExists(coord) == 0){
			allPoints[currentArrayPoint].coord[0] = x;
			allPoints[currentArrayPoint].coord[1] = y;
			currentArrayPoint += 1;
		}
	}

	int getArrayAddressFromCoord(short coordToCheck[]){
			int i;
			for ( i = 0; i < currentArrayPoint; i++ ){
				if ( coordToCheck[0] == allPoints[i].coord[0]){
					if ( coordToCheck[1] == allPoints[i].coord[1]){
						return i;
					}
				}
			} return 0;
		}

	/* Wenn ein Punkt besucht wird, werden die Kanten des aktuellen Punktes gespeichert,
	 * er als Besucht markiert und die 4 Umliegenden Punkte erstellt, fals es sie noch nicht gibt!
	*/
	void visitPoint(){

		//Holt die Adresse in dem Array zu den Aktuellen Coordinaten
		int i = getArrayAddressFromCoord(currentCoord);

		if ( allPoints[i].visited == 0){
			allPoints[i].edges = Robot_GetIntersections();
			allPoints[i].visited = 1;

			createPoints(currentCoord[0] + 1,currentCoord[1]);
			createPoints(currentCoord[0] - 1,currentCoord[1]);
			createPoints(currentCoord[0],currentCoord[1] + 1);
			createPoints(currentCoord[0],currentCoord[1] - 1);
		}


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
		int i;
		for ( i = 0; i < currentArrayPoint; i++ ){
			if (allPoints[i].visited == 1){
				printf( "(%i,%i) mit den Kanten: %i!\n",allPoints[i].coord[0],allPoints[i].coord[1],allPoints[i].edges );
			}
		}
		printf( "bekannt.\n\n\n");
	}

	// ---------------- Bear Heaven -----------------

	int westVisit=0,eastVisit=0,northVisit=0,southVisit=0;
/*
void checkVisited(){
	short eastPoint[2] = {currentCoord[0] + 1,currentCoord[1]};
	short westPoint[2] = {currentCoord[0] - 1,currentCoord[1]};
	short northPoint[2] = {currentCoord[0],currentCoord[1] + 1};
	short southPoint[2] = {currentCoord[0],currentCoord[1] - 1};




	int a = getArrayAddressFromCoord(eastPoint);
	int b = getArrayAddressFromCoord(westPoint);
	int c = getArrayAddressFromCoord(northPoint);
	int d = getArrayAddressFromCoord(southPoint);

	if (allPoints[b].visited == 0){

		    westVisit = 1;

	}
	if (allPoints[a].visited == 0){

			eastVisit = 1;
		}
	if (allPoints[c].visited == 0){

			northVisit = 1;
		}
	if (allPoints[d].visited == 0){

			southVisit = 1;

}
}

*/

	setNull();printStatusPoints();
	moveSouth();printStatusPoints();
	moveSouth();printStatusPoints();
	moveEast();printStatusPoints();
	moveEast();printStatusPoints();
	moveNorth();printStatusPoints();
	moveEast();printStatusPoints();

	/*
	printf("Token: %d\n", Robot_Move(0, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	printf("Token: %d\n", Robot_Move(1, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	//printf("Token: %d\n", Robot_Move(2, 0));

	*/




	return EXIT_SUCCESS;
}
