#include <cmath>
#include <iostream>
#include "GUI.h"
#include <ctime>
#include <chrono>
#include <math.h>

#define PI 3.14159265358979324
	int  game[300][450]={{-1}};
    int  zikl=0,cur_x=120,cur_y=0;
    int figure[10][15];
	int buf[4][4],check[4][4];
	int l=0,ti=100,score=0;
    bool start=true;
    int del[10];
    int over=1,fig=0,tmr=0;
    
enum UserEventType
{
    EVENT_CLOSE = 1
};

// дочернее окно
class ChildWindow : public Window
{
public:
    ChildWindow() { m_count = 4; }
    ~ChildWindow() {}

    void OnDraw(Context *cr);
    bool OnLeftMouseButtonClick(const Point &position);
    bool OnRightMouseButtonClick(const Point &position);
	bool OnKeyEvent(uint64_t keyval);
	void Figure();
	void Transition();
    void Move(int way);
	void trans();   
	bool motion(int way);
	int max(int n);
	bool proverka(int n);
	void Del();
	bool Turn(int n);
	bool TurnCheck();
	bool OnTimer();
	bool GameOver();
	
	
private:
    uint32_t m_count;
	time_t timer=clock();
	
   	
};


void ChildWindow::OnDraw(Context *cr)
{
	Point mysize= GetSize();
	int i,j;
	int figures[3][3];
    std::cout << "ChildWindow::OnDraw()" << std::endl;
    // зальем прямоугольник окна желтым цветом
    cr->SetColor(RGB(0.2,0.2,0.2));
    if (zikl==0)
    {
    	for (i=0;i<300;i+=1)
    		for (j=0;j<450;j+=1)
    		{
    			figure[i/30][j/30]=-1;
    			game[i][j]=-1;
    		}
    	zikl+=1;
    	//Figure();
    }
    figure[1][0]=-1;
    figure[0][0]=-1;
    //cr->FillRectangle(Point(0,0), GetSize());
    for (i=0;i<300;i+=30)
    	for (j=0;j<450;j+=30)
    		if (game[i][j]==-1)
    			cr->FillRectangle(Point(i,j),Point(30,30));
    		else if ((game[i][j]==1)||(game[i][j]==10))
    			{
    				cr->SetColor(RGB(1.,0.5,0.2));
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2));
    				cur_x=i;
    				cur_y=j;
    			}
    		else if ((game[i][j]==2)||(game[i][j]==20))
    			{
    				cr->SetColor(RGB(0.5,1,0.2));
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2));   				
    			}
   		    else if ((game[i][j]==3)||(game[i][j]==30))
    			{
    				cr->SetColor(RGB(0.5,0.2,1));
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2));   				
    			}    
			 else if ((game[i][j]==4)||(game[i][j]==40))
    			{
    				cr->SetColor(RGB(0.2,1,0.5));
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2));
    				cur_x=i;
    				cur_y=j;    				
    			}  
			 else if ((game[i][j]==5)||(game[i][j]==50))
    			{
    				cr->SetColor(RGB(1,0.2,0.5));
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2));
    				cur_x=i;
    				cur_y=j;    				
    			}  
			 else if ((game[i][j]==6)||(game[i][j]==60))
    			{
    				cr->SetColor(RGB(0.8,1,0.2));
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2)); 				
    			}
    		else if ((game[i][j]==7)||(game[i][j]==70))
    			{
    				cr->SetColor(RGB(0.5,0.8,0.1));
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2)); 					
    			}        			
    		else if ((game[i][j]==100))
    			{
    				cr->FillRectangle(Point(i,j),Point(30,30));
    				cr->SetColor(RGB(0.2,0.2,0.2));
    			}		    						
    cr->SetColor(RGB(0.9,0.9,0.9));
    cr->SetLineWidth(2);
    for (i=0; i<10; i+=1)
    	cr->Rectangle(Point(i*30,0),Point((i+1)*30,449));
	cr->Line(Point(300,0),Point(300,449));
	for (i=0; i<15; i+=1)
    	cr->Rectangle(Point(0,i*30),Point(300,(i+1)*30));
	cr->Line(Point(300,0),Point(300,449));
	if(tmr)
		OnTimer();
	
}

