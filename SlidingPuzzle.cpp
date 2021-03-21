#include <bangtal.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

time_t startTime;

SceneID scene1;
ObjectID startButton, restartButton;
ObjectID puzzleArray[9];
const char* imageArray[] = { "images/0.jpg","images/1.jpg","images/2.jpg","images/3.jpg","images/4.jpg",
	"images/5.jpg","images/6.jpg","images/7.jpg","images/blank.png" };

const char* defaultImageArray[] = { "images/0.jpg","images/1.jpg","images/2.jpg","images/3.jpg","images/4.jpg",
	"images/5.jpg","images/6.jpg","images/7.jpg","images/blank.png" };

int blankImagePos = 8;


ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}


bool isCompleted() {
	for (int i = 0; i <9 ; i++) {
		if (imageArray[i] != defaultImageArray[i]) {
			return false;
		}
	}
	return true;
}

void processEndGame() {
	time_t currentTime = time(NULL);
	int timeGap = (int) currentTime - (int) startTime;
	char message[100];

	for (int i = 0; i < 9; i++) {
		hideObject(puzzleArray[i]);
	}

	sprintf_s(message, "Game Completed : 소요시간 [%d]초", timeGap);
	showMessage(message);
}

void swapImage(int pos1,int pos2){
	char* tempName = (char*) imageArray[pos1];
	imageArray[pos1] = imageArray[pos2];
	imageArray[pos2] = tempName;
	setObjectImage(puzzleArray[pos1], imageArray[pos1]);
	setObjectImage(puzzleArray[pos2], imageArray[pos2]);
	blankImagePos = pos1;

	if (isCompleted() == true) {
		processEndGame();
	}

}


void shuffle() {
	for (int i = 0; i <100; i++) {
		int pos1 = rand() % 9;
		int pos2 = rand() % 9;
		if (pos2 == blankImagePos) {
			swapImage(pos1, pos2);
		}
	}
}


void mousetCallback(ObjectID object, int x, int y, MouseAction action) {
	if(object==startButton){
		hideObject(startButton);
		showObject(restartButton);

		for (int i = 0; i < 9; i++) {
			showObject(puzzleArray[i]);
		}

		shuffle();
		startTime = time(NULL);
	}
	else if (object == restartButton) {
		for (int i = 0; i < 9; i++) {
			showObject(puzzleArray[i]);
		}

		shuffle();
		startTime = time(NULL);
	}
	else if (object == puzzleArray[0]) {
		if (blankImagePos == 1 || blankImagePos == 3) {
			swapImage(0, blankImagePos);
		}
	}
	else if (object == puzzleArray[1]) {
		if (blankImagePos == 0 || blankImagePos == 2 || blankImagePos == 4) {
			swapImage(1, blankImagePos);
		}
	}
	else if (object == puzzleArray[2]) {
		if (blankImagePos == 1 || blankImagePos == 5) {
			swapImage(2, blankImagePos);
		}
	}
	else if (object == puzzleArray[3]) {
		if (blankImagePos == 0 || blankImagePos == 4 || blankImagePos == 6) {
			swapImage(3, blankImagePos);
		}
	}
	else if (object == puzzleArray[4]) {
		if (blankImagePos == 1 || blankImagePos == 3 || blankImagePos == 5 || blankImagePos == 7) {
			swapImage(4, blankImagePos);
		}
	}
	else if (object == puzzleArray[5]) {
		if (blankImagePos == 2 || blankImagePos == 4 || blankImagePos == 8) {
			swapImage(5, blankImagePos);
		}
	}
	else if (object == puzzleArray[6]) {
		if (blankImagePos == 3 || blankImagePos == 7) {
			swapImage(6, blankImagePos);
		}
	}
	else if (object == puzzleArray[7]) {
		if (blankImagePos == 4 || blankImagePos == 6 || blankImagePos == 8) {
			swapImage(7, blankImagePos);
		}
	}
	else if (object == puzzleArray[8]) {
		if (blankImagePos == 5 || blankImagePos == 7) {
			swapImage(8, blankImagePos);
		}
	}

}

int main()
{
	setMouseCallback(mousetCallback);

	scene1 = createScene("IU", "images/IuFull.png");
	puzzleArray[0] = createObject(imageArray[0], scene1, 235, 460,false);
	puzzleArray[1] = createObject(imageArray[1], scene1, 505, 460, false);
	puzzleArray[2] = createObject(imageArray[2], scene1, 775, 460, false);
	puzzleArray[3] = createObject(imageArray[3], scene1, 235, 260, false);
	puzzleArray[4] = createObject(imageArray[4], scene1, 505, 260, false);
	puzzleArray[5] = createObject(imageArray[5], scene1, 775, 260, false);
	puzzleArray[6] = createObject(imageArray[6], scene1, 235, 60, false);
	puzzleArray[7] = createObject(imageArray[7], scene1, 505, 60, false);
	puzzleArray[8] = createObject(imageArray[8], scene1, 775, 60, false);

	startButton = createObject("images/start.png", scene1, 590, 70, true);
	restartButton = createObject("images/restart.png",scene1, 590, 20, false);

	startGame(scene1);
}

