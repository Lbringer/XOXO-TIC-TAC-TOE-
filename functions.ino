//These are few functions designed to help with the code
//Resets everything which is cathode->high,anode->low
void reset()
{  
    digitalWrite(0,LOW);
    digitalWrite(1,LOW);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);

}
//returns value of 2->red and 1->green
//i am assuming red goes first
int check_turn(int n)
{
    if((i=0))||(i%2==0))
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
{   reset();
    int i;
    for(i=0;i<n;i++)
    {
        if(col==2)
        {
            set_red_led(r,c,true);
            delay(750);
            set_red_led(r,c,false);
            delay(750);
        }
            if(col==1)
            {
                set_green_led(r,c,true);
                delay(750);
                set_green_led(r,c,false);
                delay(750);
            }

    }        
        
}        
//this is what u will see when the match ends in a draw
void visual_draw(int n)
{  if(n==8)
{
  reset(); 
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
}
}
//this is what you will see when one wins
void visual_win(int n)
{   
    reset();
    int i;
    if(n==1)//green won
    {
        for(i=0;i<2;i++)
        {
            led_mat[0][0]=1;
            led_mat[1][1]=1;
            led_mat[2][2]=1;
            led_mat[2][0]=1;
            led_mat[1][1]=1;
            led_mat[0][2]=1;
            display();
            delay(500);
            display();
            led_mat[0][0]=0;
            led_mat[1][1]=0;
            led_mat[2][2]=0;
            led_mat[2][0]=0;
            led_mat[1][1]=0;
            led_mat[0][2]=0;
            display();
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

    }
    else//red won
    {
        for(i=0;i<2;i++)
        {
            led_mat[0][0]=2;
            led_mat[1][1]=2;
            led_mat[2][2]=2;
            led_mat[2][0]=2;
            led_mat[1][1]=2;
            led_mat[0][2]=2;
            display();
            delay(500);
            display();
            led_mat[0][0]=0;
            led_mat[1][1]=0;
            led_mat[2][2]=0;
            led_mat[2][0]=0;
            led_mat[1][1]=0;
            led_mat[0][2]=0;
            display();
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
    }
    
}
  