bool ChildWindow::OnLeftMouseButtonClick(const Point &position)
{
    std::cout << "ChildWindow::OnLeftMouseButtonClick()" << std::endl;
	--m_count;
	if(!m_count)
	{
		NotifyParent(EVENT_CLOSE,position);
	}
	return true;
}

bool ChildWindow::OnRightMouseButtonClick(const Point &position)
{
    std::cout << "ChildWindow::OnRightMouseButtonClick()" << std::endl;
    DeleteMe();
    return true;
}

bool ChildWindow::proverka(int n)
{
   	int ff=0;
   		switch (n)
   		{
   		case(3):
   		{
   	    for (int j=0; j<450; j+=30)
   	        for (int i=0; i<300; i+=30)
   	        {
   	            if (game[i][j]==ti)
   	            {
   	            if ((game[i][j+30]!=ti)&&(game[i][j+30]!=-1))
   	                return false;
   	            //if ((game[i][j+30]!=ti)&&(game[i][j+60]!=-1))
   	            	//ff=1;
   	            //if ((buff[i][j+60]==ti)&&(buff[i][j]))
   	        	}
   	        }
   	    if (ff)
   	    	start=true;
   	    return true;
   	    }
   	    case (2):
   	    {
   	   		
	   	    for (int j=0; j<450; j+=30)
	   	        for (int i=0; i<300; i+=30)
	   	        {
	   	            if (game[i][j]==ti)
	   	            {
	   	            	if (i==0)
	   	            		return false;
	   	            	else
	   	            		if ((game[i-30][j]!=ti)&&(game[i-30][j]!=-1))
	   	                		return false;
	   	            //if ((buff[i][j+60]==ti)&&(buff[i][j]))
	   	        	}
	   	        }
	   	    return true;
	   	    
   	    }
   	    case (1):
   	    {
   	   		
	   	    for (int j=0; j<450; j+=30)
	   	        for (int i=0; i<300; i+=30)
	   	        {
	   	            if (figure[i/30][j/30]==ti)
	   	            {
	   	            	if (i==9)
	   	            		return false;
	   	            	else
	   	            		if ((figure[(i+30)/30][j/30]!=ti)&&(figure[(i+30)/30][j/30]!=-1))
	   	                		return false;
	   	            //if ((buff[i][j+60]==ti)&&(buff[i][j]))
	   	        	}
	   	        }
	   	        
	   	    return true;
	   	    
   	    }   	    
   	    }
   	}

void ChildWindow::Transition()
{
	int i,j,k=0,l=0;
	for (i=0;i<10;i+=1)
	{
		for (j=0;j<15;j+=1)
		{
			game[i*30][j*30]=figure[i][j];
			std::cout<<figure[i][j]<<' ';
		}
		std::cout<<'\n';
	}
	figure[1][0]=-1;
}

void ChildWindow::trans()
{
    int i, j, k;
    j = buf[3][0];
    k = 0;
    while (j <= buf[3][l-1])
    {
        for (i = buf[2][k]; i <= buf[0][k]; i += 1)
            figure[i][j] = ti;
        k += 1;
        j += 1;

        
    }
    figure[1][0]=-1; 
    Transition();
}

