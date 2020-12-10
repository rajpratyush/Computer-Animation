#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
//DDA
void dda(int x1,int y1,int x2,int y2)
{
  float L,xnew,ynew,Dx,Dy;
  int dx,dy;
  int i=1;
  dx=abs(x2-x1);
  dy=abs(y2-y1);
  if(dx>=dy)
    L=dx;
  else
    L=dy;
  Dx=dx/L;
  Dy=dy/L;
  xnew=x1+0.5;ynew=y1+0.5;
  putpixel((int)xnew,(int)ynew,15);


  while(i<=L)
  {
    xnew=xnew+Dx;
    ynew=ynew+Dy;
    putpixel((int)xnew,(int)ynew,15);
    i++;
  }
}
//Bresenham
void gba(int x1,int y1,int x2,int y2)
{
 int exc=0,temp,s1,s2,dx,dy,xnew,ynew;
 int i,midx,midy,pk;
 midx=getmaxx()/2;
 midy=getmaxy()/2;
 dx=abs(x2-x1);
 dy=abs(y2-y1);
 xnew=x1;
 ynew=y1;
 s1=(x2-x1)/dx;
 s2=(y2-y1)/dy;
 if(dy>dx)
 {
  temp=dy;
  dy=dx;
  dx=temp;
  exc=1;
}
pk=2*dy-dx;
if(xnew>0)
 putpixel(midx-xnew,midy+ynew,10);
for(i=1;i<=dx;i++)
{
	while(pk>0)
  {
    if(exc==1)
      xnew=xnew+s1;
    else
    {
      ynew=ynew+s2;
    }
    pk=pk-2*dx;
  }
  if(exc==1)
   ynew=ynew+s2;
 else
   xnew=xnew+s1;
 pk=pk+2*dy;
 putpixel(xnew+midx,midy-ynew,10);

}
}

//midpoint circle && 
void midcircle(int r,int midx,int midy)
{
 int i,x,y,xc,yc;
 float pk;
 xc = getmaxx()/2;
 yc = getmaxy()/2;
 pk=1.25-r;
 x=0;
 y=r;
 do
 {
  if(pk<0)
  {
   x=x+1;
   pk=pk+2*x+1;
 }
 else
 {
   x=x+1;
   y=y-1;
   pk=pk+2*x-2*y+10;
 }
 putpixel(midx+xc+x,(yc-midy)+y,4);
 putpixel(midx+xc+y,(yc-midy)+x,4);
 putpixel(midx+xc-y,(yc-midy)-x,4);
 putpixel(midx+xc+y,(yc-midy)-x,4);
 putpixel(midx+xc-y,(yc-midy)+x,4);
 putpixel(midx+xc+y,(yc-midy)+x,4);
 putpixel(midx+xc-x,(yc-midy)-y,4);
 putpixel(midx+xc+x,(yc-midy)-y,4);
 putpixel(midx+xc-x,(yc-midy)+y,4);
}
while(x<y);
}

