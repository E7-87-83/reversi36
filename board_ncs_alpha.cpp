#include <iostream>
#include <string>
#include <D:\zzz_programming\othello_project\m_board_ncs.hpp>
#include <vector>
using namespace std;



class board
{
	public:
		bool side_to_move;
		void initalization_board();           
		void initalization_board(bool is_it_a_playing_board);
		void displayboard();
		bool step(int column , int row, bool p_side);  //p_side -> true, white; p_side -> false, black
		bool mobilityzero(bool sideTmove);
		pure_field y;//		char field[6][7];
		int number_of_white_pieces;
		int number_of_black_pieces;
		int countingblackpieces();             
		int countingwhitepieces();             		
		

};


board ace_one;


int board::countingblackpieces() {
	int i,j;
	int p = 0;
	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {if (ace_one.y.field[j][i]=='x') {p++;}}
	}
	return p;
}

int board::countingwhitepieces() {
	int i,j;
	int p = 0;
	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {if (ace_one.y.field[j][i]=='o') {p++;}}
	}
	return p;	
}





void board::initalization_board() {
	int i,j;
	
	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {ace_one.y.field[j][i]='*';}
		cout << endl;
	}	
}


void board::initalization_board(bool is_it_a_playing_board) {

	board::initalization_board();
	
	if (is_it_a_playing_board) { 
		ace_one.y.field[2][3] = 'o'; // 'x' is black, 'o' is white , '*' is empty board
		ace_one.y.field[3][4] = 'o';
		ace_one.y.field[3][3] = 'x';
		ace_one.y.field[2][4] = 'x';
	}
	
	ace_one.side_to_move = false;
}

void board::displayboard() {
	int i,j;
	
	cout << "  abcdef" << endl;
	
	for (i = 1; i<=6; i++) {
		cout << i << " ";
		for (j=0; j<=5; j++) {cout << ace_one.y.field[j][i];}
		cout << endl;
	}
}