bool ChildWindow::TurnCheck()
{
	int i, j, k;
    j = check[3][0];
    k = 0;
    while (j <= check[3][l-1])
    {
        for (i = check[2][k]; i <= check[0][k]; i += 1)
            if ((figure[i][j]!=-1)&&(figure[i][j]!=ti))
            	return false;
        k += 1;
        j += 1;
    } 
   	return true;
}
void ChildWindow::Figure()
{
	std::cout << "ChildWindow::Figure()" << std::endl;
	Context *cr;
	time_t now=time(0);
	tm *ltm = localtime(&now);
	int i,j,k;
	int mass[4][4]={  {-1,-1,-1,-1},
                        {-1,-1,-1,-1},
                        {-1,-1,-1,-1},
                        {-1,-1,-1,-1} };
    bool Fl=false;
    
    Del();
    for (i=0;i<4;i+=1)
    	for (j=0;j<4;j+=1)
    		buf[i][j]=0;
    l=0;
    
	ti = ((ltm->tm_sec)+(ltm->tm_min))%10;
	ti += (ltm->tm_sec)%10;
	ti = ti%10;
	if (ti>5)
		ti = 9-ti;
	//ti=5;
	switch (ti)
	{
		case 0:
		{
			//figure[5][0]=6;
			mass[0][4]=6;
			ti=7;
			break;				
		}
		case 1:
		{
			mass[1][0]=1;
			mass[1][1]=1;
			mass[0][0]=1;
			mass[0][1]=1;
			/*
			figure[4][0]=1;
			figure[4][1]=1;
			figure[5][0]=1;
			figure[5][1]=1;
			*/
			break;
			}
			
		case 2:
		{
			mass[0][0]=2;
			mass[0][1]=2;
			mass[0][2]=2;	 
			mass[1][0]=2;
			mass[1][1]=2;
			mass[1][2]=2;
			mass[2][0]=2;
			mass[2][1]=2;
			mass[2][2]=2;
		/*
			figure[4][0]=2;
			figure[4][1]=2;
			figure[4][2]=2;
			figure[5][0]=2;
			figure[5][1]=2;
			figure[5][2]=2;
			figure[6][0]=2;
			figure[6][1]=2;
			figure[6][2]=2;
        */
			break;
			}
			
 		case 3:
 		{
 			mass[0][0]=3;
 			mass[0][1]=3;
 			mass[0][2]=3;
 			mass[0][3]=3;
 			
 		/*
 			figure[4][0]=3;
 			figure[5][0]=3;
 			figure[6][0]=3;
 			figure[7][0]=3;
	*/
			break;
		}
		case 4 :
		{
			mass[0][0]=4;
			mass[0][1]=4;
			mass[0][2]=4;
			mass[1][0]=4;
			mass[2][0]=4;
        /*
 			figure[4][0]=4;
 			figure[5][0]=4;
 			figure[6][0]=4;
 			figure[6][1]=4;
 			figure[6][2]=4;
 			*/
			break;
			}		
		case 5:
		{
			mass[0][0]=5;
			mass[0][1]=5;
			mass[1][1]=5;
			mass[0][2]=5;
		/*
			figure[5][0]=5;
 			figure[5][1]=5;
 			figure[4][1]=5;
 			figure[5][2]=5;
		*/
			break;
			}
		case 6:
		{
			mass[0][0]=7;
			mass[0][1]=7;
			mass[1][1]=7;
			mass[1][2]=7;
		/*
			figure[5][0]=7;
 			figure[5][1]=7;
 			figure[4][1]=7;
 			figure[4][2]=7;
*/
			break;
			}	
		//ReDraw();
			
				};
	int t;
	for (i = 4; i < 8; i += 1)
    {
        Fl = false;
        t = 0;
        for (j = 0; j < 4; j += 1)
        {
            if (mass[i - 4][j] != -1)
            {
                if (!t)
                {
                    t = 1;
                    buf[2][l] = j+4;
                    buf[3][l] = i-4;
                }
                k = j+4;
                //figure[i][j] = mass[i - 4][j];
                Fl = true;
            }
        }
        
        if (Fl)
        {
            buf[0][l] = k;
            buf[1][l] = i-4;
            l += 1;
        }
        }
       
	trans();
															
}



int ChildWindow::max(int n)
{
	int mx=-1;
	for (int i=0; i<l; i+=1)
		if(mx<buf[n][i])
			mx=buf[n][i];
	return mx;
}

