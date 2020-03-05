#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cassert>
#define steps_of_perfectendgame 10;


std::string math_to_real(int column, int row) {
	std::string temp = "  ";
	temp[0] = (char) 97+column;
	temp[1] = (char) 48+row;
	return temp;        
}

struct RR {
	int rank;
	float score;
};


struct pure_step {
    int column;
    int row;
};


struct a_step {
	pure_step s;
    bool side_to_move;
};


/** struct a_step {
    int column;
    int row;
    bool side_to_move;
}; **/

struct b_step {
	pure_step s;
    bool side_to_move;
    float rating;
};



struct pure_field {
	char field[6][7];
};

class pure_board {
	public:	
		pure_field y;
		int mobility_of_black();
		int mobility_of_white();
		int stable_stones_of_black();
		int stable_stones_of_white();
};

class tree_board {
	public:
		char field[6][7];
		bool side_to_move;
		int mobility_of_black();
		int mobility_of_white();
		int stable_stones_of_black();
		int stable_stones_of_white();
//		tree_board antecedent_board;
		std::vector<tree_board> children_board;
};


class youngest_leave_of_board {
	public:
		char field[6][7];
		bool side_to_move;
		int mobility_of_black();
		int mobility_of_white();
		int stable_stones_of_black();
		int stable_stones_of_white();
		tree_board antecedent_board;
};


class z_board {
	public:
		pure_board z;
		bool side_to_move; // false -> black ; true -> white
		int mobility_of_black() {return z.mobility_of_black();}
		int mobility_of_white() {return z.mobility_of_white();}
		int stable_stones_of_black() {return z.stable_stones_of_black();}
		int stable_stones_of_white() {return z.stable_stones_of_white();}
		void step_on(pure_step);
};





bool legitimacy(pure_field y, int column, int row, bool side_to_move) {
	bool directional_legitimacy[8];
	char ray[8][6];
	int counter, malen;   // malen -> paint in German	
	
	int saeule[8];   // column in German
	int reihe[8];    // row in German
	
	saeule[0] = 0;
	reihe[0] = -1;
	saeule[1] = +1;
	reihe[1] = -1;
	saeule[2] = +1;
	reihe[2] = 0;
	saeule[3] = +1;
	reihe[3] = +1;
	saeule[4] = 0;
	reihe[4] = +1;
	saeule[5] = -1;
	reihe[5] = +1;
	saeule[6] = -1;
	reihe[6] = 0;
	saeule[7] = -1;
	reihe[7] = -1;
	

	if (y.field[column][row] == '*') {
		for (counter = 0; counter <8; counter++) {
			bool sub_partner_found = false;    // not have a high estimation of getting a partner
			bool sub_can_duan_wei = true;      // expect we can complete a line segment

			directional_legitimacy[counter] = false;
			ray[counter][0] = '*';
			malen = 1;
			while (column+malen*saeule[counter] <= 5 && column+malen*saeule[counter] >= 0 && row+malen*reihe[counter] <= 6 && row+malen*reihe[counter] >= 1  && sub_can_duan_wei && not(sub_partner_found) ) {
				switch (y.field[column+malen*saeule[counter]][row+malen*reihe[counter]]) {
					case 'x':						
						ray[counter][malen] = 'x';
						if (side_to_move) {
							malen++; 
						} else if (malen != 1) {           // 	avoid too short
								sub_partner_found = true;
								sub_can_duan_wei = true;
							} else {sub_can_duan_wei = false;}
						break;
					case 'o':
						ray[counter][malen] = 'o';
						if (side_to_move) {
							if (malen != 1) {           // 	avoid too short
								sub_partner_found = true;
								sub_can_duan_wei = true;
							} else {sub_can_duan_wei = false;}
						} else {
							malen++; 
						}
						break;
					case '*':
						sub_can_duan_wei = false;
						break;
					default:
						break;
				}
			}
			
			directional_legitimacy[counter] = sub_can_duan_wei && sub_partner_found;
			 
		}
		
		
		bool templ = false;
		for (counter = 0; counter < 8 && not(templ); counter++)
			templ = (templ or directional_legitimacy[counter]);
		return templ;	
	} else return false; 

};


int pure_board::mobility_of_black() {
	int i,j;
	int t = 0;

	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {
			if (legitimacy(y,j,i, false)) {
				t++;
			}
		}
	}	

	return t;	
} 

int pure_board::mobility_of_white() {
	int i,j;
	int t = 0;

	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {
			if (legitimacy(y,j,i, true)) {
				t++;
			}
		}
	}	

	return t;	
} 






int pure_board::stable_stones_of_black() {
	int i,j;
	int t = 0;
	
	if (y.field[0][6] == 'x') {t++;}
	if (y.field[5][6] == 'x') {t++;}
	if (y.field[0][1] == 'x') {t++;}
	if (y.field[5][1] == 'x') {t++;}

	return t;	
} 

