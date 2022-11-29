/*
 * Oliver Bartz
 * CS 160 Fall 2022
 * Project 2: Rock, Paper, Scissors Game
 * 10/30/2022
 */

package RPSGame;
import java.util.Scanner;	//user input
import java.util.Random;	//random generation


public class RPSGame{
	public static void main(String[] args) {
		int wins = 0;
		int losses = 0;
		int ties = 0;
		int games = 0;
		double winPercent = 0;
		int topStreak = 0;
		int currentStreak = 0;
		int compNum;				//computer's random number choice
		String playerChoice;		//hold's player's input for r/p/s decision
		boolean done = false;
		int gameOutcome = 99;		//0 for loss, 1 for win, 2 for tie, 3 for typo, others->error
		String userName;			//holds user's name as entered
		
		Scanner input = new Scanner(System.in);
		Random numbers = new Random();
		
		//initial welcome, username collection
		System.out.println("Welcome to the rock/paper/scissors game!\n");
		System.out.print("Please enter your nickname: ");
		userName = input.next();
		System.out.println("Welcome, " + userName + "! Let's get started.\n");
		
		//begin gameplay
		do {
			printOut();
			playerChoice = input.next();
			
			//generate and print computer choice
			compNum = numbers.nextInt(10000) % 3; //will return 0, 1, or 2
			System.out.print("The computer's choice is ");
			switch (compNum) {
				case 0 : System.out.println("rock.");
						break;
				case 1 : System.out.println("paper.");
						break;
				case 2 : System.out.println("scissors.");
						break;
				default : assert false : "ERROR: computer choice not recognized";
			}
			
			//determine and print winner
			gameOutcome = amWinner(playerChoice, compNum);
			if (gameOutcome == 1) {
				System.out.println("You win this round!!!");
				wins++;
				currentStreak++;
				games++;
			}
			else if (gameOutcome == 0) {
				System.out.println("You lose this round.");
				losses++;
				currentStreak = 0;
				games++;
			}
			else if (gameOutcome == 2) {
				System.out.println("It's a tie!");
				ties++;
				//no changing streaks, and no counting this game in statistics
			}
			else if (gameOutcome == 3) {	//player messed up their input
				System.out.println("Oops! Let's call that a tie.");
				ties++;
			}
			else assert false : "ERROR: game outcome undetermined";
			
			//calculate and print stats
			if (currentStreak > topStreak) topStreak = currentStreak;
			if (games != 0) winPercent = ((double)wins / (double)games) * 100;
			
			System.out.println(userName + ": " + wins + "  v.s. Computer: " + losses);
			System.out.print("Win percentage: ");
			System.out.printf("%.2f", winPercent);
			System.out.println("%\tCurrent streak: " + currentStreak + "\n");
			
			//prompt continuation of game
			System.out.print(userName + ", do you want to continue? ");
			done = getDecision(input.next(), input);
			
		} while (!done);
		
		//print goodbye messages
		System.out.println("\n~~~GAME OVER~~~");
		System.out.println("Your longest streak was " + topStreak + " wins in a row.");
		System.out.println("There were a total of " + ties + " ties, too.");
		if (wins > losses) {
			System.out.println("YOU WIN!!! CONGRATULATIONS!");
		}
		else if (wins < losses) {
			System.out.println("The computer wins. Better luck next time!");
		}
		else {	//tie
			System.out.println("It's a tie! You must be lucky.");
		}
		System.out.println("Thank you for playing, " + userName + ". Have a nice day!");

		input.close();
	}

	public static boolean getDecision(String input, Scanner scanner) {
		//determines if the user wants to play another round, returns bool
		//returns false if game should continue, true if done
		if (input.length() == 1) {	//single-character input: y, n, Y, N, or other
			switch(input) {
			case "y" :
			case "Y" :
				return false;
			case "n" :
			case "N" :
				return true;
			default : 				//case: the user made a typo
				System.out.print("Input not recognized. Would you like to continue playing? ");
				String decision = scanner.next();
				return getDecision(decision, scanner);
			}
		}
		else {	//multi-character input: yes, Yes, no, No, or other
			if (input.equalsIgnoreCase("yes")) return false;
			else if (input.equalsIgnoreCase("no")) return true;
			else {					//case: the user made a typo
				System.out.print("Input not recognized. Would you like to continue playing? ");
				String decision = scanner.next();
				return getDecision(decision, scanner);
			}
		}
	}
	
	public static int amWinner(String input, int compNum) {
		//parses player input, determines if the player has won, 
		//returning 1 for player wins, 0 for computer wins, and 2 for tie (99 for errors)
		int playerNum = 99;
		//encoding: 0 = rock, 1 = paper, 2 = scissors
		
		//determine player input choice
		if (input.length() == 1) {	//single char input
			switch (input) {
			case "R" :
			case "r" :
				playerNum = 0;
				break;
			case "P" :
			case "p" :
				playerNum = 1;
				break;
			case "S" :
			case "s" :
				playerNum = 2;
				break;
			default : return 3;	//error case
			}
		}
		else {	//multi-character input
			if (input.equalsIgnoreCase("rock")) playerNum = 0;
			else if (input.equalsIgnoreCase("paper")) playerNum = 1;
			else if (input.equalsIgnoreCase("scissors")) playerNum = 2;
			else return 3; //error case
		}
		
		//compare, determine winner
		if (playerNum == compNum) return 2;	//tie
		if (playerNum == 0) return (compNum - 1); //rock
		if (playerNum == 1) { //paper
			if (compNum == 0) return 1; //wins against rock
			if (compNum == 2) return 0; //loses against scissors
		}
		if (playerNum == 2) return compNum; //scissors
		else return 3;	//error case
	}
	
	public static void printOut() {
		//prints menu options for a fresh game
		System.out.println("Choose one of the following:");
		System.out.println("\tr - rock");
		System.out.println("\tp - paper");
		System.out.print("\ts - scissors\n>>");
	}
}

