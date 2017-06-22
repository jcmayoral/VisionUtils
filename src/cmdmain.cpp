/*
 * main.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */

#include "../monocularvision/MVO.h"
#include "../calibration/Calibration.h"
#include "../gui/GUI.h"

using namespace std;

int main(int argc, char ** argv){

	Calibration cal = Calibration();
	MVO mvo = MVO();
	char menu = '0';
	cvNamedWindow("main", CV_WINDOW_AUTOSIZE);
	createTrackbar("trackbar", "Linear Blend", NULL, 100, NULL);

	cout << "Welcome to the Monocular Visual Odometry Project..." << endl << "What do you want to do?" <<endl;

	while (menu!=4){

		cout << "Press your desire action\n 1. Calibrate Camera Matrix \n 2. Calibrate Scaling \n 3. Run application\n 4. Exit\n";

		//cin >> menu;
		cin.clear();
		menu = (char) cin.get();

		while (cin.fail()){
		    cin.ignore(INT_MAX, '\n'); // ignore last input
		    cout << "You can only enter numbers.\n";
		    continue;
		}

		switch(menu){
		case '1':
			cal.Calibrate();
			break;
		case '3':
			mvo.run();
			break;
		case '4':
			cout << "Thanks for visiting" << endl;
			return -1;
			break;
		default:
			cout<<"Please, press a valid option" <<endl;
			break;
		}

	}
	return -1;
}