int pure_board::stable_stones_of_white() {
	int i,j;
	int t = 0;

	if (y.field[0][6] == 'o') {t++;}
	if (y.field[5][6] == 'o') {t++;}
	if (y.field[0][1] == 'o') {t++;}
	if (y.field[5][1] == 'o') {t++;}

	return t;	
} 



void sort_moves (std::vector<b_step>& quene) {
	int i,j,k,w,a,r;
	int length_of_list = quene.size();
	bool swapped;
	b_step bridge, tempb;

	swapped = true;
	while (swapped) {
		swapped = false;
		for (i=0; i<length_of_list-1; i++) {
			if (quene[i+1].rating>quene[i].rating) {
				tempb.s.column = quene[i].s.column;          // quene.swap(quene[i+1], quene[i]); 
				tempb.s.row = quene[i].s.row;
				tempb.side_to_move = quene[i].side_to_move;
				tempb.rating = quene[i].rating;
				
				quene[i].s.column = quene[i+1].s.column;          // quene.swap(quene[i+1], quene[i]); 
				quene[i].s.row = quene[i+1].s.row;
				quene[i].side_to_move = quene[i+1].side_to_move;
				quene[i].rating = quene[i+1].rating;
				
				quene[i+1].s.column = tempb.s.column;          // quene.swap(quene[i+1], quene[i]); 
				quene[i+1].s.row = tempb.s.row;
				quene[i+1].side_to_move = tempb.side_to_move;
				quene[i+1].rating = tempb.rating;
				
				
				swapped = true;
			}
		}
	}
	
}


/**
void sort_moves (std::vector<b_step>& quene) {
	int i,j,k,w,a,r;
	int length_of_list = quene.size();
	bool swapped;
	
	while (swapped) {
		swapped = false;
		for (i=0; i<length_of_list-1; i++) {
			if (quene[i+1].rating>quene[i].rating) {
				quene.swap(quene[i+1], quene[i]); 
				swapped = true;
			}
		}
	}
		
} **/


class engine {
	public:
		bool side_of_engine;
		pure_field y;		
	// important declaration	
		std::vector<b_step> candidates_of_allowable_move;
		a_step new_move_from_opponent;
		float rate_a_move_simply(z_board y, pure_step s); 
//		float rate_a_board();   // concerning int mein_stable_stones, int dein_stable_stones, int mein_mobility, int dein_mobility, int mein_good_stone, float dein_score --- leave it to gamma version
//		bool checking_if_predicted_opp_move (int column, int row);  // leave it to gamma version
//		a_step perfect_endgame();
//		a_step perfect_endgame(z_board x);
		std::string make_a_step(pure_field yy);
		
		
		
		
};



engine engine1; //**************************************IMPORTANT



float mental_math (z_board dream, b_step& sr) {
	assert(dream.side_to_move == sr.side_to_move); 
//	std::cout << "dream.side_to_move == sr.side_to_move" << std::endl;
	assert(dream.z.y.field[sr.s.column][sr.s.row] == '*');
//	std::cout << "dream.z.y.field[sr.s.column][sr.s.row] == empty" << std::endl;	
	assert(legitimacy(dream.z.y, sr.s.column, sr.s.row, sr.side_to_move));
//	std::cout << "legitimacy(dream.z.y, sr.s.column, sr.s.row, sr.side_to_move)" << std::endl;


	int saeule[8];   // column in German
	int reihe[8];    // row in German
	
	saeule[0] = 0;  	reihe[0] = -1;
	saeule[1] = +1; 	reihe[1] = -1;
	saeule[2] = +1; 	reihe[2] = 0;
	saeule[3] = +1; 	reihe[3] = +1;
	saeule[4] = 0;   	reihe[4] = +1;
	saeule[5] = -1; 	reihe[5] = +1;
	saeule[6] = -1; 	reihe[6] = 0;
	saeule[7] = -1; 	reihe[7] = -1;

	char stm, otm;

	bool sub_partner_found;
	bool sub_can_duan_wei;
	bool directional_legitimacy[8];
	char ray[8][6];
	float tempm = 0;
	int old_stable_stones_of_w, old_stable_stones_of_b;
	
	old_stable_stones_of_w = dream.stable_stones_of_white();
	old_stable_stones_of_b = dream.stable_stones_of_black();
	


    if (sr.side_to_move) {otm = 'x'; stm = 'o';} else {otm = 'o'; stm = 'x';} 	
	
	/** Zug begin **/
	dream.z.y.field[sr.s.column][sr.s.row] = stm;
	
	int counter, malen, malen_c;   // malen -> paint in German

	for (counter = 0; counter <8; counter++) {
		bool sub_partner_found = false;    // do not have a high estimation of getting a partner
		bool sub_can_duan_wei = true;      // expect we can complete a line segment

		directional_legitimacy[counter] = false;
		ray[counter][0] = '*';
		malen = 1;
		while (sr.s.column+malen*saeule[counter] <= 5 && sr.s.column+malen*saeule[counter] >= 0 && sr.s.row+malen*reihe[counter] <= 6 && sr.s.row+malen*reihe[counter] >= 1  && sub_can_duan_wei && not(sub_partner_found) ) {
			switch (dream.z.y.field[sr.s.column+malen*saeule[counter]][sr.s.row+malen*reihe[counter]]) {
				case 'x':						
					ray[counter][malen] = 'x';
					if (sr.side_to_move) {
						malen++; 
					} else if (malen != 1) {           // 	avoid too short
							sub_partner_found = true;
							sub_can_duan_wei = true;
						} else {sub_can_duan_wei = false;}
					break;
				case 'o':
					ray[counter][malen] = 'o';
					if (sr.side_to_move) {
						if (malen != 1) {           // 	avoid too short
							sub_partner_found = true;
							sub_can_duan_wei = true;
						} else {sub_can_duan_wei = false;}
					} else {
						malen++; 
					}
					break;
				case '*':
					sub_can_duan_wei = false;
					break;
				default:
					break;
			}
		}
			
		directional_legitimacy[counter] = sub_can_duan_wei && sub_partner_found;
		if (directional_legitimacy[counter]) {
			for (malen_c = 1; malen_c <= malen-1; malen_c++) {
				dream.z.y.field[sr.s.column+malen_c*saeule[counter]][sr.s.row+malen_c*reihe[counter]] = stm;
			}
			
		}
			 
	}

	/** Zug end **/
	
	if (sr.side_to_move) {
		sr.rating = (dream.stable_stones_of_white()-old_stable_stones_of_w)*20-dream.mobility_of_black()	;       // NEED FURTHER MODIFICATION
	} else {
		sr.rating = (dream.stable_stones_of_black()-old_stable_stones_of_b)*20-dream.mobility_of_white()	;       // NEED FURTHER MODIFICATION
	}
	
	
	return tempm;
	

	
	
}