bool ChildWindow::Turn(int n)
{
	int i,j,k;
	for (i=0; i<4; i+=1)
		for (j=0;j<l;j+=1)
			check[i][j]=buf[i][j];
	if (n==1)
		{
			switch (ti)
			{
				case(3):
				{
						if (l == 1)
				{
				 	l+=3;   
				    check[0][0] -= 1;
				    check[2][0] = check[0][0];
				    check[1][0] = 0;
				    for (i = 1; i < l; i += 1)
				    {
				        check[0][i] = check[0][0];
				        check[2][i] = check[0][0];
				        check[3][i] = check[3][0]+i;
				        check[1][i] = check[3][0]+i;
				    }
				    if (TurnCheck())
				   	{ 
				   	//l += 3;
				    figure[buf[2][0]][buf[3][0]] = -1;
				    figure[buf[2][0] + 1][buf[3][0]] = -1;
				    figure[buf[0][0]][buf[3][0]] = -1;
				   	}
				   	else 
				   	{
				   		l-=3;
				   		return false;
				   	}
				}
				else
				{
				   l-=3;
				    for (i = 1; i < l+3; i += 1)
				        for (j = 0; j < 4; j += 1)
				            check[j][i] = 0;
				    check[0][0] += 1;
				    check[2][0] = check[0][0] - 3;
				    
				    if(TurnCheck())
				    {
				     //l -= 3;
				    for (i = 1; i < l+3; i += 1)
				        figure[buf[0][0]][buf[3][i]] = -1;
				       }
				       else
				       {
				       	l+=3;
				       	return false;
				       	}
				}
					break;
				}
				case(4):
				{
					int t;
					int mx;
					mx = max(0);
					for (i = 0; i < l; i += 1)
						if (buf[2][i] != mx)
						    t = i;
					if ((t == l - 1)&&(buf[2][t-1]==mx))
					{
						for (i = 0; i < l-1; i += 1)
						{
						   //figure[check[0][i]][check[3][i]] = -1;
						    check[0][i] = check[2][2];
						    check[2][i] = check[2][2];
						}
						if (TurnCheck())
						{
							for (i = 0; i < l-1; i += 1)
								figure[buf[0][i]][buf[3][i]] = -1;
						}
						else
							return false;
					}
					else if ((t == l - 1)&&(mx!=buf[0][0]))
					{

						check[0][0] = check[0][2];
						check[0][2] = check[2][2];
						if (TurnCheck())
						{
							figure[buf[0][2]][buf[3][2]] = -1;
							figure[buf[0][2] - 1][buf[3][2]] = -1;
						}
						else
							return false;						

					}
					else if ((mx == buf[0][0])&&(t!=0))
					{
						
						for (i = 1; i < l; i += 1)
						{
						    check[0][i] = check[0][0];
						    check[2][i] = check[0][0];
						}
						if (TurnCheck())
						{
							figure[buf[0][1]][buf[3][1]] = -1;
							figure[buf[0][2]][buf[3][2]] = -1;
						}
						else
							return false;						
					}
					else
					{
						check[2][2] = check[2][0];
						check[2][0] = check[0][0];
						if (TurnCheck())
						{
							figure[buf[2][0]][buf[3][0]] = -1;
							figure[buf[2][0] + 1][buf[3][0]] = -1;
						}
						else
							return false;						
					}
					break;
				}
				
				
				case(5):
				{ 
				
					int t;

					if ((l == 2) && (buf[0][0]>buf[0][1]))
					{
						l+=1;
						check[2][1] = check[0][1];
						check[2][0] = check[0][0];
						check[2][2] = check[0][0];
						check[0][1] = check[0][0];
						check[0][2] = check[0][0];

						check[1][2] = check[3][1] + 1;
						check[3][2] = check[3][1] + 1;
						if (TurnCheck())
						{
							
							for (i = 0; i < 2; i += 1)
							{
								figure[buf[2][0] + i][buf[3][0]] = -1;
							}						
						}
						else
						{
							l-=1;
							return false;
						}
					}
					else if ((l == 3) && (buf[0][0] == buf[0][1]))
					{
						l-=1;
						for (i = 0; i < 4; i += 1)
						{
						    for (j = 0; j < l; j += 1)
						        check[i][j] = check[i][j + 1];
						    check[i][2] = 0;
						}
						check[0][0] = check[2][0];
						check[2][1] = check[2][0] - 1;
						if (TurnCheck())
						{
							
							figure[buf[0][2]][buf[3][0]] = -1;
							figure[buf[0][2]][buf[3][1]] = -1;					
						}
						else
						{
						 l+=1;
							return false;	
							}					
					}
					else if (l == 2)
					{
					l+=1;
						for (i = 0; i < 4; i += 1)
						{
						    for (j = l-1; j > 0; j -= 1)
						        check[i][j] = check[i][j - 1];
						    check[2][i] = check[2][1];
						}
						check[1][0] = check[3][1] - 1;
						check[3][0] = check[3][1] - 1;
						check[0][0] = check[2][0];
						check[0][2] = check[2][0];
						if (TurnCheck())
						{
							
							figure[buf[0][1]][buf[3][1]] = -1;
							figure[buf[0][1] - 1][buf[3][1]] = -1;					
						}
						else
						{
							l-=1;
							return false;
							}						
					}
					else 
					{
						l-=1;
						for (i = 0; i < 4; i += 1)
						{
						    check[i][2] = 0;
						}
						check[0][0] = check[0][1]+1;
						check[2][1] = check[0][1];
						if (TurnCheck())
						{
							
							figure[buf[0][0]][buf[3][1]] = -1;
							figure[buf[0][0]][buf[3][2]] = -1;					
						}
						else
						{
							l+=1;
							return false;
						}
					} 
					break;
				}
				case(6):
				{
				
					break;
				}
				default:
					return true;
			
			}
		for (i=0; i<4; i+=1)
			for (j=0;j<l;j+=1)
				buf[i][j]=check[i][j];
		}
		else
			{
				switch (ti)
			{
				case(3):
				{
				if (l == 1)
				{
				 	l+=3;   
				    check[0][0] -= 1;
				    check[2][0] = check[0][0];
				    check[1][0] = 0;
				    for (i = 1; i < l; i += 1)
				    {
				        check[0][i] = check[0][0];
				        check[2][i] = check[0][0];
				        check[3][i] = check[3][0]+i;
				        check[1][i] = check[3][0]+i;
				    }
				    if (TurnCheck())
				   	{ 
				   	//l += 3;
				    figure[buf[2][0]][buf[3][0]] = -1;
				    figure[buf[2][0] + 1][buf[3][0]] = -1;
				    figure[buf[0][0]][buf[3][0]] = -1;
				   	}
				   	else 
				   	{
				   		l-=3;
				   		return false;
				   	}
				}
				else
				{
				   l-=3;
				    for (i = 1; i < l+3; i += 1)
				        for (j = 0; j < 4; j += 1)
				            check[j][i] = 0;
				    check[0][0] += 1;
				    check[2][0] = check[0][0] - 3;
				    
				    if(TurnCheck())
				    {
				     //l -= 3;
				    for (i = 1; i < l+3; i += 1)
				        figure[buf[0][0]][buf[3][i]] = -1;
				       }
				       else
				       {
				       	l+=3;
				       	return false;
				       	}
				}
					break;
				}
				case(4):
				{
					int t;
					int mx;
					mx = max(0);
					for (i = 0; i < l; i += 1)
						if (buf[2][i] != mx)
						    t = i;
					if ((t == l - 1) && (buf[2][t - 1] == mx))
					{
						    check[2][0] = check[2][2];
						    check[2][2] = check[2][1];
						 	if (TurnCheck())
						 	{
						 		figure[buf[2][2]+1][buf[3][2]] = -1;
						    	figure[buf[2][2]][buf[3][2]] = -1;
						 	}
						 	else 
						 		return false;

					}
					else if ((t == l - 1) && (mx != buf[0][0]))
					{
						
						for (i = 0; i < 2; i += 1)
						{
						    check[0][i] = check[0][2];
						    check[2][i] = check[0][2];
						}
						if (TurnCheck())
						{
							figure[buf[2][0]][buf[3][0]] = -1;
							figure[buf[2][0]][buf[3][1]] = -1;
						}
						else
							return false;
					}
					else if ((mx == buf[0][0]) && (t != 0))
					{
						
						check[0][2] = check[0][0];
						check[0][0] = check[0][1];
						if (TurnCheck())
						 	{
						 		figure[buf[0][0]][buf[3][0]] = -1;
								figure[buf[0][0] - 1][buf[3][0]] = -1;
						 	}
						 	else 
						 		return false;
					}
					else
					{
						for (i = 1; i < 3; i += 1)
						{
						    check[0][i] = check[2][0];
						    check[2][i] = check[2][0];
						}
						if (TurnCheck())
						 	{
						 		figure[buf[0][0]][buf[3][1]] = -1;
								figure[buf[0][0]][buf[3][2]] = -1;
						 	}
						 	else 
						 		return false;
					}
					break;

				}
				
				
				case(5):
				{ 
				int t;

					if ((l == 2) && (buf[0][0] > buf[0][1]))
					{
						l+=1;
						for (i = 0; i < 2; i += 1)
						{
						    check[2][i+1] = check[2][0];
						}
						check[0][0] = check[2][0];
						check[0][2] = check[2][0];

						check[1][2] = check[3][1] + 1;
						check[3][2] = check[3][1] + 1;
						
						if(TurnCheck())
						{
							
							for (i = 0; i < 2; i += 1)
							    figure[buf[0][1] + i][buf[3][0]] = -1; 		
						}
						else
						{
							l-=1;
							return false;
						}
					}
					else if ((l == 3) && (buf[0][0] == buf[0][1]))
					{
						l-=1;
						for (i = 0; i < 4; i += 1)
						{
						    for (j = 0; j < l-1; j += 1)
						        check[i][j] = check[i][j + 1];
						    check[i][2] = 0;
						}
						check[0][1] = check[0][0] - 1;
						check[2][0] = check[0][0] - 2;
						check[3][0] = check[3][1] - 1;
						check[1][0] = check[3][0];
						if(TurnCheck())
						{
							
							figure[buf[0][2]][buf[3][1]] = -1;
							figure[buf[0][0]][buf[3][2]]=-1;						 		
						}
						else
						{
							l+=1;
							return false;	
						}				 
					}
					else if (l == 2)
					{
						l+=1;
						for (i = 0; i < 4; i += 1)
						{
						    for (j = l; j > 0; j -= 1)
						        check[i][j] = check[i][j - 1];
						}

						check[0][0] = check[0][2];
						check[0][1] = check[0][2];
						check[2][0] = check[0][2];
						check[2][2] = check[0][2];
						check[1][0] = check[3][1] - 1;
						check[3][0] = check[3][1] - 1;
						if(TurnCheck())
						{
							figure[buf[2][0]][buf[3][1]] = -1;
							figure[buf[2][0] - 1][buf[3][1]] = -1; 		
						}
						else
						{
							l-=1;
							return false;
						}
					
					}
					else
					{
						l-=1;
						for (i = 0; i < 4; i += 1)
						{
						    for (j = 0; j < l; j += 1)
						        check[i][j] = check[i][j + 1];
						    check[i][2] = 0;
						}
						check[0][1] = check[0][0] + 1;
						check[2][0] = check[0][0];

						if(TurnCheck())
						{
							figure[buf[0][0]][buf[3][1]] = -1;
							figure[buf[0][0]][buf[3][0]] = -1; 		
						}
						else
						{
							l+=1;
							return false;
						}
					}
        		break;
				}
					
				
				case(6):
				{
				
					break;
				}
				default:
					return true;
			}
				for (i=0; i<4; i+=1)
			for (j=0;j<l;j+=1)
				buf[i][j]=check[i][j];
			}
		}


