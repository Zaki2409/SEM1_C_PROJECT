#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CARDS 52

int balance;
int pot;
int deck[52];
int shuffle_deck[52];


void play();
void turn();
void shuffle();
int bet();
void init_deck();
int quit();


int hit(int *val);
char *card_face(int v);
char *card_suit(int v);
int card_value(int v);
void checkAce(int v1, int v2, int *a1);


int BlackJack_main()
{   
   
     printf("\n\n\t\t\t\t\t\t\t\tWelcome to my BlackJack Simulator!\n\n");

	printf("\t\t\t#######################################################################\n");
  
  printf("\t\t\t  ****** *     ******  ******  *    *       * ******  *****  *    *  \n");
  printf("\t\t\t  *    * *     *    *  *       *   *        * *    *  *      *   *   \n");
  printf("\t\t\t  ****** *     ******  *       * *          * ******  *      * *     \n");
  printf("\t\t\t  *    * *     *    *  *       *   *   *    * *    *  *      *   *   \n");
  printf("\t\t\t  ****** ***** *    *  ******  *    *  ****** *    *  *****  *    *  \n");
  printf("\t\t\t#######################################################################\n\n\n");
  printf("\n");
  printf("\n");
    
    
    printf("Below are the basic rules:\n");
    printf("- Beat the dealer's  hand without going over 21.\n- Face cards are worth 10, Aces are worth 1 or 11, whichever makes a better hand.\n- Each player starts with two cards, and one of the dealer's cards is hidden until the end.\n- Type 'hit' to ask for another card. Type 'stand' to hold your total and end your turn.\n- If you go over 21 you bust, and the dealer wins regardless of his hand.\n- If you are dealt 21 from the start (Ace & 10), you got a blackjack. If you get a blackjack, you win 2 times the amount of your bet automatically, unless the dealer also gets a blackjack, in which case it is a push.\n\n");
    printf("\n");
    printf("- Remember: Type 'hit' to get another card, and 'stand' to hold. At the beginning of the round, type 'bet' followed by the quantity you want to bet (i.e. 'bet 50').\n");
    printf("\n");
    printf("\nType 'play' to begin and 'quit' to return back .\n");
   
    
    char input[6];
    scanf("%5s", input);
    if(strcmp(input,"play")==0)
    play();
    else if(strcmp(input,"quit")==0) {
      quit();
      return 0;
    }
    return 0;
}

void play() {
  printf("lets start you off woth 500 credits \n");
  balance = 500;
  if (balance>0)
   {
    bet();
    init_deck();
    shuffle();
    turn();
  } else if ( balance <= 0 )
  {
    printf("Sorry, it looks like you lost! Type 'play' to play another game.\n");

  }
}

int bet(){
  int amount;
  printf("\nEnter the amount you want to bet\n");
  scanf("%d" , &amount);
  if(amount>balance)
        {
          printf("Invalid entry.Enter a value less than your ammount left\n");
          bet();
        }else if (amount<balance) 
            {
          printf("\nYou've made a bet of %d. Good luck!\n", amount);
}
pot = amount;
return 0;
}

int quit(){
    printf("Are you sure you want to quit? Type 'y' or 'n'.\n");
    char input[6];
    scanf("%s",input);
    if(strcmp(input,"y")==0)
    {
        printf("\nGOODBYE!!!\n");
        
    }
    else 
        printf("Quit cancelled.\n");
		return 0;
}

void init_deck()
{
    int i=0;
    for(i=0;i<52;i++)
    {
        deck[i] = i+1;  
    }
}

void shuffle()
{
    srand(time(NULL));
    int i=0;
    for(i=0;i<52;i++){
        shuffle_deck[i] = deck[i];
    }
    i=0;
    for(i=CARDS-1;i>0;i--){
        int j = rand()%(i+1);
        int n = shuffle_deck[i];
        shuffle_deck[i] = shuffle_deck[j];
        shuffle_deck[j] = n;
    }
}

char *card_suit(int v)
{
    v = v%4;
    switch(v){
        case 0 :
            return "Hearts";
        case 1 :
            return "Clubs";
        case 2 :
            return "Diamonds";
        case 3 :
            return "Spades";
    }
		return 0;
}

char *card_face(int v){
    v = v%13+1;
    char *output;
    switch(v){
        case 1 :
            output = "Ace";
            break;
        case 2 :
            output = "Two";
            break;
        case 3 :
            output = "Three";
            break;
        case 4 :
            output = "Four";
            break;
        case 5 :
            output = "Five";
            break;
        case 6 :
            output = "Six";
            break;
        case 7 :
            output = "Seven";
            break;
        case 8 :
            output = "Eight";
            break;
        case 9 :
            output = "Nine";
            break;
        case 10 :
            output = "Ten";
            break;
        case 11 :
            output = "Jack";
            break;
        case 12 :
            output = "Queen";
            break;
        case 13 :
            output = "King";
    }
    return output;
}

int hit(int *i){
    int a = shuffle_deck[*i];
    *i = *i + 1;
    return a;
}

void checkAce(int v1, int v2, int *a1){

    if(v1 == 1 || v2 == 1){
        int input;
        if(v1 == 1 && v2 == 1){
            v1 = 11;
            v2 = 1;
            *a1 = 12;
            printf("Since you got 2 Aces, we set one to be worth 11 and the other to be worth 1.\n");
        }else if(v1 == 1 || v2 == 1){
            if(v1+10+v2 == 21)
                *a1 = 21;
            else{
                printf("You've got an ace. Choose whether you want to make it count as 1 or 11.\n");
                printf("\033[0;35m");
                scanf("%d",&input);
                printf("COLOR6");
                if(input == 11)
                    *a1 += 10;
            }
        }
    }
}

