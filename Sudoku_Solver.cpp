#include<iostream>
#include<fstream>
using namespace std;

class Frame{

	int SudokuFrame[9][9];

	public:Frame(){
		menu();
	}
	
	
	  	// This function generates a menu for the user at the starting of the
	  	//program execution. This lets the user select the input method for entering
	  	//the values for the Sudoku Puzzle into the Frame object.
	private:void menu(){

                cout<<"\n======================\n";
                cout<<"   Sudoku Validator\n";
                cout<<"======================\n\n";

                cout<<"Sudoku Solver\n";
                cout<<"Please input the puzzle into this program.\n\n";
                cout<<"You can either:-\n";
                cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
               cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
                cout<<"\t   --> ";

                int opt;
                cin>>opt;

                if(opt==1) readFrameValues();
                else if(opt==2) readFrameValuesFile();
                else{
                        while(true){
                                cout<<"\nYou seem to have entered an invalid option.\n";
                                cout<<"\t   --> ";
                                cin>>opt;

                                if(opt==1) readFrameValues();
                                else if(opt==2) readFrameValuesFile();
                                else continue;

                                break;
                        }
                }

        }

	
// Reads the values for the Sudoku Frame cell-by-cell.
         
        private:void readFrameValues(){
                cout<<"\nEnter the specified value when prompted.\n";
                cout<<"Enter 0 if cell is empty.\n\n";

		int row, col;

                for(row=0; row<9; row++){ //Iterating over cells to read vals.
                        for(col=0; col<9; col++){
                                int entered_value;

                                cout<<"Enter value for cell["<<row+1<<"]["<<col+1<<"] --> ";
                                cin>>entered_value;

                                if(!(entered_value>=1 && entered_value<=9)){ //Checking for bounds in input.
                                        while(true){ //We loop until valid input is read from user.
                                                cout<<"You seem to have entered a wrong value!\n";
                                                cout<<"Enter value for cell ["<<row+1<<"]["<<col+1<<"] --> ";
                                                cin>>entered_value;

                                                if(entered_value>=1 && entered_value<=9) break;
                                        }
                                }

                                SudokuFrame[row][col]=entered_value;
                        }
                        cout<<"-------\n"; //Display a break after every row for convenience.
                }
        }
	
	//This function reads values from a specified file.
	  
	private:void readFrameValuesFile(){
		
		int row, col;
		char filename[30];
		ifstream file;
		
		cout<<"\nEnter the name of the file which contains the puzzle --> ";
		cin>>filename;

		file.open(filename,ios::in);

		for(row=0; row<9; row++){
			for(col=0; col<9; col++){

				int read_value;
				file>>read_value;

				SudokuFrame[row][col]=read_value;

				if(file.eof()) break;

			}
		}
		
		//If there aren't 81 values in the file, then it is invalid.	
		if((col*row)!=81){
			cout<<"Oops! The file doesn't have the required amount of values.\n";
			cout<<"Try again!\n";
			exit(EXIT_FAILURE);
		}

		file.close();

	}

//Returns the value of a cell of a specified col and row.
	
	public:int getCellValue(int row, int col){
		return SudokuFrame[row][col];
	}

};


class SudokuSolver{

	Frame frame;
	

//Calls the function which validates the values in the Sudoku frame.
	  
	public:SudokuSolver(){
		validateFrame();		
	}

	
//Calls functions which validates the rows, columns and 3x3 grids.
	  
	private:void validateFrame(){
		if(valuesAreValid()){
			if(rowsAreValid()){
				if(columnsAreValid()){
					if(ThreeByThreeSquaresAreValid()){
						cout<<"\nYour puzzle is valid!\n\n";
					}
					else cout<<"Your puzzle in invalid!\n";
				}
				else cout<<"Your puzzle is invalid!\n";
			}
			else cout<<"Your puzzle is invalid!\n";
		}
		else cout<<"Your puzzle is invalid!\n";
	}
	

	
//Checks if all values in the frame are between the ranges of 1-9.
	
	private:bool valuesAreValid(){		
		int row, col;

		for(row=0; row<9; row++){
			for(col=0; col<9; col++){
				int cellValue=frame.getCellValue(row,col);
				if(!(cellValue>=0 && cellValue<=9)) return false;
			}
		}

		return true;
	}

	
//Checks if the rows are valid in the frame.
	  
	private:bool rowsAreValid(){
		
		int row, col, i;

		for(row=0; row<9; row++){ //Iterating over rows

			for(i=1; i<=9; i++){ //Iter over 1-9

				if(rowContains(row,i)==false)
					return false;

			} //Value iteration loop ends here

		} //Row iteration loop ends here

		return true;
	}

//Checks if the columns in the frame are valid.
	
	private:bool columnsAreValid(){
		
		int row, col, i;
		
		for(col=0; col<9; col++){ //Iterating over cols
		
			for(i=1; i<=9; i++){ //Iter over 1-9
				
				if(columnContains(col,i)==false)
					return false;

			} //Value iteration loops ends

		} //Col iteration loop ends here
		
		return true;
	}
	
	
//Checks if the 3x3 grids in the frame are valid.
	
	private:bool ThreeByThreeSquaresAreValid(){
		
		int i_square, i;

		for(i_square=0; i_square<9; i_square++){ //Iter over squares
			
			for(i=1; i<=9; i++){ //Iter over 1-9

				if(squareContains(i_square,i)==false)
					return false;

			} //Value iteration loop ends here

		} //Square iteration loop ends here
		
		return true;
	}

	
//Checks whether a given value is present in a specified row.
	
	private:bool rowContains(int row, int value){
		int col;
		for(col=0; col<9; col++){
			if(frame.getCellValue(row,col)==value)
				return true;
		}
		return false;
	}

	
//Checks whether a given value is present in the specified column.
	
	private:bool columnContains(int col, int value){
		int row=0;
		for(row=0; row<9; row++){
			if(frame.getCellValue(row,col)==value)
				return true;
		}
		return false;
	}

	
//Checks whether a given value is present in the specified 3x3 grid.
	
	private:bool squareContains(int squareNumber, int value){
		int rowStart=(squareNumber/3)*3;
		int rowEnd=rowStart+2;
		
		int colStart=(squareNumber%3)*3;
		int colEnd=colStart+2;

		int row, col;
		for(row=rowStart; row<=rowEnd; row++){
			for(col=colStart; col<=colEnd; col++){
				if(frame.getCellValue(row,col)==value)
					return true;
			}
		}

		return false;
	}

};


int main(){
	SudokuSolver sudoku_puzzle;
	return 0;
}

