//Lalith Vaishnav Elangovan 1006916884 code for blackjack game
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int playerSum,playerCard,playerValue,dealerCard,dealerValue,dealerSum;
    int playerInput;
    if(argc==1)
        srand(time(NULL));
    else
        srand(atoi(argv[1]));

// This is to generate the two randome cards for player and dealer
    dealerCard= rand() %13 + 1;
    playerCard= rand() %13 + 1;
    printf("First cards: player %d, dealer %d \n",playerCard,dealerCard);

//This code is to make sure the cards above 10 are worth 10
    if(playerCard<=10)
        playerValue=playerCard;
    else
        playerValue=10;
    playerSum=playerValue;
    if(dealerCard<=10)
        dealerValue=dealerCard;
    else
        dealerValue=10;
    dealerSum=dealerValue;

// This section is the do while loop for the players cards 
    do {
        do{printf("Type 1 for Hit, 0 to Stay: ");
            scanf("%d",&playerInput);} while (playerInput!=1&&playerInput!=0);
        if (playerInput==1){
            playerCard= rand() %13 + 1;
            if(playerCard<=10)
                playerValue=playerCard;
            else
                playerValue=10;
            playerSum = playerValue + playerSum;
            printf("Player gets a %d, worth is %d \n",playerCard,playerSum);
       } 
    }while (playerSum<=21&&playerInput==1);
    if(playerSum>21)
        printf("Player over 21, Dealer wins\n");

//This code is for the dealer and the cards he recieves after the player
    else
        {printf("Dealer gets: ");
        do
            {dealerCard= rand() %13 + 1;
            if(dealerCard<=10)
                dealerValue=dealerCard;
            else
                dealerValue=10;
                dealerSum=dealerValue + dealerSum;
            printf("%d ", dealerCard);
    } while (dealerSum<17);
    }
    printf("\n");

// These if statements are for the various outcomes of the Blackjack game
    if (dealerSum>21&&playerSum<=21)
        printf("Dealer over 21, Player wins\n");
    if (dealerSum==playerSum)
        printf("Tie!\n");
    if (dealerSum<21&&playerSum<21&&dealerSum>playerSum)   
        printf("Dealer better than Player, Dealer wins\n");
    if (playerSum<21&&dealerSum<21&&dealerSum<playerSum)
        printf("Player better than Dealer, Player wins\n");   
    return 0;
}