int card_value(int v){

    int a;
    if(((v%13)+1)<10)
        a = v%13+1;
    else 
        a = 10;
    return a;
}



void turn(){
    int inc=0;

    int d1 = hit(&inc);
    char *cn1 = csuit(d1);
    char *cf1 = cface(d1);
    int cv1 = cval(d1);
    printf("\nYou got a %s of %s worth %d, and ", cf1, cn1, cv1);
    
    int d2 = hit(&inc);
    char *cn2 = csuit(d2);
    char *cf2 = cface(d2);
    int cv2 = cval(d2);

    printf("a %s of %s worth %d.\n", cf2, cn2, cv2);
    
    int d3 = hit(&inc);
    char *cn3 = csuit(d3);
    char *cf3 = cface(d3);
    int cv3 = cval(d3);
    printf("The dealer face up card is a %s of %s worth %d, and has XX.\n\n", cf3, cn3, cv3);
    
    int d4 = hit(&inc);
    char *cn4 = csuit(d4);
    char *cf4 = cface(d4);
    int cv4 = cval(d4);

    int player_total = cv1 + cv2;
    int dealer_total = cv3;

    checkAce(cv1, cv2, &player_total);

    printf("You have a total of %d points, and the dealer has %d.\n", player_total, dealer_total);  

    if(player_total == 21){
        printf("Congrats! You got a blackjack!! Your payout is 2-to-1, %d.\n", (int)(pot*2));
        balance += (pot*2);
    }else{
        char input[6];
        scanf("%5s", input);
        printf("\n");
        while(strcmp(input,"stand")!=0){
            if(strcmp(input,"hit") == 0){
                int val = hit(&inc);
                char *ns = csuit(val);
                char *nf = cface(val);
                int nv = cval(val);
                player_total += nv;
                printf("\n");
                printf("You got a %s of %s worth %d.\n\n", nf, ns, nv);
                printf("\n");
                if(player_total < 21){
                    if(nv==1){
                        if(player_total+10 == 21){
                            player_total += 10;
                            printf("Congrats! You got BLACKJACK! Payout is 2-to-1.\n");
                            balance += (pot*2);                         
                            break;
                        }else{
                            int input;
                            printf("You've got an ace. Choose whether you want to make it count as 1 or 11.\n");
                            printf("\n");
                            scanf("%d",&input);
                            printf("\n");
                            if(input == 11)
                                player_total += 10;
                        }
                    }
                }else if(player_total == 21){
                    printf("Congrats! You got 21!\n");
                    break;
                }else{
                    printf("Oh no, you've busted with %d. Try Again!", player_total);
                    break;
                }
            }else if(strcmp(input,"help")==0)
                printf("Type 'hit' to be dealt another card. Type 'stand' to hold.\n");
            else if(strcmp(input, "quit")==0){
                  quit();
                  
            }else
                printf("Invalid command, try again.\n");
            
            printf("Your new total is %d.\n", player_total);
            printf("\n");
            scanf("%5s", input);
            printf("\n");
        }
    }

    if(player_total < 21){

        printf("The dealer's flips a %s of %s worth %d.\n", cf4, cn4, cv4);
        dealer_total += cv4;
        if(cv4 == 1){
            if(dealer_total+11 < 21)
                dealer_total += 10;
        }

        if(dealer_total >= 16){
            printf("The dealer stands with %d.\n", dealer_total);
        }

        while(dealer_total < 16){
            int val = hit(&inc);
            char *ns = csuit(val);
            char *nf = cface(val);
            int nv = cval(val);
            dealer_total += nv;
            printf("The dealer got a %s of %s worth %d.\n", nf, ns, nv);
            if(dealer_total < 16){
                if(nv==1){
                    if(dealer_total+11<21)
                        dealer_total += 10;
                }
            }else if(dealer_total == 21){
                printf("The dealer just got 21.\n");
                break;
            }else if(dealer_total > 21){
                printf("COLOR2");
              
                printf("The dealer busted with %d! You win!\n\n", dealer_total);
                 printf("COLOR6");
                break;
            }else{
                printf("The dealer,stands with %d.\n",dealer_total);
                break;
            }
            printf("The dealer new total is %d.\n", dealer_total);
        }
        if(dealer_total<player_total){
            printf("You beat the dealer! Your payout is %d.\n",(int)(pot*2)); 
            balance += (pot*2);
        }else if(dealer_total==player_total){
            printf("COLOR2");
            printf("Its a tie! Push pot, 1-to-1 payout of %d.\n", pot);
            balance += pot;
            printf("COLOR6");
        }else if(dealer_total>player_total && dealer_total <= 21){
             printf("COLOR2");
            printf("Oh no! Looks like the dealer won. Try again!\n");
            printf("COLOR6");   
        }else{
            printf("COLOR2");
            printf("You beat the dealer! Your payout is %d.\n",(int)(pot*2)); 
            printf("COLOR6");
            balance += (pot*2);
        }
    }
    if(balance > 0)
    {
        printf("COLOR1");
        printf("\n\nYour new balance is %d.\n", balance);
        printf("COLOR6");
    }
}
