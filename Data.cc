#include "Data.h"

//constructor
Data::Data() 
	:current{nullptr}, bank{nullptr}, 
	Arts1{AcademicBuilding *AL{AL, Arts1, 40, true, 50, {2, 10, 30, 90, 160, 250}}, AcademicBuilding *ML{ML, Arts1, 60, true, 50, {4, 20, 60, 180, 320, 450}}}, 
	Arts2{AcademicBuilding *ECH{ECH, Arts2, 100, true, 50, {6, 30, 90, 270, 400, 550}}, AcademicBuilding *PAS{PAS, Arts2, 100, true, 50, {6, 30, 90, 270, 400, 550}}, AcademicBuilding *HH{HH, Arts2, 60, true, 50, {8, 40, 100, 300, 450, 600}}}, 
	Eng{AcademicBuilding *RCH{RCH, ENG, 140, true, 100, {10, 50, 150, 450, 625, 750}}, AcademicBuilding *DWE{DWE, ENG, 140, true, 100, {10, 50, 150, 450, 625, 750}}, AcademicBuilding *CPH{CPH, ENG, 160, true, 100, {12, 60, 150, 450, 625, 750}}}, 
	Health{AcademicBuilding *LHI{}, AcademicBuilding *BMH{}, AcademicBuilding *OPT{}}, 
	Env{AcademicBuilding *EV1{}, AcademicBuilding *EV2{}, AcademicBuilding *Ev3{}}, 
	Sci1{AcademicBuilding *PHYS{}, AcademicBuilding *B1{}, AcademicBuilding *B2{}}, 
	Sci2{AcademicBuilding *EIT{}, AcademicBuilding *ESC{}, AcademicBuilding *C2{}}, 
	Math{AcademicBuilding *MC{}, AcademicBuilding *DC{}}{

}; //default

//nested accessors
std::string Data::get_namePlayer(int i) { return *(players[i]).get_name(); }
char Data::get_piecePlayer(int i) { return *(players[i]).get_piece(); }
int Data::get_posPlayer(int i) { return *(players[i]).get_posn(); }

//other methods
int Data::get_NetWorth() {
	int total_val = (*current).get_balance();		// current cash balance of player
	for (const auto& property : owned_properties) {		// going through list of owned properites
		int tileNo = property.second;			//sets tileno to be that being looked at
		total_val += (board[tileNo].first).NetVal();	// adds netval of that property
	}
	return total_val;
}

//non-purchasable tile methods
void Data::TuitionPay(bool Pay300) {				// view will ask player if they want
								// to pay 300 or 10% of netval	
	if ( (*current).get_posn() == 24) {
		if (Pay300 == true) {
			(*current).change_balance(-300);
		} else {
			int net = get_NetWorth();
			(*current).change_balance(net);
		}
	}
}

void Data::CoopFee() {
	if ( (*current).get_posn() == 18) {
		(*current).change_balance(-150);
	}
}

void Data::OSAPcol() {
	if ( (*current).get_posn() == 20) {
		(*current).change_balance(200);
	}
}

void Data::TimsJail() { 			
	//REQUIRES ROLL FUNCTION
	if ( (*current).get_posn() == 30) {
	}
}

void Data::GoToJail() {
	if ( (*current).get_posn() == 10) {
		(*current).JumpTo_posn(30);
	}
};

void Data::SLC() {
	if ( ( (*current).get_posn() == 13) || ( (*current).get_posn() == 13) ){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::discrete_distribution<> d({1.0 / 8, 1.0 / 6, 1.0 / 6, 1.0 / 8,
			       	1.0 / 6, 1.0 / 6, 1.0 / 24, 1.0 /24});
		int num_pick = d(gen);			// REQUIRES RANDOM PICKING WITH %CHANCE
		switch(num_pick) {
			case 0:
				(*current).MovePosn_by(-3);		// back3
				break;
			case 1:
				(*current).MovePosn_by(-2);		// back2
				break;
			case 2:
				(*current).MovePosn_by(-1);		// back1
				break;
			case 3: 
				(*current).MovePosn_by(1);		// foreward1
				break;
			case 4: 
				(*current).MovePosn_by(2);		// foreward2
				break;
			case 5: 
				(*current).MovePosn_by(3);		// foreward3
				break;
			case 6: 
				(*current).JumpTo_posn(30);		// DC Tims Line
				break;
			case 7: 
				(*current).MovePosn_by(20);		// Collect OSAP
				break;
		}
	}
}

void Data::NH() {
	if (( (*current).get_posn() == 2) || ( (*current).get_posn() == 16) ){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::discrete_distribution<> d({1.0 / 18, 1.0 / 9, 1.0 / 6, 1.0 / 3,
			       	1.0 / 6, 1.0 / 9, 1.0 / 18});
		int num_pick = d(gen);	
		switch(num_pick) {
			case 0:
				(*current).change_balance(-200);	 
				break;
			case 1:
				(*current).change_balance(-100);
				break;
			case 2:
				(*current).change_balance(-50);
				break;
			case 3:
				(*current).change_balance(25);	
				break;
			case 4: 
				(*current).change_balance(50);
				break;
			case 5: 
				(*current).change_balance(100);		
				break;
			case 6: 
				(*current).change_balance(200);
				break;
		}
	}
}