bool board::step(int column, int row, bool p_side) {   //p_side -> true, white; p_side -> false, black
	int i;
	bool legitimacy, basic_legitimacy;
	bool temp_legitimacy[8];
	bool continuity_of_line[8];
	short int length_of_change[8];
	bool partner_found[8];
	
	// check the legitimacy of the move
	// at least one possible in the eight directions
	
	
	basic_legitimacy = (ace_one.y.field[column][row]=='*');
	legitimacy = basic_legitimacy;
	
	if (basic_legitimacy) {
		if (p_side) {ace_one.y.field[column][row]='o';} else {ace_one.y.field[column][row]='x';}
	}
	// up (N)
	
	// start of evaluation to up(N)

	partner_found[0] = false;
	
	temp_legitimacy[0] = (row!=1) && (row!=2);

	

	if (temp_legitimacy[0]) {
		continuity_of_line[0] = (ace_one.y.field[column][row]!=ace_one.y.field[column][row-1]) && (ace_one.y.field[column][row-1]!='*') ;
		i = 1;
		length_of_change[0] = 0;
		while (continuity_of_line[0] && not partner_found[0] && row-i>=1) {
			switch(ace_one.y.field[column][row-i]) {
				case '*':
					continuity_of_line[0] = false; break;
				case 'x':
					if (p_side) { length_of_change[0]++; i++; } else {partner_found[0] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[0]++; i++;} else {partner_found[0] = true;} break;
	
				} 
				
			
		}
		

	}	
	
	temp_legitimacy[0] = temp_legitimacy[0] && continuity_of_line[0] && partner_found[0];
		
		
	// end of evaluation to up(N)
	
	
	// NE

	// start of evaluation to NE

	partner_found[1] = false;
	
	temp_legitimacy[1] = ( not(column==4 || row==2)) && (not(column==5 || row==1));

	if (temp_legitimacy[1]) {
		continuity_of_line[1] = (ace_one.y.field[column][row]!=ace_one.y.field[column+1][row-1]) && (ace_one.y.field[column+1][row-1]!='*') ;
		i = 1;
		length_of_change[1] = 0;
		while (continuity_of_line[1] && not partner_found[1] && column+i<=5 && row-i>=1 ) {
			switch(ace_one.y.field[column+i][row-i]) {
				case '*':
					continuity_of_line[1] = false; break;
				case 'x':
					if (p_side) { length_of_change[1]++; i++; } else {partner_found[1] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[1]++; i++;} else {partner_found[1] = true;} break;
	
				} 
				
			
		}
		
	}	
	
	temp_legitimacy[1] = temp_legitimacy[1] && continuity_of_line[1] && partner_found[1];
//	cout << "temp_legitimacy[1]:"<< temp_legitimacy[1] << endl; // TESTING
	// end of evaluation to NE

	// right (E)
	
	// start of evaluation to right(E)
	
	partner_found[2] = false;
	
	temp_legitimacy[2] = (column!=4) && (column!=5);

	if (temp_legitimacy[2]) {
		continuity_of_line[2] = (ace_one.y.field[column][row]!=ace_one.y.field[column+1][row]) && (ace_one.y.field[column+1][row]!='*') ;
		i = 1;
		length_of_change[2] = 0;
		while (continuity_of_line[2] && not partner_found[2] && column+i<=5) {
			switch(ace_one.y.field[column+i][row]) {
				case '*':
					continuity_of_line[2] = false; break;
				case 'x':
					if (p_side) { length_of_change[2]++; i++; } else {partner_found[2] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[2]++; i++;} else {partner_found[2] = true;} break;
	
				} 
				
			
		}
		
	}	
	
	temp_legitimacy[2] = temp_legitimacy[2] && continuity_of_line[2] && partner_found[2];
		
	// end of evaluation to right(E)
	
	// SE

	// start of evaluation to SE

	partner_found[3] = false;
	
	temp_legitimacy[3] = ( not(column==4 || row==5)) && (not(column==5 || row==6));

	if (temp_legitimacy[3]) {
		continuity_of_line[3] = (ace_one.y.field[column][row]!=ace_one.y.field[column+1][row+1]) && (ace_one.y.field[column+1][row+1]!='*') ;
		i = 1;
		length_of_change[3] = 0;
		while (continuity_of_line[3] && not partner_found[3] && column+i<=5 && row+i<=6 ) {
			switch(ace_one.y.field[column+i][row+i]) {
				case '*':
					continuity_of_line[3] = false; break;
				case 'x':
					if (p_side) { length_of_change[3]++; i++; } else {partner_found[3] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[3]++; i++;} else {partner_found[3] = true;} break;
	
				} 
				
			
		}
		
	}	
	
	temp_legitimacy[3] = temp_legitimacy[3] && continuity_of_line[3] && partner_found[3];
		
	// end of evaluation to SE


	// down (S)

    // start of evaluation to down(S)
    partner_found[4] = false;

    temp_legitimacy[4] = (row!=5) && (row!=6);

	if (temp_legitimacy[4]) {
		continuity_of_line[4] = (ace_one.y.field[column][row]!=ace_one.y.field[column][row+1]) && (ace_one.y.field[column][row+1]!='*') ;
		i = 1;
		length_of_change[4] = 0;
		while (continuity_of_line[4] && not partner_found[4] && row+i<=6 ) {
			switch(ace_one.y.field[column][row+i]) {
				case '*':
					continuity_of_line[4] = false; break;
				case 'x':
					if (p_side) { length_of_change[4]++; i++; } else {partner_found[4] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[4]++; i++;} else {partner_found[4] = true;} break;
	
				} 
				
			
		}
		
	}	
	
	
	temp_legitimacy[4] = temp_legitimacy[4] && continuity_of_line[4] && partner_found[4];

    // end of evaluation to down(S);


	// SW

	// start of evaluation to SW

	partner_found[5] = false;
	
	temp_legitimacy[5] = ( not(column==1 || row==5)) && (not(column==0 || row==6));

	if (temp_legitimacy[5]) {
		
		continuity_of_line[5] = (ace_one.y.field[column][row]!=ace_one.y.field[column-1][row+1]) && (ace_one.y.field[column-1][row+1]!='*') ;
		i = 1;
		length_of_change[5] = 0;
		while (continuity_of_line[5] && not partner_found[5] && column-i>=0 && row+i<=6 ) {
			switch(ace_one.y.field[column-i][row+i]) {
				case '*':
					continuity_of_line[5] = false; break;
				case 'x':
					if (p_side) { length_of_change[5]++; i++; } else {partner_found[5] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[5]++; i++;} else {partner_found[5] = true;} break;
	
				} 
				
			
		}
		
	}	
	
	temp_legitimacy[5] = temp_legitimacy[5] && continuity_of_line[5] && partner_found[5];		
		
	// end of evaluation to SW


	// left (W)

	// start of evaluation to left(W)

	partner_found[6] = false;
	
	temp_legitimacy[6] = (column!=0) && (column!=1);

	if (temp_legitimacy[6]) {
		continuity_of_line[6] = (ace_one.y.field[column][row]!=ace_one.y.field[column-1][row]) ;
		i = 1;
		length_of_change[6] = 0;
		while (continuity_of_line[6] && not partner_found[6] && column-i>=0) {
			switch(ace_one.y.field[column-i][row]) {
				case '*':
					continuity_of_line[6] = false; break;
				case 'x':
					if (p_side) { length_of_change[6]++; i++; } else {partner_found[6] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[6]++; i++;} else {partner_found[6] = true;} break;
	
				} 
				
			
		}
		
	}	
	
	temp_legitimacy[6] = temp_legitimacy[6] && continuity_of_line[6]  && partner_found[6];

		
	// end of evaluation to left(W)


	// NW

	// start of evaluation to NW

	partner_found[7] = false;
	
	temp_legitimacy[7] = ( not(column==0 || row==1)) && (not(column==1 || row==2));

	if (temp_legitimacy[7]) {
		continuity_of_line[7] = (ace_one.y.field[column][row]!=ace_one.y.field[column-1][row-1]) && (ace_one.y.field[column-1][row-1]!='*') ;
		i = 1;
		length_of_change[7] = 0;
		while (continuity_of_line[7] && not partner_found[7] && column-i>=0 && row-i>=1 ) {
			switch(ace_one.y.field[column-i][row-i]) {
				case '*':
					continuity_of_line[7] = false; break;
				case 'x':
					if (p_side) { length_of_change[7]++; i++; } else {partner_found[7] = true;} break;
				case 'o':
					if (not p_side) { length_of_change[7]++; i++;} else {partner_found[7] = true;} break;
	
				} 
				
			
		}
		
	}	
	
	temp_legitimacy[7] = temp_legitimacy[7] && continuity_of_line[7] && partner_found[7];
		
		
	// end of evaluation to NW


	
	legitimacy = legitimacy and ( temp_legitimacy[0] or temp_legitimacy[1] or temp_legitimacy[2] or temp_legitimacy[3] or temp_legitimacy[4] or temp_legitimacy[5] or temp_legitimacy[6] or temp_legitimacy[7]); 
	
	
	if (legitimacy) {

	// up (N)

		if (temp_legitimacy[0]) {    	// start of filpping piece on the up(N) direction		

			for (i=1; i <= length_of_change[0]; i++){
				if (p_side) {
					ace_one.y.field[column][row-i] = 'o';
				} else {
					ace_one.y.field[column][row-i] = 'x';
				} 
			} 			
			
			
		}  // end of filpping piece on the up(N) direction		
					

	// NE

		if (temp_legitimacy[1]) {    	// start of filpping piece on the NE direction		

			for (i=1; i <= length_of_change[1]; i++){
				if (p_side) {
					ace_one.y.field[column+i][row-i] = 'o';
				} else {
					ace_one.y.field[column+i][row-i] = 'x';
				} 
			}
			
		}  // end of filpping piece on the NE direction		
	
	// right (E)
	
		if (temp_legitimacy[2]) {    	// start of filpping piece on the right(E) direction		

			for (i=1; i <= length_of_change[2]; i++){
				if (p_side) {
					ace_one.y.field[column+i][row] = 'o';
				} else {
					ace_one.y.field[column+i][row] = 'x';
				} 
			}

			
		}  // end of filpping piece on the right(E) direction		

	// SE
	
		if (temp_legitimacy[3]) {    	// start of filpping piece on the right(E) direction		

			for (i=1; i <= length_of_change[3]; i++){
				if (p_side) {
					ace_one.y.field[column+i][row+i] = 'o';
				} else {
					ace_one.y.field[column+i][row+i] = 'x';
				} 
				}

			
		}  // end of filpping piece on the right(E) direction		
	
	// down (S)

		if (temp_legitimacy[4]) {    	// start of filpping piece on the down(S) direction		

			for (i=1; i <= length_of_change[4]; i++){
				if (p_side) {
					ace_one.y.field[column][row+i] = 'o';
				} else {
					ace_one.y.field[column][row+i] = 'x';
				} 
			}

			
		}  // end of filpping piece on the down(S) direction		


	// SW
	
	
		if (temp_legitimacy[5]) {    	// start of filpping piece on the right(E) direction		

			for (i=1; i <= length_of_change[5]; i++){
				if (p_side) {
					ace_one.y.field[column-i][row+i] = 'o';
				} else {
					ace_one.y.field[column-i][row+i] = 'x';
				} 
				}

			
		}  // end of filpping piece on the right(E) direction		
	
	// left (W)
	
		if (temp_legitimacy[6]) {    	// start of filpping piece on the left(W) direction		

			for (i=1; i <= length_of_change[6]; i++){
				if (p_side) {
					ace_one.y.field[column-i][row] = 'o';
				} else {
					ace_one.y.field[column-i][row] = 'x';
				} 
			}

			
		}  // end of filpping piece on the left(M) direction		
	
	// NW

	
		if (temp_legitimacy[7]) {    	// start of filpping piece on the right(E) direction		

			for (i=1; i <= length_of_change[7]; i++){
				if (p_side) {
					ace_one.y.field[column-i][row-i] = 'o';
				} else {
					ace_one.y.field[column-i][row-i] = 'x';
				} 
			}
			
		}  // end of filpping piece on the right(E) direction		
		
		return true;
		
	} else {	
		if (basic_legitimacy) {ace_one.y.field[column][row]='*';}
		return false;} // return false if it is unable to take a move
}