float engine::rate_a_move_simply(z_board y, pure_step s) {    // give a score to each move
	float target;
	float wertung = 0;
	z_board future_board;
	bool pure_field;
	b_step corn;
	
	corn.s.column = s.column;
	corn.s.row = s.row;
	y.side_to_move = engine1.side_of_engine;
	corn.side_to_move = engine1.side_of_engine; 
	
	
    mental_math(y, corn);  // TESTING
		
	return corn.rating;                       // for zeroth test  // *********************WRITING*********
}





std::string engine::make_a_step(pure_field yy) {       //**************************************IMPORTANT
	int i,j,counter,take;
	int k = 0;
	pure_step reine;
	b_step bridge;
	
	engine1.candidates_of_allowable_move.clear();
	engine1.y = yy;
	
	
	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {
			if (legitimacy(engine1.y,j,i, engine1.side_of_engine)) {
//				std::cout << "column:"<< j << "row:" << i << "\n"; //                   TESTING
				bridge.s.column=j;
				bridge.s.row=i;
				bridge.side_to_move = engine1.side_of_engine;
				bridge.rating = 0;
				engine1.candidates_of_allowable_move.push_back(bridge);
			}
		}
	}

	if (engine1.candidates_of_allowable_move.size() == 0) {                 // When mobility is zero
		std::cout << "p\n";
		return "p";
	} else if (engine1.candidates_of_allowable_move.size() == 1) {               
		return math_to_real(engine1.candidates_of_allowable_move[0].s.column, engine1.candidates_of_allowable_move[0].s.row ); // When there is only one choice to move
	} else {
		z_board tired;   // new variable
		pure_step suck;     // new variabe
		
		
		tired.side_to_move = engine1.side_of_engine;
		for (i = 1; i<=6; i++) {
			for (j=0; j<=5; j++) {
				tired.z.y.field[j][i] = engine1.y.field[j][i];
			}
		}
		
		
		for (counter = 0; counter<engine1.candidates_of_allowable_move.size(); counter++) { 
			suck.column = engine1.candidates_of_allowable_move[counter].s.column;
			suck.row = engine1.candidates_of_allowable_move[counter].s.row;
			engine1.candidates_of_allowable_move[counter].rating = engine1.rate_a_move_simply(tired, suck);
		}
		

		sort_moves(engine1.candidates_of_allowable_move);
		if (engine1.candidates_of_allowable_move[1].rating == engine1.candidates_of_allowable_move[0].rating ) {take = rand() % 2; } else {take = 0;}                  // for alpha test: select the highest rating move(s) only
		

		return math_to_real(engine1.candidates_of_allowable_move[take].s.column, engine1.candidates_of_allowable_move[take].s.row ); 
		
	}
	
	
	// for gamma test: perfect endgame
	
}