bool ChildWindow::GameOver()
{
	int i;
	for (i=0;i<10;i+=1)
	{
		if (!(proverka(3))&&(figure[i][0]==ti))
			return false;
	}
}

bool ChildWindow::motion(int way)
{
    
    int i, j;
    if (proverka(3))
    {
    switch (way)
    {
    case 1:
    {

    	if (proverka(1))
    	{
			int mx = max(0);
		    if ((buf[0][0] + 1 > 9)||(buf[3][l-1]==15)||(buf[3][l-1]==14))
		        return false;
		    for (i = 0; i < l; i += 1)
		    {
		 
		        figure[buf[2][i]][buf[3][i]] = -1;
		        buf[0][i] += 1;
		        buf[2][i] += 1;
		    }
		    return true;
		 }
		 else
		 	return false;
    }
    case 2:
    {
    	if (proverka(2))
    	{
        if ((buf[2][0] - 1 < 0)||(buf[3][l-1]==15)||(buf[3][l-1]==14))
            return false;
        for (i = 0; i < l; i += 1)
        {
        
            figure[buf[0][i]][buf[3][i]] = -1;
            buf[0][i] -= 1;
            buf[2][i] -= 1;

        }

        return true;
        }
        else
        	return false;
    }
    case 3:
    {
    	if (proverka(3))
    	{
		    for (i = l-1; i >= 0; i -= 1)
		    {
		        if ((buf[3][l-1] + 1 > 15))
		        {
		        	//ti*=10;
		      		return false;
		      	}
		         
		        else
		        {
		            for (j = buf[2][i]; j <= buf[0][i]; j += 1)
		            {
		            	//if (figure[j][buf[3][i])
		                	figure[j][buf[3][i]] = -1;
		                	}
		            buf[3][i] += 1;
		        }
		    }
		    
        }
        else
        	return false;
        	
        	}
        //if (buf[3][l-1]==15)
        	//buf[3][l-1]=14;
        //buf[3][l - 1] -= 1;
        for (i=0;i<4;i+=1)
        {
        	for (j=0;j<4;j+=1)
        		std::cout<<buf[i][j]<<' ';
        	std::cout<<'\n';
        }
        
        if (buf[3][l-1]==14)
        {
        	start=true;
        	if (ti<10)
        	{
        		ti*=10;
        		start=true;
        	}
        	return false;
        	//start=true;
        }
        return true;
    
    }
    }
    else
    {
    	//ti*=10;
    //start=true;
    	return false;
    }
}

