#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define clear() printf("\033[H\033[J")

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define SECOND_HAND_RADIUS 14
#define MINUTE_HAND_RADIUS 10
#define HOUR_HAND_RADIUS 8 

char display[SCREEN_HEIGHT][SCREEN_WIDTH];

void displayTime() {
	int i;
	for(i=0; i<SCREEN_HEIGHT; i++) {
		int j;
		for(j=0; j<SCREEN_WIDTH; j++) {
			printf("%c", display[i][j]);
		}
		printf("\n");
	}
}

void swap(int * a, int * b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void drawLine(int x1, int y1, int x2, int y2) {

	if (y1 > y2) {swap(&x1, &x2); swap(&y1, &y2);}

    int dx = x2 - x1;
    int dy = y2 - y1;
    
    // Determine the sign of dx and dy
    int signX = (dx > 0) ? 1 : -1;
    int signY = (dy > 0) ? 1 : -1;
    
    // Absolute values of dx and dy
    dx = (dx < 0) ? -dx : dx;
    dy = (dy < 0) ? -dy : dy;
    
    // Determine the axis along which to iterate
    int axis;
    if (dx > dy) {
        axis = 0; // x-axis
    } else {
        axis = 1; // y-axis
        // Swap dx and dy for symmetry
        int temp = dx;
        dx = dy;
        dy = temp;
    }
    
    // Initialize decision parameters
    int decision = 2 * dy - dx;
    int x = x1, y = y1;
    
    // Print the initial point
    
    // Iterate along the selected axis
	int i;
    for (i = 0; i < dx; i++) {

		int updated = 0;
        // Update coordinates based on the axis
        if (axis == 0) {
            x += signX;
        } else {
            y += signY;
        }
        
        // Update decision parameter
        if (decision >= 0) {
            if (axis == 0) {
                y += signY;
				updated = 1;
            } else {
                x += signX;
				updated = 1;
            }
            decision -= 2 * dx;
        }
        decision += 2 * dy;

        // Print the current point
		display[y][x] = updated ? 
			(signY * signX == 1 ? '\\' : '/') : 
			(axis ?  '|' : '_' );
    }
}


int main ()
{
  while(1){
  	time_t rawtime;
  	struct tm * timeinfo;

	const int SCREEN_CENTER_X = SCREEN_HEIGHT - 1;
	const int SCREEN_CENTER_Y = SCREEN_HEIGHT / 2 - 1;

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
	clear();
  	printf ("Current local time and date: %s\n", asctime (timeinfo) );
	int h = timeinfo->tm_hour;
	int m = timeinfo->tm_min;
	int s = timeinfo->tm_sec;

	int date = timeinfo->tm_mday;
	int weekDay = (timeinfo->tm_wday + 36 - date) % 7;
	// int weekDay = timeinfo->tm_wday;
	int month = timeinfo->tm_mon;
	int year = timeinfo->tm_year;

	// printf("%02d:%02d:%02d\n", h, m, s);
	// printf("%d  %02d / %02d / %04d", weekDay, date, month + 1, year + 1900);

	int i;
	for(i=0; i<SCREEN_HEIGHT; i++) {
		int j;
		for(j=0; j<SCREEN_WIDTH; j++) {
			// display[i][j] = 48 + j % 10;
			display[i][j] = ' ';
		}
	}
	
	display[0] [29] = '1';
	display[0] [30] = '2';
	display[2] [46] = '1';
	display[7] [56] = '2';
	display[15][63] = '3';
	display[22][56] = '4';
	display[27][46] = '5';
	display[30][31] = '6';
	display[27][16] = '7';
	display[22][5] = '8';
	display[15][0] = '9';
	display[7] [4] = '1';
	display[7] [5] = '0';
	display[2] [14] = '1'; 
	display[2] [15] = '1'; 

	int secondX = cos(acos(-1.0) * ((s + 45) % 60) / 30.0) * SECOND_HAND_RADIUS * 2 + SCREEN_CENTER_X;
	int secondY = sin(acos(-1.0) * ((s + 45) % 60) / 30.0) * SECOND_HAND_RADIUS + SCREEN_CENTER_Y;

	int minuteX = cos(acos(-1.0) * ((m + 45) % 60) / 30.0) * MINUTE_HAND_RADIUS * 2 + SCREEN_CENTER_X;
	int minuteY = sin(acos(-1.0) * ((m + 45) % 60) / 30.0) * MINUTE_HAND_RADIUS + SCREEN_CENTER_Y;

	int hourX = cos(acos(-1.0) * (((h + 9) % 12) / 6.0 + m / 360.0)) * HOUR_HAND_RADIUS * 2 + SCREEN_CENTER_X;
	int hourY = sin(acos(-1.0) * (((h + 9) % 12) / 6.0 + m / 360.0)) * HOUR_HAND_RADIUS + SCREEN_CENTER_Y;
	// printf("%2d | %2d\n", secondX, secondY);

	drawLine(SCREEN_CENTER_X, SCREEN_CENTER_Y, secondX, secondY);
	drawLine(SCREEN_CENTER_X, SCREEN_CENTER_Y, minuteX, minuteY);
	drawLine(SCREEN_CENTER_X, SCREEN_CENTER_Y, hourX, hourY);

	displayTime();

	sleep(1);
  }
  return 0;
}