//Flood Fill And Boundary Fill
void boundaryFill(int x,int y,int newcolor,int bcolor)
{
  if(getpixel(x,y)!=bcolor && getpixel(x,y)!=newcolor)
  {
    putpixel(x,y,newcolor);
    boundaryFill(x+1,y,newcolor,bcolor);
    boundaryFill(x,y+1,newcolor,bcolor);
    boundaryFill(x-1,y,newcolor,bcolor);
    boundaryFill(x,y-1,newcolor,bcolor);
  }
}
void floodFill(int x,int y,int oldcolor,int newcolor)
{
  if(getpixel(x,y) == oldcolor)
  {
    putpixel(x,y,newcolor);
    floodFill(x+1,y,oldcolor,newcolor);
    floodFill(x,y+1,oldcolor,newcolor);
    floodFill(x-1,y,oldcolor,newcolor);
    floodFill(x,y-1,oldcolor,newcolor);
    // floodFill(x+1,y-1,oldcolor,newcolor);
    // floodFill(x-1,y-1,oldcolor,newcolor);
    // floodFill(x+1,y+1,oldcolor,newcolor);
    // floodFill(x-1,y+1,oldcolor,newcolor);
  }
}
//Bezeir Curve
void bezeir(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
  int p0[2],p1[2],p2[2],p3[2],x[4],y[4],i,j,u;
  float ss=0.0,Bx,By;
  p0[0]=x1;
  p0[1]=y1;
  p1[0]=x2;
  p1[1]=y2;
  p2[0]=x3;
  p2[1]=y3;
  p3[0]=x4;
  p3[1]=y4;
  x[0]=p0[0]; x[1]=p1[0]; x[2]=p2[0]; x[3]=p3[0];
  y[0]=p0[1]; y[1]=p1[1]; y[2]=p2[1]; y[3]=p3[1];
  for(ss=0;ss<=1;ss+=0.0005)
  {
    Bx=pow((1-ss),3) * p0[0] + 3*ss*pow((1-ss),2) * p1[0] + 3*ss*ss*(1-ss)*p2[0] + pow(ss,3) * p3[0];
    By=pow((1-ss),3) * p0[1] + 3*ss*pow((1-ss),2) * p1[1] + 3*ss*ss*(1-ss)*p2[1] + pow(ss,3) * p3[1];
    putpixel(Bx,By,6);
  }
  for(i=0;i<4;i++)
  {
    putpixel(x[i],y[i],6);
  }
}