void ChildWindow::Del()
{
	int i,j,k,t;
	for (i=0;i<10;i+=1)
		del[i]=0;
	t=0;
	for (j=14;j>0;j-=1)
	{
		k=0;
		for (i=0;i<10;i+=1)
		{
			if (figure[i][j]!=-1)
				k+=1;
		}
		if (k==10)
		{
			del[t]=j;
			t+=1;
			for (i=0;i<10;i+=1)
				figure[i][j]=-1;
		}
	}
	if (t)
	{
		k=t;
		score+=t*100+((t-1)%10*10);
		for (j=k-1;j>=0;j-=1)
		for (t=del[j];t>1;t-=1)
			for (i=0;i<10;i+=1)
					//if (figure[i][j-1]!=-1)
			{
				figure[i][t]=figure[i][t-1];
				if (j==k-1)
					figure[i][t-1]=-1;
			}
	
		
	}
}

bool ChildWindow::OnTimer()
{
	if ((clock()-timer)>50000)
	{
		timer=clock();
		if(proverka(3))
		{
			motion(3);
			if (buf[3][0]==15)
			{
				buf[3][0]=14;
				start=true;
			}
			trans();
		}
		else
		{
			start=true;
		}
		std::cout<<"ChildWindow::OnTimer()"<<std::endl;
	}
	ReDraw();
	return true;
}

