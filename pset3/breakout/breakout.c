//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 0.24 * PADDLE_WIDTH
 
// dimensions and location of paddle
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH HEIGHT/8

#define PADDLE_Y HEIGHT - PADDLE_HEIGHT - 10
#define PADDLE_X WIDTH/2 - PADDLE_WIDTH/2
 
// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
GLabel placeLabel(GWindow window, GLabel label, string text, string color, int y_coor);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initiate message label
    GLabel message = "";         
    
    // set initial speed within limits
    double y_velocity;
    double x_velocity;
    
    do
    {
        x_velocity = drand48();
    }while (x_velocity > 0.75);
    
    do
    {
        y_velocity = drand48();
    }while (y_velocity < 0.3);
        
    // display messages and wait before start
    message = placeLabel(window, message, "You have 3 lives" , "GRAY", 10);
    pause(2500);
    removeGWindow(window, message);
    pause(100);
    message = placeLabel(window, message, "Click to play", "GRAY", 10);
    waitForClick();
    removeGWindow(window, message);    
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
            
        // Update ball location
        double y_ball = getY(ball) + y_velocity;
        double x_ball = getX(ball) + x_velocity;         
        setLocation(ball, x_ball, y_ball);
                
        // move paddle with mouse
        GEvent mouse = getNextEvent(MOUSE_EVENT);
        
        if (mouse != NULL)
        {
            if (getEventType(mouse) ==  MOUSE_MOVED)
            {       
                double new_x = getX(mouse) - PADDLE_WIDTH/2;    
                setLocation(paddle, new_x, PADDLE_Y);                
            }
        }
            
        // collision conditions
        GObject collision = detectCollision(window, ball);
               
        if (collision != NULL)
        {           
            if (collision == paddle)
            {
                y_velocity = -y_velocity;
            } 
            // else it must be brick          
            else if (strcmp(getType(collision), "GRect") == 0)
            {
                y_velocity = -y_velocity;
                removeGWindow(window, collision);  
                bricks -= 1;
                points += 1;
                updateScoreboard(window, label, points); 
                
                // increase speed every ROW points
                if (points % ROWS == 0)
                    y_velocity += .1;            
            }
        }
        
        // conditions when out of bounds        
        // if upper bound
        if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        } 
        // if lower bound
        else if (getY(ball) + RADIUS >= HEIGHT)
        {            
            lives -= 1;
            removeGWindow(window, ball);
            
            if (lives > 0) 
            {            
                ball = initBall(window);                    
                waitForClick();
            }                       
        }
        // if left or right bound
        else if (getX(ball) + RADIUS >= WIDTH || getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        } 
        
        pause(1);
    }
    
    if(bricks == 0)
    {
        placeLabel(window, message, "CONGRATULATIONS!", "GREEN", HEIGHT/2 - 20);
    }
    else
    {
        placeLabel(window, message, "GAME OVER", "RED", HEIGHT/2);
    }
    
    placeLabel(window, message, "Click to exit", "GRAY", 10);   
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}


GLabel placeLabel(GWindow window, GLabel label, string text, string color, int y_coor)
{
    label = newGLabel(text);     
    setFont(label, "SansSerif-20");
    setColor(label, color);
    double x = WIDTH/2 - getWidth(label)/2;
    double y = getHeight(label)/2 + y_coor;
    setLocation(label, x, y);
    add(window, label); 
    return label;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // horizontal free space between bricks
    int spaces = 7;
    
    // y-coordinate of first brick
    double y = 100;
    
    // width and height of bricks
    double width = (double) (WIDTH - ((COLS+1) * spaces)) / COLS ;
    double height = 10;
    
    // print ROW rows
    for (int i = 0; i < ROWS; i++)
    {           
        // set colour for brick rows             
        string brick_colour;
        
        if (i % 5 == 0)
        {
            brick_colour = "BLUE";
        }       
        else if (i % 5 == 1)
        {
            brick_colour = "CYAN";
        }
        else if (i % 5 == 2)
        {
            brick_colour = "GREEN";
        }
        else if (i % 5 == 3)
        {
            brick_colour = "RED";
        }
        else if (i % 5 == 4)
        {
            brick_colour = "MAGENTA";
        }
        
        // x-coordinate of bricks
        double x = 0; 
        
        // print COLS collumns of bricks
        for (int j = 0; j < COLS; j++)
        {   
            // put spaces before brick
            x += spaces;
            
            // draw brick
            GRect brick = newGRect(x, y, width, height);
            setFilled(brick, true);
            setColor(brick, brick_colour);           
            add(window, brick);
            
            // x-coordinate for next brick
            x += width;      
        }
        
        // y-coordinate for next row
        y += height + 5;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    
    double x = WIDTH/2 - RADIUS/2;
    double y = HEIGHT/2 - RADIUS/2;
    
    GOval ball = newGOval(x, y, RADIUS, RADIUS);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{ 
    // draw, fill, add and return paddle
    GRect paddle = newGRect(PADDLE_X, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(paddle, true);
    setFillColor(paddle, "BLACK"); 
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    
    GLabel label = newGLabel("0");     
    setFont(label, "SansSerif-30");
    setColor(label, "GRAY" );
    double x = WIDTH/2 - getWidth(label)/2;
    double y = HEIGHT/2 - getHeight(label)/2;
    setLocation(label, x, y);
    sendToBack(label);
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + RADIUS, y + RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
