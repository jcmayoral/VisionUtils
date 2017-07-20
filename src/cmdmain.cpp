#include "featuredetection/FD.h"
/*
 * main.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: jose
 */
using namespace std;

int startCMD(){

        FaultDetection fd = FaultDetection();
	char menu = '0';
	cvNamedWindow("main", CV_WINDOW_AUTOSIZE);
	createTrackbar("trackbar", "Linear Blend", NULL, 100, NULL);

	cout << "Welcome to the Monocular Visual Odometry Project..." << endl << "What do you want to do?" <<endl;

	while (menu!=4){

		cout << "Press your desire action \n 1. Run application\n 4. Exit\n";

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
            fd.run();
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
    return 1;
}