// родительское окно
class MainWindow : public Window
{
public:
    MainWindow() {}
    ~MainWindow() {}

    void OnCreate();
    void OnDraw(Context *cr);
    void OnSizeChanged();
    void OnNotify(Window *child, uint32_t type, const Point &position);
    void OnChildDelete(Window *pChild);
    bool OnKeyPress(uint64_t value);
    void do_drawing(Context *cr);
	ChildWindow cw;
	
	
private:
    ChildWindow *m_pChild;
    RGB         m_color;
    bool Fl=false;	
};

void MainWindow::OnDraw(Context *cr)
{
	char str[]="SCORE: ";
	char sc[6];
    std::cout << "MainWindow::OnDraw()" << std::endl;
	Point size = GetSize();
	Point center(size.GetX()/2,size.GetY()/2);

    // зальем прямоугольник окна серым цветом
    cr->SetColor(RGB(0.8,0.8,0.8));
    cr->FillRectangle(Point(0,0), size);

	double scaleX = 0.5*size.GetX();
	double scaleY = 0.5*size.GetY();
	Point from(size.GetX(),size.GetY()/2);
	cr->SetColor(RGB(0,0.5,1));
    cr->SetLineWidth(5);
    cr->Line(Point(0.,450.),Point(900.,450.));
    cr->SetColor(RGB(0,0,0));
    cr->FillRectangle(Point(0.,450.),Point(900.,450.));
    cr->SetColor(RGB(1,1,1));
    cr->SetLineWidth(15);
    cr->Rules(Point(50.,470.));
    cr->SetLineWidth(30);
    cr->SetColor(RGB(0,0,1));
    cr->Score(Point(550,70),str);
    //score=m_pChild->sc;
    
    sprintf(sc,"%d",score);
    cr->Score(Point(700,70),sc);
    
    if (!over)
   	{
   		cr->SetLineWidth(50);
   		cr->SetColor(RGB(1,0,0));
   		cr->End(Point(50.,150));
   	}
   	
   	if ((start)&&(fig))
    	{
    		for (int r=0;r<3;r+=1)
    			for (int g=4;g<=7;g+=1)
    				if (figure[g][r]!=-1)
    				{
    					start=false;
    					Fl=false;
    					over=0;
    				}
    		for (int g=0;g<10;g+=1)
    			if (figure[g][0]!=-1)
    			{
    					start=false;
    					Fl=false;
    					over=0;
    			}
    		cw.Figure();
    		ReDraw();
    		start=false;
    	}
}	
void MainWindow::OnCreate()
{
    std::cout << "MainWindow::OnCreate()" << std::endl;

    // начальный цвет - белый
    m_color = RGB(1,1,1);

    // создаем объект дочернего окна
    m_pChild = new ChildWindow;

    Point mysize = GetSize();
    Point childsize(mysize.GetX()/3,mysize.GetY());
    Point childpos((mysize.GetX()-childsize.GetX())/2, (mysize.GetY()-childsize.GetY())-50);

    // добавляем дочернее окно
    AddChild(m_pChild,childpos,childsize);
}

