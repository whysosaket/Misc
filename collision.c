#include<stdio.h>
#include<math.h>
#include<stdbool.h>

unsigned long long int collisions = 0;

typedef struct{
    double mass;
    double velocity;
    double X;
    double width;
} Block;

double calculateMomentum(Block block);
void energyTransfer(Block *, Block *);

bool checkBlockCollision(Block *, Block *);
void wallImpact(Block *block);

/*
    Given Equations,
    1. v = u + at;
    2. S = ut + (at^2)/2;
    3. v^2 - u^2 = 2aS
    4. mv = p
    5. 
*/

int main(){

    Block smallBlock = {1, 0, 10};
    Block largeBlock = {1, -10, 50};
    smallBlock.width = 1;
    largeBlock.width = sqrt(largeBlock.mass);
    double wallPosition = 0;


    double smallMomentum = calculateMomentum(smallBlock);
    double largeMomentum = calculateMomentum(largeBlock);

    printf("Small Block (Initial Momentum): %lf\n", smallMomentum);
    printf("Large Block (Initial Momentum): %lf\n", largeMomentum);

    while(true){
        bool breakCondition = smallBlock.velocity>0&&largeBlock.velocity>0&&largeBlock.velocity>smallBlock.velocity;
        if(breakCondition) break;

        // condition of wall collision
        bool isWallCollision = smallBlock.X <= wallPosition;
        if (isWallCollision) {
            wallCollision(&smallBlock);
            collisions++;
        }

        // condition for block collision
        bool isBlockCollision = true;
        if(isBlockCollision){
            energyTransfer(&smallBlock, &largeBlock);
            collisions++;
        }
    }

    printf("Number of Collisions: %lld\n", collisions);
    printf("Small Block (Final Velocity): %lf\n", smallBlock.velocity);
    printf("Large Block (Final Velocity): %lf\n", largeBlock.velocity);

    return 0;
}

double calculateMomentum(Block block){
    return block.mass*block.velocity;
}

void energyTransfer(Block *smallBlock, Block *largeBlock){
    double smallVf = ((smallBlock->mass - largeBlock->mass) * smallBlock->velocity + 2 * largeBlock->mass * largeBlock->velocity) / (smallBlock->mass + largeBlock->mass);
    double largeVf = ((largeBlock->mass - smallBlock->mass) * largeBlock->velocity + 2 * smallBlock->mass * smallBlock->velocity) / (smallBlock->mass + largeBlock->mass);

    smallBlock->velocity = smallVf;
    largeBlock->velocity = largeVf;
}

void wallImpact(Block *block) {
    block->velocity = -block->velocity;
}

bool checkBlockCollision(Block *smallBlock, Block *largeBlock){

    // bool velocityOppositeDirection = (smallBlock->velocity >= 0 && largeBlock->velocity < 0);
    // bool velocityTowardsPositive = (smallBlock->velocity > 0 && largeBlock->velocity >= 0 && largeBlock->velocity < smallBlock->velocity);
    // bool velocityTowardsNegaive = (smallBlock->velocity <= 0 && largeBlock->velocity < 0 && largeBlock->velocity > smallBlock->velocity);

    bool collisionCondition = ((smallBlock->X+smallBlock->width)+smallBlock->velocity) >= (largeBlock->X+largeBlock->velocity);
    // bool collisionOnNextStep = (velocityOppositeDirection || velocityTowardsPositive || velocityTowardsNegaive) && collisionCondition;

    return collisionCondition;
}
