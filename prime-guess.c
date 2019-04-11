/*
 * prime-guess.c
 * 
 * Copyright 2018 Stephen Stengel <stephen.stengel@cwu.edu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

/*
A prime number guessing game.
TODO: 	
* 	!!!!If they quit at any point, save the high score to a file.
* 
* 		Change the input methods to use getline().
* 
* 		Use what I know now about character input.
* 
* 		If they guess wrong, tell what their guess is divisible by.
* 
* 		If they say quit, tell a cool fact about that last number.
* 		Modes-
			Sequential mode. Guess the next prime.
			Random prime mode. 	Starts at a random prime and asks for the next
								prime.
			Backwards mode. Asks for the preceding prime.

			Must be able to switch between modes without stopping program.
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

int play_setup(void);

int play(int start_point_prime, int high_score);

int get_guess(int start_point_prime);

int prompt(int a);

int start_point_maker(void);

int prime_checker(int test_int);

int next_prime_finder(int start_number);

_Bool is_guess_correct(int user_guess, int next_prime);

int main()
{
	//printf("Size of int: %lu\n", sizeof(int));
	int start_point_prime;
	int high_score;
	high_score = 0;
	_Bool is_play_again;
	is_play_again = TRUE;
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			       "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	printf("#################################################################"
			"###############\n");
	printf("#                             PRIME GUESSING GAME!               "
			"              #\n");
	printf("#################################################################"
			"###############\n");

	printf("\nHello there! "
			"This is a game where you guess the next prime number!\n\n");	

	while (is_play_again)
	{
		start_point_prime = play_setup();
		high_score = play(start_point_prime, high_score);
		
		printf("Play again? (Enter y/n):");
		char play_again;
		char c;
		while ( (c = getchar()) != '\n'){};//munches extra chars in stdin
		scanf("%c", &play_again);
		printf("\n");
		
		if (play_again == 'y' || play_again == 'Y')
		{
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			       "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		}
		else
		{
			printf("Goodbye!\n\n");
			is_play_again = FALSE;
		}
	}
	
	return 0;
}

int play_setup()
{
	int start_point_prime;
	start_point_prime = start_point_maker();
	return start_point_prime;
}

int play(int start_point_prime, int high_score)
{
	unsigned int correct_counter;
	correct_counter = 0;
		
	int user_guess;
	user_guess = get_guess(start_point_prime);
	
	_Bool is_correct;
	is_correct = TRUE;
	
	int next_prime;
	
	while(is_correct)
	{
		next_prime = next_prime_finder(start_point_prime);
		is_correct = is_guess_correct(user_guess, next_prime);
		
		
		if (is_correct)
		{
			correct_counter++;
			start_point_prime = next_prime;
			printf("Correct!\n\n");
			user_guess = get_guess(start_point_prime);
		}
	}
	
	
	printf("Incorrect!\n\n");
	printf("The next prime after %d is: %d\n\n", start_point_prime, next_prime);
	printf("You got %d in a row correct!\n\n", correct_counter);
	
	if (correct_counter > high_score)
	{
		high_score = correct_counter;
		
		printf("###############################\n");
		printf("#       NEW HIGH SCORE!       #\n");
	}
	else if (correct_counter == high_score)
	{
		printf("###############################\n");
		printf("# You matched the high score! #\n");
	}
	printf("###############################\n");
	printf("# Your Score:     %11d #\n", correct_counter);
	printf("# High Score:     %11d #\n", high_score);
	printf("###############################\n");
	
	return high_score;
}

int get_guess(int start_point_prime)
{
	int user_guess;
	user_guess = -1;
	
	while (user_guess <= start_point_prime)
	{
		printf("What is the next prime after %d? (Enter 0 to quit.): ",
				start_point_prime);
		scanf("%d", &user_guess);
		
		if (user_guess == 0)
		{
			printf("Goodbye!\n\n");
			exit(0);
			return 0;
		}
		else if (user_guess <= start_point_prime)
		{
			printf("Guess a bigger number.\n");
			user_guess = -1;
		}
	}
	
	return user_guess;
}



_Bool is_guess_correct(int user_guess, int next_prime)
{
	if(user_guess == next_prime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int prime_checker(int number_to_test_for_primality)
{
	if(number_to_test_for_primality < 2)
	{
		return FALSE;
	}
	int divisor;
	divisor = 2;
	while(divisor <= sqrt(number_to_test_for_primality))
	{
		if(number_to_test_for_primality % divisor == 0)
		{
			return FALSE;
		}
		divisor++;
	}
	return TRUE;
}

//Returns the next prime number after the input number.
int next_prime_finder(int start_number)
{
	int i;
	i = start_number + 1;
			
	while (i < 2000000000)
	{
		if(prime_checker(i))
		{
			return i;
		}
		i++;
	}
	printf("Hey we just went through a lot of numbers without finding a"
			" prime. Something went wrong.\n");
	exit(1);
}

//start_point_maker() asks what prime the player wants to start at. It checks if
//that number is positive and if it is prime. If it is not positive or prime, it
//asks for another number. Returns the start point as an int.
int start_point_maker()
{
	int start_point_request;
	start_point_request = 1;
	
	_Bool is_start_point_prime;
	is_start_point_prime = FALSE;
	
	while(!is_start_point_prime)
	{
		printf("What prime number would you like to start at? (Enter 0 to quit): ");
		scanf("%d", &start_point_request);
		printf("\n");
		
		if (start_point_request == 0)
		{
			printf("Goodbye!\n\n");
			exit(0);
		}
		else if (start_point_request < 0)
		{
			printf("Pick a POSITIVE prime number to start at, please."
					" Like 2, or 127.\n\n");
			//continue;//jumps to the condition statement at the start of while.
			//Don't need this if I use "else if" by putting the extra lines of
			//code into the if statement in one line.
		}
		
		//is_start_point_prime = prime_checker(start_point_request);
		//if(!is_start_point_prime)
		else if (!( is_start_point_prime = prime_checker(start_point_request)))
		{
			printf("Invalid number! Pick a prime number to start at."
					" Like 2, or 127.\n\n");
		}
	}
	
	return start_point_request;
}
