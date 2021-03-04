//SUSMIT STARTS
#define up 9
#define down 10
#define right 11
#define left 12
#define select 13
int button[5] = {up , down , right , left , select};
int col_red[3] = {3 , 4 , 5} , col_green[3] = {6 , 7 , 8} , row[3] = {0 , 1 , 2};
int led_mat[3][3];
void setup()
{
  for (int i = 0 ; i < 3 ; i++)
  {
    pinMode (col_red[i] , OUTPUT);
    pinMode (col_green[i] , OUTPUT);
    pinMode (row[i] , OUTPUT);
  }
  for (int i = 0 ; i < 5 ; i++)
  {
    pinMode (button[i] , INPUT);
  }
}

void set_col_red (int c , bool val)
{
  if (val) digitalWrite (col_red[c] , HIGH);
  else digitalWrite (col_red[c] , LOW);
}

void set_col_green (int c , bool val)
{
  if (val) digitalWrite (col_green[c] , HIGH);
  else digitalWrite (col_green[c] , LOW);
}

void set_row (int r , bool val)
{
  if (val) digitalWrite (row[r] , LOW);
  else digitalWrite (row[r] , HIGH);
}


void set_red_led (int r , int c , bool val) // setting red led
{
  set_col_red (c , val);
  set_row (r , val);
}

void set_green_led (int r , int c , bool val) //setting green led
{
  set_col_green (c , val);
  set_row (r , val);
}

void led_mat_init ()//initializing all OFF scenario
{
  for (int i = 0 ; i < 3 ; i++)
    for (int j = 0 ; j < 3 ; j++)
    	led_mat[i][j] = 0;
}

void display()
{
  for (int i = 0 ; i < 3 ; i++)
    for (int j = 0 ; j < 3 ; j++)
      led_light (led_mat[i][j] , i , j);
}

void led_light (int state , int i , int j)
{
  reset();
  if (state == 0) 
  {
    set_red_led (i , j , false);
    set_green_led (i , j , false);
  }
  else if (state == 1)//green in on
  {
    set_red_led(i , j , false);
    set_green_led(i , j , true);
    delay(2);
    set_green_led(i , j , false);
  }
  else if (state == 2)//red led is on
  {
    set_green_led(i , j , false);
    set_red_led(i , j , true);
    delay(2);
    set_red_led(i , j , false);
  }
  else {}
  reset();
}