void main()
{

 int gd=DETECT,gm,maxy,i,maxx,discorad,middlex,middley,trig=0,mov=0,mov1=0,transy=0,transx=0,scaleflag=1,scalex1,scaley1,scalex2,scaley2;
 initgraph(&gd,&gm,"C:\\turboc3\\bgi");
 middlex=getmaxx()/2;
 middley=getmaxy()/2;
 maxx=middlex*2;
 maxy=middley*2;
 //for x direc
 //line(middlex,0,middlex,getmaxy());
 //for y direc
 //line(0,middley,getmaxx(),middley);
 //printf("%d \t %d \t %d \t %d \n",getmaxx(),getmaxy(),middlex,middley);
 do
 {
   clearviewport();
 //Road
   rectangle(0,130,maxx,260);
   rectangle(0,260,maxx,400);
   rectangle(0,0,maxx,130);
   setfillstyle(1,9);
   floodfill(10,10,WHITE);
   rectangle(0,400,maxx,maxy);
   line(0,128,maxx,128);
   line(0,129,maxx,129);
   setfillstyle(1,8);
   floodfill(60,270,WHITE);
  //Road ka divider ---------------------
  for(i=1;i<60;i=i+2)
  {
    setcolor(4);
    line(10+(10*i),335,20+(10*i),335);
    setcolor(15);
  }

  //grass field
   setfillstyle(1,10);
   floodfill(70,410,WHITE);
    //grass
   for(i=1;i<20;i++)
   {
    setcolor(2);
    line(30+(30*i),430,10+(30*i),415);
    line(30+(30*i),430,40+(30*i),415);
    line(15+(30*i),460,0+(30*i),445);
    line(15+(30*i),460,25+(30*i),445);
    setcolor(15);
  }

//light box using scale 1 for Green ,2 for Orange ,3 for RED
  // 20 = X2-X1 && 20 = Y2-Y1
  scalex1=20;
  scaley1=20*2;
  scalex2=20;
  scaley2=20*2;
  if(scaleflag==1)
  {
    rectangle(maxx-80,180,maxx-60,200);
    setfillstyle(1,2);
    floodfill(maxx-70,190,WHITE);
    scaleflag=2;
  }
  else if(scaleflag==2)
  {
    rectangle(maxx-80,180-scalex1,maxx-60,200+scalex2);
    setfillstyle(1,6);
    floodfill(maxx-70,190,WHITE);
    scaleflag=3;
  }
  else if(scaleflag==3)
  {
    rectangle(maxx-80,180-scaley1,maxx-60,200+scaley2);
    setfillstyle(1,4);
    floodfill(maxx-70,190,WHITE);
    scaleflag=1;
  }
  
//down hill1
 // bezeir(0,maxy-5,80,410,160,maxy-80,200,maxy-5);
//bottom Divide
  line(0,maxy-5,maxx,maxy-5);
  line(0,maxy-6,maxx,maxy-6);
  line(0,maxy-4,maxx,maxy-4);
  line(0,maxy-3,maxx,maxy-3);
  line(0,maxy-2,maxx,maxy-2);
  line(0,maxy-1,maxx,maxy-1);
//down hill2
 // bezeir(200,maxy-5,280,420,360,maxy-80,460,maxy-5);
//up hill1
  bezeir(0,130,80,10,160,50,200,130);
//setfillstyle(1,2);
//floodfill(140,100,6);
//up hill2
  bezeir(200,130,280,20,360,50,460,130);

//up hill3
  bezeir(460,130,520,10,580,30,630,130);
//stickman1 head,body,leftH,rightH,leftL,rightL
  circle(30,160,20);
  line(30,180,30,220);
  line(30,200,10,190+transy);
  line(30,200,50,190+transy);
  line(30,220,20-transx,260);
  line(30,220,40+transx,260);
//stickman2 head,body,leftH,rightH,leftL,rightL
  circle(80,160,20);
  line(80,180,80,220);
  line(80,200,60,190+transy);
  line(80,200,100,190+transy);
  line(80,220,70-transx,260);
  line(80,220,90+transx,260);
//stickman3 head,body,leftH,rightH,leftL,rightL
  circle(130,160,20);
  line(130,180,130,220);
  line(130,200,110,190+transy);
  line(130,200,150,190+transy);
  line(130,220,120-transx,260);
  line(130,220,140+transx,260);
//sun
  circle(460,50,20);
  boundaryFill(460,50,14,15);
//flag
  line(middlex,250,middlex,150);
  rectangle(middlex,150,middlex+60,190);
  setfillstyle(2,14);
  floodfill(middlex+15,170,WHITE);
  //fract tree
  line(middlex+120,260,middlex+120,220); //1
  delay(50);
  line(middlex+120,220,middlex+100,200); //21
  line(middlex+120,220,middlex+140,200); //22
  delay(50);
  line(middlex+100,200,middlex+110,180); //211
  line(middlex+100,200,middlex+90,180); //212
  line(middlex+140,200,middlex+130,180); //221
  line(middlex+140,200,middlex+150,180); //222
  delay(50);
  // line(middlex+110,180,middlex+105,160); //2111
  // line(middlex+110,180,middlex+115,160); //2112
  // line(middlex+90,180,middlex+85,160); //2121
  // line(middlex+90,180,middlex+95,160); //2122
  // line(middlex+130,180,middlex+125,160); //2211
  // line(middlex+130,180,middlex+135,160); //2212
  // line(middlex+150,180,middlex+145,160); //2221
  // line(middlex+150,180,middlex+155,160); //2222

//flag Shadow using Shear
  line(middlex,250,middlex-80,170);
  line(middlex-80,170,middlex-40,150);
  line(middlex-40,150,middlex-20,170);
  line(middlex-20,170,middlex-60,190);
  //setfillstyle(1,15);
  //boundaryFill(middlex-40,180,WHITE);



//car1
  // rectangle(20+mov1,295,30+mov1,310);
  // rectangle(30+mov1,270,110+mov1,310);
  // rectangle(110+mov1,290,150+mov1,310);
  // line(110+mov1,290,80+mov1,290);
  // line(80+mov1,290,80+mov1,270);
  //
  rectangle(30+mov1,280,150+mov1,310);
  setfillstyle(1,BLUE);
  floodfill(33+mov1,290,WHITE);
  //rectangle(150+mov1,290,155+mov1,300);

  
  setcolor(8);
  line(60+mov1,280,110+mov1,280);
  line(150+mov1,290,150+mov1,300);
  line(42+mov1,310,58+mov1,310);
  line(102+mov1,310,118+mov1,310);
  setcolor(WHITE);
  //headlight
  circle(150+mov1,295,5);
  setfillstyle(1,YELLOW);
  floodfill(152+mov1,295,WHITE);
  bezeir(60+mov1,280,80+mov1,255,100+mov1,270,110+mov1,280);
  circle(50+mov1,310,9);
  //circle(110+mov1,320,9);
  //circle(50+mov1,320,9);
  circle(110+mov1,310,9);

  setfillstyle(1,BLACK);
  floodfill(50+mov1,308,WHITE);
  setfillstyle(1,BLACK);
  floodfill(110+mov1,308,WHITE);

  //  //car1 colors
  // setfillstyle(1,RED);
  // floodfill(22+mov1,296,WHITE);
  // setfillstyle(1,CYAN);
  // floodfill(32+mov1,271,WHITE);
  // setfillstyle(1,CYAN);
  // floodfill(112+mov1,291,WHITE);
  // setfillstyle(1,BLUE);
  // floodfill(82+mov1,280,WHITE);
  // setfillstyle(1,0);
  // floodfill(30+mov1,320,WHITE);
  // setfillstyle(1,0);
  // floodfill(110+mov1,320,WHITE);
  // setfillstyle(1,0);
  // floodfill(50+mov1,320,WHITE);
  // setfillstyle(1,0);
  // floodfill(130+mov1,320,WHITE);



//car2
  //rectangle(20+mov,365,30+mov,380);
  //rectangle(30+mov,340,110+mov,380);
  setcolor(6);
  rectangle(30+mov,360,150+mov,380);
  line(30+mov,360,30+mov,345);
  //line(110+mov,360,110+mov,345);
  bezeir(30+mov,345,50+mov,335,90+mov,335,110+mov,345);
  //bezeir(30+mov,380,45+mov,360,45+mov,370,30+mov,345);
  bezeir(130+mov,360,120+mov,355,120+mov,340,110+mov,345);
  //arrange
  setcolor(8);
  line(31+mov,360,130+mov,360);
  //line(30+mov,380,30+mov,345);
  line(53+mov,380,67+mov,380);
  line(150+mov,368,150+mov,372);
  line(104+mov,380,117+mov,380);
  setcolor(6);
  //line(110+mov,360,80+mov,360);
  //line(80+mov,360,80+mov,340);
  circle(60+mov,380,9);
  //circle(110+mov,390,9);
  //circle(50+mov,390,9);
  circle(110+mov,380,7);
  //headlight
  circle(150+mov,370,4);
  //setfillstyle(1,YELLOW);
  //floodfill(151+mov,271,6);

  setfillstyle(1,BLACK);
  floodfill(60+mov,379,6);
  setfillstyle(1,BLACK);
  floodfill(110+mov,379,6);
  //  //car 2colors
  // setfillstyle(1,BLUE);
  // floodfill(22+mov,366,WHITE);
  // setfillstyle(1,YELLOW);
  // floodfill(32+mov,341,WHITE);
  // setfillstyle(1,YELLOW);
  // floodfill(112+mov,361,WHITE);
  // setfillstyle(1,GREEN);
  // floodfill(82+mov,350,WHITE);
  // setfillstyle(1,0);
  // floodfill(30+mov,390,WHITE);
  // setfillstyle(1,0);
  // floodfill(110+mov,390,WHITE);
  // setfillstyle(1,0);
  // floodfill(50+mov,390,WHITE);
  // setfillstyle(1,0);
  // floodfill(130+mov,390,WHITE);
  setcolor(WHITE);
//red indicator
  rectangle(maxx-100,260,maxx-40,265);
  setfillstyle(1,4);
  floodfill(maxx-80,263,WHITE);
  rectangle(maxx-100,395,maxx-40,400);
  setfillstyle(1,4);
  floodfill(maxx-80,397,WHITE);
//zebra cross
  dda(maxx-100,260,maxx-100,400);
  dda(maxx-40,260,maxx-40,400);
  setfillstyle(3,15);
  floodfill(maxx-60,300,WHITE);
//arc bird1
  arc(100,20,0,85,10);
  arc(110,30,10,90,10);
//arc bird2
  arc(140,20,0,85,10);
  arc(150,30,10,90,10);
//arc bird3
  arc(130,40,0,85,10);
  arc(140,50,10,90,10);
  if(trig%2==00)
  {
    transy=15;
    transx=10;
  }
  else
  {
    transx=0;
    transy=0;
  }
  trig++;
  mov=mov+15;
  mov1=mov1+8;
  delay(900);

}while(mov!=540);

getch();
closegraph();
}