void MainWindow::OnSizeChanged()
{
    std::cout << "MainWindow::OnSizeChanged()" << std::endl;
    if(m_pChild)
    {
        Point mysize = GetSize();
        Point childsize(mysize.GetX()/2.65-1,450);
        Point childpos((mysize.GetX()-childsize.GetX())/2, (mysize.GetY()-childsize.GetY())/4-30);

        m_pChild->SetPosition(childpos);
        m_pChild->SetSize(childsize);
        
    }
    
}

void MainWindow::OnNotify(Window *child, uint32_t type, const Point &position)
{
    std::cout << "MainWindow::OnNotify()" << std::endl;
    if(m_pChild == child && type == EVENT_CLOSE)
    {
        DeleteMe();
    }
}

void MainWindow::OnChildDelete(Window *pChild)
{
    std::cout << "MainWindow::OnChildDelete()" << std::endl;
    if(m_pChild == pChild)
    {
        m_pChild = NULL;
    }
}

bool MainWindow::OnKeyPress(uint64_t keyval)
{
//vvodim docherniy class
    	
    std::cout << "MainWindow::OnKeyPress(" << keyval << ")" << std::endl;
    if (keyval=='1')
    	{
    		Fl=true;
    		std::cout << "MainWindow::OnKeyPress( GO! )" << std::endl;
    		if (ti==100)
    			score=0;
    		if (start)
    		{
    			cw.Figure();
    			start=false;
    			fig=1;
    		}
		}
    else if (keyval=='2')
    	{Fl=false;
    	tmr=0;
    	}
    else if (keyval=='0')
    	{
    		Fl=false;
    		zikl=0;
    		start=true;
    		ti=100;
    		score=0;
    		fig=0;
    		over=1;
    		tmr=0;
    	}
    else  if (keyval=='b')
    {
        DeleteMe();
        return true;
    }
    else if (keyval=='3')
    	tmr=1;
    else
       	if (Fl)
    	{

		switch(keyval)
		{
		
		case 'a':
		{
				std::cout << "ChildWindow::OnKeyEvent LEFT" << keyval <<std::endl;
				if (cw.motion(2))
					cw.trans();
				break;
		}
		case 's':
		{
			std::cout << "ChildWindow::OnKeyEvent DOWN" << keyval <<std::endl;
			
			if (cw.motion(3))
			{
					cw.trans();
					if (!cw.proverka(3))
					{
						if (ti<10)
						{
							ti*=10;
							start=true;
						}
						cw.trans();
						}
					
			}
			
			else
			{
				cw.trans();
				start=true;
				//ti*=10;
			}
			
			break;
		}
		case 'd':
		{
				std::cout << "ChildWindow::OnKeyEvent RIGHT" << keyval <<std::endl;
				if (cw.motion(1))
					for (int i=0; i<l; i+=1)
					{
						for (int j=0; j<l;j+=1)
							std::cout<<buf[i][j]<<' ';
						std::cout<<'\n';
					}
					cw.trans();
				break;
		}
		case 'q':
		{
			
			std::cout << "ChildWindow::OnKeyEvent TURN LEFT" << keyval <<std::endl;
			cw.Turn(-1);
			cw.trans();
				
				break;
				}
		case 'e':
		{
			
			std::cout << "ChildWindow::OnKeyEvent TURN RIGHT" << keyval<<std::endl;
			cw.Turn(1);
			cw.trans();
				break;
				}
		case 't':
		{
			cw.Figure();
			break;
		}
		default:
        ;
			}
  
    
    }
    ReDraw();
    return true;
}

void MainWindow::do_drawing(Context *cr)
{
	cr->SetColor(RGB(1,0,0));
}

// функция main
int main(int argc, char **argv)
{
    MainWindow *pWindow = new MainWindow;
	ChildWindow *chWindow = new ChildWindow;
	Context *cr;
    int res = Run(argc, argv, pWindow, 900, 600);
	
	
    delete pWindow;

    return res;
}