int is_win()//see if their is a winner 2 for RED, 1 for GREEN , 0 for not one
{
    for (int i = 0 ; i < 3 ; i++)
    {
        if (led_mat[i][0] == led_mat[i][1] && led_mat[i][1] == led_mat[i][2]) return led_mat[i][0];
        if (led_mat[0][i] == led_mat[1][i] && led_mat[1][i] == led_mat[2][i]) return led_mat[0][i];
    }
    if (led_mat[0][0] == led_mat[1][1] && led_mat[1][1] == led_mat[2][2]) return led_mat[1][1];
    if (led_mat[0][2] == led_mat[1][1] && led_mat[1][1] == led_mat[2][0]) return led_mat[2][0];
    return 0;
}
//Aditya start
//These are few functions designed to help with the code
//Resets everything which is cathode->high,anode->low
void reset()
{
  	Serial.flush();
    for (int i = 0 ; i < 3 ; i++)
    {
      digitalWrite (row[i] , HIGH);
      digitalWrite (col_red[i] , LOW);
      digitalWrite (col_green[i] , LOW);
    }
}
//returns value of 2->red and 1->green
//i am assuming red goes first
int check_turn(int n)
{
    if((n==0)||(n%2==0))
    {
        return(2);//means it is reds turn
    }
    else
    {
        return(1);//means it is greens turn
    }
}
//makes one led blink
//r->row,c->column,col->red or green,i->how many times to blink?
void blink(int r,int c,int col,int n)
{
  	reset();
    int i;
    for(i=0;i<n;i++)
    {
        if(col==2)
        {
            set_red_led(r,c,true);
            delay(5);
            set_red_led(r,c,false);
            delay(750);
            set_red_led(r,c,false);
            delay(5);
            set_red_led(r,c,true);
            delay(750);
        }
            if(col==1)
            {
                set_green_led(r,c,true);
                delay(5);
                set_green_led(r,c,false);
                delay(750);
                set_green_led(r,c,false);
                delay(5);
                set_green_led(r,c,true);
                delay(750);
            }

    }
  	reset();
        
}        
//this is what u will see when the match ends in a draw
void visual_draw(int n)
{  if(n==0)
{
  reset();
  led_mat_init();
  int i,j;
  //both colour lights of one row get on 
  for(i=0;i<3;i++)
  {
     set_row(i,true);
     for(j=0;j<3;j++)
     {
     set_col_green(j,true);
     set_col_red(j,true);
     set_col_green(j+1,true);
     set_col_red(j+1,true);
     set_col_green(j+2,true);
     set_col_red(j+2,true);
       delay(500);
       reset();
     }
     
 }
  //countinously all on
  set_row(0,true);
  set_row(1,true);
  set_row(2,true);
  set_col_green(0,true);
  set_col_green(1,true);
  set_col_green(2,true);
  set_col_red(0,true);
  set_col_red(1,true);
  set_col_red(2,true);
  delay(1000);
  reset();
  led_mat_init();
}
}
//this is what you will see when one wins
void visual_win(int n)
{   
    reset();
    led_mat_init();
    int i;
    if(n==1)//green won
    {
        for(i=0;i<1;i++)
        {
            led_mat[0][0]=1;
            led_mat[1][1]=1;
            led_mat[2][2]=1;
            led_mat[2][0]=1;
            led_mat[1][1]=1;
            led_mat[0][2]=1;
            for(i=0;i<50;i++)
            {
                  display();
            }
            delay(500);
            display();
            led_mat[0][0]=0;
            led_mat[1][1]=0;
            led_mat[2][2]=0;
            led_mat[2][0]=0;
            led_mat[1][1]=0;
            led_mat[0][2]=0;
            for(i=0;i<50;i++)
            {
                 display();
            }
            delay(500);
            display();
            
        }
       set_row(0,true);
       set_row(1,true);
       set_row(2,true);
       set_col_green(0,true);
       set_col_green(1,true);
       set_col_green(2,true);
       delay(500);
       reset();
       led_mat_init();

    }
    else//red won
    {
        for(i=0;i<1;i++)
        {
            led_mat[0][0]=2;
            led_mat[1][1]=2;
            led_mat[2][2]=2;
            led_mat[2][0]=2;
            led_mat[1][1]=2;
            led_mat[0][2]=2;
            for(i=0;i<50;i++)
            {
                 display();
            }
            delay(500);
            display();
            led_mat[0][0]=0;
            led_mat[1][1]=0;
            led_mat[2][2]=0;
            led_mat[2][0]=0;
            led_mat[1][1]=0;
            led_mat[0][2]=0;
            for(i=0;i<50;i++)
            {
                 display();
            }
            delay(500);
            display();
        }
        
       set_row(0,true);
       set_row(1,true);
       set_row(2,true);
       set_col_red(0,true);
       set_col_red(1,true);
       set_col_red(2,true);
       delay(500);
       reset();
       led_mat_init();
    }
}
//ADITYA ENDS
//ADNAN STARTS
bool button_press (int but)
{
  if (digitalRead(but) == HIGH)
  {
    for(int i = 0 ; i < 10 ; i++)
    {
      display();
      delay(5);
    }
    return true;
  }
  else return false;
}
    
void select_pos(int but , int *i , int *j) //test func ignore
{
  int a = (*i-1 < 0)?3+(*i-1):(*i-1);
  int b = (*j-1 < 0)?3+(*j-1):(*j-1);
  if (but == up) *i = a%3;
  if (but == down) *i = (*i+1)%3;
  if (but == left) *j = b%3;
  if (but == right) *j = (*j+1)%3;
  reset();
}
int button_read ()
{
  if (button_press(up) == true) return up;
  else if (button_press(down) == true) return down;
  else if (button_press(right) == true) return right;
  else if (button_press(left) == true) return left;
  else return -1;
  reset();
}
//ADNAN ENDS
//SUSMIT STARTS
void loop ()
{
  reset();
  led_mat_init();
  int winner_check = 0;
  for (int iter = 0 ; iter < 9 ; iter++)
  {
    int i = 0 , j = 0;
    int turn = check_turn(iter);
    display();
    while (button_press(select) != true || led_mat[i][j] != 0)
    {
      display();
      int but = button_read();
      //for (int i = 0 ; i < 50 ; i++)
       // display();
      display();
      select_pos(but , &i , &j);
      display();
      reset();
      if (1)
      {
        display();
        if (turn == 1)
        {
          reset();
          set_red_led(i , j , false);
          set_green_led(i , j , true);
          delay(2);
          set_green_led(i , j , false);
          reset();
        }
        if (turn == 2)
        {
          reset();
          set_green_led(i , j , false);
          set_red_led (i , j , true);
          delay(2);
          set_red_led(i , j , false);
          reset();
        }
      }
    }
    if (led_mat[i][j] == 0)
    {
      (turn == 1)?led_mat[i][j] = 1:led_mat[i][j] = 2;
      display();
      int check = is_win();
      if (check == 1 || check == 2) {reset() ; visual_win(check) ; winner_check = 1 ; break;}
    } 
  }
  if (winner_check == 0) visual_draw(winner_check);
}
//SUSMIT ENDS