bool make_step(string locatestone) {
	int c, r;
	c = (int) locatestone[0] - 97;
	r = (int) locatestone[1] - 48;
	
	if (c<=5 && c>=0 && r<=6 && r>=1) {

		if (ace_one.step(c, r, ace_one.side_to_move)) {
			ace_one.side_to_move = not(ace_one.side_to_move);
			return true; } else {
			cout << "invalid move!" <<endl;
			return false;
		};
	} else if (locatestone[0]=='p' && ace_one.mobilityzero(ace_one.side_to_move)) {                       // Pass
	      ace_one.side_to_move = not(ace_one.side_to_move);
	      return true;
	} else { 
		if (locatestone[0]=='p') { cout << "you have mobility" << endl; }
		return false;
	}
		
}


bool board::mobilityzero(bool silicon) {
	board ref_desk, backupplace;	

	int i,j,k;
	int counter = 0;
	
	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {
			ref_desk.y.field[j][i] = ace_one.y.field[j][i];
			backupplace.y.field[j][i] = ace_one.y.field[j][i];
		}
	}	

	for (i = 1; i<=6; i++) {
		for (j=0; j<=5; j++) {
			if (ref_desk.y.field[j][i] == '*') {
				if ( ref_desk.step(j,i,silicon) ) {
					counter++;
					for (i = 1; i<=6; i++) {
						for (j=0; j<=5; j++) {ref_desk.y.field[j][i] = backupplace.y.field[j][i]; ace_one.y.field[j][i] = backupplace.y.field[j][i];}
					}	

				}
			}
			}
	}	

	if (counter!=0) {
		return false;
	} else { 
		return true;
	}

}



int main() {
	int number_of_attempts = 1;
	string sequence_of_moves[1000];	
	string step;
	bool endgameduetostruck;
	char tip;
	bool valid_step;

	
//	ace_one.number_of_occupied_grids = ace_one.countingoccupiedpieces();
//	ace_one.number_of_white_pieces = ace_one.countingwhitepieces();
//	ace_one.number_of_black_pieces = ace_one.countingblackpieces();
	ace_one.initalization_board(true);
	

	ace_one.displayboard();
	
	sequence_of_moves[0] = "";
	sequence_of_moves[1] = "";
	
	
	cout << "What mode do you want? \n";
	cout <<	 "A: two-person game \n";
	cout <<  "B: person-computer game, \n";
	cout <<  "  while you are black B:\n";
	cout << "W: computer-person game, \n";
    cout <<  "  while you are white W." << endl;
	cout << "C: computer-computer game, \n";
	
	cin >> tip;
	
	switch (tip) {
		case 'A': 
				
			step = "";
			endgameduetostruck = ace_one.mobilityzero(true) && ace_one.mobilityzero(false);
			while (step!="q" and step!="r" and not(endgameduetostruck)  ) {
				cin >> step;
				number_of_attempts++;
				sequence_of_moves[number_of_attempts] = step;
				if (step!="q" and step!="r") {make_step(step);}
				endgameduetostruck = ace_one.mobilityzero(true) && ace_one.mobilityzero(false);
				ace_one.displayboard();
			}
			break;
			
		case 'B': 
			step = ""; 
			engine1.side_of_engine = true; 	
			valid_step = true;
			endgameduetostruck = ace_one.mobilityzero(true) && ace_one.mobilityzero(false);
			while (step!="q" and step!="r" and not(endgameduetostruck)) {
				if (ace_one.side_to_move == false) cin >> step; 
				valid_step = make_step(step);
				if (step!="q" and step!="r" and valid_step) {ace_one.side_to_move = true; ace_one.displayboard();}  
				
				if (valid_step) {
					make_step(engine1.make_a_step(ace_one.y)); 
					ace_one.side_to_move = false;
					endgameduetostruck = ace_one.mobilityzero(true) && ace_one.mobilityzero(false);
				}
				ace_one.displayboard();  
			}				
			break;
			
		case 'W': 
			step = ""; 
			ace_one.side_to_move = false;
			engine1.side_of_engine = false; 	
			valid_step = true;
			endgameduetostruck = ace_one.mobilityzero(true) && ace_one.mobilityzero(false);
			make_step(engine1.make_a_step(ace_one.y));
			ace_one.displayboard();
			while (step!="q" and step!="r" and not(endgameduetostruck)) {
				if (ace_one.side_to_move == true) cin >> step; 
				valid_step = make_step(step);
				if (step!="q" and step!="r" and valid_step) {ace_one.side_to_move = false; ace_one.displayboard();}  
				
				if (valid_step) {
					make_step(engine1.make_a_step(ace_one.y)); 
					ace_one.side_to_move = true;
					endgameduetostruck = ace_one.mobilityzero(true) && ace_one.mobilityzero(false);
				}
				ace_one.displayboard();  
			}				
			break;

		case 'C':
			cout << "This function is under construction. (from the dumbest pawn, 26th Nov 2017) \n"	;
			break;

		default: break;
		
	}
	
	/** start case: resign **/
	
	/** end case: resign **/

	/** start case: natural end **/
	if (endgameduetostruck) {
		ace_one.number_of_black_pieces = ace_one.countingblackpieces();
		ace_one.number_of_white_pieces = ace_one.countingwhitepieces();
		if (ace_one.number_of_black_pieces > ace_one.number_of_white_pieces) {
			cout << "Black wins. "  << ace_one.number_of_black_pieces <<"-" << ace_one.number_of_white_pieces << endl;			
		} else if (ace_one.number_of_black_pieces < ace_one.number_of_white_pieces) {
			cout << "White wins. " << ace_one.number_of_black_pieces <<"-" << ace_one.number_of_white_pieces << endl;
		} else { 
			cout << "Draw. " <<  ace_one.number_of_black_pieces <<"-" << ace_one.number_of_white_pieces << endl;
		}
	}
	/** end case: natural end **/	
	
	
	
	
	cout << endl;
	

	
	
	return 0;

}
